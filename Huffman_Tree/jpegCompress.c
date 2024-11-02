#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#define range(x) 0<=x&&x<=7
int QTABLE[8][8]={{16,11,10,16,24,40,51,61},
                 {12,12,14,19,26,58,60,55},
                 {14,13,16,24,40,57,69,56},
                 {14,17,22,29,51,87,80,62},
                 {18,22,37,56,68,109,103,77},
                 {24,35,55,64,81,104,113,92},
                 {49,64,78,87,103,121,120,101},
                 {72,92,95,98,112,100,103,99}};

typedef struct HuffmanNode{
    int data;
    struct HuffmanNode *Left, *Right; 
}Hnode,HTree;

typedef struct listnode{
    int data;
    int count;
    struct listnode *next,*front;
    Hnode *node;
}listnode;

typedef struct boolnode{
    bool data;
    struct boolnode *next,*front;
}boolnode;

bool IsEmpty(Hnode*node){
    if(node==NULL)
    return 1;
    return 0;
}
bool IsLeaf(Hnode*node){
    if(!IsEmpty(node)&&IsEmpty(node->Left)&&IsEmpty(node->Right))
    return 1;
    return 0;
}

//矩阵运算，除以量化表
void Minus(int matrix[8][8]){
    for(int i = 0;i<8;i++){
        for(int j=0;j<8;j++){
            matrix[i][j] = matrix[i][j]/QTABLE[i][j];
        }
    }
}

//ZigZag排序
int* ZigZag(int matrix[8][8],int col){
    int*result = (int*)malloc(col*col*sizeof(int));
    int* head = result;
    int x = 0;
    int y = 0;
    for(int step=0;step<=2*(col-1);step++){
        if(step<=col-1){
            if(step%2==0){
            y = step;
            x = 0;
            for(;x<=step;y--,x++){
                *result  =  matrix[y][x];
                result ++;
                }
            }
            else{
                y = 0;
                x = step;
                for(;y<=step;x--,y++){
                    // printf("%d\n",*(matrix + col*y + x));
                    *result  = matrix[y][x];
                    result ++;
                    }
            }
        }
        else{
            if(step%2==0){
                y = col-1;
                x = step - y;
                for(;x<=col-1;x++,y--){
                    *result  =  matrix[y][x];
                    result ++;
                }
            }
            else{
                x = col-1;
                y = step - x;
                for(;y<=col-1;y++,x--){
                    *result  =  matrix[y][x];
                    result ++;
                }
            }
        }
    }
    return head;
}

//luanch huffman tree for encoding and decoding
Hnode* HuffmanCoding(int*sequence,int size){
    listnode *head = (listnode*)malloc(sizeof(listnode));
    head->next = NULL;
    listnode *ptr = NULL;
    int count = 0;
    for(int i=0;i<size;i++){
        ptr = head;
        while(ptr->next!=NULL){
            if(ptr->next->data==sequence[i]){
                ptr->next->count++;
                break;
            }
            ptr=ptr->next;
        }
        if(ptr->next==NULL){
            ptr->next = (listnode*)malloc(sizeof(listnode));
            ptr->next->front = ptr;
            ptr->next->node =NULL;
            ptr->next->data=*(sequence+i);
            ptr->next->count=1;
            ptr->next->next = NULL;
            count++;
        }
    }
    Hnode *leftleaf = NULL;
    Hnode *rightleaf =NULL;
    Hnode *root = NULL;
    listnode *min=NULL;
    int score = 0;
    for(int i=1;i<count;i++){
        score = 0;
        //找最小次数对应的值
        min = head->next;
        ptr = head->next;
        while(ptr!=NULL){
            if(ptr->count<=min->count){
                min=ptr;
            }
            ptr=ptr->next;
        }
        if(min->node==NULL){
            leftleaf = (Hnode*)malloc(sizeof(Hnode));
            leftleaf->data = min->data;
            leftleaf->Left = NULL;
            leftleaf->Right = NULL;
        }
        else{
            leftleaf = min->node;
        }
        score +=min->count;
        min->front->next = min->next;
        if(min->next!=NULL){
            min->next->front = min->front;
        }
        //记录一下为什么出错：
        //最后一次根结点重新分配空间（“操作二”）后，根结点的地址恰好为head->next->next的同地址（每次都是），
        //所以"操作一"处的ptr的操作作用于root导致root->Right->data变成乱码，导致huffman树节点保存错误
        //最后操作时的head->next->next本来应该是NULL，而这里不是，是因为

        // if(min->next!=NULL){
        //     min->front->next = min->next;
        //     min->next->front = min->front;
        // }这里是源码

        //导致min->next==NULL时，不能将min->front->next指针对准NULL
        //而接下来释放了空间,为接下来的root的重新空间分配提供了空间，导致root的新地址也是此处

        //然后在接下来的encoder程序中由于有一个数据节点保存失败，指针始终找不到它，导致异常
        free(min);
        ptr=NULL;
        min = head->next;
        ptr = head->next;
        while(ptr!=NULL){
            if(ptr->count<=min->count){
                min=ptr;
            }
            ptr=ptr->next;
        }
        if(min->node==NULL){
            rightleaf = (Hnode*)malloc(sizeof(Hnode));
            rightleaf->data = min->data;
            rightleaf->Left = NULL;
            rightleaf->Right = NULL;
        }
        else{
            rightleaf = min->node;
        }
        score+=min->count;

        min->front->next = min->next;
        if(min->next!=NULL){
            min->next->front = min->front;
        }
        free(min);
        //生成huffmanTree
        root = (Hnode*)malloc(sizeof(Hnode));//malloc会返回一个新地址
        //“操作二”
        root->Left = leftleaf;
        root->Right = rightleaf;
        ptr = (listnode*)malloc(sizeof(listnode)); 
        ptr->count = score;
        ptr->node = root;
        if(head->next!=NULL){
            ptr->next = head->next;
            ptr->next->front = ptr;//“操作1” Debug
        }
        ptr->front = head;
        head->next = ptr;     
    }   
    return (head->next->node);
}

//search the target node, and log the path
int Search(Hnode*root,int target,int leafdir,boolnode*top,int length,bool* found){
    if(*found == true){
        return length;
    }
    if(root!=NULL){
        boolnode*ptr=NULL;
        if(leafdir!=-1){
            ptr=(boolnode*)malloc(sizeof(boolnode));
            ptr->next=NULL;
            top->next = ptr;
            ptr->front = top;
            ptr->data  = leafdir;
        }
        else{
            ptr = top;
        }
        length+=1;
        length =  Search(root->Right,target,1,ptr,length,found);
        if(*found == true){
            return length;
        }
        length =  Search(root->Left,target,0,ptr,length,found);
        if(*found == true){
            return length;
        }
        if(IsLeaf(root)&&(root->data==target)){
            *found = true;
            return length;
            }
        length--;
    }
    return length;
}
//encoding, 1st step
int EncoderStep1(boolnode* start,HTree* root,int *sequence,int size){
    boolnode* bighead = start;
    boolnode *smallhead = bighead;
    int target = 0;
    int length = 0;
    bool found ;
    for(int s=0;s<size;s++){
        target = *(sequence+s);
        found = false;
        length+=Search(root,target,-1,smallhead,-1,&found);
        while(smallhead->next!=NULL){
            smallhead = smallhead->next;
        }
    }
    return length;
}
//encoding, 2nd step
bool* EncoderStep2(boolnode*start, int length){
    bool *coding = (bool*)malloc(length*sizeof(bool));
    boolnode *pointer = start;
    for(int i=0;i<length;i++){
        coding[i] = pointer->next->data;
        pointer = pointer->next;
    }
    return coding;
}
//decoding,step 1
int* Decoder(bool* coding, int length,HTree* root,int size){
    int *output = (int*)malloc(size*sizeof(int));
    Hnode *ptr = root;
    int index = 0;
    for(int i=0;i<length;i++){
        if(coding[i]==1){
            ptr = ptr->Right;
        }
        else{
            ptr = ptr->Left;
        }
        if(IsLeaf(ptr)){
            *(output+index) = ptr->data;
            index++;
            ptr = root;
        }
    }
    return output;
} 
void ZigZagBack(int matrix[8][8],int* decode,int size,int col){
    int x=0,y=0,index=0;
    for(int i=0;i<col*2-2;i++){
        if(i<=col-1){
            if(i%2==0){
                x = 0,y=i;
                while(x<=i){
                    matrix[y][x] = decode[index++];
                    x++,y--;}}
            else{
                x = i,y=0;
                while(y<=i){
                    matrix[y][x] = decode[index++];
                    x--,y++;}}}
        else{
            if(i%2==0){
                x = i-col+1,y=col-1;
                while(x<col){
                    matrix[y][x] = decode[index++];
                    y--,x++;}}
            else{
                x = col-1, y=i-col+1;
                while(y<col){
                    matrix[y][x] = decode[index++];
                    y++,x--;}}}}
}
int main(){
    int matrix1[8][8];
    int value = 64;
    for (int i = 0; i <8 ; i++) {
        for (int j = 0; j < 8; j++) {
            matrix1[i][j] = value--;
        }
    }
    Minus(matrix1);
    int* output = ZigZag(matrix1,8);
    HTree* huffmanTree = HuffmanCoding(output,64);
    for(int i=0;i<64;i++){
        printf("%d ",*(output+i));
    }
    printf("\n");
    boolnode*start=(boolnode*)malloc(sizeof(boolnode));
    start->next = NULL;
    start->front =NULL; 
    int len = EncoderStep1(start,huffmanTree,output,64);
    bool *coding = EncoderStep2(start,len);
    for(int i=0;i<len;i++){
        printf("%d",coding[i]);
    }
    printf("\n");
    int *decode = Decoder(coding,len,huffmanTree,64);
    for(int i=0;i<64;i++){
        printf("%d ",*(decode+i));
    }
    printf("\n");
    int matrix2[8][8]; 
    ZigZagBack(matrix2,decode,64,8);
    for (int i = 0; i <8 ; i++) {
        for (int j = 0; j < 8; j++) {
            printf("%d ",matrix2[i][j]);
        }
        printf("\n");
    }
    free(decode);
    return 0;
}