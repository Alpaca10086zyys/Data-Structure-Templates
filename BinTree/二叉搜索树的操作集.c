#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct TNode* Position;
typedef Position BinTree;
struct TNode {
    ElementType Data;
    BinTree Left;
    BinTree Right;
};
void PreorderTraversal(BinTree BT); /* 先序遍历，由裁判实现，细节不表 */
void InorderTraversal(BinTree BT);  /* 中序遍历，由裁判实现，细节不表 */

BinTree Insert(BinTree BST, ElementType X);
BinTree Delete(BinTree BST, ElementType X);
Position Find(BinTree BST, ElementType X);
Position FindMin(BinTree BST);
Position FindMax(BinTree BST);

Position FindMin(BinTree BST) {
    if (!BST)
        return NULL;
    else {
        if (BST->Left) 
            return FindMin(BST->Left);
        else
            return BST;
    }
}
Position FindMax(BinTree BST) {
    if (!BST)
        return NULL;
    else {
        if (BST->Right)
            return FindMin(BST->Right);
        else
            return BST;
    }
}
BinTree Insert(ElementType X, BinTree BST)
{
    if (!BST) {
       /*若原树为空，生成并返回一个结点的二叉搜索树*/
        BST = (BinTree)malloc(sizeof(struct TNode));
        BST->Data = X;
        BST->Left = BST->Right = NULL;
    }
    else {/*开始寻找要插入元素的位置*/
        if (X < BST->Data)
            BST->Left = Insert(X, BST->Left);
        //递归插入左子树
        else if (X < BST->Data)
            BST->Right = Insert(X, BST->Right);
        //递归插入右子数
    }
    return BST;
}
BinTree Delete(BinTree BST, ElementType X) {
    if (!BST)
        return NULL;
    Position Tmp;
    if (X < BST->Data) {
        BST->Left = Delete(BST->Left, X);
    }
    else if (X > BST->Data) {
        BST->Right = Delete(BST->Right, X);
    }
    else {//找到节点了
        if (BST->Left && BST->Right) {
            /* 从右子树中找最小的元素填充删除结点 */
            Tmp = FindMin(BST->Right);
            BST->Data = Tmp->Data;
            /* 从右子树中删除最小元素 */
            BST->Right = Delete(BST->Right, BST->Data);
        }
        else { /* 被删除结点有一个或无子结点 */
            Tmp = BST;
            if (!BST->Left)       /* 只有右孩子或无子结点 */
                BST = BST->Right;
            else                   /* 只有左孩子 */
                BST = BST->Left;
            free(Tmp);
        }
    }
    return BST;
}
Position Find(BinTree BST, ElementType X) {
    if (!BST)
        return NULL;
    else {
        if (X < BST->Data)
            BST->Left = Insert(X, BST->Left);
        //递归插入左子树
        else if (X < BST->Data)
            BST->Right = Insert(X, BST->Right);
        else
            return BST;
    }
}
int main()
{
    BinTree BST, MinP, MaxP, Tmp;
    ElementType X;
    int N, i;

    BST = NULL;
    scanf("%d", &N);
    for (i = 0; i < N; i++) {
        scanf("%d", &X);
        BST = Insert(BST, X);
    }
    printf("Preorder:"); PreorderTraversal(BST); printf("\n");
    MinP = FindMin(BST);
    MaxP = FindMax(BST);
    scanf("%d", &N);
    for (i = 0; i < N; i++) {
        scanf("%d", &X);
        Tmp = Find(BST, X);
        if (Tmp == NULL) printf("%d is not found\n", X);
        else {
            printf("%d is found\n", Tmp->Data);
            if (Tmp == MinP) printf("%d is the smallest key\n", Tmp->Data);
            if (Tmp == MaxP) printf("%d is the largest key\n", Tmp->Data);
        }
    }
    scanf("%d", &N);
    for (i = 0; i < N; i++) {
        scanf("%d", &X);
        BST = Delete(BST, X);
    }
    printf("Inorder:"); InorderTraversal(BST); printf("\n");

    return 0;
}
/* 你的代码将被嵌在这里 */