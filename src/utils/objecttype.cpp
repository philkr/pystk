#include "objecttype.h"
#include "utils/log.hpp"
#include <iostream>
#include <unordered_map>
#include <vector>

ObjectType getOT(const std::string & debug_name) {
	if (debug_name.find("track") != std::string::npos) return OT_TRACK;
	if (debug_name.find("water") != std::string::npos) return OT_BACKGROUND;
	if (debug_name.find("item")  != std::string::npos) return OT_PICKUP;
	if (debug_name.find("bomb")  != std::string::npos) return OT_BOMB;
	if (debug_name.find("tree")  != std::string::npos) return OT_BACKGROUND;
	if (debug_name.find("Tree")  != std::string::npos) return OT_BACKGROUND;
	if (debug_name.find("conifer")!=std::string::npos) return OT_BACKGROUND;
	if (debug_name.find("wheel") != std::string::npos) return OT_KART;
	if (debug_name.find("kart")  != std::string::npos) return OT_KART;
// 	if (debug_name.find("water") != std::string::npos) return OT_KART;
	
	Log::warn("ObjectType", ("Unknown object type  '" + debug_name + "'!").c_str());
	return OT_UNKNOWN;
	return OT_NONE;
}
static int last_object_id[NUM_OT] = {0};
static std::unordered_map<std::string, int> unknown_ot;
static std::vector<std::string> unknown_ot_name;

std::string unknownDebugName(int id) {
	if (id < unknown_ot_name.size())
		return unknown_ot_name[id];
	return "<invalid>";
}
int newObjectId(ObjectType ot) {
	if (ot == OT_NONE) return 0;
	return (++last_object_id[ot]) + (ot << OBJECT_TYPE_SHIFT);
}
int newObjectId(const std::string & debug_name) {
	ObjectType ot = getOT(debug_name);
	if (ot == OT_UNKNOWN) {
		auto it = unknown_ot.find(debug_name);
		if (it == unknown_ot.end()) {
			it = unknown_ot.insert({debug_name, unknown_ot_name.size()}).first;
			unknown_ot_name.push_back(debug_name);
		}
		return it->second + (ot << OBJECT_TYPE_SHIFT);
	}
	return newObjectId(ot);
}
void resetObjectId() {
	for(int i=0; i<NUM_OT; i++)
		last_object_id[i] = 0;
}
