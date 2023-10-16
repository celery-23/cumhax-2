#include <stddef.h>

#include "util/vfunc_macros.h"
#include "globals.h"
#include "tf2/classes/IMaterial.h"
#include "tf2/classes/IMaterialSystem.h"
#include "tf2/classes/KeyValues.h"

IMaterial* shaded_mat = NULL;
IMaterial* wireframe_mat = NULL;
IMaterial* plasma_mat = NULL;
IMaterial* chrome_mat = NULL;

const char* shaded_mat_source = "VertexLitGeneric\n{\n\t$basetexture white\n\t$bumpmap dev/flat_normal\n\t$selfillum 1\n\t$selfillumFresnel 1\n\t$selfillumFresnelMinMaxExp \"[-0.5 0.5 2]\"\n\t$selfillumTint \"[1.0 1.0 1.0]\"\n}";
const char* wireframe_mat_source = "UnlitGeneric\n{\n\t$basetexture white\n\t$wireframe 1\n}";
const char* plasma_mat_source = "Refract\n{\n\t$bumpmap dev/flat_normal\n\t$normalmap grey\n\t$refractamount 0.03\n\t$refracttint \"[1 0 5]\"\n\t$bluramount 1\n\t$envmap matsys_regressiontest/cubemap\n\t$envmaptint \"[1.5 0.5 1.5]\"\n\t$model 1\n}";
const char* chrome_mat_source = "VertexLitGeneric\n{\n\t$basetexture vgui/white_additive\n\t$envmap cubemaps/cubemap_specular001\n\t$color2 \"[1 1 1]\"\n\t$envmapcontrast 10\n\t$envmaptint \"[1 1 1]\"\n\t$selfillum 1\n\t$selfillumFresnel 1\n\t$selfillumTint \"[1.5 1.5 1.5]\"\n}";

IMaterial* create_mat_from_source(const char* source, const char* mat_name, const char* key_name) // key_name should be the name of the shader?
{
	KeyValues* kv = GET_VFUNC(KeyValuesSystem, AllocKeyValuesMemory, key_values_system)
		(key_values_system, 0, KEY_VALUES_SIZE);

	// We shouldn't need to worry about leaking a KeyValues here because it should be freed when the material is freed.

	KeyValues_ctor(kv, 0, key_name);
	KeyValues_LoadFromBuffer(kv, 0, mat_name, (char*)source, NULL, NULL);

	// All of this should run before the material system hook is installed.
	return GET_VFUNC(IMaterialSystem, CreateMaterial, material_system)
		(material_system, 0, mat_name, kv);
}

void free_mat(IMaterial* mat)
{
	GET_VFUNC(IMaterial, DecrementReferenceCount, mat)(mat, 0);
	GET_VFUNC(IMaterial, DeleteIfUnreferenced, mat)(mat, 0);
}

int init_chams_mats(void)
{
	shaded_mat = create_mat_from_source(shaded_mat_source, "cum_shaded", "VertexLitGeneric");
	wireframe_mat = create_mat_from_source(wireframe_mat_source, "cum_wireframe", "UnlitGeneric");
	plasma_mat = create_mat_from_source(plasma_mat_source, "cum_plasma", "Refract");
	chrome_mat = create_mat_from_source(chrome_mat_source, "cum_chrome", "VertexLitGeneric");
	return 0;
}

void free_chams_mats(void)
{
	if (shaded_mat != NULL) free_mat(shaded_mat);
	if (wireframe_mat != NULL) free_mat(wireframe_mat);
	if (plasma_mat != NULL) free_mat(plasma_mat);
	if (chrome_mat != NULL) free_mat(chrome_mat);
	return;
}