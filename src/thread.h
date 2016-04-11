#pragma once
#include "sapphire_sg.h"
#include"context.h"

struct SapphireSG_Queue;
struct SapphireSG_ThreadKit;


SAPPHIRESG_API_EXPORT
struct SapphireSG_ThreadKit *SG_CreateThreadKit(struct SapphireSG_Context *ctx);

SAPPHIRESG_API_EXPORT
void SG_RunRenderer(struct SapphireSG_ThreadKit *kit, void (*set_context)(void *arg), void *arg);

#define SG_GetNextQueue SG_GetNextPutQueue

SAPPHIRESG_API_EXPORT
struct SapphireSG_Queue *SG_GetNextTakeQueue(struct SapphireSG_ThreadKit *kit);
SAPPHIRESG_API_EXPORT
struct SapphireSG_Queue *SG_GetNextPutQueue(struct SapphireSG_ThreadKit *kit);

SAPPHIRESG_API_EXPORT
void SG_PutGroup(struct SapphireSG_ThreadKit *kit, struct SapphireSG_Group *group);
SAPPHIRESG_API_EXPORT
struct SapphireSG_Group *SG_TakeGroup(struct SapphireSG_ThreadKit *kit);
SAPPHIRESG_API_EXPORT
struct SapphireSG_Group *SG_TakeGroupFromQueue(struct SapphireSG_ThreadKit *kit, struct SapphireSG_Queue **queue);

SAPPHIRESG_API_EXPORT
void SG_ClearQueue(struct SapphireSG_ThreadKit *kit, unsigned q);
SAPPHIRESG_API_EXPORT
void SG_ShrinkQueue(struct SapphireSG_ThreadKit *kit, unsigned q);
