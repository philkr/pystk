#include "state.hpp"

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/numpy.h>

#include "config/stk_config.hpp"
#include "karts/abstract_kart.hpp"
#include "karts/controller/controller.hpp"
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

namespace py = pybind11;

typedef std::tuple<float, float, float> PyVec3;
PyVec3 P(const Vec3 & v) {
	return PyVec3(v.getX(), v.getY(), v.getZ());
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
	enum Type {
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
		py::class_<PyAttachment> c(m, "Attachment");
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
	enum Type {
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
		py::class_<PyPowerup> c(m, "Powerup");
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
	float overall_distance = 0;
	
	PyAttachment attachment;
	
	PyPowerup powerup;
	static void define(py::object m) {
#define R(x) .def_readonly(#x, &PyKartState::x)
		py::class_<PyKartState, std::shared_ptr<PyKartState>>(m, "KartState")
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
		  R(attachment)
		  R(powerup)
#undef R
		 .def("__repr__", [](const PyKartState &k) { return "<KartState id=" + std::to_string(k.id)+" player_id=" + std::to_string(k.player_id)+" name='"+k.name+"' ...>"; });
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
	}
	PyItem(const Item * i = nullptr) {
		update(i);
	}
	void update(const Item * i) {
		if (i) {
			id = i->getObjectId();
			location = P(i->getXYZ());
			size = i->getAvoidancePoint(0) ? (i->getXYZ() - *i->getAvoidancePoint(0)).length() : 1.1;
		}
	}
};

struct PyTrack {
	float length;
	int lap_count;
	py::array_t<float> path_nodes;
	py::array_t<float> path_width;
	
	static void define(py::object m) {
		py::class_<PyTrack >(m, "Track")
         .def(py::init<>())
#define R(x) .def_readonly(#x, &PyTrack::x)
		  R(length)
		  R(lap_count)
		  R(path_nodes)
		  R(path_width)
#undef R
		 .def("update", &PyTrack::update) 
		 .def("__repr__", [](const PyTrack &t) { return "<Track length="+std::to_string(t.length)+" lap_count="+std::to_string(t.lap_count)+">"; });
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
			for(int i=0; i<g->getNumNodes(); i++) {
				DriveNode * node = g->getNode(i);
				memcpy(path_nodes.mutable_data(i,0), node->getLowerCenter().m_floats, 3*sizeof(float));
				memcpy(path_nodes.mutable_data(i,1), node->getUpperCenter().m_floats, 3*sizeof(float));
				*path_width.mutable_data(i) = node->getPathWidth();
			}
		}
	}
};

struct PyWorldState {
	std::vector<std::shared_ptr<PyKartState> > karts;
	std::vector<std::shared_ptr<PyItem> > items;
	
	static void define(py::object m) {
		py::class_<PyWorldState >(m, "WorldState")
         .def(py::init<>())
#define R(x) .def_readonly(#x, &PyWorldState::x)
		  R(karts)
		  R(items)
#undef R
		 .def("update", &PyWorldState::update) 
		 .def("__repr__", [](const PyWorldState &k) { return "<WorldState #karts="+std::to_string(k.karts.size())+">"; });
	}
	
	void update() {
		World * w = World::getWorld();
		LinearWorld * lw = dynamic_cast<LinearWorld*>(w);
		if (w) {
			World::KartList k = w->getKarts();
			karts.resize(k.size());
			for(int i=0, pid=0; i<k.size(); i++) {
				if (!karts[i])
					karts[i].reset(new PyKartState());
				karts[i]->update(k[i].get());
				karts[i]->player_id = k[i]->getController()->isLocalPlayerController() ? pid++ : -1;
				if (lw) {
					karts[i]->finished_laps = lw->getFinishedLapsOfKart(i);
					karts[i]->overall_distance = lw->getOverallDistance(i);
				}
			}
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
// 		items ItemManager::getItem();
	}
};

void defineState(py::object m) {
	PyAttachment::define(m);
	PyPowerup::define(m);
	PyKartState::define(m);
	PyItem::define(m);
	PyWorldState::define(m);
	PyTrack::define(m);
};

