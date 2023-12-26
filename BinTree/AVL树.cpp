#include <iostream>
#include <time.h>
#include <algorithm>
#include <fstream>
using namespace std;

clock_t start_Insert, stop_Insert;
clock_t start_Find, stop_Find;
clock_t start_Delete, stop_Delete;
double duration_Insert, duration_Find, duration_Delete;//函数经过的时间

class avlNode {
public:
    int key;
    avlNode* left;
    avlNode* right;
    avlNode() {}
    avlNode(int v) { key = v; left = nullptr; right = nullptr; }
};
/*
avlNode* LL(avlNode* root) {
    avlNode* t = root->left;
    root->left = t->right;
    t->right = root;
    return t;
}
avlNode* RR(avlNode* root) {

    avlNode* t = root->right;
    root->right = t->left;
    t->left = root;
    return t;
}
avlNode* LR(avlNode* root) {
    root->left = RR(root->left);
    return LL(root);
}
avlNode* RL(avlNode* root) {
    root->right = LL(root->right);
    return RR(root);
}
*/
avlNode* RR(avlNode* y) {
    avlNode* x = y->left;
    avlNode* T2 = x->right;

    // 旋转
    x->right = y;
    y->left = T2;

    // 更新高度
    //y->height = max(height(y->left), height(y->right)) + 1;
    //x->height = max(height(x->left), height(x->right)) + 1;

    // 返回新的根节点
    return x;
}
avlNode* LR(avlNode* x) {
    avlNode* y = x->right;
    avlNode* T2 = y->left;

    // 旋转
    y->left = x;
    x->right = T2;

    // 更新高度
    //x->height = max(height(x->left), height(x->right)) + 1;
    //y->height = max(height(y->left), height(y->right)) + 1;

    // 返回新的根节点
    return y;
}
avlNode* minValueavlNode(avlNode* root) {
    avlNode* curr = root;
    /* 循环查找最左边的叶节点 */
    while (curr->left != NULL)
        curr = curr->left;
    return curr;
}
int getheight(avlNode* root) {
    if (root == nullptr) {
        return 0;
    }
    return max(getheight(root->left), getheight(root->right)) + 1;
}
int getBalance(avlNode* N) {
    if (N == NULL)
        return 0;
    return getheight(N->left) - getheight(N->right);
}
avlNode* Insert(int key, avlNode* root) {
    /* 1. 正常的BST插入 */
    if (root == NULL) {
        avlNode* tmp = new avlNode(key);
        return tmp;
    }
    if (key < root->key)
        root->left = Insert(key,root->left);
    else if (key > root->key)
        root->right = Insert(key,root->right);
    else // 不允许重复键
        return root;

    /* 2. 更新节点的高度 */
    //avlNode->height = 1 + max(height(avlNode->left), height(avlNode->right));
    /* 3. 获取平衡因子以检查此节点是否失衡 */
    int balance = getBalance(root);
    // 如果节点失衡，则有四种情况
    // 左左情况
    if (balance > 1 && key < root->left->key)
        return RR(root);
    // 右右情况
    if (balance < -1 && key > root->right->key)
        return LR(root);
    // 左右情况
    if (balance > 1 && key > root->left->key) {
        root->left = LR(root->left);
        return RR(root);
    }
    // 右左情况
    if (balance < -1 && key < root->right->key) {
        root->right = RR(root->right);
        return LR(root);
    }
    /* 返回未改变的节点指针 */
    return root;
}
avlNode* Delete(int key, avlNode* root) {
    // STEP 1: 正常的BST删除
    if (root == NULL)
        return root;
    // 如果要删除的键小于根的键，则它在左子树中
    if (key < root->key)
        root->left = Delete(key,root->left);
    // 如果要删除的键大于根的键，则它在右子树中
    else if (key > root->key)
        root->right = Delete(key,root->right);
    // 如果键和根的键相同，则这是要删除的节点
    else {
        // 节点有一个或没有子节点
        if ((root->left == NULL) || (root->right == NULL)) {
            avlNode* temp = root->left ? root->left : root->right;

            // 没有子节点的情况
            if (temp == NULL) {
                temp = root;
                root = NULL;
            }
            else // 一个子节点的情况
                *root = *temp; // 复制非空子节点的内容到这个节点
            delete temp;
        }
        else {
            // 两个子节点的情况：获取中序后继（最小值在右子树）
            avlNode* temp = minValueavlNode(root->right);

            // 将后继的内容复制到这个节点
            root->key = temp->key;

            // 删除后继
            root->right = Delete( temp->key, root->right);
        }
    }
    // 只有一个节点的情况
    //if (root == NULL)
        //return root;


    // STEP 2: 获取平衡因子以检查此节点是否失衡
    int balance = getBalance(root);

    // 如果节点失衡，则有四种情况

    // 左左情况
    if (balance > 1 && getBalance(root->left) >= 0)
        return RR(root);

    // 左右情况
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = LR(root->left);
        return RR(root);
    }

    // 右右情况
    if (balance < -1 && getBalance(root->right) <= 0)
        return LR(root);

    // 右左情况
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = RR(root->right);
        return LR(root);
    }
    return root;
}
avlNode* Find(int key, avlNode* root) {
    while (key != root->key) {
        if (root == nullptr)
            return nullptr;
        if (key > root->key)
            root = root->right;
        else if (key < root->key)
            root = root->left;
    }
    return root;
}

int main() {
    /*
    avlNode* root=nullptr;
    ifstream inputFile("C:/Users/20991/Desktop/Data_Tree/operation_1_20.txt"); //打开输入文件
    ofstream outputFile("C:/Users/20991/Desktop/Data_Tree/output_1_AVL.txt");  // 打开输出文件
    cout << "Success open！";
    outputFile << "operation_1:" << endl;
    //读入数据到程序
    long long count;
    long long val;
    for (int i = 0; i < 20; i++) {
        inputFile >> count;
        avlNode* Root = nullptr;
        start_Insert = clock();
        for (long long j = 0; j < count; j++) {
            inputFile >> val;
            Root=Insert(val, Root);
        }

        stop_Insert = clock();
        duration_Insert = ((double)(stop_Insert - start_Insert)) / CLK_TCK;
        outputFile << "N=" << count << " Insert_time:" << duration_Insert << endl;

        start_Find = clock();
        for (int j = 0; j < 1000; j++) {
            inputFile >> val;
            Find(val, Root);
        }
        stop_Find = clock();
        duration_Find = ((double)(stop_Find - start_Find)) / CLK_TCK;
        outputFile << "N=" << count << " Find_time:" << duration_Find << endl;

        start_Delete = clock();
        for (long long j = 0; j < count; j++) {
            inputFile >> val;
            Root = Delete(val, Root);
        }
        stop_Delete = clock();
        duration_Delete = ((double)(stop_Delete - start_Delete)) / CLK_TCK;
        outputFile << "N=" << count << " Delete_time:" << duration_Delete << endl;

        cout << i << "ok!" << endl;
    }
    inputFile.close();
    outputFile.close();  // 关闭文件
    cout << "finish";
    */
    int a[10]={ 5,2,9,6,8,3,7,4,1,10 };
    avlNode* root = nullptr;
    for (int i = 0; i < 10; i++) {
        root = Insert(a[i], root);
    }
    Find(a[3], root);
    for (int j = 0; j < 10; j++)
        root = Delete(a[j], root);
    return 0;
}