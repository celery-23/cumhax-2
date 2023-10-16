#include "util/vtable.h"
#include "globals.h"
#include "tf2/classes/IVModelRender.h"
#include "features/chams/chams.h"

VtableHook IVModelRender_hook;

void __fastcall DrawModelExecute_hook(IVModelRender* ecx, int edx, DrawModelState_t* state, const ModelRenderInfo_t* pInfo, matrix3x4_t* pCustomBoneToWorld)
{
	// if (should do chams)
	chams(state, (ModelRenderInfo_t*)pInfo, pCustomBoneToWorld);

	//else
	//GET_VFUNC(IVModelRender, DrawModelExecute, &IVModelRender_hook.original_vtable_ptr)
	//				(model_render, 0, state, pInfo, pCustomBoneToWorld);
}