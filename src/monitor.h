#pragma once

struct SapphireSG_Monitor;

struct SapphireSG_Monitor *SG_CreateMonitor();

void SG_DestroyMonitor(struct SapphireSG_Monitor *);

void SG_LockMonitor(struct SapphireSG_Monitor *);
void SG_UnlockMonitor(struct SapphireSG_Monitor *);
void SG_WaitMonitor(struct SapphireSG_Monitor *);
void SG_NotifyMonitor(struct SapphireSG_Monitor *);
void SG_NotifyAllMonitor(struct SapphireSG_Monitor *);
