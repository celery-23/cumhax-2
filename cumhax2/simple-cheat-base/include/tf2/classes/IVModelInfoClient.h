#pragma once

#include "util/vfunc_macros.h"
#include "model_t.h"

typedef void IVModelInfoClient;

DECLARE_VFUNC(IVModelInfoClient, GetModelName, 3, const char*, const model_t* model);