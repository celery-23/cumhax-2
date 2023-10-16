#pragma once

#include <stdbool.h>

#include "util/vfunc_macros.h"
#include "../enums.h"
#include "IMaterialVar.h"

typedef void IMaterial;

DECLARE_VFUNC(IMaterial, IncrementReferenceCount, 12, void);
DECLARE_VFUNC(IMaterial, DecrementReferenceCount, 13, void);
DECLARE_VFUNC(IMaterial, DeleteIfUnreferenced, 50, void);
DECLARE_VFUNC(IMaterial, SetMaterialVarFlag, 29, void, MaterialVarFlags_t flags, bool on);
DECLARE_VFUNC(IMaterial, FindVar, 11, IMaterialVar*, const char* varName, bool* found, bool complain);
