// DataStructure.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "tree.h"
#include "graph.h"
/*
string cto_string(int num) {
	char a[10] = { 0 };
	char b[10] = { 0 };
	int len = 0;
	while (num) {
		a[len] = num % 10 + '0';
		num /= 10;
		++len;
	}
	string res = "";
	int k = 0;
	for (int i = len - 1; i >= 0; --i) {
		b[k++] = a[i];
	}
	res = b;
	return res;
}

//dev C++不支持的函数
int cstoi(string num) {
	int res = 0;
	int len = num.size();
	for (int i = 0; i<len; ++i) {
		res += (num[i] - '0');
		res *= 10;
	}
	return res / 10;
}
*/
int main() {
	Graph* G = (Graph*)malloc(sizeof(Graph));
	for (int i = 0; i < 6; i++)
	{
		G->vexs[i] = 'a' + i;
	}
	G->vexnum = 6;
	G->arcnum = 10;
	G->edge[0] = *(new EdgeType(1, 3, 1));
	G->edge[1] = *(new EdgeType(4, 6, 2));
	G->edge[2] = *(new EdgeType(2, 5, 3));
	G->edge[3] = *(new EdgeType(3, 6, 4));
	G->edge[4] = *(new EdgeType(2, 3, 5));
	G->edge[5] = *(new EdgeType(3, 4, 5));
	G->edge[6] = *(new EdgeType(1, 4, 5));
	G->edge[7] = *(new EdgeType(1, 2, 6));
	G->edge[8] = *(new EdgeType(3, 5, 6));
	G->edge[9] = *(new EdgeType(5, 6, 6));
	MiniSpanTree_Kruskal(G);
	/*TreeNode* head;
	string exp = "+*5^x2*8x";
	head = ReadExpr(exp);
	cout << "表达式：" << exp << endl;
	cout << "表达式的中缀形式为：";
	WriteExpr(head);
	cout << "给变量赋值后的形式为：";
	Assign(head, 'x', 2);
	WriteExpr(head);
	cout << "表达式的值为：";
	cout << Value(head) << endl;*/
	return 0;
}