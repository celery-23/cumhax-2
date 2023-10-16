#include "util/vtable.h"
#include "util/sig_scan.h"
#include "external/MinHook/MinHook.h"
#include "globals.h"
#include "hooks/ClientModeShared_hook.h"
#include "hooks/IVModelRender_hook.h"
#include "hooks/CL_LoadWhitelist_hook.h"
#include "hooks/IMaterialSystem_hook.h"

void* CL_LoadWhitelist_addr = NULL;
void** CL_LoadWhitelist_original = NULL;

void init_hooks(void)
{
	ClientModeShared_hook = vtable_hook_new(client_mode_shared);
	IVModelRender_hook = vtable_hook_new(model_render);
	IMaterialSystem_hook = vtable_hook_new(material_system);

	hook_vfunc(ClientModeShared_hook, CreateMove_hook, GET_VFUNC_INDEX(ClientModeShared, CreateMove));
	hook_vfunc(IVModelRender_hook, DrawModelExecute_hook, GET_VFUNC_INDEX(IVModelRender, DrawModelExecute));
	hook_vfunc(IMaterialSystem_hook, FindTexture_hook, GET_VFUNC_INDEX(IMaterialSystem, FindTexture));

	MH_Initialize();

	CL_LoadWhitelist_addr = scan_sig_module("engine.dll", "55 8B EC 83 EC ? 56 8B 75 ? 8B CE FF 75");

	MH_CreateHook(CL_LoadWhitelist_addr, CL_LoadWhitelist_hook, CL_LoadWhitelist_original);
	MH_EnableHook(CL_LoadWhitelist_addr);
}

void release_hooks(void)
{
	vtable_hook_delete(ClientModeShared_hook);
	vtable_hook_delete(IVModelRender_hook);
	vtable_hook_delete(IMaterialSystem_hook);
	MH_RemoveHook(MH_ALL_HOOKS);
	MH_Uninitialize();
}