#include<stdlib.h>
#include<stdio.h>
#define elemtype int
typedef struct StackNode
{
    elemtype data;
    struct StackNode*next;
}StackNode;
typedef struct ChainStack
{
    StackNode*top;
    int total;//total num of elements
}ChainStack;
ChainStack* InitCStack()//launch new ChainStack
{
    ChainStack*CStack = (ChainStack*)malloc(sizeof(ChainStack));
    if(CStack==NULL)
    {
        printf("error: memory not enough");
        exit(1);
    }
    CStack->top=NULL;
    CStack->total=0;
    return CStack;
}
int EmptyStack(ChainStack*CS) //empty means 0, else means 1;
{
    if (CS->top==NULL)
    return 0;
    return 1;
}
int Clear_Stack(ChainStack*CStack)//clear ChainStack
{
    if(CStack==NULL)
    {
        printf("error: stack not existed!");
        exit(1);
    }
    if(EmptyStack(CStack))
        return 1;
    StackNode*delete =NULL;
    while(CStack!=NULL)
    {
        delete = CStack->top;
        CStack->top =CStack->top->next;
        free(delete);
        CStack->total--;
    }
    return 1;
}
int Destroy_Stack(ChainStack*CStack)//totally release the memory of ChainStack
{
    Clear_Stack(CStack);
    free(CStack);
    return 1;
}
int Push(ChainStack*CStack,elemtype elem)
{
    StackNode*newnode = (StackNode*)malloc(sizeof(StackNode));
    if(!newnode)
    {
        printf("error: memory not enough!");
        exit(1);
    }
    newnode->data = elem;
    newnode->next = CStack->top;
    CStack->top = newnode;
    CStack->total++;
    return 1;
}
int Pop(ChainStack*CStack)
{
    if(!EmptyStack(CStack))
    {
        printf("error: empty stack!");
        return 0;
    }
    StackNode*delete = CStack->top;
    CStack->top = CStack->top->next;
    free(delete);
    CStack->total--;
    return 1;
}
elemtype GetTop(ChainStack*CStack)
{
    return CStack->top->data;
}
int main()
{
    ChainStack*CStack = InitCStack();
    elemtype elem;
    while(scanf("%d",&elem))
    {
        Push(CStack,elem);
    }
    printf("stack length:%d\n",CStack->total);
    while(EmptyStack(CStack))
    {
        printf("%d ",GetTop(CStack));
        Pop(CStack);
    }
    return 0;
}