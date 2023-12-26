#include<iostream>
#include<cmath>
#include<algorithm>
#include<queue>
using namespace std;
int num = 0;
class Node {
public:
    int val;
    Node* left;
    Node* right;
    int height;//节点高度
    Node() {}
    Node(int v) { val = v; left = NULL; right = NULL; height = 1; }
};

int height(Node* n) {
    return n == NULL ? 0 : n->height;
}
Node* right_rotate(Node* node) { //右旋转，以参数node为轴做右旋转操作，并把新的根结点返回

    //节点旋转
    Node* child = node->left;
    node->left = child->right;
    child->right = node;

    //高度更新 先node,再child，注意：此时的child已经是该子树的根结点了，实质上是从下往上
    node->height = max(height(node->left), height(node->right)) + 1;
    child->height = max(height(child->left), height(child->right)) + 1;

    return child;
}

Node* left_rotate(Node* node) { //左旋转，以参数node为轴做左旋转操作，并把新的结点返回

    //节点旋转
    Node* child = node->right;
    node->right = child->left;
    child->left = node;

    //高度更新 先node,再child，注意：此时的child已经是该子树的根结点了，实质上是从下往上
    node->height = max(height(node->left), height(node->right)) + 1;
    child->height = max(height(child->right), height(child->left)) + 1;

    return child;
}

Node* left_right(Node* node) {
    //先做左旋
    node->left=left_rotate(node->left);//子树做左旋，并将根结点的左指针指向旋转后的子树根结点
    return right_rotate(node);//返回右旋转后的根结点
}

Node* right_left(Node* node) {
    //先做右旋
    node->right = right_rotate(node->right);//子树做右旋，并将根结点的左指针指向旋转后的子树根结点
    return left_rotate(node);//返回左旋转后的根结点
}

Node* Insert(Node* root,Node* n) {
    if (!root) {
        return n;
    }
    if (root->val > n->val) {//往左
        root->left = Insert(root->left, n);
        //回溯时判断节点是否失衡
        if (height(root->left) - height(root->right) > 1) {//root左子树太高
            if (height(root->left->left) >= height(root->left->right)) {
                //结点失衡LL情况
                root= right_rotate(root);
            }
            else {
                //LR
                root = left_right(root);
            }
        }
        
    }
    else if (root->val < n->val) {
        root->right = Insert(root->right, n);
        //回溯时判断节点是否失衡
        if (height(root->right) - height(root->left) > 1) {
            if (height(root->right->right) >= height(root->right->left)) {
                //结点失衡RR情况
                root = left_rotate(root);
            }
            else {
                //RL
                root = right_left(root);
            }
        }
    }
    //子树中增加了新的结点，在回溯时检测更新节点高度
    root->height = max(height(root->left), height(root->right)) + 1;

    return root;
}
// 判断是否为完全二叉树
bool isCompleteBinaryTree(Node* root) {
    if (root == NULL)
        return true;

    queue<Node*> q;
    q.push(root);
    bool flag = false;

    while (!q.empty()) {
        Node* node = q.front();
        q.pop();
        if (node->left) {
            // 如果之前出现了空节点，但当前节点有左子节点或右子节点，则不是完全二叉树
            if (flag)
                return false;
            q.push(node->left);
        }
        else {
            // 如果当前节点没有左子节点但有右子节点，则标记之后的节点必须是叶子节点
            flag = true;
        }
        if (node->right) {
            // 如果之前出现了空节点，但当前节点有右子节点，则不是完全二叉树
            if (flag)
                return false;
            q.push(node->right);
        }
        else {
            // 如果当前节点没有右子节点，则标记之后的节点必须是叶子节点
            flag = true;
        }
    }
    return true;
}

int main() {
    int N,val;
    cin >> N;
    cin >> val;
    Node* Root = new Node(val);
    num += 1;
    for (int i = 1; i < N; i++) {
        cin >> val;
        Node* n = new Node(val);
        Root = Insert(Root, n);
        num += 1;
    }
    queue <Node*> q;
    q.push(Root);
    while (!q.empty()) {
        if (q.front()->left)
            q.push(q.front()->left);
        if (q.front()->right)
            q.push(q.front()->right);
        if (num != 1)
            cout << q.front()->val << ' ';
        else
            cout << q.front()->val;
        q.pop();
        num--;
    }
    if (isCompleteBinaryTree(Root))
        cout << "\nYes";
    else
        cout << "\nNo";
    return 0;
}
