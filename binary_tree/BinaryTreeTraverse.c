#include<stdlib.h>
#include<stdio.h>
#define elemtype int
#define MAXNUM 500
#define true 1
#define false 0
typedef struct BinaryNode{
    elemtype data;
    struct BinaryNode *Left,*Right;
}BinaryNode;

typedef struct BinaryNodeStack{
    BinaryNode*data[MAXNUM];
    int top;
}BNStack;

typedef struct BinaryNodeQueue{
    BinaryNode*data[MAXNUM];
    int front,rear;
}BNQueue;

elemtype Visit(BinaryNode *node){
    printf("%d ",node->data);
    return node->data;
}

int IsEmpty(BinaryNode *node){
    if(node==NULL)
        return true;
    return false;
}
//recursion traverse of binary tree
void Traverse_1(BinaryNode *root){
    if(IsEmpty(root))
        return;
    Visit(root);
    Traverse_1(root->Left);
    Traverse_1(root->Right);
    return;
}
//stack traverse , controlling MAXNUM, here is no stack overflow detection
void Traverse_2(BinaryNode *root){
    if(IsEmpty(root))
        return;
    BNStack stack;
    BinaryNode*temp;
    stack.top=0;
    stack.data[stack.top] = root;
    while(stack.top>=0){
        temp = stack.data[stack.top];
        stack.top -- ;
        Visit(temp);
        if(!IsEmpty(temp->Right)){
            stack.top++;
            stack.data[stack.top] = temp->Right;
        }
        if(!IsEmpty(temp->Left)){
            stack.top++;
            stack.data[stack.top] = temp->Left;
        }
    }
}
//queue traverse of binary tree, no overflow detection
void Traverse_3(BinaryNode*root){
    if(IsEmpty(root))
        return;
    BNQueue queue;
    queue.front=0;
    queue.rear =0;
    queue.data[queue.rear]=root;
    queue.rear++;
    while(queue.front!=queue.rear){
        Visit(queue.data[queue.front]);
        if(!IsEmpty(queue.data[queue.front]->Left)){
            queue.data[queue.rear] = queue.data[queue.front]->Left;
            queue.rear++;
            queue.rear = queue.rear%MAXNUM;
        }
        if(!IsEmpty(queue.data[queue.front]->Right)){
            queue.data[queue.rear] = queue.data[queue.front]->Right;
            queue.rear++;
            queue.rear = queue.rear%MAXNUM;
        }
        queue.front++;
        queue.front = queue.front%MAXNUM;
    }
}

// void CreateTree(BinaryNode**root){
//     root = (BinaryNode*)malloc(sizeof(BinaryNode));
//     if(!root){
//         printf("Create Failure: malloc error");
//     }
    
// }

int main()
{
    BinaryNode node[10];
    for(int i = 0;i<=9;i++)
    {
        node[i].Left =NULL;
        node[i].Right =NULL;
    }
    node[0].data = 1;
    node[0].Left = &node[3];
    node[0].Right = &node[9];
    node[3].data = 3;
    node[9].data = 8;
    node[3].Left = &node[5];
    node[3].Right = &node[4];
    node[9].Left = &node[6];
    node[4].data = 2;
    node[5].data = 5;
    node[6].data = 10;
    node[6].Left = &node[2];
    node[2].data = 0;
    node[6].Right = &node[7];
    node[7].data = 7;
    node[5].Left = &node[1];
    node[1].data =24;
    node[5].Right = &node[8];
    node[8].data = 12;
    Traverse_1(node);
    printf("\n");
    Traverse_2(node);
    printf("\n");
    Traverse_3(node);
    return 0;
}