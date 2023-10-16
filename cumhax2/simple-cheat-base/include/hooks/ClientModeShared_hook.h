#pragma once

#include "util/vtable.h"
#include "tf2/classes/ClientModeShared.h"

extern VtableHook ClientModeShared_hook;

bool __fastcall CreateMove_hook(ClientModeShared* ecx, int edx, float input_sample_frametime, CUserCmd* pCommand);