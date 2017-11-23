#pragma once
using namespace std;

struct TreeNode {
	char val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(char x) : val(x), left(NULL), right(NULL) {}
};

int check_char(char val) {
	if (val == '+' || val == '-' || val == '*' || val == '/' || val == '^') return 1;	// 运算符
	else if (val >= '0' && val <= '9') return -1;
	else if ((val >= 'a' && val <= 'z') || (val >= 'A' || val <= 'Z')) return 0;
}

// 假如当前字符是运算符，就沿着左枝一直往下生成，如果当前位是数字，则向右枝生成，如果右枝也是数字，
// 则向上找到一个缺右枝的节点
// 重要规则: 一个节点的父节点必须是运算符
// VALIDATED
TreeNode* ReadExpr(string exp) {
	TreeNode* head = new TreeNode(exp[0]);
	TreeNode* p = head;
	TreeNode* s;
	vector<TreeNode*> parent;
	string sub = exp;
	int n = sub.size();
	int fg;

	while (n > 1) {
		--n;
		sub = sub.substr(1, n);
		fg = check_char(sub[0]);
		if (check_char(p->val) != 1) {	// 假如当前节点不是运算符，则节点跳转到上一个右节点空置的节点
			if (parent.size() == 0) {
				cout << "ERROR 3!" << endl;
				return nullptr;
			}
			p = *(--parent.end());	//取栈顶
			parent.pop_back();
		}
		if (fg == 1) {
			
			if (p->left == NULL) {
				parent.push_back(p);	// 假如是运算符则当前节点且右子树为空，节点进栈
				p->left = new TreeNode(sub[0]);
				p = p->left;
			}
			else if (p->right == NULL)
			{
				p->right = new TreeNode(sub[0]);
				p = p->right;
			}
			else
			{
				cout << "ERROR 1!" << endl;
			}
		}
		else {
			if (p->left == NULL) {
				parent.push_back(p);
				p->left = new TreeNode(sub[0]);
				p = p->left;
			}
			else if (p->right == NULL) {
				p->right = new TreeNode(sub[0]);
				p = p->right;
			}
			else
			{
				cout << "ERROR 2!" << endl;
			}
		}
	}
	return head;
}

// VALIDATED
void tree_exp_merge(TreeNode* head, string &str) {
	if (head == nullptr) return;
	if (head->left != NULL) str += "(";
	tree_exp_merge(head->left, str);
	str += head->val;
	tree_exp_merge(head->right, str);
	if (head->right != NULL) str += ")";
}

// VALIDATED
string merge_exp(TreeNode* head) {
	string res = "";
	tree_exp_merge(head, res);
	int len = res.size() - 2;
	string ans(res, 1, len);
	return ans;
}

// VALIDATED
void WriteExpr(TreeNode* head) {
	cout << merge_exp(head) << endl;
}

// VALIDATED
void WriteExpr2(TreeNode* head) {
	if (head == nullptr) return;
	if(head->left != NULL) cout << "(";
	WriteExpr(head->left);
	cout << head->val;
	WriteExpr(head->right);
	if (head->right != NULL) cout << ")";
}

// VALIDATED
void Assign(TreeNode *head, char var, int val) {
	if (head == nullptr) return;
	Assign(head->left, var, val);
	if (head->val == var) head->val = '0' + val;
	Assign(head->right, var, val);
}

// VALIDATED
string merge_var(string var_a, string var_b) {
	string ans = var_a;
	for (int i = 0; i < var_b.length(); i++)
	{
		if (ans.find(var_b[i]) == string::npos) {
			ans += var_b[i];
		}
	}
	return ans;
}

// VALIDATED
int cacu_num(int a, int b, char optr) {
	switch (optr)
	{
	case '+':return a + b;
	case '-':return a - b;
	case '*':return a * b;
	case '/':return a / b;
	case '^':return (int)pow(a, b);
	default:
		cout << "CACU ERROR!" << endl;
		return 0;
		break;
	}
}

// VALIDATED
string multiple_string(string a, string b, char optr) {
	int flag = 0;
	for (int i = 0; i < a.length(); i++)
	{
		if (check_char(a[i]) == 0) {
			++flag;
			break;
		}
	}
	for (int i = 0; i < b.length(); i++)
	{
		if (check_char(b[i]) == 0) {
			++flag;
			break;
		}
	}
	if (!flag) {	// 没有变量纯数字的情况
		if (optr == '^') {
			int ans = (int)pow(stoi(a), stoi(b));
			return to_string(ans);
		}
		return to_string(cacu_num(stoi(a), stoi(b), optr));	// 直接计算即可
	}

	if (optr != '*') return "(" + a + optr + b + ")";
	if(a[0] == '(' || b[0] == '(') return "(" + a + optr + b + ")";
	int sp_site1 = 0, sp_site2 = 0;
	string num_a = "", num_b = "";	// num_a表示a的系数

	for (int i = 0; i < a.length(); i++)
	{
		sp_site1 = i;
		if (a[i] >= '9' || a[i] <= '0') break;
		num_a += a[i];
	}
	string var_a(a, sp_site1);	// var_a表示a的变量
	for (int i = 0; i < b.length(); i++)
	{
		sp_site2 = i;
		if (b[i] >= '9' || b[i] <= '0') break;
		num_b += b[i];
	}
	string var_b(b, sp_site2);
	if (num_a == "") num_a = "1";
	if (num_b == "") num_b = "1";

	if (var_a[0] >= '0' && var_a[0] <= '9') var_a = "";	//说明字符串a为1位数
	if (var_b[0] >= '0' && var_b[0] <= '9') var_b = "";

	// VALIDATED
	int rel_num_a = stoi(num_a);
	int rel_num_b = stoi(num_b);

	int ans = rel_num_a * rel_num_b;
	string res = to_string(ans);
	string var = merge_var(var_a, var_b);	// 合并两个变量
	return res + var;
}

// VALIDATED
string Value2(TreeNode *head) {
	string ans = "";
	TreeNode* p = head->left;
	vector<TreeNode*> pre = { head };
	cout << "注意：表达式中的'/'会自动四舍五入" << endl;
	while (pre.size() != 0) {
		while (p != nullptr) {
			pre.push_back(p);
			p = p->left;
		}
		pre.pop_back();
		while (*(--pre.end()) != head) {	// 只要栈顶元素不是头节点

		}
	}
	return nullptr;
}

// VALIDATED
string parse_str(TreeNode* head) {
	string left_merge = "", right_merge = "", ans = "";
	if (check_char(head->val) == 1) {
		left_merge = parse_str(head->left);
		right_merge = parse_str(head->right);
		ans = multiple_string(left_merge, right_merge, head->val);
		return ans;
	}
	else return ans + head->val;

}

// VALIDATED
string Value(TreeNode* head) {
	string null_string = "";
	if (head->left == nullptr) return null_string + head->val;	// 只有一位数字的情况
	string value = parse_str(head);
	if (value[0] != '(') return value;
	string res(value, 1, value.size() - 2);
	return res;
}

// VALIDATED
TreeNode* CompoundExpr(char p, TreeNode* e1, TreeNode* e2) {
	TreeNode* ans = new TreeNode(p);
	ans->left = e1;
	ans->right = e2;
	return ans;
}