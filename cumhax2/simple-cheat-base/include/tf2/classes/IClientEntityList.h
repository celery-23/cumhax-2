#pragma once

#include "util/vfunc_macros.h"
#include "IClientEntity.h"

typedef void IClientEntityList;
typedef unsigned long CBaseHandle; // Should be 32 bits

DECLARE_VFUNC(IClientEntityList, GetClientEntity, 3, IClientEntity*, int nEntityIndex);
DECLARE_VFUNC(IClientEntityList, GetClientEntityFromHandle, 4, IClientEntity*, CBaseHandle hEnt);
