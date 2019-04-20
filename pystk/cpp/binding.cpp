#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>
#include <memory>
#include <string>
#include <sstream>
#include <vector>
#include "pystk.hpp"
#include "state.hpp"
#include "utils/objecttype.h"
#include "utils/log.hpp"

namespace py = pybind11;
using namespace pybind11::literals;

namespace pybind11 {
class ro_view : public py::object {
public:
	template<typename T>
    explicit ro_view(const T * v, const std::vector<Py_ssize_t> & shape) {
		// Compute the stride
		static std::vector<Py_ssize_t> stride;
		stride.resize( shape.size() );
		Py_ssize_t itemsize = sizeof(T), s = 1;
		for(int i=stride.size()-1; i>=0; i--) {
			stride[i] = s * itemsize;
			s *= shape[i];
		}
		static std::string fmt;
		fmt = py::format_descriptor<T>::format();
		
		static Py_buffer buf { };
		buf.buf = const_cast<T *>(v);
		buf.itemsize = itemsize;
		buf.format = const_cast<char *>(fmt.c_str());
		buf.ndim = (int) shape.size();
		buf.len = s;
		buf.strides = stride.data();
		buf.shape = const_cast<Py_ssize_t *>(shape.data());
		buf.suboffsets = nullptr;
		buf.readonly = true;
		buf.internal = nullptr;

		m_ptr = PyMemoryView_FromBuffer(&buf);
		if (!m_ptr)
			py::pybind11_fail("Unable to create memoryview from buffer descriptor");
    }

    PYBIND11_OBJECT_CVT(ro_view, object, PyMemoryView_Check, PyMemoryView_FromObject)
};
}

template<typename T>
py::memoryview view(const T * v, const std::vector<ssize_t> & shape) {
	std::vector<ssize_t> stride = shape;
	ssize_t s = sizeof(T);
	for(int i=stride.size()-1; i>=0; i--) {
		stride[i] = s;
		s *= shape[i];
	}
	py::buffer_info bi(const_cast<T * >(v), shape, stride);
	return py::memoryview(bi);
}

PYBIND11_MAKE_OPAQUE(std::vector<PySTKPlayerConfig>);

PYBIND11_MODULE(pystk_cpp, m) {
	m.doc() = "Python SuperTuxKart interface";
	
	// Make offscreen rendering default
#ifndef WIN32
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
		if (ll == "eror") Log::setLogLevel(Log::LL_ERROR);
		if (ll == "fatal") Log::setLogLevel(Log::LL_FATAL);
	}
	
	// Define the game state
	defineState(m);
	
	{
		py::enum_<Log::LogLevel>(m, "LogLevel")
		.value("debug", Log::LL_DEBUG)
		.value("verbose", Log::LL_VERBOSE)
		.value("info", Log::LL_INFO)
		.value("warn", Log::LL_WARN)
		.value("eror", Log::LL_ERROR)
		.value("fatal", Log::LL_FATAL);
		
		m.def("set_log_level", Log::setLogLevel);
	}
	
	{
		py::enum_<ObjectType>(m, "ObjectType")
		.value("kart", ObjectType::OT_KART)
		.value("track", ObjectType::OT_TRACK)
		.value("background", ObjectType::OT_BACKGROUND)
		.value("pickup", ObjectType::OT_PICKUP)
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
	
		cls.def_readwrite("screen_width", &PySTKGraphicsConfig::screen_width);
		cls.def_readwrite("screen_height", &PySTKGraphicsConfig::screen_height);
		cls.def_readwrite("glow", &PySTKGraphicsConfig::glow );
		cls.def_readwrite("dof", &PySTKGraphicsConfig::dof );
		cls.def_readwrite("particles_effects", &PySTKGraphicsConfig::particles_effects );
		cls.def_readwrite("animated_characters", &PySTKGraphicsConfig::animated_characters );
		cls.def_readwrite("motionblur", &PySTKGraphicsConfig::motionblur );
		cls.def_readwrite("mlaa", &PySTKGraphicsConfig::mlaa );
		cls.def_readwrite("texture_compression", &PySTKGraphicsConfig::texture_compression );
		cls.def_readwrite("ssao", &PySTKGraphicsConfig::ssao );
		cls.def_readwrite("degraded_IBL", &PySTKGraphicsConfig::degraded_IBL );
		cls.def_readwrite("high_definition_textures", &PySTKGraphicsConfig::high_definition_textures );
		cls.def_readwrite("render_window", &PySTKGraphicsConfig::render_window );
		
		cls.def_static("hd", &PySTKGraphicsConfig::hd,"High-definitaiton graphics settings");
		cls.def_static("sd", &PySTKGraphicsConfig::sd,"Standard-definition graphics settings");
		cls.def_static("ld", &PySTKGraphicsConfig::ld,"Low-definition graphics settings");
	}
	
	{
		py::class_<PySTKPlayerConfig, std::shared_ptr<PySTKPlayerConfig>> cls(m, "PlayerConfig", "SuperTuxKart player configuration.");
	
		py::enum_<PySTKPlayerConfig::Controller>(cls, "Controller")
			.value("PLAYER_CONTROL", PySTKPlayerConfig::PLAYER_CONTROL)
			.value("AI_CONTROL", PySTKPlayerConfig::AI_CONTROL);
		
		cls
		.def(py::init<const std::string&, PySTKPlayerConfig::Controller>(), py::arg("kart")="", py::arg("controller")=PySTKPlayerConfig::PLAYER_CONTROL)
		.def_readwrite("kart", &PySTKPlayerConfig::kart )
		.def_readwrite("controller", &PySTKPlayerConfig::controller );

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
		.def(py::init<int,PySTKRaceConfig::RaceMode,std::vector<PySTKPlayerConfig>,std::string,int,int,int,float>(), py::arg("difficulty") = 2, py::arg("mode") = PySTKRaceConfig::NORMAL_RACE, py::arg("players") = std::vector<PySTKPlayerConfig>{{"",PySTKPlayerConfig::PLAYER_CONTROL}}, py::arg("track") = "", py::arg("laps") = 3, py::arg("seed") = 0, py::arg("num_kart") = 1, py::arg("step_size") = 0.1)
		.def_readwrite("difficulty", &PySTKRaceConfig::difficulty)
		.def_readwrite("mode", &PySTKRaceConfig::mode)
		.def_readwrite("players", &PySTKRaceConfig::players)
		.def_readwrite("track", &PySTKRaceConfig::track)
		.def_readwrite("laps", &PySTKRaceConfig::laps)
		.def_readwrite("seed", &PySTKRaceConfig::seed)
		.def_readwrite("num_kart", &PySTKRaceConfig::num_kart)
		.def_readwrite("step_size", &PySTKRaceConfig::step_size);
	}

	{
		py::class_<PySTKRenderData, std::shared_ptr<PySTKRenderData> >(m, "RenderData", "SuperTuxKart rendering output")
		.def_property_readonly("image", [](const PySTKRenderData & rd) { return py::ro_view(rd.color_buf_.data(), {rd.height, rd.width, 3}); }, "Color image of the kart")
		.def_property_readonly("depth", [](const PySTKRenderData & rd) { return py::ro_view(rd.depth_buf_.data(), {rd.height, rd.width}); }, "Depth image of the kart")
		.def_property_readonly("instance", [](const PySTKRenderData & rd) { return py::ro_view(rd.instance_buf_.data(), {rd.height, rd.width}); }, "Instance labels");
	}

	{
		py::class_<PySTKAction, std::shared_ptr<PySTKAction> >(m, "Action", "SuperTuxKart action")
		.def(py::init<float,float,bool,bool,bool,bool>(), py::arg("steer") = 0, py::arg("acceleration") = 0, py::arg("nitro") = false, py::arg("drift") = false, py::arg("rescue") = false, py::arg("fire") = false)
		
		.def_readwrite("steer", &PySTKAction::steering_angle, "Steering angle, normalize to -1..1")
		.def_readwrite("acceleration", &PySTKAction::acceleration, "Acceleration, normalize to 0..1.")
		.def_readwrite("brake", &PySTKAction::brake, "Hit the brakes.")
		.def_readwrite("nitro", &PySTKAction::nitro, "Use nitro.")
		.def_readwrite("drift", &PySTKAction::drift, "Drift while turning.")
		.def_readwrite("rescue", &PySTKAction::rescue, "Call the bird.")
		.def_readwrite("fire", &PySTKAction::fire, "Fire the current pickup item")
		.def("__str__", [](const PySTKAction & a) -> std::string { return ((std::stringstream&)(std::stringstream() << "<Action S:" << a.steering_angle << "  A:" << a.acceleration << "  b:" << (int) a.brake << "  n:" << (int) a.nitro << "  d:" << (int) a.drift << "  r:" << (int) a.rescue << "  f:" << (int) a.fire << " >")).str();});
	}
	
	m.def("is_running", &PySuperTuxKart::isRunning,"Is supertuxkart running?");
	{
		py::class_<PySuperTuxKart, std::shared_ptr<PySuperTuxKart> >(m, "SuperTuxKart", "SuperTuxKart instance")
		.def(py::init<const PySTKRaceConfig &>(),py::arg("config"))
		.def("start", &PySuperTuxKart::start,"")
		.def("step", (bool (PySuperTuxKart::*)(const PySTKAction &)) &PySuperTuxKart::step,"Take a step with an action")
		.def("step", (bool (PySuperTuxKart::*)()) &PySuperTuxKart::step,"Take a step without chaning the action")
		.def("stop", &PySuperTuxKart::stop,"")
		.def_property_readonly("render_data", &PySuperTuxKart::render_data, "rendering data from the last step");
	}
	
	m.def("list_tracks", &PySuperTuxKart::listTracks);
	m.def("list_karts", &PySuperTuxKart::listKarts);
	
	// Initialize SuperTuxKart
	m.def("init", &PySuperTuxKart::init);
	m.def("clean", &PySuperTuxKart::clean);
	
	auto atexit = py::module::import("atexit");
		atexit.attr("register")(py::cpp_function([]() {
			// A bit ugly
			PySuperTuxKart::running_kart = nullptr;
			PySuperTuxKart::clean();
		}));
}

