#include<stdio.h>
#include<stdlib.h>
/*
typedef struct LNode *list表示定义了一个别名list，
list代表 struct LNode *类型的别名，它是一个指针类型。
list a，就代表定义了一个struct LNode *类型的变量a。
*/
typedef int ElementType; // 给int取一个别名ElementType 
typedef struct LNode *List;
#define MAXSIZE 100
struct LNode
{
    ElementType Data[MAXSIZE];
    int Last;
};
/*
而struct LNode代表一个结构体类型。
struct LNode a代表定义了struct LNode类型的变量a。
*/
// struct LNode L;
// List PtrL;

//初始化(建立空的顺序表)
List MakeEmpty(){
    List PtrL;
    PtrL = (List)malloc(sizeof(struct LNode));
    // Last代表最后一个元素，-1代表表中没有元素
    PtrL->Last = -1;
    return PtrL;
}

// 查找
// 平均查找次数为(n+1)/2,时间复杂度O(n)
int Find(ElementType X, List PtrL){
    int i = 0;
    while (i<=PtrL->Last && PtrL->Data[i]!=X)
        i++;
    if(i > PtrL->Last)
        return -1;
        /*如果没找到返回-1*/
    else
        return i;
}

// 插入，平均移动次数n/2，时间复杂度O(n)
// 在第i个位置(1<=i<=n+1)上插入一个值为X的新元素
void Insert(ElementType X, int i, List PtrL){
    // 首先检查表是否满了
    if(PtrL->Last == MAXSIZE-1)
    {   printf("表满");
        return;
    }
    // 其次检查插入位置的合法性
    if(i < 1 || i > PtrL->Last + 2){
        printf("插入位置不合法");
        return;
    }
    // 完成上述检查后，将线性表中元素从按照从后向前的顺序依次往后挪动一个单位
    for(int j=PtrL->Last; j>=i-1;j--){
        PtrL->Data[j+1] = PtrL->Data[j]; 
    }
    PtrL->Data[i-1] = X;
    PtrL->Last++;
    return;
}

// 删除，平均移动(n-1)/2个元素，时间复杂度O(n)
// 删除表的第i(1<=i<=n)个位置上的元素
void Delete(int i, List PtrL){
    // 首先判断删除位置合法性
    if(i<1 || i>PtrL->Last+1){
        printf("不存在第%d个元素",i);
        return;
    }
    // 判断删除操作合法后，以从左向右的顺序，依次向前移动一个元素
    for(int j=i;j<=PtrL->Last;j++)
        PtrL->Data[j-1] = PtrL->Data[j];
    PtrL->Last--;
    return;
}

// 测试打印
void testPrint(List Ptrl){
    printf("===============\n");
    for(int i=0; i<=Ptrl->Last;i++)
        printf("The No.%d Element is %d\n",i+1,Ptrl->Data[i]);
}

// 测试
int main(){
    // 1. 新建一个空表
    List MyList = MakeEmpty();
    // 2. 在空表的第一个位置插入1
    Insert(1, 1, MyList);
    testPrint(MyList);
    // 3. 在空表的第二个位置插入3
    Insert(3, 2, MyList);
    testPrint(MyList);
    // 4. 在空表的第二个位置插入2
    Insert(2, 2, MyList);
    testPrint(MyList);
    // 5. 查找元素2的下标
    int pos = Find(2, MyList);
    printf("Elemet 2 index is %d\n", pos);
    // 6. 删除第1个元素
    Delete(1, MyList);
    testPrint(MyList);
    system("pause");
    return 0;
}