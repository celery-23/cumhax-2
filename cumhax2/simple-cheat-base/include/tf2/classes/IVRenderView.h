#pragma once

#include "util/vfunc_macros.h"

typedef void IVRenderView;

DECLARE_VFUNC(IVRenderView, SetColorModulation, 6, void, float* blend);
DECLARE_VFUNC(IVRenderView, SetBlend, 4, void, float blend);