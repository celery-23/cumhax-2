#include <string.h>
#include <stddef.h>

#include "util/vtable.h"
#include "globals.h"
#include "tf2/classes/IMaterialSystem.h"

VtableHook IMaterialSystem_hook;

ITexture* __fastcall FindTexture_hook(IMaterialSystem* ecx, int edx, const char* pTextureName, const char* pTextureGroupName, bool complain, int nAdditionalCreationFlags)
{
	ITexture* ret = GET_VFUNC(IMaterialSystem, FindTexture, &IMaterialSystem_hook.original_vtable_ptr)
		(material_system, 0, pTextureName, pTextureGroupName, complain, nAdditionalCreationFlags);

	if (ret != NULL)
	{
		if (GET_VFUNC(ITexture, IsTranslucent, ret)(ret, 0))
		{
			return ret;
		}
	}

	if (pTextureGroupName != NULL)
	{
		if (strcmp(pTextureGroupName, "World textures") == 0 || strstr(pTextureName, "props") != NULL
			|| strstr(pTextureName, "water") != NULL || strstr(pTextureName, "glass") != NULL
			|| strstr(pTextureName, "door") != NULL || strstr(pTextureName, "tools") != NULL
			|| strstr(pTextureName, "chicken") != NULL || strstr(pTextureName, "wall28") != NULL
			|| strstr(pTextureName, "wall26") != NULL || strstr(pTextureName, "hay") != NULL
			|| strstr(pTextureName, "decal") != NULL || strstr(pTextureName, "overlay") != NULL)
		{
				return GET_VFUNC(IMaterialSystem, FindTexture, &IMaterialSystem_hook.original_vtable_ptr)
									(material_system, 0, "grey", "Other textures", complain, nAdditionalCreationFlags);
		}
	}

	/*			if (sName.find("water") != std::string_view::npos || sName.find("glass") != std::string_view::npos
				|| sName.find("door") != std::string_view::npos || sName.find("tools") != std::string_view::npos
				|| sName.find("player") != std::string_view::npos || sName.find("chicken") != std::string_view::npos
				|| sName.find("wall28") != std::string_view::npos || sName.find("wall26") != std::string_view::npos
				|| sName.find("decal") != std::string_view::npos || sName.find("overlay") != std::string_view::npos
				|| sName.find("hay") != std::string_view::npos)*/

	return ret;				
}