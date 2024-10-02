#include<stdlib.h>
#include<stdio.h>
#define elemtype int
#define MAXNUM 1000
typedef struct indicator
{
    int front;
    int rear;
}indicator;
typedef struct CircularQueue
{
    elemtype data[MAXNUM];
    int total ;
    indicator ind;
}CircularQueue;
CircularQueue*InitQueue()
{
    CircularQueue*CQueue = (CircularQueue*)malloc(sizeof(CircularQueue));
    if(!CQueue)
    {
        printf("error: malloc failed!");
        exit(1);
    }
    CQueue->ind.front=0;
    CQueue->ind.rear=0;
    CQueue->total =0;
    return CQueue;
}
int EmptyQueue(CircularQueue*Cqueue)
{
    if(Cqueue->ind.front ==Cqueue->ind.rear)
    return 0;
    return 1;
}
int Destroy_Queue(CircularQueue*Cqueue)
{
    if(Cqueue!=NULL)
    free(Cqueue);
    return 1;
}
int Clear_Queue(CircularQueue*Cqueue)
{
    if(Cqueue==NULL)
        {printf("error: Cqueue not existed!");
         return 0;
        }
    if(EmptyQueue(Cqueue))
    {
        Cqueue->ind.front=Cqueue->ind.rear;
        Cqueue->total=0;
    }
    return 1;
}
int Push(CircularQueue*Cqueue,elemtype data)
{
    if(!Cqueue)
    {
        printf("error: queue not existed!");
        return 0;
    }
    if(Cqueue->total==MAXNUM)
        {
            printf("error: full queue!");
            return 0;
        }
    Cqueue->data[Cqueue->ind.rear]=data;
    Cqueue->ind.rear++;
    Cqueue->ind.rear = Cqueue->ind.rear %MAXNUM;
    Cqueue->total++;
    return 1;
}
int Pop(CircularQueue*Cqueue)
{
    if(!Cqueue)
    {
        printf("error: queue not existed!");
        return 0;
    }
    if(!EmptyQueue(Cqueue))
    {
        printf("error: empty queue!");
        return 0;
    }
    Cqueue->ind.front++;
    Cqueue->total--;
    return 1;   
}
elemtype GetTop(CircularQueue*Cqueue)
{
    if(!Cqueue)
    {
        printf("error: queue not existed!");
        return 0;
    }
        if(!EmptyQueue(Cqueue))
    {
        printf("error: empty queue!");
        return 0;
    }
    return Cqueue->data[Cqueue->ind.front];
}
int main()
{
    CircularQueue*cqueue = InitQueue();
    elemtype x;
    while(scanf("%d",&x))
    {
        Push(cqueue,x);
    }
    while(EmptyQueue(cqueue))
    {
        printf("%d ",GetTop(cqueue));
        Pop(cqueue);
    }
    return 0;
}