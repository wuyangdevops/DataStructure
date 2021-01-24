#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
 
typedef int ElementType;
const int MAXSIZE = 1000;
 
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
 
/*栈*/
typedef int Position;
typedef struct SNode *PtrToSNode;
 
struct SNode
{
	BinTree *Data; /*存储元素的数组*/
	Position Top;      /*栈顶指针*/
	int MaxSize;		/*堆栈最大容量*/
};
typedef PtrToSNode Stack;
 
 
/*==============================栈定义=====================================*/
 
Stack CreateStack(int MaxSize) {
	/*创建堆栈*/
	Stack S = (Stack)malloc(sizeof(struct SNode));
	S->Data = (BinTree *)malloc(sizeof(MaxSize * sizeof(struct TNode)));
	S->Top = -1;
	S->MaxSize = MaxSize;
	return S;
}
 
bool IsFull(Stack S) {
	/*判断堆栈是否满*/
	return(S->Top == S->MaxSize - 1);
}
 
bool Push(Stack S, BinTree X) {
	/*入栈*/
	if (IsFull(S)) {
		printf("堆栈满");
		return false;
	}
	else {
		S->Data[++(S->Top)] = X;
		return true;
	}
}
 
bool IsEmpty(Stack S) {
	/*判断堆栈是否为空*/
	return(S->Top == -1);
}
 
BinTree Pop(Stack S) {
	/*出栈*/
	if (IsEmpty(S)) {
		printf("堆栈空");
		return NULL;
	}
	else
		return(S->Data[(S->Top)--]);
}
 
BinTree Peek(Stack S) {
	/*取栈顶元素*/
	if (IsEmpty(S)) {
		printf("堆栈空");
		return NULL;
	}
	else
		return(S->Data[S->Top]);
}
 
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
 
/*
二叉树非递归遍历
在沿左子树深入时，进入一个结点就将其压入堆栈。
若是先序遍历，则在入栈之前访问之，当沿左分支深入不下去时，则返回，即从堆栈中弹出前面压入的结点；
若为中序遍历，则此时访问该结点，然后从该结点的右子树继续深入；
若为后续遍历，则将此结点二次入栈，然后从该结点的右子树继续深入，与前面类同，仍为进入一个结点入栈
一个结点，深入不下去再返回，直到第二次从栈里弹出该结点，才访问之。
*/
 
/*二叉树前序遍历(非递归)*/
void PreorderTraversal(BinTree BT) {
	BinTree T;
	Stack S = CreateStack(MAXSIZE);
	/*从根结点出发*/
	T = BT;
	while (T||!IsEmpty(S))
	{
		/*一直向左并将沿途结点压入堆栈*/
		while (T)
		{
			printf("%d\t", T->Data);
			Push(S, T);
			T = T->Left;
		}
		/*结点弹出堆栈*/
		T = Pop(S);
		/*转向右子树*/
		T = T->Right;
	}
}
 
/*二叉树中序遍历*/
void InorderTraversal(BinTree BT) {
	BinTree T;
	/*创建空堆栈S,元素类型为BinTree*/
	Stack S = CreateStack(MAXSIZE);
	/*从根结点出发*/
	T = BT;
	while (T || !IsEmpty(S))
	{
		/*一直向左并将沿途结点压入堆栈*/
		while (T) {
			Push(S, T);
			T = T->Left;
		}
		/*结点弹出堆栈*/
		T = Pop(S);
		/*(访问)打印结点*/
		printf("%d\t", T->Data);
		/*转向右子树*/
		T = T->Right;
	}
}
 
/*二叉树后序遍历*/
void PostorderTraversal(BinTree BT) {
	BinTree T;
	Stack S = CreateStack(MAXSIZE);
	T = BT;
	/*定义存储结点被访问次数的数组*/
	ElementType flag[MAXSIZE];
	while (T || !IsEmpty(S)) {
		/*一直向走并将沿途结点压入堆栈*/
		while (T) {
			/*将访问次数标志初始化为0*/
			Push(S, T);
			flag[S->Top] = 0;
			T = T->Left;
		}
 
		while (!IsEmpty(S) && flag[S->Top] == 1)
		{
			/*当结点被两次访问时则访问*/
			T = Pop(S);
			printf("%d\t", T->Data);
		}
 
		if (!IsEmpty(S)) {
			flag[S->Top] = 1;
			T = Peek(S);
			/*向右子树深入*/
			T = T->Right;
		}
		else
			break;
	}
}
 
/*层序遍历
1. 从队列中取出一个元素；
2. 访问该元素所指结点；
3. 若该元素所指结点的左、右孩子结点非空，则将其左、右孩子的指针顺序入队
*/
 
void LevelorderTraversal(BinTree BT) {
	Queue Q;
	BinTree T;
 
	/*空树直接返回*/
	if (!BT) return;
	/*创建空队列*/
	Q = CreateQueue();
	AddQ(Q, BT);
	while (!IsEmpty(Q))
	{
		T = DeleteQ(Q);
		/*访问取出队列的结点*/
		printf("%d\t", T->Data);
		
		if (T->Left)	AddQ(Q, T->Left);
		if (T->Right)	AddQ(Q, T->Right);
	}
}
 
 
int main() {
	printf("==================创建二叉树==================\n");
	printf("*****请输入1 2 3 4 5 6 7 0 0 10 0 0 13 0 0 0 0 0 0**********\n");
	/*
							1
				2						3
			4		5				6		7
				10						13
	*/
	BinTree BT = CreateBinTree();
	printf("\n================二叉树前序遍历======================\n");
	PreorderTraversal(BT);
	printf("\n================二叉树中序遍历======================\n");
	InorderTraversal(BT);
	printf("\n================二叉树后序遍历======================\n");
	PostorderTraversal(BT);
	printf("\n================二叉树层序遍历======================\n");
	LevelorderTraversal(BT);
	return 0;
}