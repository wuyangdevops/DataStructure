#define _CRT_SECURE_NO_WARNINGS
#define ERROR -1
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

/* 边的定义 */
typedef struct ENode_L * PtrToENode_L;
struct ENode_L {
	Vertex V1, V2;	/* 有向边<V1,V2> */
	WeightType Weight;	/* 权重 */
};
typedef PtrToENode_L Edge_L;

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
typedef struct GNode_L * PtrToGNode_L;
struct GNode_L
{
	int Nv;	/* 顶点数 */
	int Ne;	/* 边数 */
	AdjList G;	/* 邻接表 */
};
typedef PtrToGNode_L LGraph;	/* 以邻接表方式存储的图类型 */

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
		/*
		0 1 8 0 2 5 1 2 5 1 4 5 1 5 4 2 3 8 2 6 4 3 6 7 3 7 5 4 5 4 5 6 4 5 8 2 6 7 5 6 8 3 6 9 6 7 9 6 8 9 7
		*/
		printf("0 1 8 0 2 5 1 2 5 1 4 5 1 5 4 2 3 8 2 6 4 3 6 7 3 7 5 4 5 4 5 6 4 5 8 2 6 7 5 6 8 3 6 9 6 7 9 6 8 9 7\n");
		/* 读入边，格式为"起点 终点 权重"，插入邻接矩阵 */
		for (i = 0; i < Graph->Ne; i++) {
			scanf("%d %d %d", &E->V1, &E->V2, &E->weight);
			InsertEdge(Graph, E);
		}
	}
	getchar();
	/* 如果顶点有数据的话，读入数据 */
	printf("=======输入数据============\n");
	printf("ZBWXDLHYFC\n");
	for (V = 0; V < Graph->Nv; V++) {
		scanf("%c", &(Graph->Data[V]));
	}
	return Graph;
}

/* 邻接表 */
LGraph CreateGraph_L(int VertexNum) {
	/* 初始化一个有VertexNum个顶点但没有边的图 */
	Vertex V;
	LGraph Graph;

	Graph = (LGraph)malloc(sizeof(struct GNode_L));	/* 建立图 */
	Graph->Nv = VertexNum;
	Graph->Ne = 0;
	/* 初始化邻接表头指针 */
	/* 注意：这里默认顶点编号从0开始，到(Graph->Nv - 1) */
	for (V = 0; V < Graph->Nv; V++)
		Graph->G[V].FirstEdge = NULL;

	return Graph;
}

void InsertEdge(LGraph Graph, Edge_L E) {
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

/*
最小生成树 MST

假设G=(V,E)为一张网图，其中V为网图中所有顶点的集合，E为网图中所有带权边的集合。
设置两个新的集合VT和ET，其中集合VT用于存放G的最小生成树中的顶点，集合ET存放G的最小
生成树中的边（即当前树T={ET;VT}）。令集合VT的初值为VT={v0}(假设构造最小生成树时，从顶点
vo出发)，集合ET的初始值为∅。

Prim算法：
从所有u∈VT，v∈V-VT的边中，选取具有最小权值的边(u,v)，将顶点v加入集合VT中，将边(u,v)
加入集合ET中，如此不断重复，直到VT=T时，最小生成树构造完毕，此时集合ET中包含了最小生成树的
所有边。
*/

Vertex FindMinDist(MGraph Graph, WeightType dist[]) {
	/* 返回未被收录顶点中dist最小者 */
	Vertex MinV, V;
	WeightType MinDist = INFINITY;

	for (V = 0; V < Graph->Nv; V++) {
		if (dist[V] != 0 && dist[V] < MinDist) {
			/* 若V未被收录，且dist[V]更小 */
			MinDist = dist[V];	/* 更新最小距离 */
			MinV = V;	/* 更新对应顶点 */
		}
	}
	if (MinDist < INFINITY)	/* 若找到最下dist */
		return MinV;
	else return ERROR;	/* 若这样顶点不存在，返回-1作为标记 */
}

void print_dist(int s, WeightType dist[]) {
	printf("\n***********此时dist数组为************\n");
	for (int i = 0; i < s; i++) {
		if (dist[i] < INFINITY)
			printf("%d\t", dist[i]);
		else
			printf("∞\t");
	}
}

int Prim(MGraph Graph, LGraph MST) {
	/* 将最小生成树保存为邻邻接表存储的图MST，返回最小权重和 */
	/* 引入两个辅助一维数组parent和dist
		其中数组parent用来保存当前树的顶点生长过程中，每个顶点的父顶点，parent[0]=-1表示
		v0为根。
		dist[j]用来保存顶点vj到VT顶点的边的最小权值，即存储各顶点与当前树的“距离”——
		如果vj属于当前树，则dist[j]=0；如果vj不属于当前树且不是当前树所有顶点的邻接点，则用
		dist[j]=∞表示。
	*/
	WeightType dist[MaxVertexNum], TotalWeight;
	Vertex parent[MaxVertexNum], V, W;
	int VCount;
	Edge_L E;

	/* 初始化。默认下标是0 */
	for (V = 0; V < Graph->Nv; V++) {
		/* 若V到W没有直接的边，则Graph->G[V][W]定义为INFINITY */
		dist[V] = Graph->G[0][V];
		parent[V] = 0;	/* 暂且定义所有顶点的父结点都是初始点0 */
	}
	TotalWeight = 0;	/* 初始化权重和 */
	VCount = 0;		/* 初始化收录的顶点数 */

	/* 创建包含所有顶点但没有边的图(邻接表) */
	MST = CreateGraph_L(Graph->Nv);
	/* 建立空的边结点 */
	E = (Edge_L)malloc(sizeof(struct ENode_L));

	/* 将初始点0收录进MST */
	dist[0] = 0;
	VCount++;
	parent[0] = -1;	/* 当前树根是0 */
	MST->G[0].Data = Graph->Data[0];

	while (1)
	{
		print_dist(Graph->Nv, dist);
		/*
		每一轮循环开始时，首先从dist数组中找到距离树最近的结点
		并将其收录到树中
		*/
		V = FindMinDist(Graph, dist);
		/* V=未被收录顶点中dist最小者 */
		if (V == ERROR)	/* 若这样的V不存在 */
			break;	/* 算法结束 */

		/* 将V及相应的边<parent[V], V>收录进MST */
		E->V1 = parent[V];
		E->V2 = V;
		printf("\n============加入了边<%d,%d>=============\n", E->V1, E->V2);
		E->Weight = dist[V];
		TotalWeight += dist[V];
		InsertEdge(MST, E);
		MST->G[V].Data = Graph->Data[V];
		dist[V] = 0;
		VCount++;

		/*
		每一轮收录新的结点到树中后，图的结构都产生了变化
		需要重新计算各结点到树的距离
		(如果因为新结点的加入使得X结点到树的距离变近，则更新X结点到树的距离dist[X])
		*/
		for (W = 0; W < Graph->Nv; W++) /* 对图中的每个顶点W */
			if (dist[W] != 0 && Graph->G[V][W] < INFINITY) {
				/* 若W是V的邻接点并且未被收录 */
				if (Graph->G[V][W] < dist[W]) {
					/* 若收录V使得dist[W]变小 */
					dist[W] = Graph->G[V][W];	/* 更新dist[W] */
					parent[W] = V;	/* 更新树 */
				}
			}
	} /* while结束 */
	if (VCount < Graph->Nv)	/* MST中收的顶点不到V个 */
		return ERROR;
	printf("\n*******邻接表如下*********\n");
	for (int i = 0; i < MST->Nv; i++) {
		PtrToAdjVNode p = MST->G[i].FirstEdge;
		/* 打印顶点表头结点 */
		printf("%d|%c|->", i, MST->G[i].Data);
		/* 打印各邻接点 */
		while (p) {
			printf("%d|%d|->", p->AdjV, p->Weight);
			p = p->Next;
		}
		printf("\n");
	}
	return TotalWeight;	/* 算法执行完毕，返回最小权重或错误标记 */
}

int main() {
	printf("***************开始生成MGraph******************\n");
	MGraph Graph = BuildGraph_M();
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
	printf("\n********开始生成MST********\n");
	LGraph MST = NULL;
	int total = Prim(Graph, MST);
	printf("\n**********最小权重=%d***********\n", total);
	return 0;
}
