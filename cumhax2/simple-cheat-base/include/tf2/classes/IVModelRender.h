#pragma once

#include "util/vfunc_macros.h"
#include "../enums.h"
#include "IMaterial.h"
#include "DrawModelState.h"
#include "ModelRenderInfo.h"
#include "matrix.h"

typedef void IVModelRender;
typedef unsigned short ModelInstanceHandle_t;


DECLARE_VFUNC(IVModelRender, ForcedMaterialOverride, 1, void, IMaterial* newMaterial, OverrideType_t nOverrideType);
DECLARE_VFUNC(IVModelRender, DrawModelExecute, 19, void, DrawModelState_t* state, const ModelRenderInfo_t* pInfo, matrix3x4_t* pCustomBoneToWorld);
