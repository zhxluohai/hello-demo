#include <iostream>
#include <vector>
#include <string>
using namespace std;

// 【合并版 KMP】内部自动计算 next，不需要单独调用 getNext
int kmp(const string& mainStr, const string& pattern) 
{
	int n = mainStr.size();   // 主串长度
	int m = pattern.size();   // 模式串长度
	
	if (m == 0) return 0;     // 空串直接返回0
	
	// ======================
	// 第一步：内部生成 next 数组
	// ======================
	vector<int> next(m, -1);
	int j = 0, k = -1;
	while (j < m - 1) {
		if (k == -1 || pattern[j] == pattern[k]) {
			j++;
			k++;
			next[j] = k;
		} else {
			k = next[k];
		}
	}
	
	// ======================
	// 第二步：开始 KMP 匹配
	// ======================
	int i = 0; // 主串指针
	j = 0;     // 模式串指针（重置）
	
	while (i < n && j < m) {
		if (j == -1 || mainStr[i] == pattern[j]) {
			i++;
			j++;
		} else {
			j = next[j]; // 跳转
		}
	}
	
	// 匹配成功返回起始位置，失败返回 -1
	return (j == m) ? (i - j) : -1;
}

// 测试
int main() {
	string mainStr = "ababcabcac";
	string pattern = "abcac";
	
	int index = kmp(mainStr, pattern);
	cout << "出现位置：" << index << endl;
	return 0;
}
