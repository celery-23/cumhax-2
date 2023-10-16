#pragma once

#include <stdbool.h>

#include "util/vfunc_macros.h"
#include "IMaterial.h"
#include "KeyValues.h"

typedef void IMaterialSystem;
typedef void ITexture;
typedef void IMatRenderContext;

DECLARE_VFUNC(IMaterialSystem, CreateMaterial, 72, IMaterial*, char const* pMaterialName, KeyValues* pVMTKeyValues);
DECLARE_VFUNC(IMaterialSystem, FindMaterial, 73, IMaterial*, char* pMaterialName, char* pTextureGroupName, bool complain, char* pComplainPrefix);
DECLARE_VFUNC(IMaterialSystem, FindTexture, 81, ITexture*, const char* pTextureName, const char* pTextureGroupName, bool complain, int nAdditionalCreationFlags);
DECLARE_VFUNC(IMaterialSystem, GetRenderContext, 100, IMatRenderContext*);

DECLARE_VFUNC(ITexture, IsTranslucent, 6, bool);