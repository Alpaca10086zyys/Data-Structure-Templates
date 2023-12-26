#include<iostream>
using namespace std;
int dfs(char* pre,char* in,int n){   //求二叉树的高度
    if(n == 0){    //若没有结点，为空树
        return 0;
    }
    int i;
    for(i = 0; i < n; i++){
        if(in[i] == pre[0]){  //找到根结点在中序的位置
            break;
        }
    }
    int left = dfs(pre+1,in,i);  //左子树的深度
    int right = dfs(pre+i+1,in+i+1,n-i-1);   //右子树的深度
    return max(left,right)+1;  //返回左右子树深度的较大值中的较大值+根结点
}
int main(){
    int n;
    cin >> n;
    char pre[n+1],in[n+1];  //先序和中序
    cin >> pre >> in;
    cout << dfs(pre,in,n) << endl;
    return 0;
}