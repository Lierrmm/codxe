#pragma once

#include "structs.h"

namespace qos
{
namespace mp
{
static auto cm = reinterpret_cast<clipMap_t *>(0x839CB3D0);
static auto g_entities = reinterpret_cast<gentity_s *>(0x838B15A0);
// level.clients pointer. max clients is 12 it seems
static gclient_s **level_clients = reinterpret_cast<gclient_s **>(0x83983A78);
static const PlayerKeyState *playerKeys = reinterpret_cast<PlayerKeyState *>(0x82AAA2B0);
static auto client_fields = reinterpret_cast<client_fields_s *>(0x8202ACA0);
static auto entity_fields = reinterpret_cast<ent_field_t *>(0x82036B78);

typedef void (*Cbuf_AddText_t)(int localClientNum, const char *text);
static Cbuf_AddText_t Cbuf_AddText = reinterpret_cast<Cbuf_AddText_t>(0x8225C288);

static auto Hunk_AllocateTempMemoryHighInternal = reinterpret_cast<void *(*)(int size)>(0x822B89E8);

static auto Scr_AddInt = reinterpret_cast<void (*)(int value)>(0x8227FBC8);
static auto Scr_AddSourceBuffer =
    reinterpret_cast<char *(*)(const char *filename, const char *extFilename, const char *codePos, bool archive)>(
        0x82275DD8);
static auto Scr_GetFunction = reinterpret_cast<BuiltinFunction (*)(const char **pName, int *type)>(0x8223F788);
static auto Scr_GetMethod = reinterpret_cast<BuiltinMethod (*)(const char **pName, int *type)>(0x8223F838);
static auto Scr_GetVector = reinterpret_cast<void (*)(unsigned int index, float *vectorValue)>(0x82284618);
static auto Scr_GetString = reinterpret_cast<char *(*)(unsigned int index)>(0x82284430);

typedef gentity_s *(*GetPlayerEntity_t)(scr_entref_t entref);
static GetPlayerEntity_t GetPlayerEntity = reinterpret_cast<GetPlayerEntity_t>(0x82232D20);

static auto Scr_GetNumParam = reinterpret_cast<unsigned int (*)()>(0x8227FBB8);
static auto Scr_Error = reinterpret_cast<void (*)(const char *error)>(0x82280180);
static auto Scr_ObjectError = reinterpret_cast<void (*)(const char *error)>(0x822802B8);

typedef int (*Scr_GetInt_t)(unsigned int index);
static auto Scr_GetInt = reinterpret_cast<Scr_GetInt_t>(0x82283F08);

typedef void (*GScr_AddFieldsForClient_t)();
static GScr_AddFieldsForClient_t GScr_AddFieldsForClient = reinterpret_cast<GScr_AddFieldsForClient_t>(0x82217578);

typedef void (*GScr_AddFieldsForEntity_t)();
static GScr_AddFieldsForEntity_t GScr_AddFieldsForEntity = reinterpret_cast<GScr_AddFieldsForEntity_t>(0x82245838);

static auto Scr_AddClassField =
    reinterpret_cast<void (*)(unsigned int classnum, const char *name, unsigned __int16 offset)>(0x8227C818);

typedef void (*Scr_SetClientField_t)(gclient_s *client, int offset);
static Scr_SetClientField_t Scr_SetClientField = reinterpret_cast<Scr_SetClientField_t>(0x822175D0);

static auto Scr_SetGenericField = reinterpret_cast<void (*)(unsigned __int8 *b, fieldtype_t type, int ofs)>(0x82246878);
static auto Scr_GetGenericField = reinterpret_cast<void (*)(unsigned __int8 *b, fieldtype_t type, int ofs)>(0x822469B0);

typedef void (*Scr_GetObjectField_t)(unsigned int classnum, unsigned int entnum, unsigned int offset);
static Scr_GetObjectField_t Scr_GetObjectField = reinterpret_cast<Scr_GetObjectField_t>(0x82246C80);

static auto va = reinterpret_cast<char *(*)(char *format, ...)>(0x822C1848);

typedef int (*Key_StringToKeynum_t)(const char *str);
static Key_StringToKeynum_t Key_StringToKeynum = reinterpret_cast<Key_StringToKeynum_t>(0x821C2AD0);

} // namespace mp
} // namespace qos
