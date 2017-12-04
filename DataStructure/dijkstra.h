#pragma once
#include "dijkstra.h"
#include "stdafx.h"
using namespace std;

#ifndef NUM_MAX
#define NUM_MAX 100		//����������ֵ
#endif // !NUM_MAX
#define MAX_INT 100000


int G[NUM_MAX][NUM_MAX] = { 0 };	//����ͼ���ڽӾ���
int F[NUM_MAX] = { 0 };	//���涥���Ƿ��Ѿ����������·��
int D[NUM_MAX];	//���·��
int pre[NUM_MAX];	//ǰ������
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
	int verFound = -1;	//�ҵ��Ķ���
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

		if (!F[verFound]) {	//�ö���û�б���ӽ�ȥ
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
