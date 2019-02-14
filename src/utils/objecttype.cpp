#include "objecttype.h"
#include "utils/log.hpp"
#include <iostream>
#include <unordered_map>
#include <vector>

ObjectType getOT(const std::string & debug_name) {
	return OT_UNKNOWN;
	return OT_NONE;
}
static uint32_t last_object_id[NUM_OT] = {0};
static std::unordered_map<std::string, uint32_t> unknown_ot;
static std::vector<std::string> unknown_ot_name;

std::string unknownDebugName(uint32_t id) {
	if (id < unknown_ot_name.size())
		return unknown_ot_name[id];
	return "<invalid>";
}
ObjectID makeObjectId(ObjectType ot, uint32_t i) {
	if (ot == OT_NONE) return 0;
	return ((uint32_t)ot << OBJECT_TYPE_SHIFT) + i;
}
ObjectID newObjectId(ObjectType ot) {
	return makeObjectId(ot, ++last_object_id[ot]);
}
ObjectID newObjectId(const std::string & debug_name) {
	ObjectType ot = getOT(debug_name);
	if (ot == OT_UNKNOWN) {
		auto it = unknown_ot.find(debug_name);
		if (it == unknown_ot.end()) {
			it = unknown_ot.insert({debug_name, unknown_ot_name.size()}).first;
			unknown_ot_name.push_back(debug_name);
		}
		else {
			Log::warn("ObjectType", ("Unknown object type  '" + debug_name + "'!").c_str());
		}
		return makeObjectId(ot, it->second);
	}
	return newObjectId(ot);
}
void resetObjectId() {
	for(int i=0; i<NUM_OT; i++)
		last_object_id[i] = 0;
}
