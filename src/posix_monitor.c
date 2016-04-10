#include "monitor.h"

#include <assert.h>

struct SapphireSG_Monitor {
	pthread_mutex_t mutex;
	pthread_cond_t  cv;
};

struct SapphireSG_Monitor *SG_CreateMonitor() {
	int err = 0;
	struct SapphireSG_Monitor *const that = malloc(sizeof(struct SapphireSG_Monitor));
	pthread_condattr_t cv_attr;
	pthread_mutexattr_t mx_attr;

	err = pthread_condattr_init(&cv_attr);
	assert(err == 0);
	err = pthread_mutexattr_init(&mx_attr);
	assert(err == 0);

	err = pthread_cond_init(&(that->cv), &cv_attr);
	assert(err == 0);

	err = pthread_mutex_init(&(that->mutex), &mx_attr);
	assert(err == 0);

	err = pthread_condattr_destroy(&cv_attr);
	assert(err == 0);
	err = pthread_mutexattr_destroy(&mx_attr);
	assert(err == 0);

	return that;

}

void SG_DestroyMonitor(struct SapphireSG_Monitor *that) {
	int err;

	err = pthread_cond_destroy(&(that->cv));
	assert(err == 0);

	err = pthread_mutex_destroy(&(that->mutex));
	assert(err == 0);

	free(that);
}

void SG_LockMonitor(struct SapphireSG_Monitor *that) {
	pthread_mutex_lock(&(that->mutex));
}

void SG_UnlockMonitor(struct SapphireSG_Monitor *that) {
	pthread_mutex_unlock(&(that->mutex));
}

void SG_WaitMonitor(struct SapphireSG_Monitor *that) {
	int err = pthread_cond_wait(&(that->cv), &(that->mutex));
	assert(err == 0);
}

void SG_NotifyMonitor(struct SapphireSG_Monitor *that) {
	int err = pthread_cond_signal(&(that->cv));
	assert(err == 0);
}

void SG_NotifyAllMonitor(struct SapphireSG_Monitor *that) {
	int err = pthread_cond_broadcast(&(that->cv));
	assert(err == 0);
}