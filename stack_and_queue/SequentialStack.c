#include<stdio.h>
#include<stdlib.h>
#define MAXNUM 1000
#define elemtype int
typedef struct stack
{
    elemtype stack[MAXNUM];
    int top;
}stack;

stack *initial()
{
    stack*S = (stack*)malloc(sizeof(stack));
    S->top =0;
    return S;
}
int Empty_Stack(stack**S)//not empty equals 1, empty equals 0;
{
    if((*S)->top>0)
    return 1;
    if((*S)->top<0)
    exit(1);
    return 0;
}
int Destroy_Stack(stack**S)
{
    if((*S)==NULL)
    return 0;
    free(*S);
    return 1;
}
int Push(stack**S,elemtype input)
{
    if((*S)==NULL){
        *S = initial();
        printf("error: stack not existed!\n");
        Push(S,input);
        return 1;
    }
    if((*S)->top == MAXNUM){
        printf("error: full stack!\n");
        return 0;
    }
    (*S)->stack[++(*S)->top] = input;
    return 1;
}
elemtype Pop(stack**S)
{
    if((*S)==NULL){
        printf("error: stack not existed!\n");
        exit(1);
    }
    if(!Empty_Stack(S)){
        printf("error: empty stack!\n");
        exit(1);
    }
    (*S)->top--;
    return (*S)->stack[(*S)->top+1];
}
elemtype Get_Top(stack**S)
{
    if((*S)==NULL){
        printf("error: stack not existed!\n");
        exit(1);
    }
    if(!Empty_Stack(S)){
        printf("error: empty stack!\n");
        exit(1);
    }
    return (*S)->stack[(*S)->top];
}
int Clear_Stack(stack**S)
{
    if((*S)==NULL){
        printf("error: stack not existed!\n");
        return 0;
    }
    (*S)->top = 0;
    return 1;
}

int main()
{
    stack *pstack = NULL;
    elemtype data;
    pstack = initial();
    while(scanf("%d",&data))
    {
        if(Push(&pstack,data)!=1)
        break;
    }
    while(Empty_Stack(&pstack))
    {
        printf("%d ",Get_Top(&pstack));
        Pop(&pstack);
    }
    return 0;
}