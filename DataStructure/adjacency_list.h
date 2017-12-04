#pragma once
#include "stdafx.h"
using namespace std;
#define MAX_SIZE 35

struct Node {
	int nodeName;	//表结点的值
	int edgeLen;	//边上的权值
	Node *next;
	Node(int node, int edge) :nodeName(node), edgeLen(edge), next(nullptr) {}
};

struct VNode {
	int headNodeName;	//头结点的值
	Node* headEdge;		//表结点集(边界表)
	VNode(int headNode) :headNodeName(headNode), headEdge(nullptr) {}
};

struct ALGraph {
	VNode* adjlist;	//头结点集
	int vertexNum;	//结点个数
	int edgeNum;	//边的个数(输入点对的个数)
};

//保存遍历得到的树
struct EdgeTree {
	int parent[MAX_SIZE];//当前结点的前一个结点
	int edge[MAX_SIZE];	//每个点到parent的距离
	int son[MAX_SIZE];	//当前结点的后一个结点
	int tree_len;	//树的长度
	int preSite;	//当前该存储的位置，在进行图的遍历时用
};

vector<int> visited;	//标志当前结点是否已访问
EdgeTree* tree;			//生成树

//初始化生成树
void initTree(ALGraph* g) {
	tree = (EdgeTree*)malloc(sizeof(EdgeTree));
	tree->tree_len = g->vertexNum;
	tree->preSite = 0;
	for (int i = 0; i < MAX_SIZE; i++)
	{
		tree->edge[i] = 0;
		tree->parent[i] = -1;	//-1表示空值
		tree->son[i] = -1;
	}
}

//结点插入指定位置的边界表
void insertGraph(ALGraph* g, int site, int v, int edge) {
	VNode* vnode = (g->adjlist + site);
	Node* node = vnode->headEdge;
	if (!node) {	//结点为空，说明不存在边界表，则创建边界表
		vnode->headEdge = new Node(v, edge);
		return;
	}
	while (node->next) {
		if (node->next->nodeName == v) return;	// 说明结点已存在于边界表
		node = node->next;
	}
	node->next = new Node(v, edge);	//说明当前结点未重复
	return;
}

//创建图的邻接多重表的表示
ALGraph* createGraph(vector<int> allVer, vector<int> ver1, vector<int> ver2, vector<int> edge) {
	ALGraph* g = new ALGraph();
	g->vertexNum = allVer.size();	//结点个数
	g->adjlist = (VNode*)malloc(sizeof(VNode)*(g->vertexNum));	//分配邻接表的内存空间
	g->edgeNum = edge.size();	//边的个数(点对的个数)
	int len = ver1.size();	// len_ver1 == len_ver2
	int verSite = -1;

	for (int i = 0; i < allVer.size(); i++)	//给头结点赋值
	{
		g->adjlist[i] = allVer[i];
	}

	for (int i = 0; i < len; i++)
	{	//无向带权图(生成树是有向的)
		insertGraph(g, ver1[i] - 1, ver2[i], edge[i]);
		insertGraph(g, ver2[i] - 1, ver1[i], edge[i]);
	}
	return g;
}

void initVisited(int len, int flag) {
	for (int i = 0; i < len; i++)
	{
		if (flag) visited[i] = 0;	//flag == 1说明是第二次初始化，所以不用添加值
		else visited.push_back(0);
	}
}

//对一个头结点进行递归访问，被深度优先函数调用
void Visit(ALGraph* g, int v) {
	visited[v] = 1;

	VNode* vnode = (g->adjlist + v);
	Node* head = vnode->headEdge;
	int pre = vnode->headNodeName;
	while (head) {  
		int newV = head->nodeName - 1;
		if (visited[newV] == 0) {
			tree->edge[tree->preSite] = head->edgeLen;
			tree->parent[tree->preSite] = pre;
			tree->son[tree->preSite] = newV + 1;
			tree->preSite++;
			Visit(g, newV);
		}
		head = head->next;
	}
	return;
}

//深度优先遍历
void DFS(ALGraph* g, int v) {
	initTree(g);
	int n = g->vertexNum;
	int site = -1;
	initVisited(g->vertexNum, 0);
	VNode* start = g->adjlist + v;
	Node* first = start->headEdge;

	visited[v] = 1;
	Visit(g, start->headNodeName - 1);	//访问头结点
	while (first) {	//只要表结点未被访问完
		if (visited[first->nodeName - 1] == 0) Visit(g, first->nodeName - 1);	//假如表结点未被访问，就访问该结点
		first = first->next;	//表结点向后移动
	}
	return;
}

//广度优先遍历
void BFS(ALGraph* g, int v) {
	initTree(g);
	initVisited(g->vertexNum, 1);
	vector<int> queue;
	visited[v] = 1;
	queue.push_back(v);
	while (queue.size() != 0) {
		int u = queue[0];	//取队首元素
		queue.erase(queue.begin());	//退队列
		Node* head = (g->adjlist + u)->headEdge;
		int pre = u + 1;	//pre为生成树的上一个结点(parent)

		while (head) {	//只要结点不为空
			int newV = head->nodeName - 1;
			if (!visited[newV]) {	//只要未被访问
				visited[newV] = 1;
				tree->parent[tree->preSite] = pre;
				tree->edge[tree->preSite] = head->edgeLen;
				tree->son[tree->preSite] = newV + 1;	//图中顶点范围为0—n-1，所以这里+1
				tree->preSite++;
				queue.push_back(newV);	//入队列
			}
			head = head->next;	//结点向后移动
		}
	}
}

//输出顶点集
void showTreeVertex() {
	if (tree->parent[0] == -1) {	//结点不连通
		cout << "该结点不连通，无遍历序列";
		return;
	}
	cout << tree->parent[0] << " ";
	for (int i = 0; i < tree->tree_len - 1; i++)
	{
		if (tree->son[i] == -1) return;
		cout << tree->son[i] << " ";	//son[i]为下一个遍历得到的结点
	}
}

//输出边集
void showTreeEdge() {
	for (int i = 0; i < tree->tree_len - 1; i++)
	{
		if (tree->parent[i] == -1) {
			if (i == 0) cout << "该结点不连通，无遍历序列";
			return;
		}
		cout << tree->edge[i] << "(" << tree->parent[i] << "→" << tree->son[i] << ") ";
	}
}

//销毁图，释放空间
void delelteGraph(ALGraph *g) {
		if (g->adjlist) free(g->adjlist);
}