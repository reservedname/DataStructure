#pragma once
#include "dijkstra.h"
#include "stdafx.h"
using namespace std;

#ifndef NUM_MAX
#define NUM_MAX 100		//顶点个数最大值
#endif // !NUM_MAX
#define MAX_INT 100000


int G[NUM_MAX][NUM_MAX] = { 0 };	//保存图的邻接矩阵
int F[NUM_MAX] = { 0 };	//保存顶点是否已经被加入最短路径
int D[NUM_MAX];	//最短路径
int pre[NUM_MAX];	//前驱顶点
int n = 0, v = 0;

void initGraph() {
	memset(G, 0, sizeof(G));
	cin >> n >> v;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cin >> G[i][j];
			if (G[i][j] == -1) G[i][j] = MAX_INT;
		}
	}
}

void showPath(int k) {
	if (pre[k] == -1) {
		cout << k << "->";
		return;
	}
	showPath(pre[k]);
	cout << k << "->";
}

void dijkstra() {
	initGraph();
	for (int i = 0; i < n - 1; i++)
	{
		F[i] = 0;
		D[i] = G[v][i];
		if (G[v][i] != MAX_INT) pre[i] = v;
		else pre[i] = -1;
	}
	F[v] = 1;
	pre[v] = -1;

	int min = MAX_INT + 1;
	int verFound = -1;	//找到的顶点
	int k = 0;
	for (int i = 0; i < n; i++)
	{
		min = MAX_INT + 1;
		for (int j = 0; j < n; j++)
		{
			if (!F[j] && D[j] < min) {
				min = D[j];
				verFound = j;
			}
		}

		if (!F[verFound]) {	//该顶点没有被添加进去
			for (int j = 0; j < n; j++)
			{
				if (!F[j] && D[j] > D[verFound] + G[verFound][j]) {
					D[j] = D[verFound] + G[verFound][j];
					pre[j] = verFound;
					k = j;
				}
			}
		}
		F[verFound] = 1;
	}
	for (int i = 0; i < n; i++)
	{
		showPath(i); cout << endl;
	}
}
