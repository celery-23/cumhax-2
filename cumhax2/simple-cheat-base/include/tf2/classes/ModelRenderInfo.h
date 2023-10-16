#pragma once

#include "Vector.h"
#include "matrix.h"
#include "model_t.h"

typedef unsigned short ModelInstanceHandle_t;

typedef struct
{
	Vector origin;
	Vector angles;
	void* pRenderable; //IClientRenderable*
	const model_t* pModel;
	const matrix3x4_t* pModelToWorld;
	const matrix3x4_t* pLightingOffset;
	const Vector* pLightingOrigin;
	int flags;
	int entity_index;
	int skin;
	int body;
	int hitboxset;
	ModelInstanceHandle_t instance;

} ModelRenderInfo_t;