#pragma once

#include "util/vfunc_macros.h"

typedef void IEngineClient;

DECLARE_VFUNC(IEngineClient, GetLocalPlayer, 12, int);
DECLARE_VFUNC(IEngineClient, GetMaxClients, 21, int);