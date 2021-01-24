#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#define MaxVertexNum 100	/* 最大顶点数设为100 */
#define INFINITY 65535	/* ∞设为双字节无符号整数的最大值65535 */
typedef int Vertex;		/* 用顶点下标表示顶点，为整型 */
typedef int WeightType;	/* 边的权值设为整型 */
typedef char DataType;	/* 顶点存储的数据类型设为字符型 */
 
/*===========================结构体============================*/
/*
图
邻接矩阵
G[i][j] = 1 - 若(vi.vj)或<vi,vj>是E中的边
		= 0 - 若(vi.vj)或<vi,vj>不是E中的边
*/
 
/* 图结点的定义 */
typedef struct GNode * PtrToGNode;
struct GNode {
	int Nv;	/* 顶点数 */
	int Ne;	/* 边数 */
	WeightType G[MaxVertexNum][MaxVertexNum];	/* 邻接矩阵 */
	DataType Data[MaxVertexNum];	/* 存顶点的数据 */
	/* 若顶点无数据，此时Data[]可以不用出现 */
};
typedef PtrToGNode MGraph;	/* 以邻接矩阵存储的图类型 */
 
 
/*
创建一个包含全部顶点但没有边的图，再逐条插入边，从而创建了一个无向网图的数据对象。
其中Edge是边的类型，边结构中包含两个端点V1和V2,还有边的权重Weight。Edge是指向这个结构的指针。
*/
 
/* 边的定义 */
typedef struct ENode * PtrToENode;
struct ENode {
	Vertex V1, V2;	/* 有向边<V1,V2> */
	WeightType weight;	/* 权重 */
};
 
typedef PtrToENode Edge;
 
/* 队列 */
typedef struct QNode * PtrToQNode;
struct QNode
{
	Vertex * Data;	/* 存储元素的数组 */
	int Front, Rear;	/* 队列的头、尾指针 */
	int MaxSize;	/* 队列的最大容量 */
};
 
typedef PtrToQNode Queue;
 
/*============================队列=============================*/
 
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
 
/*==============================图====================================*/
 
MGraph CreateGraph(int VertexNum) {
	/* 初始化一个有VertexNum个顶点但没有边的图 */
	Vertex V, W;
	MGraph Graph;
 
	Graph = (MGraph)malloc(sizeof(struct GNode));	/* 建立图 */
	Graph->Nv = VertexNum;
	Graph->Ne = 0;
	/* 初始化邻接矩阵 */
	/* 注意：这里默认顶点编号从0开始，到(Graph->Nv-1) */
	for (V = 0; V < Graph->Nv; V++)
		for (W = 0; W < Graph->Nv; W++)
			Graph->G[V][W] = INFINITY;
	return Graph;
}
 
void InsertEdge(MGraph Graph, Edge E) {
	/* 插入边<V1,V2> */
	Graph->G[E->V1][E->V2] = E->weight;
	/* 若是无向图，还要插入边<V2,V1> */
	Graph->G[E->V2][E->V1] = E->weight;
}
 
MGraph BuildGraph() {
	MGraph Graph;
	Edge E;
	Vertex V;
	int Nv, i;
 
	printf("=======输入顶点个数(8)=======\n");
	scanf("%d", &Nv);	/* 读入顶点个数 */
	Graph = CreateGraph(Nv);	/* 初始化有Nv个顶点但没有边的图 */
	//getchar();
	printf("====验证输入===%d", Nv);
	printf("\n=======输入边数(9)=======\n");
	scanf("%d", &(Graph->Ne));	/* 读入边数 */
	printf("====验证输入===%d", Graph->Ne);
	//getchar();
	if (Graph->Ne != 0) {	/* 如果有边 */
		E = (Edge)malloc(sizeof(struct ENode));	/* 建立边结点 */
		printf("\n=======输入边 格式为 起点 终点 权重=======\n");
		printf("0 1 1 0 3 1 0 4 1 1 2 1 2 3 1 4 7 1 4 5 1 5 6 1 6 7 1\n");
		/* 读入边，格式为"起点 终点 权重"，插入邻接矩阵 */
		for (i = 0; i < Graph->Ne; i++) {
			scanf("%d %d %d", &E->V1, &E->V2, &E->weight);
			printf("====验证输入===%d %d %d", E->V1, E->V2, E->weight);
			InsertEdge(Graph, E);
		}
	}
	getchar();
	/* 如果顶点有数据的话，读入数据 */
	printf("=======输入数据============\n");
	printf("ABCDEFGH\n");
	for (V = 0; V < Graph->Nv; V++) {
		scanf("%c", &(Graph->Data[V]));
		printf("====验证输入===%c", Graph->Data[V]);
	}
	return Graph;
}
 
/* 遍历(广度优先 BFS) 
在遍历过程中需要一个访问标志数组Visited[]，它是全局变量，其Nv个初始值都是false。
一旦某个顶点被访问，则其相应的分量置为true。
*/
 
bool IsEdge(MGraph Graph, Vertex V, Vertex W) {
	/*
	检查<V,W>是否是图中的一条边，即W是否是V的邻接点
	*/
	return (Graph->G[V][W]<INFINITY ? true : false);
}
 
/*
Visited[]为全局变量，已经初始化为false
*/
 
void BFS(MGraph Graph, Vertex S) {
	/* 以S为出发点对邻接矩阵存储的图Graph进行BFS搜索 */
 
	bool Visited[8];
	for (int i = 0; i < 8; i++)
		Visited[i] = false;
 
	Queue Q;
	Vertex V, W;
 
	/* 创建空队列 */
	Q = CreateQueue(MaxVertexNum);
	/* 访问顶点S */
	printf("%c\t", Graph->Data[S]);
	/* 标记S已访问 */
	Visited[S] = true;
	/* S入队列 */
	AddQ(Q, S);
 
	while (!IsEmpty(Q))
	{
		V = DeleteQ(Q);	/* 弹出V */
		for (W = 0; W < Graph->Nv; W++) {
			/* 若W是V的邻接点并且未访问过 */
			if ((!Visited[W]) && IsEdge(Graph, V, W)) {
				/* 访问顶点W */
				printf("%c\t", Graph->Data[W]);
				Visited[W] = true;	/* 标记W已访问 */
				AddQ(Q, W);	/* W入队列 */
			}
		}
	}	/* while结束 */
}
 
/*
遍历(深度优先DFS)
*/
bool Visited[8] = { false };
void DFS(MGraph Graph, Vertex S) {
	/* 以S为出发点对邻接矩阵存储的图Graph进行DFS搜索 */
	/* 访问S */
	printf("%c\t", Graph->Data[S]);
	/* Visited数组中将顶点S置为true */
	Visited[S] = true;
	for (Vertex W = 0; W < Graph->Nv; W++)
		if (IsEdge(Graph, S, W) && (!Visited[W]))	/* 对S的尚未访问的邻接顶点W递归调用DFS */
			DFS(Graph, W);
}
 
 
int main() {
	MGraph Graph = BuildGraph();
	/*
			A       B       C       D       E       F       G       H
	A       ∞      1       ∞      1       1       ∞      ∞      ∞
	B       1       ∞      1       ∞      ∞      ∞      ∞      ∞
	C       ∞      1       ∞      1       ∞      ∞      ∞      ∞
	D       1       ∞      1       ∞      ∞      ∞      ∞      ∞
	E       1       ∞      ∞      ∞      ∞      1       ∞      1
	F       ∞      ∞      ∞      ∞      1       ∞      1       ∞
	G       ∞      ∞      ∞      ∞      ∞      1       ∞      1
	H       ∞      ∞      ∞      ∞      1       ∞      1       ∞
	*/
	printf("\n\n**********图的邻接矩阵如下**************\n\n");
	printf("\n\tA\tB\tC\tD\tE\tF\tG\tH\n");
	for (int i = 0; i < 8; i++) {
		printf("%c\t", Graph->Data[i]);
		for (int j = 0; j < 8; j++) {
			if (Graph->G[i][j] < INFINITY)
				printf("%d\t", Graph->G[i][j]);
			else
				printf("∞\t");
		}
		printf("\n");
	}
 
	printf("\n\n******从E开始进行广度优先遍历(BFS)***************\n");
	printf("\n****预期：E->A->F->H->B->D->G->C*****\n");
	BFS(Graph, 4);
	printf("\n\n******从E开始进行深度优先遍历(DFS)**************\n");
	printf("\n****预期：E->A->B->C->D->F->G->H*****\n");
	DFS(Graph, 4);
	return 1;
}