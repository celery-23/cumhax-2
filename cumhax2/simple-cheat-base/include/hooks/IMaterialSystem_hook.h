#pragma once

#include "util/vtable.h"
#include "tf2/classes/IMaterialSystem.h"

extern VtableHook IMaterialSystem_hook;

ITexture* __fastcall FindTexture_hook(IMaterialSystem* ecx, int edx, const char* pTextureName, const char* pTextureGroupName, bool complain, int nAdditionalCreationFlags);