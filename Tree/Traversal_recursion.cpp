#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
 
typedef int ElementType;
 
ElementType NoInfo = 0;		/*用0表示没有结点*/
 
/*============================结构体===========================================*/
/*
二叉树最常用的表示方法是用链表表示，每个结点由数据和左右指针三个数据成员组成
*/
 
typedef struct TNode * TPosition;
/*二叉树类型*/
typedef TPosition BinTree;
/*树结点定义*/
struct TNode
{
	ElementType Data;	/*结点数据*/
	BinTree Left;	/*指向左子树*/
	BinTree Right;	/*指向右子树*/
};
 
typedef struct Node *PtrToNode;
/*队列中的结点*/
struct Node
{
	BinTree Data;
	PtrToNode Next;
};
 
typedef PtrToNode QPosition;
 
/*队列*/
typedef struct QNode * PtrToQNode;
struct QNode
{
	QPosition Front, Rear;	/*队列的头、尾指针*/
};
 
typedef PtrToQNode Queue;
 
/*=========================================队列定义=========================================*/
 
bool IsEmpty(Queue Q) {
	/*判空*/
	return(Q->Front == NULL);
}
 
Queue CreateQueue() {
	Queue Q = (Queue)malloc(sizeof(struct QNode));
	Q->Front = Q->Rear = NULL;
	return Q;
}
 
bool AddQ(Queue Q, BinTree X) {
	/*入队*/
	/*申请新队列结点*/
	QPosition TmpCell = (QPosition)malloc(sizeof(struct Node));
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
 
 
BinTree DeleteQ(Queue Q) {
	/*出队*/
	QPosition FrontCell;
	BinTree FrontElem;
 
	if (IsEmpty(Q)) {
		printf("队列空\n");
		return NULL;
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
 
 
/*======================================二叉树=================================================*/
/*二叉树层序生成算法*/
BinTree CreateBinTree() {
	ElementType Data;
	BinTree BT, T;
	/*创建空队列*/
	Queue Q = CreateQueue();
 
	/*建立第一个结点，即根结点*/
	scanf("%d", &Data);
	if (Data != NoInfo) {
		/*分配根结点单元，并将结点地址入队*/
		BT = (BinTree)malloc(sizeof(struct TNode));
		BT->Data = Data;
		BT->Left = BT->Right = NULL;
		AddQ(Q, BT);
	}
	else
		/*若第一个数据就是0，返回空树*/
		return NULL;
	while (!IsEmpty(Q))
	{
		/*从队列中取出一结点地址*/
		T = DeleteQ(Q);
		/*读入T的左孩子*/
		scanf("%d", &Data);
		if (Data == NoInfo)
			T->Left = NULL;
		else {
			/*分配新结点，作为出队结点的左孩子；新结点入队*/
			T->Left = (BinTree)malloc(sizeof(struct TNode));
			T->Left->Data = Data;
			T->Left->Left = T->Left->Right = NULL;
			AddQ(Q, T->Left);
		}
		/*读入T的右孩子*/
		scanf("%d", &Data);
		if (Data == NoInfo)
			T->Right = NULL;
		else
		{
			/*分配新结点，作为出队结点右孩子，新结点入队*/
			T->Right = (BinTree)malloc(sizeof(struct TNode));
			T->Right->Data = Data;
			T->Right->Left = T->Right->Right = NULL;
			AddQ(Q, T->Right);
		}
	}/*结束while*/
	return BT;
}
 
/*二叉树前序遍历*/
void PreorderTraversal(BinTree BT) {
	if (BT) {
		printf("%d\t", BT->Data);
		PreorderTraversal(BT->Left);
		PreorderTraversal(BT->Right);
	}
}
 
/*二叉树中序遍历*/
void InorderTraversal(BinTree BT) {
	if (BT) {
		InorderTraversal(BT->Left);
		printf("%d\t", BT->Data);
		InorderTraversal(BT->Right);
	}
}
 
/*二叉树后序遍历*/
void PostorderTraversal(BinTree BT) {
	if (BT) {
		PostorderTraversal(BT->Left);
		PostorderTraversal(BT->Right);
		printf("%d\t", BT->Data);
	}
}
 
 
int main() {
	printf("==================创建二叉树==================\n");
	printf("*****请输入1 2 3 4 5 6 7 0 0 10 0 0 13 0 0 0 0 0 0**********\n");
	BinTree BT = CreateBinTree();
	printf("\n================二叉树前序遍历======================\n");
	PreorderTraversal(BT);
	printf("\n================二叉树中序遍历======================\n");
	InorderTraversal(BT);
	printf("\n================二叉树后序遍历======================\n");
	PostorderTraversal(BT);
	return 0;
}