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


// defined in */scripts/entity_defs/SpaceMgr.def

namespace KBEngine
{

class KBENGINEPLUGINS_API EntityBaseEntityCall_SpaceMgrBase : public EntityCall
{
public:

	EntityBaseEntityCall_SpaceMgrBase(int32 eid, const FString& ename);

	virtual ~EntityBaseEntityCall_SpaceMgrBase();
};

class KBENGINEPLUGINS_API EntityCellEntityCall_SpaceMgrBase : public EntityCall
{
public:

	EntityCellEntityCall_SpaceMgrBase(int32 eid, const FString& ename);

	virtual ~EntityCellEntityCall_SpaceMgrBase();
};

}