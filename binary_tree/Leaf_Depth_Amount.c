#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#define elemtype int
#define MAXNUM 500
#define true 1
#define false 0
typedef struct BinaryNode{
    elemtype data;
    struct BinaryNode *Left,*Right;
}BinaryNode;

int IsEmpty(BinaryNode *node){
    if(node==NULL)
        return true;
    return false;
}
//随机创建二叉树，coef控制树的深度
void CreateTree(BinaryNode*root,int coef){
    root->data = rand()%20;
    root->Left = (BinaryNode*)malloc(sizeof(BinaryNode));
    if(!root->Left)
    {
        printf("malloc failure");
        exit(1);
    }
    root->Right = (BinaryNode*)malloc(sizeof(BinaryNode));
    if(!root->Right)
    {
        printf("malloc failure");
        exit(1);
    }
    if(rand()%coef!=0)
    CreateTree(root->Left,coef-1); 
    else {
        free(root->Left);
        root->Left =NULL;
    }
    if(rand()%coef!=0)
    CreateTree(root->Right,coef-1);  
    else {
        free(root->Right);
        root->Right =NULL;
    }
}
//前序打印二叉树
void Traverse_1(BinaryNode *root){
    if(IsEmpty(root))
        return;
    printf("%d ", root->data);
    Traverse_1(root->Left);
    Traverse_1(root->Right);
    return;
}
//查询二叉树的深度
int DepthTree(BinaryNode*root,int depth, int maxdepth){
    if(!IsEmpty(root)){
        depth++;
        if(depth>maxdepth)
        maxdepth = depth;
        maxdepth=DepthTree(root->Left,depth,maxdepth);
        maxdepth=DepthTree(root->Right,depth,maxdepth);
    }
    return maxdepth;    
}
//查询二叉树的叶子节点数目
int LeafTree(BinaryNode*root,int leaf)
{
    if(!IsEmpty(root)){
        if(root->Left==NULL&root->Right==NULL){
            leaf++;
        }
        else{
            leaf = LeafTree(root->Left,leaf);
            leaf = LeafTree(root->Right,leaf);
        }
    }
    return leaf;
}
int main()
{
    BinaryNode Root;
    int Coef=7;
    srand((unsigned)time(NULL));
    CreateTree(&Root,Coef);
    Traverse_1(&Root);
    printf("Depth:%d ",DepthTree(&Root,0,0));
    printf("leaf amount:%d",LeafTree(&Root,0));
}