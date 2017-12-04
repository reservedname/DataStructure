#pragma once
#include "stdafx.h"
using namespace std;
#define HASH_LENTH 50
#define NAME_LENTH 30
#define M 47

struct Name
{
	string name;
	int key;	//姓名的关键值
};

struct HashTable
{
	string hash_name;
	int hash_key;
	int st;	// search times
};

Name str_name[HASH_LENTH];
HashTable hash_table[HASH_LENTH];

int addAscall(string str) {
	int len = str.size();
	int sum = 0;
	for (int i = 0; i < len; i++)
	{
		sum += str[i] - '0';
	}
	return sum;
}

//初始化姓名表
void initNameTable(vector<string> str) {
	for (int i = 0; i < NAME_LENTH; i++)
	{
		str_name[i].name = str[i];
		str_name[i].key = addAscall(str[i]);
	}
}

//初始化散列表
void initHashTable() {
	for (int i = 0; i < HASH_LENTH; i++)
	{
		hash_table[i].hash_name = "";
		hash_table[i].hash_key = 0;
		hash_table[i].st = 0;
	}
}

//创建哈希表
void createHashTable(vector<string> str) {
	initNameTable(str);
	initHashTable();

	int count_st = 1;	//记录查找次数
	int addr = -1;	//记录地址值
	int d = -1;
	for (int i = 0; i < HASH_LENTH; i++)
	{
		count_st = 1;
		addr = str_name[i].key % M;	//哈希函数
		d = addr;

		if (hash_table[addr].st == 0) {	//不发生冲突
			hash_table[addr].hash_name = str_name[i].name;
			hash_table[addr].hash_key = str_name[i].key;
			hash_table[addr].st = 1;
		}
		else
		{	//伪随机探测再散列法处理冲突
			while (hash_table[d].hash_key != 0) {	//只要还有冲突
				d = (d + str_name[i].key % 10 + 1) % M;
				++count_st;
			}
			hash_table[d].hash_name = str_name[i].name;
			hash_table[d].hash_key = str_name[i].key;
			hash_table[d].st = count_st;
		}
	}
}

void HashFind(string name) {
	int asc = addAscall(name);
	int addr = asc % M;
	int d = addr;

	if (hash_table[addr].hash_key == asc && name == hash_table[addr].hash_name) {	//一次就查找到
		cout << "NAME: " << hash_table[addr].hash_name << "  KEY: " << hash_table[addr].hash_key
			<< " SEARCH_LENTH: " << hash_table[addr].st << endl;
	} else if (hash_table[addr].hash_key == 0) {	//地址上为空
		cout << "CAN'T FIND ANY RECORDS" << endl;
	} else {
		int count_st = 0;
		while (true) {
			d = (d + asc % 10 + 1) % M;
			++count_st;
			if (hash_table[d].hash_key == 0) {	//依然没找到
				cout << "CAN'T FIND ANY RECORDS" << endl;
				return;
			}
			else if (hash_table[d].hash_key == asc) {
				cout << "NAME: " << hash_table[d].hash_name << "  KEY: " << hash_table[d].hash_key
					<< " SEARCH_LENTH: " << hash_table[d].st << endl;
				return;
			}
		}
	}
	return;
}