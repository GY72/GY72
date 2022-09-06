#ifndef  _QUEUE_H_
#define  _QUEUE_H_



/*******************************/
/* @brief  队列中每个元素的类型
/*******************************/
typedef struct {
    u8  cmd_pos;        //命令，字模空间
    u8  *str;      
    u8  len;            //图标个数
    u8  w;
    u8  h;
    u8  x;
    u8  y;
}ZM_MSG_t;

#define Queue_EleType ZM_MSG_t
#define Queue_LEN   32

typedef struct 
{
    u8 front;
    u8 rear;
    u8 length;
    Queue_EleType *dat;
}CQueue_t;

void init_cqueue(CQueue_t * queue, Queue_EleType * buf, u8 len);
bool inQueue(CQueue_t * queue, Queue_EleType value);
bool outQueue(CQueue_t * queue, Queue_EleType *p_value);
bool queueIsEmpty(CQueue_t * queue);
bool queueIsFull(CQueue_t * queue);
size_t getQueueLength(CQueue_t * queue);




#endif


