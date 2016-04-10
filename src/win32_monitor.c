#include "monitor.h"

#include <assert.h>
#include <Windows.h>

struct SapphireSG_Monitor {
	CONDITION_VARIABLE cv;
	CRITICAL_SECTION cs;
};

struct SapphireSG_Monitor *SG_CreateMonitor() {
	struct SapphireSG_Monitor *const that = malloc(sizeof(struct SapphireSG_Monitor));
	assert(that);

	InitializeConditionVariable(&(that->cv));
	InitializeCriticalSection(&(that->cs));

	return that;
}

void SG_DestroyMonitor(struct SapphireSG_Monitor *that) {
	assert(that);

	WakeAllConditionVariable(&(that->cv));
	DeleteCriticalSection(&(that->cs));

	free(that);
}

void SG_LockMonitor(struct SapphireSG_Monitor *that) {
	assert(that);
	EnterCriticalSection(&(that->cs));
}

void SG_UnlockMonitor(struct SapphireSG_Monitor *that) {
	assert(that);
	LeaveCriticalSection(&(that->cs));
}

void SG_WaitMonitor(struct SapphireSG_Monitor *that) {
	assert(that);
	SleepConditionVariableCS(&(that->cv), &(that->cs), INFINITE);
}

void SG_NotifyMonitor(struct SapphireSG_Monitor *that) {
	assert(that);
	WakeConditionVariable(&(that->cv));
}

void SG_NotifyAllMonitor(struct SapphireSG_Monitor *that) {
	assert(that);
	WakeAllConditionVariable(&(that->cv));
}
