#ifndef OBJECTTYPE_H
#define OBJECTTYPE_H
#include <string>

enum ObjectType {
	OT_NONE=-1,
	OT_KART=0,
	OT_TRACK,
	OT_BACKGROUND,
	OT_PICKUP,
	OT_BOMB,
	OT_OBJECT,
	OT_PROJECTILE,
	OT_UNKNOWN,
	NUM_OT
};

const int OBJECT_TYPE_SHIFT = 24;

ObjectType getOT(const std::string & debug_name);
int newObjectId(ObjectType ot);
int newObjectId(const std::string & debug_name);
void resetObjectId();
std::string unknownDebugName(int i);

#endif // OBJECTTYPE_H

