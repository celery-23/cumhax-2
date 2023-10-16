#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

#include "external/hashmap/hashmap.h"
#include "globals.h"
#include "tf2/enums.h"
#include "tf2/classes/ClientClass.h"
#include "tf2/classes/RecvTable.h"

const char* desired_classes[] = { "CTFPlayer", "CBaseCombatCharacter"};
#define N_DESIRED_CLASSES (sizeof(desired_classes) / sizeof(const char*))


#define NETVAR_ENTRY_NAME_LEN_MAX 64
typedef struct
{
	char name[NETVAR_ENTRY_NAME_LEN_MAX];
	int offset;
} NetvarMapEntry;

struct hashmap* netvar_map = NULL;

int netvar_map_entry_compare(const void* a, const void* b, const void* udata);
uint64_t netvar_map_entry_hash(const void* item, uint64_t seed0, uint64_t seed1);

void dump_table(RecvTable* table, const char* base_class_name, int offset);

/* ======================================================================================================================== */

int init_netvar_offsets(void)
{
	netvar_map = hashmap_new(sizeof(NetvarMapEntry), 0, 0, 0, netvar_map_entry_hash, netvar_map_entry_compare, NULL, NULL);

	ClientClass* all_classes = GET_VFUNC(IBaseClientDLL, GetAllClasses, base_client_dll)
											(base_client_dll, 0);

	int i;
	for (i = 0; i < N_DESIRED_CLASSES; i++)
	{
		ClientClass* current_class = all_classes;

		while (current_class != NULL)
		{
			if (strcmp(current_class->m_pNetworkName, desired_classes[i]) == 0)
			{
				RecvTable* table = current_class->m_pRecvTable;

				if (table != NULL)
				{
					dump_table(table, current_class->m_pNetworkName, 0);
				}
			}
			current_class = current_class->m_pNext;
		}
	}

	//size_t iter;
	//void* item;

	/*
	while (hashmap_iter(netvar_map, &iter, &item))
	{
		NetvarMapEntry* entry = item;
		PRINTF("%s\n", entry->name);
	}
	*/

	return 0;
}

void dump_table(RecvTable* table, const char* base_class_name, int offset)
{
	int i;
	for (i = 0; i < table->m_nProps; i++)
	{
		RecvProp prop = table->m_pProps[i];
		if (prop.m_RecvType == DPT_DataTable)
		{
			dump_table(prop.m_pDataTable, base_class_name, offset + prop.m_Offset);
		}

		if (isdigit((int)prop.m_pVarName[0]))
			continue;

		if (strcmp(prop.m_pVarName, "baseclass") == 0)
			continue;

		NetvarMapEntry entry;
		snprintf(entry.name, sizeof(entry.name), "%s.%s", base_class_name, prop.m_pVarName);
		entry.offset = prop.m_Offset;

		hashmap_set(netvar_map, &entry);
	}
}

void free_netvar_offsets(void)
{
	hashmap_free(netvar_map);
}

int get_netvar_offset(const char* netvar_name)
{
	NetvarMapEntry query = { 0 };
	strncpy_s(query.name, NETVAR_ENTRY_NAME_LEN_MAX, netvar_name, NETVAR_ENTRY_NAME_LEN_MAX);

	const NetvarMapEntry* res = hashmap_get(netvar_map, &query);
	if (res == NULL)
		return -1;

	else 
		return res->offset;
}

void* get_netvar(void* object, const char* netvar_name)
{
	int offset = get_netvar_offset(netvar_name);
	if (offset == -1)
		return NULL;

	else
		return (void*)((int)object + offset);
}

/* ======================================================================================================================== */

int netvar_map_entry_compare(const void* a, const void* b, const void* udata)
{
	const NetvarMapEntry* entry_a = a;
	const NetvarMapEntry* entry_b = b;
	return strcmp(entry_a->name, entry_b->name);
}

uint64_t netvar_map_entry_hash(const void* item, uint64_t seed0, uint64_t seed1)
{
	const NetvarMapEntry* entry = item;
	return hashmap_murmur(entry->name, strlen(entry->name), seed0, seed1);
}
