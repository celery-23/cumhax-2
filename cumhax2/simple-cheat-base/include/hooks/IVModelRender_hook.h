#pragma once

#include "util/vtable.h"
#include "tf2/classes/IVModelRender.h"

extern VtableHook IVModelRender_hook;

void __fastcall DrawModelExecute_hook(IVModelRender* ecx, int edx, DrawModelState_t* state, const ModelRenderInfo_t* pInfo, matrix3x4_t* pCustomBoneToWorld);