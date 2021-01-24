#include<stdio.h>
#include<stdlib.h>
 
/*
队列的链式存储
队列的头(Front)必须指向链表的头结点，队列的尾(Rear)指向链表的尾结点
*/
 
typedef int ElementType;
 
ElementType ERROR = -1;
 
typedef struct Node *PtrToNode;
/*队列中的结点*/
struct Node
{
	ElementType Data;
	PtrToNode Next;
};
 
typedef PtrToNode Position;
 
/*队列*/
typedef struct QNode * PtrToQNode;
struct QNode
{
	Position Front, Rear;	/*队列的头、尾指针*/
};
 
typedef PtrToQNode Queue;
 
/*
采用链式存储的入队和出队操作实际就是在一个链表的尾部插入结点或者在头部删除结点
*/
 
bool IsEmpty(Queue Q) {
	/*判空*/
	return(Q->Front == NULL);
}
 
Queue CreateQueue() {
	Queue Q = (Queue)malloc(sizeof(struct QNode));
	Q->Front = Q->Rear = NULL;
	return Q;
}
 
bool AddQ(Queue Q, ElementType X) {
	/*入队*/
	/*申请新队列结点*/
	Position TmpCell = (Position)malloc(sizeof(struct Node));
	TmpCell->Next = NULL;
	TmpCell->Data = X;
	/*如果队列此时为空*/
	if (IsEmpty(Q)) {
		Q->Front = Q->Rear = TmpCell;
	}
	else {
		/*将结点插入到队尾*/
		Q->Rear->Next = TmpCell;
		Q->Rear = TmpCell;
	}
	return true;
}
 
ElementType DeleteQ(Queue Q) {
	/*出队*/
	Position FrontCell;
	ElementType FrontElem;
 
	if (IsEmpty(Q)) {
		printf("队列空\n");
		return ERROR;
	}
	else {
		FrontCell = Q->Front;
		/*若队列只有一个元素*/
		if (Q->Front == Q->Rear)
			/*删除后队列置为空*/
			Q->Front = Q->Rear = NULL;
		else
			Q->Front = Q->Front->Next;
		FrontElem = FrontCell->Data;
		/*释放被删除结点空间*/
		free(FrontCell);
		return FrontElem;
	}
}
 
void LinkedQueueDemo() {
	printf("============初始化队列=======================\n");
	Queue Q = CreateQueue();
	printf("============依次入队1-10=====================\n");
	for (int i = 1;i <= 10;i++)
		AddQ(Q, i);
	printf("===========依次出队10次======================\n");
	ElementType x;
	for (int j = 1;j <= 10;j++) {
		x = DeleteQ(Q);
		printf("%d\t", x);
	}
	printf("\n=============尝试继续出队========================\n");
	x = DeleteQ(Q);
}
 
 
int main() {
	LinkedQueueDemo();
	return 0;
}