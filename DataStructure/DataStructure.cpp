// DataStructure.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "adjacency_list.h"
//#include "hash_name_table.h"

int main() {
/*	vector<string> name =
	{
		"wangyi","yiwang","zhaosan","liusi","chenwu","linliu","dingqi","zhouba","sunjiu","lishi",
		"yanger","wushier","lvshisan","yanshisi","shenshiwu","dwjiqdr","saduhwar","sadas","sadw","sadas",
		"sadasad","sadad","sadwre","eitjer","eriuhsd","asdwre","ejtrii","erhasd","sadwrr","fdfezzd"
	};
	string s = "";
	createHashTable(name);
	while (cin >> s) {
		HashFind(s);
	}*/
	/*
	6 5
	0 6 -1 8 -1 -1
	18 0 7 -1 -1 10
	9 -1 0 15 -1 -1
	-1 -1 12 0 -1 -1
	-1 -1 -1 4 0 -1
	24 5 -1 25 -1 0
	*/
//	dijkstra();
	int i = 0;
	int v1, v2, e;
	int v = -1;
	int m = 0, num = 0;
	vector<int> allVer, ver1, ver2, edge;

	cout << "输入点的个数：";
	cin >> m;
	for (int j = 0; j < m; j++)
	{
		allVer.push_back(j + 1);
	}
	cout << "请输入点对(结点值范围为1-m，从1开始计数)，输入0 0 0结束输入：" << endl;
	do
	{
		cin >> v1 >> v2 >> e;
		if (!v1 && !v2 && !e) break;
		if (v1 == 0 || v2 == 0 || v1 > m || v2 > m) {
			cout << "数据输入错误，请输入正确的点对，结点值范围为1-m，从1开始计数：" << endl;
			continue;
		}
		ver1.push_back(v1);
		ver2.push_back(v2);
		edge.push_back(e);
	} while (true);//同时为0则退出
	cout << "输入起点：";
	cin >> v;
	

	ALGraph* g = createGraph(allVer, ver1, ver2, edge);
	cout << "+--------------+" << endl;
	cout << "|   遍历方式   |  深度优先遍历" << endl;
	cout << "+--------------+" << endl;
	cout << "| 节点访问序列 |  ";
	DFS(g, v - 1);
	showTreeVertex();
	cout << endl;
	cout << "+--------------+" << endl;
	cout << "| 生成树的边集 |  ";
	showTreeEdge();
	cout << endl;
	cout << "+--------------+" << endl;


	cout << "\n\n";
	cout << "+--------------+" << endl;
	cout << "|   遍历方式   |  广度优先遍历" << endl;
	cout << "+--------------+" << endl;
	cout << "| 节点访问序列 |  ";
	BFS(g, v - 1);
	showTreeVertex();
	cout << endl;
	cout << "+--------------+" << endl;
	cout << "| 生成树的边集 |  ";
	showTreeEdge();
	cout << endl;
	cout << "+--------------+" << endl;
	delelteGraph(g);
	return 0;
}