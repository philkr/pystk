#include <pybind11/numpy.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>
#include <memory>
#include <string>
#include <sstream>
#include <vector>
#include "pickle.hpp"
#include "pystk.hpp"
#include "state.hpp"
#include "view.hpp"
#include "utils/objecttype.h"
#include "utils/log.hpp"

#ifdef WIN32
#include <Windows.h>
#endif

namespace py = pybind11;
using namespace pybind11::literals;

PYBIND11_MAKE_OPAQUE(std::vector<PySTKPlayerConfig>);

void path_and_init(const PySTKGraphicsConfig & config) {
	auto sys = py::module::import("sys"), os = py::module::import("os");
	auto path = os.attr("path"), env = os.attr("environ");
	auto module_path = path.attr("join")(path.attr("dirname")(path.attr("abspath")(sys.attr("modules")["pystk"].attr("__file__"))), "pystk_data");
	// Give supertuxkart a hint where the assets are
	env["SUPERTUXKART_DATADIR"] = module_path;
	PySTKRace::init(config);
}
PYBIND11_MODULE(pystk, m) {
	m.doc() = "Python SuperTuxKart interface";

	// Make offscreen rendering default
	if (!getenv("IRR_DEVICE_TYPE"))
#ifdef WIN32
		_putenv_s("IRR_DEVICE_TYPE", "offscreen");
#else
		setenv("IRR_DEVICE_TYPE", "offscreen", 0);
#endif
	// Adjust the log level
	Log::setLogLevel(Log::LL_FATAL);
	if (getenv("PYSTK_LOG_LEVEL")) {
		std::string ll = getenv("PYSTK_LOG_LEVEL");
		if (ll == "debug") Log::setLogLevel(Log::LL_DEBUG);
		if (ll == "verbose") Log::setLogLevel(Log::LL_VERBOSE);
		if (ll == "info") Log::setLogLevel(Log::LL_INFO);
		if (ll == "warn") Log::setLogLevel(Log::LL_WARN);
		if (ll == "error") Log::setLogLevel(Log::LL_ERROR);
		if (ll == "fatal") Log::setLogLevel(Log::LL_FATAL);
	}
	
	// Define the game state
	defineState(m);
	
	{
		py::enum_<Log::LogLevel>(m, "LogLevel", "Global logging level")
		.value("debug", Log::LL_DEBUG)
		.value("verbose", Log::LL_VERBOSE)
		.value("info", Log::LL_INFO)
		.value("warn", Log::LL_WARN)
		.value("error", Log::LL_ERROR)
		.value("fatal", Log::LL_FATAL);
		
		m.def("set_log_level", Log::setLogLevel, "Set the global log level");
	}
	
	{
		py::enum_<ObjectType>(m, "ObjectType")
		.value("kart", ObjectType::OT_KART)
		.value("track", ObjectType::OT_TRACK)
		.value("background", ObjectType::OT_BACKGROUND)
		.value("pickup", ObjectType::OT_PICKUP)
		.value("nitro", ObjectType::OT_NITRO)
		.value("bomb", ObjectType::OT_BOMB)
		.value("object", ObjectType::OT_OBJECT)
		.value("projectile", ObjectType::OT_PROJECTILE)
		.value("unknown", ObjectType::OT_UNKNOWN)
		.value("N", ObjectType::NUM_OT);
		m.def("unknown_debug_name", unknownDebugName);
		m.attr("object_type_shift") = OBJECT_TYPE_SHIFT;
	}
	{
		py::class_<PySTKGraphicsConfig, std::shared_ptr<PySTKGraphicsConfig>> cls(m, "GraphicsConfig", "SuperTuxKart graphics configuration.");
	
		cls.def_readwrite("screen_width", &PySTKGraphicsConfig::screen_width, "Width of the rendering surface (int)")
		.def_readwrite("screen_height", &PySTKGraphicsConfig::screen_height, "Height of the rendering surface (int)")
		.def_readwrite("glow", &PySTKGraphicsConfig::glow, "Enable glow around pickup objects (bool)")
		.def_readwrite("bloom", &PySTKGraphicsConfig::bloom, "Enable the bloom effect (bool)")
		.def_readwrite("light_shaft", &PySTKGraphicsConfig::light_shaft, "Enable light shafts (bool)")
		.def_readwrite("dynamic_lights", &PySTKGraphicsConfig::dynamic_lights, "Enable dynamic lighting (bool)")
		.def_readwrite("dof", &PySTKGraphicsConfig::dof, "Depth of field effect (bool)")
		.def_readwrite("particles_effects", &PySTKGraphicsConfig::particles_effects, "Particle effect 0 (none) to 2 (full)" )
		.def_readwrite("animated_characters", &PySTKGraphicsConfig::animated_characters, "Animate characters (bool)" )
		.def_readwrite("motionblur", &PySTKGraphicsConfig::motionblur, "Enable motion blur (bool)" )
		.def_readwrite("mlaa", &PySTKGraphicsConfig::mlaa, "Enable anti-aliasing (bool)" )
		.def_readwrite("texture_compression", &PySTKGraphicsConfig::texture_compression, "Use texture compression (bool)" )
		.def_readwrite("ssao", &PySTKGraphicsConfig::ssao, "Enable screen space ambient occlusion (bool)" )
		.def_readwrite("degraded_IBL", &PySTKGraphicsConfig::degraded_IBL, "Disable specular IBL (bool)" )
		.def_readwrite("high_definition_textures", &PySTKGraphicsConfig::high_definition_textures, "Enable high definition textures 0 / 2" )
		.def_readwrite("render_window", &PySTKGraphicsConfig::render_window, "Show the rendering window (bool)" );
		add_pickle(cls);
		
		cls.def_static("hd", &PySTKGraphicsConfig::hd, "High-definitaiton graphics settings");
		cls.def_static("sd", &PySTKGraphicsConfig::sd, "Standard-definition graphics settings");
		cls.def_static("ld", &PySTKGraphicsConfig::ld, "Low-definition graphics settings");
	}
	
	{
		py::class_<PySTKPlayerConfig, std::shared_ptr<PySTKPlayerConfig>> cls(m, "PlayerConfig", "SuperTuxKart player configuration");
	
		py::enum_<PySTKPlayerConfig::Controller>(cls, "Controller", "Let the player or AI drive, AI ignores step(action)")
			.value("PLAYER_CONTROL", PySTKPlayerConfig::PLAYER_CONTROL)
			.value("AI_CONTROL", PySTKPlayerConfig::AI_CONTROL);
		
		cls
		.def(py::init<const std::string&, PySTKPlayerConfig::Controller, int>(), py::arg("kart")="", py::arg("controller")=PySTKPlayerConfig::PLAYER_CONTROL, py::arg("team")=0)
		.def_readwrite("kart", &PySTKPlayerConfig::kart, "Kart type (string), see list_karts for a list of kart types" )
		.def_readwrite("controller", &PySTKPlayerConfig::controller, "Controller type (PlayerConfig.Controller)" )
		.def_readwrite("team", &PySTKPlayerConfig::team, "Team of the player (int) 0 or 1" );
		add_pickle(cls);

		py::bind_vector<std::vector<PySTKPlayerConfig>>(m, "VectorPlayerConfig");
	}
	
	{
		py::class_<PySTKRaceConfig, std::shared_ptr<PySTKRaceConfig>> cls(m, "RaceConfig", "SuperTuxKart race configuration.");
	
		py::enum_<PySTKRaceConfig::RaceMode>(cls, "RaceMode")
			.value("NORMAL_RACE", PySTKRaceConfig::RaceMode::NORMAL_RACE)
			.value("TIME_TRIAL", PySTKRaceConfig::RaceMode::TIME_TRIAL)
			.value("FOLLOW_LEADER", PySTKRaceConfig::RaceMode::FOLLOW_LEADER)
			.value("THREE_STRIKES", PySTKRaceConfig::RaceMode::THREE_STRIKES)
			.value("FREE_FOR_ALL", PySTKRaceConfig::RaceMode::FREE_FOR_ALL)
			.value("CAPTURE_THE_FLAG", PySTKRaceConfig::RaceMode::CAPTURE_THE_FLAG)
			.value("SOCCER", PySTKRaceConfig::RaceMode::SOCCER);
		
		cls
		.def(py::init<int,PySTKRaceConfig::RaceMode,std::vector<PySTKPlayerConfig>,std::string,bool,int,int,int,float,bool>(), py::arg("difficulty") = 2, py::arg("mode") = PySTKRaceConfig::NORMAL_RACE, py::arg("players") = std::vector<PySTKPlayerConfig>{{"",PySTKPlayerConfig::PLAYER_CONTROL}}, py::arg("track") = "", py::arg("reverse") = false, py::arg("laps") = 3, py::arg("seed") = 0, py::arg("num_kart") = 1, py::arg("step_size") = 0.1, py::arg("render") = true)
		.def_readwrite("difficulty", &PySTKRaceConfig::difficulty, "Skill of AI players 0..2 (int)")
		.def_readwrite("mode", &PySTKRaceConfig::mode, "Specify the type of race (RaceMode)")
		.def_readwrite("players", &PySTKRaceConfig::players, "List of all agent players (List[PlayerConfig])")
		.def_readwrite("track", &PySTKRaceConfig::track, "Track name (str)")
		.def_readwrite("reverse", &PySTKRaceConfig::reverse, "Reverse the track (bool)")
		.def_readwrite("laps", &PySTKRaceConfig::laps, "Number of laps the race runs for (int)")
		.def_readwrite("seed", &PySTKRaceConfig::seed, "Random seed (int)")
		.def_readwrite("num_kart", &PySTKRaceConfig::num_kart, "Total number of karts, fill the race with num_kart - len(players) AI karts (int)")
		.def_readwrite("step_size", &PySTKRaceConfig::step_size, "Game time between different step calls (float)")
		.def_readwrite("render", &PySTKRaceConfig::render, "Is rendering enabled? (bool)");
		add_pickle(cls);
	}

	{
		py::class_<PySTKRenderData, std::shared_ptr<PySTKRenderData> > cls(m, "RenderData", "SuperTuxKart rendering output");
		cls
		.def_property_readonly("image", [](const PySTKRenderData & rd) { return py::ro_view(rd.color_buf_.data(), {rd.height, rd.width, 3}); }, "Color image of the kart (memoryview[uint8] screen_height x screen_width x 3)")
		.def_property_readonly("depth", [](const PySTKRenderData & rd) { return py::ro_view(rd.depth_buf_.data(), {rd.height, rd.width}); }, "Depth image of the kart (memoryview[float] screen_height x screen_width)")
		.def_property_readonly("instance", [](const PySTKRenderData & rd) { return py::ro_view(rd.instance_buf_.data(), {rd.height, rd.width}); }, "Instance labels (memoryview[uint32] screen_height x screen_width)");
		add_pickle(cls);
	}

	{
		py::class_<PySTKAction, std::shared_ptr<PySTKAction> > cls(m, "Action", "SuperTuxKart action");
		cls
		.def(py::init<float,float,bool,bool,bool,bool,bool>(), py::arg("steer") = 0, py::arg("acceleration") = 0, py::arg("brake") = false, py::arg("nitro") = false, py::arg("drift") = false, py::arg("rescue") = false, py::arg("fire") = false)
		
		.def_readwrite("steer", &PySTKAction::steering_angle, "Steering angle, normalize to -1..1 (float)")
		.def_readwrite("acceleration", &PySTKAction::acceleration, "Acceleration, normalize to 0..1 (float)")
		.def_readwrite("brake", &PySTKAction::brake, "Hit the brakes (bool)")
		.def_readwrite("nitro", &PySTKAction::nitro, "Use nitro (bool)")
		.def_readwrite("drift", &PySTKAction::drift, "Drift while turning (bool)")
		.def_readwrite("rescue", &PySTKAction::rescue, "Call the rescue bird (bool)")
		.def_readwrite("fire", &PySTKAction::fire, "Fire the current pickup item (bool)")
		.def("__str__", [](const PySTKAction & a) -> std::string { return ((std::stringstream&)(std::stringstream() << "<Action S:" << a.steering_angle << "  A:" << a.acceleration << "  b:" << (int) a.brake << "  n:" << (int) a.nitro << "  d:" << (int) a.drift << "  r:" << (int) a.rescue << "  f:" << (int) a.fire << " >")).str();});
		add_pickle(cls);
	}
	
	m.def("is_running", &PySTKRace::isRunning,"Is a race running?");
	{
		py::class_<PySTKRace, std::shared_ptr<PySTKRace> >(m, "Race", "The SuperTuxKart race instance")
		.def(py::init<const PySTKRaceConfig &>(),py::arg("config"))
		.def("restart", &PySTKRace::restart,"Restart the current track. Use this function if the race config does not change, instead of creating a new SuperTuxKart object")
		.def("start", &PySTKRace::start,"start the race")
		.def("step", (bool (PySTKRace::*)(const std::vector<PySTKAction> &)) &PySTKRace::step, py::arg("action"), "Take a step with an action per agent")
		.def("step", (bool (PySTKRace::*)(const PySTKAction &)) &PySTKRace::step, py::arg("action"), "Take a step with an action for agent 0")
		.def("step", (bool (PySTKRace::*)()) &PySTKRace::step, "Take a step without changing the action")
		.def("stop", &PySTKRace::stop,"Stop the race")
		.def_property_readonly("render_data", &PySTKRace::render_data, "rendering data from the last step (List[RenderData])")
		.def_property_readonly("last_action", &PySTKRace::last_action, "the last action the agent took (List[Action])")
		.def_property_readonly("config", &PySTKRace::config,"The current race configuration (RaceConfig)");
	}
	
	m.def("list_tracks", &PySTKRace::listTracks, "Return a list of track names (possible values for RaceConfig.track)");
	m.def("list_karts", &PySTKRace::listKarts, "Return a list of karts to play as (possible values for PlayerConfig.kart");
	
	// Initialize SuperTuxKart
	m.def("init", &path_and_init, py::arg("config"), "Initialize Python SuperTuxKart. Only call this function once per process. Calling it twice will cause a crash.");
	m.def("clean", &PySTKRace::clean, "Free Python SuperTuxKart, call this once at exit (optional). Will be called atexit otherwise.");
	
	auto atexit = py::module::import("atexit");
		atexit.attr("register")(py::cpp_function([]() {
			// A bit ugly
			PySTKRace::running_kart = nullptr;
			PySTKRace::clean();
		}));
}

