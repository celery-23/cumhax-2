#include <stddef.h>
#include <stdbool.h>
#include <string.h>

#include "util/vtable.h"
#include "globals.h"
#include "features/chams/chams_data.h"
#include "netvars.h"
#include "tf2/enums.h"
#include "tf2/classes/IMaterial.h"
#include "tf2/classes/IMaterialSystem.h"
#include "tf2/classes/IVModelRender.h"
#include "tf2/classes/IClientEntity.h"
#include "tf2/classes/IClientEntityList.h"
#include "tf2/classes/ClientClass.h"
#include "tf2/classes/IMatRenderContext.h"
#include "tf2/classes/C_BaseEntity.h"
#include "tf2/classes/C_BaseCombatWeapon.h"

#define DME()					GET_VFUNC(IVModelRender, DrawModelExecute, &IVModelRender_hook.original_vtable_ptr)(model_render, 0, state, pInfo, pCustomBoneToWorld)
#define MATERIAL_OVERRIDE(mat)  GET_VFUNC(IVModelRender, ForcedMaterialOverride, &IVModelRender_hook.original_vtable_ptr)(model_render, 0, mat, OVERRIDE_NORMAL);

void draw_entity_attachments(IClientEntity* ent);
void draw_player_weapon(IClientEntity* ent);

extern VtableHook IVModelRender_hook;
extern VtableHook IMaterialSystem_hook;

extern IMaterial* shaded_mat;
extern IMaterial* wireframe_mat;
extern IMaterial* plasma_mat;
extern IMaterial* chrome_mat;

void chams(DrawModelState_t* state, ModelRenderInfo_t* pInfo, matrix3x4_t* pCustomBoneToWorld)
{
	IClientEntity* ent = GET_VFUNC(IClientEntityList, GetClientEntity, client_entity_list)
										(client_entity_list, 0, pInfo->entity_index);

	if (ent == NULL)
	{

		const char* model_name = GET_VFUNC(IVModelInfoClient, GetModelName, model_info_client)(model_info_client, 0, pInfo->pModel);

		// Checking if model is the viewmodel weapon model
		if (strstr(model_name, "weapon") == NULL
			|| strstr(model_name, "arrow") != NULL
			|| strstr(model_name, "w_syringe") != NULL
			|| strstr(model_name, "nail") != NULL
			|| strstr(model_name, "shell") != NULL
			|| strstr(model_name, "parachute") != NULL
			|| strstr(model_name, "buffbanner") != NULL
			|| strstr(model_name, "shogun_warbanner") != NULL
			|| strstr(model_name, "targe") != NULL
			|| strstr(model_name, "shield") != NULL
			|| strstr(model_name, "repair_claw") != NULL
			)
			goto normal;

		else
			{
				MATERIAL_OVERRIDE(chrome_mat);
				DME();
				MATERIAL_OVERRIDE(NULL);
				return;
			}
	}

	ClientClass* client_class = (ClientClass*)IClientEntity_GetIClientClass(ent);
	void* local_player = GET_LOCAL_PLAYER();


	static bool should_draw_hats = false;
	if (client_class->m_ClassID == CTFWearable)
	{
		if (should_draw_hats)
			goto normal;

		else
			return;
	}

	if (client_class->m_ClassID == CTFViewModel)
	{
		void* shared = get_netvar(local_player, "CTFPlayer.m_Shared");
		int cond = *(int*)get_netvar(shared, "CTFPlayer.m_nPlayerCond");

		if (cond & TFCond_Cloaked || cond & TFCond_CloakFlicker)
			goto normal;

		MATERIAL_OVERRIDE(plasma_mat);
		DME();
		MATERIAL_OVERRIDE(NULL);

		return;
	}

	else if (client_class->m_ClassID == CTFPlayer)
	{
		void* shared = get_netvar(ent, "CTFPlayer.m_Shared");
		int cond = *(int*)get_netvar(shared, "CTFPlayer.m_nPlayerCond");


		if (cond & TFCond_Ubercharged || cond & TFCond_UberchargeFading || cond & TFCond_Cloaked || cond & TFCond_CloakFlicker)
			goto normal;

		
		// Teammate or disguised
		if (*(int*)get_netvar(ent, "CTFPlayer.m_iTeamNum") == *(int*)get_netvar(local_player, "CTFPlayer.m_iTeamNum") || (cond & TFCond_Disguised))
		{

			MATERIAL_OVERRIDE(wireframe_mat);
			DME();

			should_draw_hats = true;
			draw_entity_attachments(ent);
			should_draw_hats = false;

			draw_player_weapon(ent);
			MATERIAL_OVERRIDE(NULL);

			return;
		}

		// Enemy
		else
		{
			IMatRenderContext* render_ctx = GET_VFUNC(IMaterialSystem, GetRenderContext, &IMaterialSystem_hook.original_vtable_ptr)(material_system, 0); // Not necessary to use the original vtable but I think it's good practice.
			GET_VFUNC(IMatRenderContext, SetStencilEnable, render_ctx)(render_ctx, 0, true);

			float red[] = { 1.0f, 0.0f, 0.0f, 0.0f };
			GET_VFUNC(IVRenderView, SetColorModulation, render_view)(render_view, 0, red); // Draw enemies in red

			// Unoccluded
			{
				GET_VFUNC(IMatRenderContext, SetStencilCompareFunction, render_ctx)(render_ctx, 0, STENCILCOMPARISONFUNCTION_ALWAYS);
				GET_VFUNC(IMatRenderContext, SetStencilPassOperation, render_ctx)(render_ctx, 0, STENCILOPERATION_REPLACE);
				GET_VFUNC(IMatRenderContext, SetStencilFailOperation, render_ctx)(render_ctx, 0, STENCILOPERATION_KEEP);
				GET_VFUNC(IMatRenderContext, SetStencilZFailOperation, render_ctx)(render_ctx, 0, STENCILOPERATION_KEEP);
				GET_VFUNC(IMatRenderContext, SetStencilReferenceValue, render_ctx)(render_ctx, 0, 1);
				GET_VFUNC(IMatRenderContext, SetStencilWriteMask, render_ctx)(render_ctx, 0, 0xFF);
				GET_VFUNC(IMatRenderContext, SetStencilTestMask, render_ctx)(render_ctx, 0, 0x0);

				MATERIAL_OVERRIDE(shaded_mat);
				DME();
				should_draw_hats = true;
				draw_entity_attachments(ent);
				should_draw_hats = false;
				draw_player_weapon(ent);
			}

			// Occluded
			{
				GET_VFUNC(IMatRenderContext, SetStencilCompareFunction, render_ctx)(render_ctx, 0, STENCILCOMPARISONFUNCTION_EQUAL);
				GET_VFUNC(IMatRenderContext, SetStencilPassOperation, render_ctx)(render_ctx, 0, STENCILOPERATION_KEEP);
				GET_VFUNC(IMatRenderContext, SetStencilFailOperation, render_ctx)(render_ctx, 0, STENCILOPERATION_KEEP);
				GET_VFUNC(IMatRenderContext, SetStencilZFailOperation, render_ctx)(render_ctx, 0, STENCILOPERATION_KEEP);
				GET_VFUNC(IMatRenderContext, SetStencilReferenceValue, render_ctx)(render_ctx, 0, 0);
				GET_VFUNC(IMatRenderContext, SetStencilWriteMask, render_ctx)(render_ctx, 0, 0);
				GET_VFUNC(IMatRenderContext, SetStencilTestMask, render_ctx)(render_ctx, 0, 0xFF);

				MATERIAL_OVERRIDE(wireframe_mat);
				GET_VFUNC(IMatRenderContext, DepthRange, render_ctx)(render_ctx, 0, 0.0, 0.2f);
				DME();
				GET_VFUNC(IMatRenderContext, DepthRange, render_ctx)(render_ctx, 0, 0.0f, 1.0f);
			}

			float white[] = { 1.0f, 1.0f, 1.0f, 1.0f };
			GET_VFUNC(IVRenderView, SetColorModulation, render_view)(render_view, 0, white);
			MATERIAL_OVERRIDE(NULL);
			GET_VFUNC(IMatRenderContext, SetStencilEnable, render_ctx)(render_ctx, 0, false);
			return;

		}

	}

normal:

	DME();

}

void draw_entity_attachments(IClientEntity* ent)
{
	int child = ((C_BaseEntity*)ent)->m_pMoveChild & 0xFFF;
	IClientEntity* attachment = GET_VFUNC(IClientEntityList, GetClientEntity, client_entity_list)(client_entity_list, 0, child);

	int i;
	for (i = 0; i < 10; i++)
	{
		if (attachment == NULL)
			return;

		ent_id id = ((ClientClass*)IClientEntity_GetIClientClass(attachment))->m_ClassID;
		if (id == CTFWearable)
		{
			IClientRenderable* renderable = &attachment->IClientRenderable_vtable;
			GET_VFUNC(IClientRenderable, DrawModel, renderable)(renderable, 0, STUDIO_RENDER);
		}

		int peer = ((C_BaseEntity*)attachment)->m_pMovePeer & 0xFFF;
		attachment = GET_VFUNC(IClientEntityList, GetClientEntity, client_entity_list)(client_entity_list, 0, peer);
	}
}

void draw_player_weapon(IClientEntity* ent)
{
	int weapon_handle = *(int*)get_netvar(ent, "CBaseCombatCharacter.m_hActiveWeapon");
	IClientEntity* weapon = GET_VFUNC(IClientEntityList, GetClientEntityFromHandle, client_entity_list)(client_entity_list, 0, weapon_handle);
	IClientRenderable* renderable = &weapon->IClientRenderable_vtable;
	GET_VFUNC(IClientRenderable, DrawModel, renderable)(renderable, 0, STUDIO_RENDER);
}