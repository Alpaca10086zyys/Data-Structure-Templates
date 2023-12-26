#include<iostream>
using namespace std;
void preorder(char* str, int pos, string& input,int &index) {
    if (pos <= input.size()) {
        str[pos] = input[index++];
        preorder(str, pos * 2, input,index);
        preorder(str, pos * 2 + 1, input,index);
    }
}
void postorder(char* str, int pos, int size) {
    if (pos <= size) {
        postorder(str, pos * 2, size);
        postorder(str, pos * 2+1, size);
        cout << str[pos];
    }
}
int main() {
    string input;
    cin >> input;
    char* BinTree = new char[input.size() + 1];
    int index = 0;
    preorder(BinTree, 1, input,index);//建树
    postorder(BinTree, 1, input.size());
    return 0;
}
