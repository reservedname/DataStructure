#pragma once
#include "stdafx.h"
using namespace std;
#define MAX_SIZE 35

struct Node {
	int nodeName;	//�����ֵ
	int edgeLen;	//���ϵ�Ȩֵ
	Node *next;
	Node(int node, int edge) :nodeName(node), edgeLen(edge), next(nullptr) {}
};

struct VNode {
	int headNodeName;	//ͷ����ֵ
	Node* headEdge;		//���㼯(�߽��)
	VNode(int headNode) :headNodeName(headNode), headEdge(nullptr) {}
};

struct ALGraph {
	VNode* adjlist;	//ͷ��㼯
	int vertexNum;	//������
	int edgeNum;	//�ߵĸ���(�����Եĸ���)
};

//��������õ�����
struct EdgeTree {
	int parent[MAX_SIZE];//��ǰ����ǰһ�����
	int edge[MAX_SIZE];	//ÿ���㵽parent�ľ���
	int son[MAX_SIZE];	//��ǰ���ĺ�һ�����
	int tree_len;	//���ĳ���
	int preSite;	//��ǰ�ô洢��λ�ã��ڽ���ͼ�ı���ʱ��
};

vector<int> visited;	//��־��ǰ����Ƿ��ѷ���
EdgeTree* tree;			//������

//��ʼ��������
void initTree(ALGraph* g) {
	tree = (EdgeTree*)malloc(sizeof(EdgeTree));
	tree->tree_len = g->vertexNum;
	tree->preSite = 0;
	for (int i = 0; i < MAX_SIZE; i++)
	{
		tree->edge[i] = 0;
		tree->parent[i] = -1;	//-1��ʾ��ֵ
		tree->son[i] = -1;
	}
}

//������ָ��λ�õı߽��
void insertGraph(ALGraph* g, int site, int v, int edge) {
	VNode* vnode = (g->adjlist + site);
	Node* node = vnode->headEdge;
	if (!node) {	//���Ϊ�գ�˵�������ڱ߽���򴴽��߽��
		vnode->headEdge = new Node(v, edge);
		return;
	}
	while (node->next) {
		if (node->next->nodeName == v) return;	// ˵������Ѵ����ڱ߽��
		node = node->next;
	}
	node->next = new Node(v, edge);	//˵����ǰ���δ�ظ�
	return;
}

//����ͼ���ڽӶ��ر�ı�ʾ
ALGraph* createGraph(vector<int> allVer, vector<int> ver1, vector<int> ver2, vector<int> edge) {
	ALGraph* g = new ALGraph();
	g->vertexNum = allVer.size();	//������
	g->adjlist = (VNode*)malloc(sizeof(VNode)*(g->vertexNum));	//�����ڽӱ���ڴ�ռ�
	g->edgeNum = edge.size();	//�ߵĸ���(��Եĸ���)
	int len = ver1.size();	// len_ver1 == len_ver2
	int verSite = -1;

	for (int i = 0; i < allVer.size(); i++)	//��ͷ��㸳ֵ
	{
		g->adjlist[i] = allVer[i];
	}

	for (int i = 0; i < len; i++)
	{	//�����Ȩͼ(�������������)
		insertGraph(g, ver1[i] - 1, ver2[i], edge[i]);
		insertGraph(g, ver2[i] - 1, ver1[i], edge[i]);
	}
	return g;
}

void initVisited(int len, int flag) {
	for (int i = 0; i < len; i++)
	{
		if (flag) visited[i] = 0;	//flag == 1˵���ǵڶ��γ�ʼ�������Բ������ֵ
		else visited.push_back(0);
	}
}

//��һ��ͷ�����еݹ���ʣ���������Ⱥ�������
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

//������ȱ���
void DFS(ALGraph* g, int v) {
	initTree(g);
	int n = g->vertexNum;
	int site = -1;
	initVisited(g->vertexNum, 0);
	VNode* start = g->adjlist + v;
	Node* first = start->headEdge;

	visited[v] = 1;
	Visit(g, start->headNodeName - 1);	//����ͷ���
	while (first) {	//ֻҪ����δ��������
		if (visited[first->nodeName - 1] == 0) Visit(g, first->nodeName - 1);	//�������δ�����ʣ��ͷ��ʸý��
		first = first->next;	//��������ƶ�
	}
	return;
}

//������ȱ���
void BFS(ALGraph* g, int v) {
	initTree(g);
	initVisited(g->vertexNum, 1);
	vector<int> queue;
	visited[v] = 1;
	queue.push_back(v);
	while (queue.size() != 0) {
		int u = queue[0];	//ȡ����Ԫ��
		queue.erase(queue.begin());	//�˶���
		Node* head = (g->adjlist + u)->headEdge;
		int pre = u + 1;	//preΪ����������һ�����(parent)

		while (head) {	//ֻҪ��㲻Ϊ��
			int newV = head->nodeName - 1;
			if (!visited[newV]) {	//ֻҪδ������
				visited[newV] = 1;
				tree->parent[tree->preSite] = pre;
				tree->edge[tree->preSite] = head->edgeLen;
				tree->son[tree->preSite] = newV + 1;	//ͼ�ж��㷶ΧΪ0��n-1����������+1
				tree->preSite++;
				queue.push_back(newV);	//�����
			}
			head = head->next;	//�������ƶ�
		}
	}
}

//������㼯
void showTreeVertex() {
	if (tree->parent[0] == -1) {	//��㲻��ͨ
		cout << "�ý�㲻��ͨ���ޱ�������";
		return;
	}
	cout << tree->parent[0] << " ";
	for (int i = 0; i < tree->tree_len - 1; i++)
	{
		if (tree->son[i] == -1) return;
		cout << tree->son[i] << " ";	//son[i]Ϊ��һ�������õ��Ľ��
	}
}

//����߼�
void showTreeEdge() {
	for (int i = 0; i < tree->tree_len - 1; i++)
	{
		if (tree->parent[i] == -1) {
			if (i == 0) cout << "�ý�㲻��ͨ���ޱ�������";
			return;
		}
		cout << tree->edge[i] << "(" << tree->parent[i] << "��" << tree->son[i] << ") ";
	}
}

//����ͼ���ͷſռ�
void delelteGraph(ALGraph *g) {
		if (g->adjlist) free(g->adjlist);
}