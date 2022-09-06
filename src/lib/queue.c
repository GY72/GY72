

#include "..\include_s.h"

void init_cqueue(CQueue_t * queue, Queue_EleType * buf, u8 len)
{
    queue->dat     = buf;
    queue->front   = 0;
    queue->rear    = 0;
    queue->length  = len;   
}

bool queueIsEmpty(CQueue_t * queue)
{
    return (queue->rear == queue->front);
}

bool queueIsFull(CQueue_t * queue)
{
    return ((queue->rear + 1) % (queue->length) == queue->front);
}

size_t getQueueLength(CQueue_t * queue)
{
    return ((queue->rear) - (queue->front) + (queue->length)) % (queue->length);
}

bool inQueue(CQueue_t * queue, Queue_EleType value)
{
    if (queueIsFull(queue))
    {
        return false;
    }

    queue->dat[queue->rear] = value;
    queue->rear = (queue->rear + 1) % (queue->length);        //

    return true;
}

bool outQueue(CQueue_t * queue, Queue_EleType *p_value)
{
    if (queueIsEmpty(queue))
    {
        return false;
    }

    *p_value = queue->dat[queue->front];
    queue->front = (queue->front + 1) % (queue->length);

    return true;
}









