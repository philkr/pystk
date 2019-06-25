#ifndef OBJECTTYPE_H
#define OBJECTTYPE_H
#include <string>

enum ObjectType {
	OT_NONE=0,
	OT_KART,
	OT_TRACK,
	OT_BACKGROUND,
	OT_PICKUP,
	OT_NITRO,
	OT_BOMB,
	OT_OBJECT,
	OT_PROJECTILE,
	OT_UNKNOWN,
	NUM_OT
};

const int OBJECT_TYPE_SHIFT = 24;
typedef uint32_t ObjectID;

ObjectType getOT(const std::string & debug_name);
ObjectID makeObjectId(ObjectType ot, uint32_t i);
ObjectID newObjectId(ObjectType ot);
ObjectID newObjectId(const std::string & debug_name);
void resetObjectId();
std::string unknownDebugName(uint32_t i);

#endif // OBJECTTYPE_H

