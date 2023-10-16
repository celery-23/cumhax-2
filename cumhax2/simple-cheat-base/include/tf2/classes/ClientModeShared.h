#pragma once

#include <stdbool.h>

#include "util/vfunc_macros.h"
#include "CUserCmd.h"

typedef void ClientModeShared;
typedef void CViewSetup;

DECLARE_VFUNC(ClientModeShared, CreateMove, 21, bool, float input_sample_frametime, CUserCmd* pCommand);
DECLARE_VFUNC(ClientModeShared, DoPostScreenSpaceEffects, 39, void, CViewSetup* pSetup);
DECLARE_VFUNC(ClientModeShared, OverrideView, 16, void, CViewSetup* pSetup);