/*
	Generated by KBEngine!
	Please do not modify this file!
	
	tools = kbcmd
*/

#pragma once

#include "KBECommon.h"
#include "EntityCall.h"
#include "KBETypes.h"
#include "CustomDataTypes.h"


// defined in */scripts/entity_defs/NPC.def

namespace KBEngine
{

class KBENGINEPLUGINS_API EntityBaseEntityCall_NPCBase : public EntityCall
{
public:

	EntityBaseEntityCall_NPCBase(int32 eid, const FString& ename);

	virtual ~EntityBaseEntityCall_NPCBase();
};

class KBENGINEPLUGINS_API EntityCellEntityCall_NPCBase : public EntityCall
{
public:

	EntityCellEntityCall_NPCBase(int32 eid, const FString& ename);

	virtual ~EntityCellEntityCall_NPCBase();
};

}