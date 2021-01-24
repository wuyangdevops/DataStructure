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
 
/*====================二叉搜索树===========================
二叉搜索树(BST)也叫做二叉排序树或二叉查找树。
1. 非空左子树的所有键值小于其根结点的键值
2. 非空右子树的所有键值大于其根结点的键值
3. 左、右子树都是二叉搜索树
二叉搜索树的动态查找
*/
 
TPosition Find_recur(BinTree BST, ElementType X) {
	/*递归*/
	if (!BST)	return NULL;	/*查找失败*/
	if (X > BST->Data) {
		/*在右子树中递归查找*/
		return Find_recur(BST->Right, X);
	}
	else if (X < BST->Data) {
		/*在左子树中递归查找*/
		return Find_recur(BST->Left, X);
	}
	else {
		/*在当前结点查找成功，返回当前结点的地址*/
		return BST;
	}
}
 
TPosition Find_non_recur(BinTree BST, ElementType X) {
	/*非递归-迭代查找*/
	while (BST)
	{
		if (X > BST->Data) {
			/*向右子树中移动，继续查找*/
			BST = BST->Right;
		}
		else if (X < BST->Data) {
			/*向左子树中移动，继续查找*/
			BST = BST->Left;
		}
		else
		{
			/*在当前结点查找成功，跳出循环*/
			break;
		}
	}
	return BST;
}
 
TPosition FindMin_cur(BinTree BST) {
	/*
	递归查找最小元素
	最小元素在最左端点
	*/
	if (!BST) return NULL;	/* 空的BST，返回NULL */
	else if (!BST->Left)	return BST;	/*找到最左端点并返回*/
	else return FindMin_cur(BST->Left);	/* 沿左分支递归查找 */
}
 
TPosition FindMin_non_cur(BinTree BST) {
	/*
	迭代查找最小元素
	*/
	if(BST) {
		while (BST->Left)
			BST = BST->Left; /* 沿左分支一直向下，直到最左端结点 */
	}
	return BST;
}
 
TPosition FindMax_cur(BinTree BST) {
	/* 递归查找最大元素 */
	if(!BST) return NULL;
	else if (!BST->Right) return BST;
	else return FindMax_cur(BST->Right);
}
 
TPosition FindMax_non_cur(BinTree BST) {
	/* 迭代查找最大元素 */
	if (BST) {
		while (BST->Right)
			BST = BST->Right;
	}
	return BST;
}
 
 
/*==============二叉搜索树的插入=================*/
BinTree Insert(BinTree BST, ElementType X) {
	if (!BST) { /* 若原树为空，生成并返回一个结点的二叉搜索树 */
		BST = (BinTree)malloc(sizeof(struct TNode));
		BST->Data = X;
		BST->Left = BST->Right = NULL;
	}
	else { /* 开始找要插入元素的值 */
		if (X < BST->Data)
			BST->Left = Insert(BST->Left, X);	/* 递归插入左子树 */
		else if (X > BST->Data)
			BST->Right = Insert(BST->Right, X);	/* 递归插入右子树 */
		/* else X已经存在，什么都不做 */
	}
	return BST;
}
 
void InorderTraversal(BinTree BST) {
	if (BST) {
		InorderTraversal(BST->Left);
		printf("%d\t", BST->Data);
		InorderTraversal(BST->Right);
	}
}
 
/*
二叉搜索树的删除
(1) 要删除的是叶结点；
(2) 如果要删除的结点只有一个孩子结点；
(3) 如果要删除的结点有左、右两颗子树
*/
BinTree Delete(BinTree BST, ElementType X) {
	TPosition Tmp;
	if(!BST)
		printf("要删除的元素未找到");
	else {
		if (X < BST->Data)
			BST->Left = Delete(BST->Left, X);	/* 从左子树递归删除 */
		else if (X > BST->Data)
			BST->Right = Delete(BST->Right, X);	/* 从右子树递归删除 */
		else {	/* BST就是要删除的结点 */
			/* 如果被删除结点有左右两个子结点 */
			if (BST->Left && BST->Right) {
				/* 从右子树中找最小的元素填充删除结点 */
				Tmp = FindMin_cur(BST->Right);
				BST->Data = Tmp->Data;
				/* 从右子树中删除最小元素 */
				BST->Right = Delete(BST->Right, BST->Data);
			}
			else { /* 被删除结点有一个或无子结点 */
				Tmp = BST;
				if (!BST->Left)	/* 只有右孩子或无子结点 */
					BST = BST->Right;
				else           /* 只有左孩子 */
					BST = BST->Left;
				free(Tmp);
			}
		}
	}
	return BST;
}
 
 
int main() {
	printf("==================创建二叉树==================\n");
	printf("*****请输入8 6 12 4 7 10 13 0 0 0 0 0 0 0 0**********\n");
	/*
								8
						6				12
					4		7		10		13
	*/
	BinTree BT = CreateBinTree();
	TPosition BT1 = Find_recur(BT, 7);
	printf("\n==============递归查找7================\n");
	printf("\n=====%x========\n", BT1);
	TPosition BT2 = Find_non_recur(BT, 7);
	printf("\n==============迭代查找7================\n");
	printf("\n=====%x========\n", BT2);
 
	printf("\n===============递归查找最小元素==============\n");
	TPosition Min1 = FindMin_cur(BT);
	printf("\n======%x===========\n", Min1);
	printf("\n===============迭代查找最小元素==============\n");
	TPosition Min2 = FindMin_non_cur(BT);
	printf("\n======%x===========\n", Min2);
 
	printf("\n===============递归查找最大元素==============\n");
	TPosition Max1 = FindMax_cur(BT);
	printf("\n======%x===========\n", Max1);
	printf("\n===============迭代查找最小元素==============\n");
	TPosition Max2 = FindMax_non_cur(BT);
	printf("\n======%x===========\n", Max2);
 
	printf("\n=============中序遍历=============\n");
	InorderTraversal(BT);
	printf("\n==============插入9===================\n");
	Insert(BT, 9);
	InorderTraversal(BT);
	printf("\n============删除8====================\n");
	BT = Delete(BT, 8);
	InorderTraversal(BT);
	return 0;
}