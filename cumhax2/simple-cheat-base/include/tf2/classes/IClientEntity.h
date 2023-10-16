#pragma once

#include "util/vfunc_macros.h"
#include "tf2/classes/IClientClass.h"

typedef struct
{
	void* IClientUnknown_vtable;
	void* IClientRenderable_vtable;
	void* IClientNetworkable_vtable;
	void* IClientThinkable_vtable;
} IClientEntity;


/* ======================================================================================================================== */

typedef void IClientNetworkable;

DECLARE_VFUNC(IClientNetworkable, GetClientClass, 2, IClientClass*);

inline IClientClass* IClientEntity_GetIClientClass(IClientEntity* ent)
{
	return GET_VFUNC(IClientNetworkable, GetClientClass, &ent->IClientNetworkable_vtable)
		(&ent->IClientNetworkable_vtable, 0);
}

/* ======================================================================================================================== */

typedef void IClientRenderable;

DECLARE_VFUNC(IClientRenderable, DrawModel, 10, int, int flags);
