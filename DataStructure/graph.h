#pragma once
#include "stdafx.h"
#define TREE_NUM 10
#define MAX_VERTEX_NUM 6
#define MAX_EDGE_NUM 10
#define MAXV 256
using namespace std;

typedef struct {
	int parent;
}Node;

typedef struct {
	Node nodes[TREE_NUM];
	int n;
}PTree;

typedef PTree MFSet;
//查找i所属的子集
int fix_mfset(MFSet &S, int i)
{
	if (i<1 || i>S.n) return -1;
	int j = 0, k = 0, t = 0;
	for (j = i; S.nodes[j].parent>0; j = S.nodes[j].parent);
	//for (k = i; k != j; k = t) {
	//	t = S.nodes[k].parent;
	//	S.nodes[k].parent = j;
	//}
	return j;
}

//将i合并到j所属的子集
int mix_mfset(MFSet &S, int i, int j)
{
	if (i<1 || i>S.n || j<1 || j>S.n) return 0;
	//if (S.nodes[i].parent>S.nodes[j].parent) {	//说明j中的元素多(头结点的parent为元素个数的负数)
	//	S.nodes[j].parent += S.nodes[i].parent;
	//	S.nodes[i].parent = j;
	//}
	//else {
	//	S.nodes[i].parent += S.nodes[j].parent;
	//	S.nodes[j].parent = i;
	//}
	S.nodes[i].parent = j;
	return 1;
}

class EdgeType {
public:
	int v1;
	int v2;
	int w;     /*边的权值*/
	EdgeType(int c1, int c2, int vec) :v1(c1), v2(c2), w(vec) {}
};

class Graph{
public:
	char vexs[MAX_VERTEX_NUM];		// 顶点信息
	EdgeType edge[MAX_EDGE_NUM];	// 边的信息(需要提前排好序)
	int vexnum, arcnum;// 图中顶点的数目和边的数目
};
EdgeType  *MSTree;

void MiniSpanTree_Kruskal(Graph* G)
{
	//EdgeType *&MSTree
	MFSet S;
	S.n = 6;
	int i = 0, k = 0;
	int v1, v2;
	for (i = 0; i<G->vexnum; i++) S.nodes[i].parent = -1;	// 初始化，每个点独自成一个子集
	EdgeType* MSTree = (EdgeType *)malloc((G->vexnum - 1) * sizeof(EdgeType));	// n个点只需要n-1个边连接
	i = 0; k = 0;
	while (k < (G->vexnum - 1) && (i <G->arcnum)) {	// 只需要选择n-1个点即可
		v1 = fix_mfset(S, G->edge[i].v1); // 查找顶点所在的连通分量
		v2 = fix_mfset(S, G->edge[i].v2);
		if (v1 != v2) { // 两个顶点不在同一连通分量中

			MSTree[k].v1 = G->edge[i].v1;	// 把这条边添加到生成树中
			MSTree[k].v2 = G->edge[i].v2;
			MSTree[k].w = G->edge[i].w;

			k++;
			mix_mfset(S, v1, v2); // 将两棵树归并为一棵树
		}
		i++;  // 继续考察下一条权值最小边
	}
	for (i = 0; i<(G->vexnum - 1); i++) printf("(%d, %d) :%d\n", MSTree[i].v1, MSTree[i].v2, MSTree[i].w);
}

void Kruskal(EdgeType E[], int n)
{
	int i, j, k; int vset[MAXV];
	for (i = 0; i < n; i++)  vset[i] = i;
	k = 1; j = 0;
	while (k < n) { /*生成的边数小于n时循环*/
		if (vset[E[j].v1] != vset[E[j].v2]) {	// 不属于同一集合
			printf("(%d,%d):%d\n", E[j].v1, E[j].v2, E[j].w);
			k++;
			for (i = 0; i<n; i++)      /*两个集合统一编号*/
				if (vset[i] == vset[E[j].v2])	// 把所有根节点是v2的节点并入v1
					vset[i] = vset[E[j].v1];
		}
		j++;   	/*扫描下一条边*/
	}
}
