#include<stdio.h>
#include<stdlib.h>
typedef int ElementType;
typedef struct LNode *List;
struct LNode{
    ElementType Data;
    List Next;
};
// struct LNode L;
// List PtrL;

//1. 求表长 O(n)
int getLen(List PtrL){
    /*p指向链表第一个节点*/
    List p = PtrL;
    int j = 0;
    while(p){
        p = p->Next;
        j++;
    }
    return j;
}

//2. 查找
//2.1 按序号查找 - 时间复杂度O(n)
List FindKth(int K, List PtrL){
    List p = PtrL;
    int i = 1;
    while(p!=NULL && i<K){
        p = p->Next;
        i++;
    }
    if(i==K){
        /*找到第K个节点，返回指针*/
        return p;
    }
    else
    {
        return NULL;
    }
}
//2.2按值查找 - 时间复杂度O(n)
List FindXElement(ElementType X, List Ptrl){
    List p = Ptrl;
    while(p!=NULL && p->Data!=X){
        p = p->Next;
    }
    return p;
}

//3. 插入 在第i(1<=i<=n+1)个节点前插入一个值为X的新结点
// 平均查找次数n/2，时间复杂度O(n)
List Insert(ElementType X, int i, List Ptrl){
    List p,s;
    /*如果插入节点在表头*/
    if(i == 1){
        /*申请节点*/
        s = (List)malloc(sizeof(struct LNode));
        s->Data = X;
        s->Next = Ptrl;
        return s;
    }
    /*查找到第i-1个节点*/
    p = FindKth(i-1, Ptrl);
    /*如果第i-1个节点不存在，则无法插入*/
    if(p==NULL){
        printf("Error!");
        return NULL;
    }else
    {
        s = (List)malloc(sizeof(struct LNode));
        s->Data = X;
        /*新节点插入到第i-1个节点后面*/
        s->Next = p->Next;
        p->Next = s;
        return Ptrl;
    }}


//4. 删除第i(1<=i<=n)个位置上的节点
// 平均查找次数n/2，时间复杂度O(n)
List Delete(int i, List Ptrl){
    List p, s;
    if(i == 1){
        s = Ptrl;
        if(Ptrl!=NULL){
            Ptrl = Ptrl->Next;
        }else
        {
            return NULL;
        }
        free(s);
        return Ptrl;
    }
    /*查找第i-1个节点*/
    p = FindKth(i-1, Ptrl);
    if(p==NULL){
        printf("No %d Node does not exists\n", i-1);
        return NULL;
    }
    else if(p->Next == NULL){
        printf("No %d Node does not exits\n", i);
        return NULL;
    }
    else
    {
        s = p->Next;
        p->Next = s->Next;
        free(s);
        return Ptrl;
    }
}

void testPrint(List Ptrl){
    List p;
    p = Ptrl;
    printf("====================\n");
    int i = 1;
    while (p!=NULL)
    {
        printf("No %d Element is %d\n",i,p->Data);
        p = p->Next;
        i++;
    }
}

void printData(List Ptrl){
    if(Ptrl == NULL){
        printf("data is NULL");
    }
    else
    {
        printf("data is %d", Ptrl->Data);
    }
    
}

void testLinkedList(){
    //测试链表
    List p2, Ptrl;
    Ptrl = (List)malloc(sizeof(struct LNode));
    Ptrl->Data = 0;
    Ptrl->Next=NULL;
    //1. 在链表的第一个节点前插入元素1
    Ptrl = Insert(1, 1, Ptrl);
    testPrint(Ptrl);
    //2. 在链表的第一个节点前插入元素2
    Ptrl = Insert(2, 1, Ptrl);
    testPrint(Ptrl);
    //3. 在链表的第二个节点前插入元素3
    Ptrl = Insert(3, 2, Ptrl);
    testPrint(Ptrl);
    //4. 删除第2个节点
    Ptrl = Delete(2, Ptrl);
    testPrint(Ptrl);
    //5. 查找第2个节点
    p2 = FindKth(2, Ptrl);
    printData(p2);
}

int main(){
    testLinkedList();
    system("pause");
    return 0;
}