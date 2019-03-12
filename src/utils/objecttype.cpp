#include "objecttype.h"
#include <iostream>

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
	
	std::cout << "Unknown object type : '"<<debug_name<<"'!"<<std::endl;
	return OT_NONE;
}
int last_object_id[NUM_OT] = {0};

int newObjectId(ObjectType ot) {
	if (ot == OT_NONE) return 0;
	return (++last_object_id[ot]) + (ot << OBJECT_TYPE_SHIFT);
}
int newObjectId(const std::string & debug_name) {
	return newObjectId(getOT(debug_name));
}
void resetObjectId() {
	for(int i=0; i<NUM_OT; i++)
		last_object_id[i] = 0;
}
