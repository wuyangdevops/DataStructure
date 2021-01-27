#define _CRT_SECURE_NO_WARNINGS
#define ERROR -1
#include<stdio.h>
#include<stdlib.h>
#define MaxVertexNum 100	/* 最大顶点数设为100 */
#define INFINITY 65535	/* ∞设为双字节无符号整数的最大值65535 */
typedef int Vertex;		/* 用顶点下标表示顶点，为整型 */
typedef int WeightType;	/* 边的权值设为整型 */
typedef int DataType;	/* 顶点存储的数据类型设为字符型 */

/*===========================结构体============================*/
/*
图
邻接矩阵
G[i][j] = 1 - 若(vi.vj)或<vi,vj>是E中的边
		= 0 - 若(vi.vj)或<vi,vj>不是E中的边
*/

/* 图结点的定义 */
typedef struct GNode_M * PtrToGNode_M;
struct GNode_M {
	int Nv;	/* 顶点数 */
	int Ne;	/* 边数 */
	WeightType G[MaxVertexNum][MaxVertexNum];	/* 邻接矩阵 */
	DataType Data[MaxVertexNum];	/* 存顶点的数据 */
	/* 若顶点无数据，此时Data[]可以不用出现 */
};
typedef PtrToGNode_M MGraph;	/* 以邻接矩阵存储的图类型 */


/*
创建一个包含全部顶点但没有边的图，再逐条插入边，从而创建了一个无向网图的数据对象。
其中Edge是边的类型，边结构中包含两个端点V1和V2,还有边的权重Weight。Edge是指向这个结构的指针。
*/

/* 边的定义 */
typedef struct ENode_M * PtrToENode_M;
struct ENode_M {
	Vertex V1, V2;	/* 有向边<V1,V2> */
	WeightType weight;	/* 权重 */
};

typedef PtrToENode_M Edge_M;

/*==============================图====================================*/
/* 邻接矩阵 */
MGraph CreateGraph_M(int VertexNum) {
	/* 初始化一个有VertexNum个顶点但没有边的图 */
	Vertex V, W;
	MGraph Graph;

	Graph = (MGraph)malloc(sizeof(struct GNode_M));	/* 建立图 */
	Graph->Nv = VertexNum;
	Graph->Ne = 0;
	/* 初始化邻接矩阵 */
	/* 注意：这里默认顶点编号从0开始，到(Graph->Nv-1) */
	for (V = 0; V < Graph->Nv; V++)
		for (W = 0; W < Graph->Nv; W++)
			Graph->G[V][W] = INFINITY;
	return Graph;
}

void InsertEdge(MGraph Graph, Edge_M E) {
	/* 插入边<V1,V2> */
	Graph->G[E->V1][E->V2] = E->weight;
	/* 若是无向图，还要插入边<V2,V1> */
	Graph->G[E->V2][E->V1] = E->weight;
}

MGraph BuildGraph_M() {
	MGraph Graph;
	Edge_M E;
	Vertex V;
	int Nv, i;

	printf("=======输入顶点个数(10)=======\n");
	scanf("%d", &Nv);	/* 读入顶点个数 */
	Graph = CreateGraph_M(Nv);	/* 初始化有Nv个顶点但没有边的图 */
	//getchar();
	printf("\n=======输入边数(17)=======\n");
	scanf("%d", &(Graph->Ne));	/* 读入边数 */
	//getchar();
	if (Graph->Ne != 0) {	/* 如果有边 */
		E = (Edge_M)malloc(sizeof(struct ENode_M));	/* 建立边结点 */
		printf("\n=======输入边 格式为 起点 终点 权重=======\n");
		printf("0 1 2 0 3 5 1 2 5 1 3 2 2 4 8 2 5 4 3 5 4 3 6 2 4 5 2 4 7 5 5 6 3 5 7 9 5 8 6 6 8 7 7 8 3 7 9 4 8 9 8\n");
		/* 读入边，格式为"起点 终点 权重"，插入邻接矩阵 */
		for (i = 0; i < Graph->Ne; i++) {
			scanf("%d %d %d", &E->V1, &E->V2, &E->weight);
			InsertEdge(Graph, E);
		}
	}
	getchar();
	/* 如果顶点有数据的话，读入数据 */
	printf("=======输入数据============\n");
	printf("0 1 2 3 4 5 6 7 8 9\n");
	for (V = 0; V < Graph->Nv; V++) {
		scanf("%d", &(Graph->Data[V]));
	}
	return Graph;
}

/* ==================Dijkstra算法==================== */
/* 
(1) 假设用带权的邻接矩阵G来表示带权有向图，G[v][w]表示弧<v,w>上的权值。
	S为已找到从s出发的最短路径的终点的集合，它的初始状态为∅。
	那么，从s出发到图上其余各顶点(终点)v可能达到最短路径长度的初值为：
		dist[v]=G[s][v]	v∈V
		path[v] = -1(表示v尚无父结点)
(2) 选择v，使得
	dist[v] = min{dist[w]|w∈V-S}
	则v就是当前求得的一条从s出发的最短路径的终点。令S=S∪{v}
(3) 修改从s出发到集合V-S上任一顶点w可达的最短路径长度dist[w]如下：
	dist[w] = min{dist[w], dist[v]+G[v][w]}
	同时更新w的父顶点:path[w]=v
*/

Vertex FindMinDist(MGraph Graph, int dist[], bool collected[]) {
	/* 返回未被收录顶点中dist最小者 */
	Vertex MinV, V;
	int MinDist = INFINITY;

	for (V = 0; V < Graph->Nv; V++) {
		if (collected[V] == false && dist[V] < MinDist) {
			/* 若V未被收录，且dist[V]更小 */
			MinDist = dist[V];	/* 更新最小距离 */
			MinV = V;	/* 更新对应顶点 */
		}
	}
	if (MinDist < INFINITY)	/* 若找到最小dist */
		return MinV;	/* 返回对应的顶点下标 */
	else return ERROR;	/* 若这样的顶点不存在，返回错误标记 */
}

bool Dijkstra(MGraph Graph, int dist[], int path[], Vertex S) {
	bool collected[MaxVertexNum];
	Vertex V, W;

	/* 初始化：此处默认邻接矩阵中不存在的边用INFINITY表示 */
	for (V = 0; V < Graph->Nv; V++) {
		dist[V] = Graph->G[S][V];
		if (dist[V] < INFINITY)
			path[V] = S;
		else
			path[V] = -1;
		collected[V] = false;
	}
	/* 先将起点收入集合 */
	dist[S] = 0;
	collected[S] = true;

	while (1)
	{
		/* V=未被收录顶点中dist最小者 */
		V = FindMinDist(Graph, dist, collected);
		if (V == ERROR)	/* 若这样的V不存在 */
			break;		/* 算法结束 */
		collected[V] = true;	/* 收录V */
		printf("\n\n++++++++++收录v%d++++++++++++++\n", V);
		for (W = 0; W < Graph->Nv; W++) /* 对图中的每个顶点W */
			/* 若W是V的邻接点并且未被收录 */
			if (collected[W] == false && Graph->G[V][W] < INFINITY) {
				if (Graph->G[V][W] < 0)	/* 若有负边 */
					return false;	/* 不能正确解决，返回错误标记 */
				/* 若收录V使得dist[W]变小 */
				if (dist[V] + Graph->G[V][W] < dist[W]) {
					dist[W] = dist[V] + Graph->G[V][W];	/* 更新dist[W] */
					path[W] = V;	/* 更新S到W的路径 */
				}
			}
		for(int i=1;i<Graph->Nv;i++)
			printf("\n****此时V0->V%d距离是%d*******\n", i, dist[i]);
	}	/* while结束 */
	return true;	/* 算法执行完毕，返回正确标记 */
}

int main() {
	printf("***************开始生成MGraph******************\n");
	MGraph Graph = BuildGraph_M();
	printf("\n\n**********图的邻接矩阵如下**************\n\n");
	printf("\n\tv0\tv1\tv2\tv3\tv4\tv5\tv6\tv7\tv8\tv9\n");
	for (int i = 0; i < 10; i++) {
		printf("v%d\t", Graph->Data[i]);
		for (int j = 0; j < 10; j++) {
			if (Graph->G[i][j] < INFINITY)
				printf("%d\t", Graph->G[i][j]);
			else
				printf("∞\t");
		}
		printf("\n\n");
	}

	printf("\n============开始执行Dijkstra算法================\n");
	Vertex S = 0;	/* 起始结点 */
	int dist[MaxVertexNum];
	int path[MaxVertexNum];
	bool flag;
	flag = Dijkstra(Graph, dist, path, S);
	if (flag == true) {
		/* Dijkstra算法成功执行 */
		printf("\n++++++v0->v9最短路径=%d+++++++++\n路径：\n", dist[9]);
		int index = 9;
		while (index>0)
		{
			printf("<-%d\t", index);
			int point = path[index];
			index = point;
		}
	}
	return 0;
}
