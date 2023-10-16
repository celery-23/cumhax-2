#pragma once

#include "tf2/classes/ClientModeShared.h"
#include "tf2/classes/IClientEntityList.h"
#include "tf2/classes/IEngineClient.h"
#include "tf2/classes/IBaseClientDLL.h"
#include "tf2/classes/ICvar.h"
#include "tf2/classes/IVModelRender.h"
#include "tf2/classes/IMaterialSystem.h"
#include "tf2/classes/KeyValues.h"
#include "tf2/classes/IVRenderView.h"
#include "tf2/classes/IVModelInfoClient.h"

extern ClientModeShared* client_mode_shared;
extern IClientEntityList* client_entity_list;
extern IEngineClient* engine_client;
extern ICvar* cvar;
extern IVModelRender* model_render;
extern IBaseClientDLL* base_client_dll;
extern IMaterialSystem* material_system;
extern KeyValuesSystem* key_values_system;
extern IVRenderView* render_view;
extern IVModelInfoClient* model_info_client;

extern KeyValues_ctor_t KeyValues_ctor;
extern KeyValues_LoadFromBuffer_t KeyValues_LoadFromBuffer;

#define PRINTF(fmt, ...) GET_VFUNC(ICvar, ConsolePrintf, cvar)(cvar, fmt, ##__VA_ARGS__)
#define GET_CLIENT_ENTITY(index) GET_VFUNC(IClientEntityList, GetClientEntity, client_entity_list)(client_entity_list, 0, index)
#define GET_LOCAL_PLAYER() GET_VFUNC(IClientEntityList, GetClientEntity, client_entity_list)(client_entity_list, 0, GET_VFUNC(IEngineClient, GetLocalPlayer, engine_client)(engine_client, 0))

int init_interfaces(void);
int init_func_ptrs(void);
