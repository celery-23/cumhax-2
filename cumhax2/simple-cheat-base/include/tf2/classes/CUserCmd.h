#pragma once

#include <stdbool.h>

#include "tf2/classes/Vector.h"

typedef struct
{
	void* vtable;
	int command_number;
	int tick_count;
	Vector viewangles;
	float forwardmove;
	float sidemove;
	float upmove;
	int	buttons;
	unsigned char impulse;
	int weaponselect;
	int weaponsubtype;
	int random_seed;
	short mousedx;
	short mousedy;
	bool hasbeenpredicted;
} CUserCmd;
