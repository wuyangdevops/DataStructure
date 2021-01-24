#define _CRT_SECURE_NO_WARNINGS
#define MaxVertexNum 100	/* 最大顶点数设为100 */
 
#include<stdio.h>
#include<stdlib.h>
 
typedef int Vertex;		/* 用顶点下标表示顶点，为整型 */
typedef int WeightType;	/* 边的权值设为整型 */
typedef char DataType;	/* 顶点存储的数据类型设为字符型 */
 
 
/*
图(邻接表)
对于图G中的每个顶点vi，将所有邻接于vi的顶点vj链成一个单链表，
这个单链表就称为顶点vi的邻接表，再将所有点的邻接表表头放到
一个数组中，就构成了图的邻接表。
*/
 
/*
顶点表
顶点域|边表头指针
Data|FirstEdge
边表
邻接点域|指针域
AdjV|Next
网图的边表
邻接点域|边上信息|指针域
AdjV|Weight|Next
*/
 
/*===================结构体============================*/
/* 边的定义 */
typedef struct ENode * PtrToENode;
struct ENode {
	Vertex V1, V2;	/* 有向边<V1,V2> */
	WeightType Weight;	/* 权重 */
};
typedef PtrToENode Edge;
 
/* 邻接点的定义 */
typedef struct AdjVNode * PtrToAdjVNode;
struct AdjVNode {
	Vertex AdjV;	/* 邻接点下标 */
	WeightType Weight;	/* 边权重 */
	PtrToAdjVNode Next;	/* 指向下一个邻接点的指针 */
};
 
/* 顶点表头结点的定义 */
typedef struct Vnode {
	PtrToAdjVNode FirstEdge;	/* 边表头指针 */
	DataType Data;	/* 存顶点的数据 */
} AdjList[MaxVertexNum];	/* AdjList是邻接表类型 */
 
/* 图结点的定义 */
typedef struct GNode * PtrToGNode;
struct GNode
{
	int Nv;	/* 顶点数 */
	int Ne;	/* 边数 */
	AdjList G;	/* 邻接表 */
};
typedef PtrToGNode LGraph;	/* 以邻接表方式存储的图类型 */
 
/* 队列 */
typedef struct QNode * PtrToQNode;
struct QNode
{
	Vertex * Data;	/* 存储元素的数组 */
	int Front, Rear;	/* 队列的头、尾指针 */
	int MaxSize;	/* 队列的最大容量 */
};
 
typedef PtrToQNode Queue;
 
/*=====================队列=========================*/
Queue CreateQueue(int MaxSize) {
	/*创建队列*/
	Queue Q = (Queue)malloc(sizeof(struct QNode));
	Q->Data = (Vertex *)malloc(MaxSize * sizeof(Vertex));
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
 
bool AddQ(Queue Q, Vertex X) {
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
 
Vertex DeleteQ(Queue Q) {
	/*出队*/
	if (IsEmpty(Q)) {
		printf("队列空\n");
		return -1;
	}
	else {
		Q->Front = (Q->Front + 1) % Q->MaxSize;
		return Q->Data[Q->Front];
	}
}
 
/*=========================图==============================*/
LGraph CreateGraph(int VertexNum) {
	/* 初始化一个有VertexNum个顶点但没有边的图 */
	Vertex V;
	LGraph Graph;
 
	Graph = (LGraph)malloc(sizeof(struct GNode));	/* 建立图 */
	Graph->Nv = VertexNum;
	Graph->Ne = 0;
	/* 初始化邻接表头指针 */
	/* 注意：这里默认顶点编号从0开始，到(Graph->Nv - 1) */
	for (V = 0; V < Graph->Nv; V++)
		Graph->G[V].FirstEdge = NULL;
	
	return Graph;
}
 
void InsertEdge(LGraph Graph, Edge E) {
	/* 插入边 */
	PtrToAdjVNode NewNode;
	/* 插入边<V1,V2> */
	/* 为V2建立新的邻接点 */
	NewNode = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
	/* 为新的邻接点写入下标(V2) */
	NewNode->AdjV = E->V2;
	/* 为新的邻接点写入权重 */
	NewNode->Weight = E->Weight;	/* 边的权重写入V2的权重 */
	/* 将V2插入V1的表头 */
	NewNode->Next = Graph->G[E->V1].FirstEdge;
	Graph->G[E->V1].FirstEdge = NewNode;
 
	/* 若是无向图，还要插入边<V2,V1> */
	/* 为V1建立新的邻接点 */
	NewNode = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
	NewNode->AdjV = E->V1;
	NewNode->Weight = E->Weight;
	/* 将V1插入V2的表头 */
	NewNode->Next = Graph->G[E->V2].FirstEdge;
	Graph->G[E->V2].FirstEdge = NewNode;
}
 
LGraph BuildGraph() {
	LGraph Graph;
	Edge E;
	Vertex V;
	int Nv, i;
	printf("\n=========请输入顶点个数(8)==============\n");
	scanf("%d", &Nv);	/* 读入顶点个数 */
	Graph = CreateGraph(Nv);	/* 初始化有Nv个顶点但没有边的图 */
 
	printf("\n==========请输入边数(9)===============\n");
	scanf("%d", &(Graph->Ne));	/* 读入边数 */
	if (Graph->Ne != 0) {
		/* 如果有边 */
		E = (Edge)malloc(sizeof(struct ENode));	/* 建立边结点 */
		/* 读入边，格式为 起点 终点 权重，插入邻接表 */
		printf("\n====请输入边，格式：起点 终点 权重======\n");
		/* 为了方便起见，当有多种选择的时候，采用字母序的策略选择下一个邻接点 */
		printf("7 6 1 7 4 1 6 5 1 5 4 1 4 0 1 3 0 1 3 2 1 2 1 1 1 0 1\n");
		for (i = 0; i < Graph->Ne; i++) {
			scanf("%d %d %d", &E->V1, &E->V2, &E->Weight);
			InsertEdge(Graph, E);
		}
	}
	getchar();
	printf("\n=======依次输入各结点数据===========\n");
	printf("ABCDEFGH\n");
	/* 如果顶点有数据的话，读入数据 */
	for (V = 0; V < Graph->Nv; V++)
		scanf("%c", &(Graph->G[V].Data));
 
	return Graph;
}
 
/*================图的遍历=======================*/
/* 深度优先遍历(DFS) */
bool Visited[8] = { false };
 
void reset_visit() {
	/* 重置Visited数组 */
	extern bool Visited[8];
	for (int i = 0; i < 8; i++)
		Visited[i] = false;
}
 
/* Visited[]为全局变量，已经初始化为false */
void DFS(LGraph Graph, Vertex V) {
	/* 以V为出发点对邻接表存储的图Graph进行DFS搜索 */
	PtrToAdjVNode W;
 
	/* 访问第V个顶点 */
	printf("%c\t", Graph->G[V].Data);
	/* 标记V已访问 */
	Visited[V] = true;
 
	for (W = Graph->G[V].FirstEdge; W; W = W->Next)	/* 对V的每个邻接点W->AdjV */
		if (!Visited[W->AdjV])	/* 若W->AdjV未被访问 */
			DFS(Graph, W->AdjV);	/* 则递归访问之 */
}
 
/* 广度优先遍历(DFS) */
void BFS(LGraph Graph, Vertex S) {
	/* 以S为出发点对邻接表存储的图Graph进行BFS搜索 */
	Queue Q;
	Vertex V;
	PtrToAdjVNode W;
 
	Q = CreateQueue(MaxVertexNum);	/* 创建空队列 */
	/* 访问顶点S */
	printf("%c\t", Graph->G[S].Data);
	Visited[S] = true;	/* 标记S已访问 */
	AddQ(Q, S);	/* S入队列 */
 
	while (!IsEmpty(Q))
	{
		V = DeleteQ(Q);	/* 弹出V */
		for (W = Graph->G[V].FirstEdge; W; W = W->Next)	/* 对V的每个邻接点 */
		{
			if (!Visited[W->AdjV])
			{
				/* 访问顶点K */
				printf("%c\t", Graph->G[W->AdjV].Data);
				/* 标记W已访问 */
				Visited[W->AdjV] = true;
				/* W入队列 */
				AddQ(Q, W->AdjV);
			}
		}
	}
}
 
 
int main() {
	LGraph Graph = BuildGraph();
	printf("\n*******邻接表如下*********\n");
	/*
		0|A|->1|1|->3|1|->4|1|->
		1|B|->0|1|->2|1|->
		2|C|->1|1|->3|1|->
		3|D|->2|1|->0|1|->
		4|E|->0|1|->5|1|->7|1|->
		5|F|->4|1|->6|1|->
		6|G|->5|1|->7|1|->
		7|H|->4|1|->6|1|->
	*/
	for (int i = 0; i < Graph->Nv; i++) {
		PtrToAdjVNode p = Graph->G[i].FirstEdge;
		/* 打印顶点表头结点 */
		printf("%d|%c|->", i, Graph->G[i].Data);
		/* 打印各邻接点 */
		while (p) {
			printf("%d|%d|->", p->AdjV, p->Weight);
			p = p->Next;
		}
		printf("\n");
	}
	printf("\n****从结点E开始进行DFS搜索********\n");
	printf("\n****预期E->A->B->C->D->F->G->H******\n");
	DFS(Graph, 4);
 
	printf("\n****从结点E开始进行BFS搜索********\n");
	reset_visit();
	printf("\n*****预期E->A->F->H->B->D->G->C******\n");
	BFS(Graph, 4);
	return 1;
}