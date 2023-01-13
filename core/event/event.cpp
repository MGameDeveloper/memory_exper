#include "event.h"
#include "../../common.h"

static Queue* event_queue = nullptr;
static Array* keysdetail  = nullptr;

extern bool event_init()
{
	event_queue = queue_create("queue_eventqueue", 64, sizeof(event_key));
	keysdetail  = array_create("array_keydetail", 256, sizeof(key_detail));

	if (!event_queue || !keysdetail)
		return false;

	return true;
}

extern void event_add(event_key* in_event)
{
	// if event_queue is nullptr probably you didn't call event_init() to initialize 
	// working buffers

	if (!in_event)
		return;

	key_detail* kd = (key_detail*)array_get(keysdetail, in_event->key);

	if (!kd)
		return;

	kd->state      = in_event->state;
	kd->timestamp  = in_event->timestamp;

	queue_add(event_queue, in_event);
}

extern event_key* event_get()
{
	return (event_key*)queue_get(event_queue);
}