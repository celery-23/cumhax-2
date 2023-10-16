#pragma once

#include "tf2/enums.h"

int init_netvar_offsets(void);
void free_netvar_offsets(void);

//netvar_name example: "CTFPlayer.m_fFlags"
int get_netvar_offset(const char* netvar_name);
void* get_netvar(void* object, const char* netvar_name);