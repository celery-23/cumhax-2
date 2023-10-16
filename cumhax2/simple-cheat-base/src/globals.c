#include <stddef.h>
#include <Windows.h>

#include "globals.h"
#include "util/sig_scan.h"

typedef void* (__cdecl* CreateInterface_t)(const char*, int*);

ClientModeShared* client_mode_shared;
IClientEntityList* client_entity_list;
IEngineClient* engine_client;
ICvar* cvar;
IVModelRender* model_render;
IBaseClientDLL* base_client_dll;
IMaterialSystem* material_system;
KeyValuesSystem* key_values_system;
IVRenderView* render_view;
IVModelInfoClient* model_info_client;


KeyValues_ctor_t KeyValues_ctor;
KeyValues_LoadFromBuffer_t KeyValues_LoadFromBuffer;

int init_interfaces(void)
{
	void* temp_addr;

	CreateInterface_t client_factory = (CreateInterface_t)GetProcAddress(GetModuleHandleA("client.dll"), "CreateInterface");
	CreateInterface_t engine_factory = (CreateInterface_t)GetProcAddress(GetModuleHandleA("engine.dll"), "CreateInterface");
	CreateInterface_t cvar_factory = (CreateInterface_t)GetProcAddress(GetModuleHandleA("vstdlib.dll"), "CreateInterface");
	CreateInterface_t material_system_factory = (CreateInterface_t)GetProcAddress(GetModuleHandleA("MaterialSystem.dll"), "CreateInterface");
	KeyValuesSystem_factory_t key_values_system_factory = (KeyValuesSystem_factory_t)GetProcAddress(GetModuleHandleA("vstdlib.dll"), "KeyValuesSystem");

	base_client_dll			= client_factory("VClient017", NULL);
	engine_client			= engine_factory("VEngineClient013", NULL);
	client_entity_list		= client_factory("VClientEntityList003", NULL);
	model_render			= engine_factory("VEngineModel016", NULL);
	cvar					= cvar_factory("VEngineCvar004", NULL);
	material_system			= material_system_factory("VMaterialSystem081", NULL);
	key_values_system		= key_values_system_factory();
	render_view				= engine_factory("VEngineRenderView014", NULL);
	model_info_client	    = engine_factory("VModelInfoClient006", NULL);

	temp_addr = scan_sig_module("client.dll", "8B 0D ? ? ? ? 8B 02 D9 05");
	client_mode_shared		= **(ClientModeShared***)((unsigned int)temp_addr + 2);

	return 0; // Should check for errors and return an error code. (Too lazy to do this)
}

int init_func_ptrs(void)
{
	void* temp_addr;

	temp_addr = scan_sig_module("engine.dll", "FF 15 ? ? ? ? 83 C4 08 89 06 8B C6");

	if (temp_addr == NULL)
	{
		PRINTF("KeyValues_Init not found\n");
		return -1;
	}
	else
	{
		KeyValues_ctor = (KeyValues_ctor_t)((int)temp_addr - 0x42);
	}

	temp_addr = scan_sig_module("engine.dll", "55 8B EC 83 EC 38 53 8B 5D 0C");

	if (temp_addr == NULL)
	{
		PRINTF("KeyValues_LoadFromBuffer not found\n");
		return -1;
	}
	else
	{
		KeyValues_LoadFromBuffer = (KeyValues_LoadFromBuffer_t)(temp_addr);
	}

	return 0;
}