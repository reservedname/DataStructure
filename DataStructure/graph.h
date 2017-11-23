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
//����i�������Ӽ�
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

//��i�ϲ���j�������Ӽ�
int mix_mfset(MFSet &S, int i, int j)
{
	if (i<1 || i>S.n || j<1 || j>S.n) return 0;
	//if (S.nodes[i].parent>S.nodes[j].parent) {	//˵��j�е�Ԫ�ض�(ͷ����parentΪԪ�ظ����ĸ���)
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
	int w;     /*�ߵ�Ȩֵ*/
	EdgeType(int c1, int c2, int vec) :v1(c1), v2(c2), w(vec) {}
};

class Graph{
public:
	char vexs[MAX_VERTEX_NUM];		// ������Ϣ
	EdgeType edge[MAX_EDGE_NUM];	// �ߵ���Ϣ(��Ҫ��ǰ�ź���)
	int vexnum, arcnum;// ͼ�ж������Ŀ�ͱߵ���Ŀ
};
EdgeType  *MSTree;

void MiniSpanTree_Kruskal(Graph* G)
{
	//EdgeType *&MSTree
	MFSet S;
	S.n = 6;
	int i = 0, k = 0;
	int v1, v2;
	for (i = 0; i<G->vexnum; i++) S.nodes[i].parent = -1;	// ��ʼ����ÿ������Գ�һ���Ӽ�
	EdgeType* MSTree = (EdgeType *)malloc((G->vexnum - 1) * sizeof(EdgeType));	// n����ֻ��Ҫn-1��������
	i = 0; k = 0;
	while (k < (G->vexnum - 1) && (i <G->arcnum)) {	// ֻ��Ҫѡ��n-1���㼴��
		v1 = fix_mfset(S, G->edge[i].v1); // ���Ҷ������ڵ���ͨ����
		v2 = fix_mfset(S, G->edge[i].v2);
		if (v1 != v2) { // �������㲻��ͬһ��ͨ������

			MSTree[k].v1 = G->edge[i].v1;	// ����������ӵ���������
			MSTree[k].v2 = G->edge[i].v2;
			MSTree[k].w = G->edge[i].w;

			k++;
			mix_mfset(S, v1, v2); // ���������鲢Ϊһ����
		}
		i++;  // ����������һ��Ȩֵ��С��
	}
	for (i = 0; i<(G->vexnum - 1); i++) printf("(%d, %d) :%d\n", MSTree[i].v1, MSTree[i].v2, MSTree[i].w);
}

void Kruskal(EdgeType E[], int n)
{
	int i, j, k; int vset[MAXV];
	for (i = 0; i < n; i++)  vset[i] = i;
	k = 1; j = 0;
	while (k < n) { /*���ɵı���С��nʱѭ��*/
		if (vset[E[j].v1] != vset[E[j].v2]) {	// ������ͬһ����
			printf("(%d,%d):%d\n", E[j].v1, E[j].v2, E[j].w);
			k++;
			for (i = 0; i<n; i++)      /*��������ͳһ���*/
				if (vset[i] == vset[E[j].v2])	// �����и��ڵ���v2�Ľڵ㲢��v1
					vset[i] = vset[E[j].v1];
		}
		j++;   	/*ɨ����һ����*/
	}
}
