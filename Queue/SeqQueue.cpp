#include<stdio.h>
#include<stdlib.h>
 
/*
队列的顺序存储（循环队列）
方法：少用一个元素空间。
*/
 
typedef int ElementType;
typedef int Position;
typedef struct QNode * PtrToNode;
 
struct QNode
{
	ElementType * Data;		/*存储元素的数组*/
	Position Front, Rear;		/*队列的头、尾指针*/
	int MaxSize;		/*队列的最大容量*/
};
 
typedef PtrToNode Queue;
ElementType ERROR = -1;
 
Queue CreateQueue(int MaxSize) {
	/*创建队列*/
	Queue Q = (Queue)malloc(sizeof(struct QNode));
	Q->Data = (ElementType *)malloc(MaxSize * sizeof(ElementType));
	Q->Front = Q->Rear = 0;
	Q->MaxSize = MaxSize;
	return Q;
}
 
bool IsFull(Queue Q) {
	/*判断队列是否满
	队列满：队尾指针+1就会从后面赶上队头指针
	*/
	return((Q->Rear + 1) % Q->MaxSize == Q->Front);
}
 
bool AddQ(Queue Q, ElementType X) {
	/*
	入队
	*/
	if (IsFull(Q)) {
		printf("队列满\n");
		return false;
	}
	else {
		Q->Rear = (Q->Rear + 1) % Q->MaxSize;
		Q->Data[Q->Rear] = X;
		return true;
	}
}
 
bool IsEmpty(Queue Q) {
	/*
	判断队列是否空
	*/
	return(Q->Front == Q->Rear);
}
 
ElementType DeleteQ(Queue Q) {
	/*出队*/
	if (IsEmpty(Q)) {
		printf("队列空\n");
		return ERROR;
	}
	else {
		Q->Front = (Q->Front + 1) % Q->MaxSize;
		return Q->Data[Q->Front];
	}
}
 
void SeqQueueDemo() {
	printf("===========初始化最大长度为11的队列=============\n");
	Queue Q = CreateQueue(11);
	printf("==========依次向队列加入1-10================\n");
	for (int i = 1;i <= 10;i++)
		AddQ(Q, i);
	printf("==========尝试继续向队列加入11================\n");
	AddQ(Q, 11);
	printf("==========依次从队列取出10个数据================\n");
	for (int j = 1;j <= 10;j++) {
		ElementType tmp = DeleteQ(Q);
		printf("%d\t", tmp);
	}
	printf("\n===========尝试继续取一个数据===================\n");
	ElementType x = DeleteQ(Q);
}
 
int main() {
	SeqQueueDemo();
	return 0;
}