#pragma once
#include"context.h"

struct SapphireSG_Queue;
struct SapphireSG_ThreadKit;

struct SapphireSG_ThreadKit *SG_CreateThreadKit(struct SapphireSG_Context *ctx);

void SG_RunRenderer(struct SapphireSG_ThreadKit *kit, void (*set_context)(void *arg), void *arg);

#define SG_GetNextQueue SG_GetNextPutQueue
struct SapphireSG_Queue *SG_GetNextTakeQueue(struct SapphireSG_ThreadKit *kit);
struct SapphireSG_Queue *SG_GetNextPutQueue(struct SapphireSG_ThreadKit *kit);

void SG_PutGroup(struct SapphireSG_ThreadKit *kit, struct SapphireSG_Group *group);
struct SapphireSG_Group *SG_TakeGroup(struct SapphireSG_ThreadKit *kit);
struct SapphireSG_Group *SG_TakeGroupFromQueue(struct SapphireSG_ThreadKit *kit, struct SapphireSG_Queue **queue);

void SG_ClearQueue(struct SapphireSG_ThreadKit *kit, unsigned q);
void SG_ShrinkQueue(struct SapphireSG_ThreadKit *kit, unsigned q);
