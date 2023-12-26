/* 题目描述 用户输入10进制数字i（-2^31<i<2^31），转为指定的进制数并输出

题目输入：第一行整数i（-2^31<i<2^31） 进制 m (2<=m<=32)超过10的使用A~V大写字母代替。

题目输出：指定的转换后的进制数表示

样例输入输出
样例1
输入:
32 32
输出:
10

样例2
输入:
43 31
输出:
1C

样例3
输入:
-13 12
输出:
-11 */

#include<iostream>
#include<string>
#include<cmath>
#include<algorithm>
using namespace std;
int convert_system(string sys) {//得到进制
	int sys_ = 0;
	for (int i = 0; i < sys.size(); i++) 
		sys_ += (sys[i] - '0') * int(pow(10, sys.size() - i - 1));
	return sys_;
}
char convert_char(int n) {//把某位上的数字转化为字符
	return n > 9 ? 'A' + n - 10 : n+'0';
}
char mode(int n, int sys, int &index) { //取余数
	int res;
	for (int i = 0; i < index + 1; i++) {
		res = n % sys;
		n /= sys;
	}
	if (n != 0)
		index++;
	else index = -1;
	return convert_char(res);
}
string convert(int n,int sys) {
	string res = "";
	string suffix = "";
	if (n < 0) {
		suffix+= '-';
		n = -n; 
	}
	int index = 0;
	while (index != -1) {
		res += mode(n, sys, index);
	}
	res += suffix;
	reverse(res.begin(),res.end());
	return res;
}
int main() {
	int n;
	cin >> n;
	string system;
	cin >> system;
	int sys_int=convert_system(system);//得到进制
	cout << convert(n, sys_int);
	return 0;
}