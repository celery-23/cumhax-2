#pragma once

#include "matrix.h"

typedef struct
{
	void* m_pStudioHdr;					//studiohdr_t*
	void* m_pStudioHWData;				//studiohwdata_t*
	void* m_pRenderable;				//IClientRenderable*
	const matrix3x4_t* m_pModelToWorld;   //pointer to array of floats. Two pointers total
	void* m_decals;						//StudioDecalHandle_t*
	int	  m_drawFlags;
	int	  m_lod;
} DrawModelState_t;