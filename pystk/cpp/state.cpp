#include "state.hpp"

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/numpy.h>

#include "config/stk_config.hpp"
#include "graphics/camera.hpp"
#include "karts/abstract_kart.hpp"
#include "karts/controller/controller.hpp"
#include "karts/controller/local_player_controller.hpp"
#include "karts/kart_properties.hpp"
#include "items/attachment.hpp"
#include "items/item.hpp"
#include "items/item_manager.hpp"
#include "items/powerup.hpp"
#include "items/powerup_manager.hpp"
#include "items/powerup_manager.hpp"
#include "modes/world.hpp"
#include "modes/linear_world.hpp"
#include "tracks/drive_graph.hpp"
#include "tracks/drive_node.hpp"
#include "tracks/track.hpp"
#include "utils/vec3.hpp"
#include "view.hpp"
#include "pickle.hpp"

namespace py = pybind11;

// AUTO Generated
struct PyAttachment;
void pickle(std::ostream & s, const PyAttachment & o);
void unpickle(std::istream & s, PyAttachment * o);
struct PyPowerup;
void pickle(std::ostream & s, const PyPowerup & o);
void unpickle(std::istream & s, PyPowerup * o);
struct PyKartState;
void pickle(std::ostream & s, const PyKartState & o);
void unpickle(std::istream & s, PyKartState * o);
struct PyItem;
void pickle(std::ostream & s, const PyItem & o);
void unpickle(std::istream & s, PyItem * o);
struct PyCamera;
void pickle(std::ostream & s, const PyCamera & o);
void unpickle(std::istream & s, PyCamera * o);
struct PyPlayer;
void pickle(std::ostream & s, const PyPlayer & o);
void unpickle(std::istream & s, PyPlayer * o);
struct PyTrack;
void pickle(std::ostream & s, const PyTrack & o);
void unpickle(std::istream & s, PyTrack * o);
struct PyWorldState;
void pickle(std::ostream & s, const PyWorldState & o);
void unpickle(std::istream & s, PyWorldState * o);
// End AUTO Generated

typedef std::tuple<float, float, float> PyVec3;
PyVec3 P(const Vec3 & v) {
	return PyVec3(v.getX(), v.getY(), v.getZ());
}
void pickle(std::ostream & s, const PyVec3 & o) {
	s.write((const char*)&std::get<0>(o), sizeof(std::get<0>(o)));
	s.write((const char*)&std::get<1>(o), sizeof(std::get<1>(o)));
	s.write((const char*)&std::get<2>(o), sizeof(std::get<2>(o)));
}
void unpickle(std::istream & s, PyVec3 * o) {
	s.read((char*)&std::get<0>(*o), sizeof(std::get<0>(*o)));
	s.read((char*)&std::get<1>(*o), sizeof(std::get<1>(*o)));
	s.read((char*)&std::get<2>(*o), sizeof(std::get<2>(*o)));
}
void pickle(std::ostream & s, const core::matrix4 & o) {
	s.write((const char*)o.pointer(), 16*sizeof(irr::f32));
}
void unpickle(std::istream & s, core::matrix4 * o) {
	s.read((char*)o->pointer(), 16*sizeof(irr::f32));
}
template<typename T>
void pickle(std::ostream & s, const py::array_t<T> & o) {
	uint32_t n = o.ndim();
	s.write((const char*)&n, sizeof(n));
	for(uint32_t i=0; i<n; i++) {
		uint32_t d = o.shape(i);
		s.write((const char*)&d, sizeof(d));
	}
	s.write((const char*)o.data(), o.nbytes());
}
template<typename T>
void unpickle(std::istream & s, py::array_t<T> * o) {
	uint32_t n;
	s.read((char *)&n, sizeof(n));
	std::vector<uint32_t> shape(n);
	s.read((char *)&shape[0], sizeof(uint32_t)*n);
	*o = py::array_t<T>(shape);
	s.read((char*)o->mutable_data(), o->nbytes());
}
template<typename T>
void pickle(std::ostream & s, const std::shared_ptr<T> & o) {
	pickle(s, *o);
}
template<typename T>
void unpickle(std::istream & s, std::shared_ptr<T> * o) {
	*o = std::make_shared<T>();
	unpickle(s, o->get());
}
namespace std {
	std::string to_string(const PyVec3 & v) {
		char buf[256] = {0};
		float x, y, z;
		std::tie(x, y, z) = v;
		sprintf(buf, "(%0.2f, %0.2f, %0.2f)", x, y, z);
		return buf;
	}
}

#define V(X) .value(#X, Type::X)

struct PyAttachment {
	enum Type: uint8_t {
		NOTHING = Attachment::ATTACH_NOTHING,
		PARACHUTE = Attachment::ATTACH_PARACHUTE,
		ANVIL = Attachment::ATTACH_ANVIL,
		BOMB = Attachment::ATTACH_BOMB,
		SWATTER = Attachment::ATTACH_SWATTER,
		BUBBLEGUM_SHIELD = Attachment::ATTACH_BUBBLEGUM_SHIELD,
	};
	Type type = NOTHING;
	float time_left = 0.f;
	static void define(py::object m) {
		py::class_<PyAttachment, std::shared_ptr<PyAttachment>> c(m, "Attachment");
		py::enum_<Type> E(c, "Type");
		E V(NOTHING)
		  V(PARACHUTE)
		  V(ANVIL)
		  V(BOMB)
		  V(SWATTER)
		  V(BUBBLEGUM_SHIELD);
		c.def_readonly("type", &PyAttachment::type)
		 .def_readonly("time_left", &PyAttachment::time_left)
		 .def("__repr__", [E](const PyAttachment &a) { return "<Attachment type=" + std::string(py::repr(E(a.type))) + " time_left="+std::to_string(a.time_left)+">"; });
		add_pickle(c);
	}
	PyAttachment(const Attachment * a = nullptr) {
		update(a);
	}
	void update(const Attachment * a) {
		if (a) {
			type = (Type)a->getType();
			time_left = stk_config->ticks2Time(a->getTicksLeft());
		} else {
			type = NOTHING;
			time_left = 0;
		}
	}
};

struct PyPowerup {
	enum Type: uint8_t {
		NOTHING    = PowerupManager::POWERUP_NOTHING,
		BUBBLEGUM  = PowerupManager::POWERUP_BUBBLEGUM,
		CAKE       = PowerupManager::POWERUP_CAKE,
		BOWLING    = PowerupManager::POWERUP_BOWLING,
		ZIPPER     = PowerupManager::POWERUP_ZIPPER,
		PLUNGER    = PowerupManager::POWERUP_PLUNGER,
		SWITCH     = PowerupManager::POWERUP_SWITCH,
		SWATTER    = PowerupManager::POWERUP_SWATTER,
		RUBBERBALL = PowerupManager::POWERUP_RUBBERBALL,
		PARACHUTE  = PowerupManager::POWERUP_PARACHUTE,
		ANVIL      = PowerupManager::POWERUP_ANVIL
	};
	Type type;
	int num = 0;
	static void define(py::object m) {
		py::class_<PyPowerup, std::shared_ptr<PyPowerup>> c(m, "Powerup");
		py::enum_<Type> E(c, "Type");
		E V(NOTHING)
		  V(BUBBLEGUM)
		  V(CAKE)
		  V(BOWLING)
		  V(ZIPPER)
		  V(PLUNGER)
		  V(SWITCH)
		  V(SWATTER)
		  V(RUBBERBALL)
		  V(PARACHUTE)
		  V(ANVIL);
		c.def_readonly("type", &PyPowerup::type)
		 .def_readonly("num" , &PyPowerup::num)
		 .def("__repr__", [E](const PyPowerup &p) { return "<Powerup type=" + std::string(py::repr(E(p.type))) + " num="+std::to_string(p.num)+">"; });
		add_pickle(c);
	}
	PyPowerup(const Powerup * p = nullptr) {
		update(p);
	}
	void update(const Powerup * p) {
		if (p) {
			type = (Type)p->getType();
			num = stk_config->ticks2Time(p->getNum());
		} else {
			type = NOTHING;
			num = 0;
		}
	}
};

struct PyKartState {
	static void define();
	int id = 0, player_id = -1;
	std::string name;
	PyVec3 location = PyVec3(0,0,0);
	PyVec3 front = PyVec3(0,0,0);
	PyVec3 velocity = PyVec3(0,0,0);
	PyVec3 size = PyVec3(0,0,0);
	float shield_time = 0.f;
	bool race_result = false;
	bool jumping = false;
	int finished_laps = 0;
	float lap_time = 0;
	float finish_time = 0;
	float overall_distance = 0;
	float distance_down_track = 0;
	float max_steer_angle = 0;
	float wheel_base = 0;
	
	PyAttachment attachment;
	
	PyPowerup powerup;
	static void define(py::object m) {
		py::class_<PyKartState, std::shared_ptr<PyKartState>> c(m, "KartState");
		c
#define R(x) .def_readonly(#x, &PyKartState::x)
		  R(id)
		  R(player_id)
		  R(name)
		  R(location)
		  R(front)
		  R(velocity)
		  R(size)
		  R(shield_time)
		  R(race_result)
		  R(jumping)
		  R(lap_time)
		  R(finished_laps)
		  R(overall_distance)
		  R(distance_down_track)
		  R(finish_time)
		  R(attachment)
		  R(powerup)
		  R(max_steer_angle)
		  R(wheel_base)
#undef R
		 .def("__repr__", [](const PyKartState &k) { return "<KartState id=" + std::to_string(k.id)+" player_id=" + std::to_string(k.player_id)+" name='"+k.name+"' ...>"; });
		add_pickle(c);
	}
	PyKartState(const AbstractKart * k = nullptr) {
		update(k);
	}
	void update(const AbstractKart * k) {
		if (k) {
			id = k->getWorldKartId();
			name = k->getKartProperties()->getNonTranslatedName();
			location = P(k->getXYZ());
			front = P(k->getFrontXYZ());
			velocity = P(k->getVelocity());
			size = PyVec3(k->getKartWidth(), k->getKartHeight(), k->getKartLength());
			shield_time = k->getShieldTime();
			race_result = k->getRaceResult();
			jumping = k->isJumping();
			attachment.update(k->getAttachment());
			powerup.update(k->getPowerup());
			max_steer_angle = k->getMaxSteerAngle();
			wheel_base = k->getKartProperties()->getWheelBase();
			finish_time = k->getFinishTime();
		}
	}
};

struct PyItem {
	int id = 0;
	PyVec3 location = PyVec3(0,0,0);
	float size = 1.1f/* sqrt(1.2) */;
	enum Type
	{
		BONUS_BOX = Item::ITEM_BONUS_BOX,
		BANANA = Item::ITEM_BANANA,
		NITRO_BIG = Item::ITEM_NITRO_BIG,
		NITRO_SMALL = Item::ITEM_NITRO_SMALL,
		BUBBLEGUM = Item::ITEM_BUBBLEGUM,
		EASTER_EGG = Item::ITEM_EASTER_EGG,
		NUM_ITEM
	};
	Type type = BONUS_BOX;
	static bool isValid(const Item * i) {
		if (!i) return false;
		return 0 <= i->getType() && (int)i->getType() < NUM_ITEM;
	}
	static void define(py::object m) {
		py::class_<PyItem, std::shared_ptr<PyItem>> c(m, "Item");
		py::enum_<Type> E(c, "Type");
		E V(BONUS_BOX)
		  V(BUBBLEGUM)
		  V(NITRO_BIG)
		  V(NITRO_SMALL)
		  V(BUBBLEGUM)
		  V(EASTER_EGG);
#define R(x) .def_readonly(#x, &PyItem::x)
		c R(id)
		  R(location)
		  R(size)
		  R(type)
#undef R
		 .def("__repr__", [E](const PyItem &i) { return "<Item id=" + std::to_string(i.id)+" location=" + std::to_string(i.location)+" size="+std::to_string(i.size)+" type="+std::string(py::repr(E(i.type)))+">"; });
		add_pickle(c);
	}
	PyItem(const Item * i = nullptr) {
		update(i);
	}
	void update(const Item * i) {
		if (i) {
			id = i->getObjectId();
			location = P(i->getXYZ());
			size = i->getAvoidancePoint(0) ? (i->getXYZ() - *i->getAvoidancePoint(0)).length() : 1.1;
			type = (Type)(int)i->getType();
		}
	}
};

struct PyCamera {
	Camera::Mode mode = Camera::CM_NORMAL;
	float aspect = 0, fov = 0;
	core::matrix4 view, projection;
	
	static void define(py::object m) {
		py::class_<PyCamera, std::shared_ptr<PyCamera> > c(m, "Camera");
		py::enum_<Camera::Mode>(c, "Mode")
		 .value("NORMAL", Camera::CM_NORMAL)
		 .value("CLOSEUP", Camera::CM_CLOSEUP)
		 .value("REVERSE", Camera::CM_REVERSE)
		 .value("LEADER_MODE", Camera::CM_LEADER_MODE)
		 .value("SIMPLE_REPLAY", Camera::CM_SIMPLE_REPLAY)
		 .value("FALLING", Camera::CM_FALLING);
		c
         .def(py::init<>())
#define R(x) .def_readonly(#x, &PyCamera::x)
		  R(mode)
		  R(aspect)
		  R(fov)
#undef R
		  .def_property_readonly("view", [](const PyCamera & c) { return py::ro_view(c.view.pointer(), {4, 4}); }, "View matrix")
		  .def_property_readonly("projection", [](const PyCamera & c) { return py::ro_view(c.projection.pointer(), {4, 4}); }, "Projection matrix")
		  
		 .def("__repr__", [](const PyCamera &t) { return "<Camera mode="+std::to_string(t.mode)+">"; });
		add_pickle(c);
	}
	
	void update(int id) {
		Camera * c = Camera::getCamera(id);
		mode = c->getMode();
		scene::ICameraSceneNode * n = c->getCameraSceneNode();
		aspect = n->getAspectRatio();
		fov = n->getFOV();
		view = n->getViewMatrix();
		projection = n->getProjectionMatrix();
	}
};

struct PyPlayer {
	int id = -1;
	std::shared_ptr<PyKartState> kart;
	std::shared_ptr<PyCamera> camera;
	static void define(py::object m) {
		py::class_<PyPlayer, std::shared_ptr<PyPlayer> > c(m, "Player");
		c.def(py::init<>())
#define R(x) .def_readonly(#x, &PyPlayer::x)
		  R(kart)
		  R(camera)
#undef R
		 .def("__repr__", [](const PyPlayer &t) { return "<Player id="+std::to_string(t.id)+">"; });
	}
	
	void update(int player_id) {
		id = player_id;
		if (!camera)
			camera.reset(new PyCamera());
		camera->update(player_id);
	}
};

struct PyTrack {
	float length;
	int lap_count;
	py::array_t<float> path_nodes;
	py::array_t<float> path_width;
	py::array_t<float> path_distance;
	
	static void define(py::object m) {
		py::class_<PyTrack, std::shared_ptr<PyTrack> > c(m, "Track");
		c.def(py::init<>())
#define R(x) .def_readonly(#x, &PyTrack::x)
		  R(length)
		  R(lap_count)
		  R(path_nodes)
		  R(path_width)
		  R(path_distance)
#undef R
		 .def("update", &PyTrack::update) 
		 .def("__repr__", [](const PyTrack &t) { return "<Track length="+std::to_string(t.length)+" lap_count="+std::to_string(t.lap_count)+">"; });
		add_pickle(c);
	}
	
	void update() {
		const Track * t = Track::getCurrentTrack();
		if (t) {
			length = t->getTrackLength();
			lap_count = race_manager->getNumLaps();
		}
		const DriveGraph * g = DriveGraph::get();
		if (g) {
			path_nodes = py::array_t<float>(py::array::ShapeContainer({g->getNumNodes(), 2, 3}));
			path_width = py::array_t<float>(py::array::ShapeContainer({g->getNumNodes(), 1}));
			path_distance = py::array_t<float>(py::array::ShapeContainer({g->getNumNodes(), 2}));
			for(int i=0; i<g->getNumNodes(); i++) {
				DriveNode * node = g->getNode(i);
				memcpy(path_nodes.mutable_data(i,0), node->getLowerCenter().m_floats, 3*sizeof(float));
				memcpy(path_nodes.mutable_data(i,1), node->getUpperCenter().m_floats, 3*sizeof(float));
				*path_width.mutable_data(i) = node->getPathWidth();
				*path_distance.mutable_data(i,0) = node->getDistanceFromStart();
				*path_distance.mutable_data(i,1) = node->getDistanceFromStart() + node->getNodeLength();
			}
		}
	}
};

struct PyWorldState {
	std::vector<std::shared_ptr<PyPlayer> > players;
	std::vector<std::shared_ptr<PyKartState> > karts;
	std::vector<std::shared_ptr<PyItem> > items;
	float time = 0;
	
	static void define(py::object m) {
		py::class_<PyWorldState, std::shared_ptr<PyWorldState>> c(m, "WorldState");
		c.def(py::init<>())
#define R(x) .def_readonly(#x, &PyWorldState::x)
		  R(players)
		  R(karts)
		  R(items)
		  R(time)
#undef R
		 .def("update", &PyWorldState::update) 
		 .def("__repr__", [](const PyWorldState &k) { return "<WorldState #karts="+std::to_string(k.karts.size())+">"; });
		// TODO: Add pickling and make sure players are updated
		add_pickle(c);
	}
	void assignPlayersKart() {
		for(auto k: karts) 
			if (k->player_id >= 0)
				players[k->player_id]->kart = k;
	}
	void update() {
		World * w = World::getWorld();
		LinearWorld * lw = dynamic_cast<LinearWorld*>(w);
		if (w) {
			World::KartList k = w->getKarts();
			karts.resize(k.size());
			players.resize(k.size());
			int pid = 0;
			for(int i=0; i<k.size(); i++) {
				if (!karts[i])
					karts[i].reset(new PyKartState());
				karts[i]->update(k[i].get());
				if (k[i]->getController()->isLocalPlayerController()) {
					karts[i]->player_id = pid;
					if (!players[pid])
						players[pid].reset(new PyPlayer());
					players[pid]->update(pid);
					pid++;
				} else {
					karts[i]->player_id = -1;
				}
				if (lw) {
					karts[i]->finished_laps = lw->getFinishedLapsOfKart(i);
					karts[i]->overall_distance = lw->getOverallDistance(i);
					karts[i]->distance_down_track = lw->getDistanceDownTrackForKart(i, true);
					karts[i]->lap_time = stk_config->ticks2Time(lw->getTicksAtLapForKart(i));
				}
			}
			players.resize(pid);
			assignPlayersKart();
			time = w->getTime();
		}
		ItemManager * im = ItemManager::get();
		if (im) {
			items.clear();
			for(int i=0; i<im->getNumberOfItems(); i++) {
				const Item * I = dynamic_cast<const Item*>(im->getItem(i));
				if (PyItem::isValid(I))
					items.push_back(std::make_shared<PyItem>(I));
			}
		}
	}
};

// AUTO Generated //
void pickle(std::ostream & s, const PyAttachment & o) {
    pickle(s, o.type);
    pickle(s, o.time_left);
}
void unpickle(std::istream & s, PyAttachment * o) {
    unpickle(s, &o->type);
    unpickle(s, &o->time_left);
}
void pickle(std::ostream & s, const PyPowerup & o) {
    pickle(s, o.type);
    pickle(s, o.num);
}
void unpickle(std::istream & s, PyPowerup * o) {
    unpickle(s, &o->type);
    unpickle(s, &o->num);
}
void pickle(std::ostream & s, const PyKartState & o) {
    pickle(s, o.id);
    pickle(s, o.player_id);
    pickle(s, o.name);
    pickle(s, o.location);
    pickle(s, o.front);
    pickle(s, o.velocity);
    pickle(s, o.size);
    pickle(s, o.shield_time);
    pickle(s, o.race_result);
    pickle(s, o.jumping);
    pickle(s, o.finished_laps);
    pickle(s, o.lap_time);
    pickle(s, o.finish_time);
    pickle(s, o.overall_distance);
    pickle(s, o.distance_down_track);
    pickle(s, o.max_steer_angle);
    pickle(s, o.wheel_base);
    pickle(s, o.attachment);
    pickle(s, o.powerup);
}
void unpickle(std::istream & s, PyKartState * o) {
    unpickle(s, &o->id);
    unpickle(s, &o->player_id);
    unpickle(s, &o->name);
    unpickle(s, &o->location);
    unpickle(s, &o->front);
    unpickle(s, &o->velocity);
    unpickle(s, &o->size);
    unpickle(s, &o->shield_time);
    unpickle(s, &o->race_result);
    unpickle(s, &o->jumping);
    unpickle(s, &o->finished_laps);
    unpickle(s, &o->lap_time);
    unpickle(s, &o->finish_time);
    unpickle(s, &o->overall_distance);
    unpickle(s, &o->distance_down_track);
    unpickle(s, &o->max_steer_angle);
    unpickle(s, &o->wheel_base);
    unpickle(s, &o->attachment);
    unpickle(s, &o->powerup);
}
void pickle(std::ostream & s, const PyItem & o) {
    pickle(s, o.id);
    pickle(s, o.location);
    pickle(s, o.size);
    pickle(s, o.type);
}
void unpickle(std::istream & s, PyItem * o) {
    unpickle(s, &o->id);
    unpickle(s, &o->location);
    unpickle(s, &o->size);
    unpickle(s, &o->type);
}
void pickle(std::ostream & s, const PyCamera & o) {
    pickle(s, o.mode);
    pickle(s, o.aspect);
    pickle(s, o.fov);
    pickle(s, o.view);
    pickle(s, o.projection);
}
void unpickle(std::istream & s, PyCamera * o) {
    unpickle(s, &o->mode);
    unpickle(s, &o->aspect);
    unpickle(s, &o->fov);
    unpickle(s, &o->view);
    unpickle(s, &o->projection);
}
void pickle(std::ostream & s, const PyTrack & o) {
    pickle(s, o.length);
    pickle(s, o.lap_count);
    ::pickle(s, o.path_nodes);
    ::pickle(s, o.path_width);
    ::pickle(s, o.path_distance);
}
void unpickle(std::istream & s, PyTrack * o) {
    unpickle(s, &o->length);
    unpickle(s, &o->lap_count);
    unpickle(s, &o->path_nodes);
    unpickle(s, &o->path_width);
    unpickle(s, &o->path_distance);
}
void pickle(std::ostream & s, const PyPlayer & o) {
    pickle(s, o.id);
    pickle(s, o.camera);
}
void unpickle(std::istream & s, PyPlayer * o) {
    unpickle(s, &o->id);
    unpickle(s, &o->camera);
}
void pickle(std::ostream & s, const PyWorldState & o) {
    pickle(s, o.time);
    pickle(s, o.players);
    pickle(s, o.karts);
    pickle(s, o.items);
}
void unpickle(std::istream & s, PyWorldState * o) {
    unpickle(s, &o->time);
    unpickle(s, &o->players);
    unpickle(s, &o->karts);
    unpickle(s, &o->items);
	o->assignPlayersKart();
}
// End AUTO Generated //



void defineState(py::object m) {
	PyAttachment::define(m);
	PyPowerup::define(m);
	PyKartState::define(m);
	PyItem::define(m);
	PyCamera::define(m);
	PyPlayer::define(m);
	PyWorldState::define(m);
	PyTrack::define(m);
};

