#include "thread.h"
#include "monitor.h"
#include "group.h"
#include <stdbool.h>
#include <assert.h>

#define QUEUE_ELEMENT_SIZE 0xFF

typedef struct SapphireSG_Group *SapphireSG_Group_p;

struct SapphireSG_Queue {
	unsigned len, index;
	SapphireSG_Group_p groups[QUEUE_ELEMENT_SIZE];
	struct SapphireSG_Queue *next;
};

struct SapphireSG_ThreadKit {

	struct SapphireSG_Context *ctx;
	struct SapphireSG_Queue queues[3];
	struct SapphireSG_Monitor *monitor;

	unsigned take_queue, put_queue;
	bool alive;

};

#define SAPPHIRESG_VALIDATE_KIT(KIT_)\
	assert(KIT_);\
	assert(KIT_->take_queue != KIT_->put_queue);\
	assert(KIT_->take_queue < 3);\
	assert(KIT_->put_queue < 3)

#define SAPPHIERSG_SWAP_QUEUE(KIT_, CHANGE_)\
do{\
	SG_LockMonitor(KIT_->monitor);\
	SAPPHIRESG_VALIDATE_KIT(KIT_);\
	KIT_->CHANGE_ = 3 - (KIT_->take_queue + KIT_->put_queue);\
	SAPPHIRESG_VALIDATE_KIT(KIT_);\
	SG_UnlockMonitor(KIT_->monitor);\
	SG_NotifyMonitor(KIT_->monitor);\
}while(0)

struct SapphireSG_ThreadKit *SG_CreateThreadKit(struct SapphireSG_Context *ctx) {
	struct SapphireSG_ThreadKit *const kit = calloc(sizeof(struct SapphireSG_ThreadKit), 1);
	assert(kit);

	kit->monitor = SG_CreateMonitor();
	assert(kit->monitor);

	kit->ctx = ctx;
	kit->take_queue = 0;
	kit->put_queue = 1;

	return kit;
}

void SG_RunRenderer(struct SapphireSG_ThreadKit *kit,
	void(*set_context)(void *arg), void *arg) {

	/* Start up (or switch to, or whatever) to a graphics context */
	if(set_context)
		set_context(arg);

start_queue:
	{
		struct SapphireSG_Queue *const base_queue = SG_GetNextTakeQueue(kit),
			*queue = base_queue;
		struct SapphireSG_Group *group;

		/* We only check for liveliness if we hit an empty queue. */
		if (base_queue->len == 0) {
			bool alive;
			SG_LockMonitor(kit->monitor);
			alive = kit->alive;
			SG_UnlockMonitor(kit->monitor);

			if (!alive)
				return;
		}

start_group:

		/* An empty group indicates the end of the queue element. */
		if ( ( group = SG_TakeGroupFromQueue(kit, &queue) ) ) {
			SG_DrawGroup(kit->ctx, group);
			goto start_group;
		}
		else {

			/* If we hit an empty element that was not the base queue, start 
			 * up from the base again. Otherwise, we hit an empty base queue,
			 * which means the end of a scene.
			 */
			if (queue != base_queue) {
				queue = base_queue;
				goto start_group;
			}
		}
	}

	goto start_queue;

}

struct SapphireSG_Queue *SG_GetNextTakeQueue(struct SapphireSG_ThreadKit*kit){

	SAPPHIERSG_SWAP_QUEUE(kit, take_queue);

	return kit->queues + kit->take_queue;

}

struct SapphireSG_Queue *SG_GetNextPutQueue(struct SapphireSG_ThreadKit *kit) {

	SAPPHIERSG_SWAP_QUEUE(kit, put_queue);

	return kit->queues + kit->put_queue;
}

void SG_PutGroup(struct SapphireSG_ThreadKit *kit,
	struct SapphireSG_Group *group) {

	struct SapphireSG_Queue *queue = kit->queues + kit->put_queue;

	while (queue->len == QUEUE_ELEMENT_SIZE) {
		if (queue->next == NULL)
			queue->next = calloc(sizeof(struct SapphireSG_Queue), 1);
		queue = queue->next;
	}

	assert(queue->len < QUEUE_ELEMENT_SIZE);

	queue->groups[queue->len++] = group;
}

struct SapphireSG_Group *SG_TakeGroup(struct SapphireSG_ThreadKit *kit) {
	struct SapphireSG_Queue *queue = kit->queues + kit->take_queue;
	return SG_TakeGroupFromQueue(kit, &queue);
}

struct SapphireSG_Group *SG_TakeGroupFromQueue(
	struct SapphireSG_ThreadKit *kit, struct SapphireSG_Queue **x_queue) {

	struct SapphireSG_Queue *queue = *x_queue;

	if (queue->len == 0)
		return NULL;

	while (queue->next && queue->next->len)
		queue = queue->next;
	
	assert(queue->len);

	queue->len--;
	x_queue[0] = queue;
	return queue->groups[queue->len];
}

void SG_ClearQueue(struct SapphireSG_ThreadKit *kit, unsigned q) {
	struct SapphireSG_Queue *queue = kit->queues + q;
	do {
		queue->len = 0;
		queue = queue->next;
	}while(queue);
}

void SG_ShrinkQueue(struct SapphireSG_ThreadKit *kit, unsigned q) {
	struct SapphireSG_Queue *queue = kit->queues + q;
	do {
		struct SapphireSG_Queue *const next = queue->next;
		free(queue);
		queue = next;
	} while (queue);
}
