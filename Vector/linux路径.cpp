#include<iostream>
#include<string>
#include<vector>
using namespace std;
string simplifyPath(string 	path) {
	vector<string> temp;
	int len=path.size();
	for(int i=0;i<len;){
		if(path[i]=='/')
			i++;
		else{
			int now_index=i;//记录起始位置
			while(i<len&&path[i]!='/'){
				i++;
			}
			string s=path.substr(now_index,i-now_index);
			/*s.substr(int a,int b)的用法是从第a个到
			第b个复制字符串s，要包括<cstring>使用*/
			if(s==".."&&!temp.empty()){
			//容器不为空且要返回上一级
				temp.pop_back();
			}
			else if(s!="."&&s!=".."){
				temp.push_back(s);
			}
		}
	}
	if(temp.empty())
		return "/";
	string res;
	for(string& s:temp){//遍历temp容器里的字符串，起名叫s
		res+="/"+s;
	}
	return res;
}
int main(){
    string path;
    cin>>path;
    string res = simplifyPath(path);
    cout<<res;
}