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
	Graph G;

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