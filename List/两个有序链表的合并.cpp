#include <iostream>
using namespace std;
class Node {
public:
    int num;
    Node* next;
    Node(int tmp) {
        num = tmp;
        next = nullptr;
    }
};
class List {
public:
    Node* head;
    Node* tail;
    int nodeCount;
    List() {
        head = nullptr;
        tail = head;
        nodeCount = 0;
    }
    void Insert(int tmp);
    void Print();
};
void List::Insert(int tmp) {
    Node* tmpNode = new Node(tmp);
    if (head == nullptr) {
        head = tail = tmpNode;
        nodeCount++;
    }
    else {
        if (tmp< head->num){//当前数据小于链表头结点保存的数据
            tmpNode->next = head;
            head = tmpNode;
            nodeCount++;
            return;
        }
        if (tmp > tail->num){//当前数据大于链表尾结点保存的数据
            tail->next = tmpNode;
            tail = tmpNode;
            nodeCount++;
            return;
        }
        Node* curr = head;
        while (curr->next != nullptr) {//寻找合适的插入位置
            if ((curr->num <= tmp) && (curr->next->num > tmp)) {           
                tmpNode->next = curr->next;
                curr->next = tmpNode;
                nodeCount++;
                return;
            }
            curr = curr->next;
        }
    }
}
void List::Print(){
    Node* tmp = head;
    bool judge = true;
    while (tmp) {
        if (judge) {
            cout << tmp->num;
            judge = false;
            tmp = tmp->next;
        }
        else {
            cout << ' ' << tmp->num;
            tmp = tmp->next;
        }
    }
}
List JoinList(List L1, List L2) {
    List L;
    Node* p1 = L1.head;
    Node* p2 = L2.head;
    while (p1 && p2) {
        if (p1->num <= p2->num) {
            if (L.head == nullptr)
                L.head = p1;
            else {
                if (L.tail == nullptr) {
                    L.tail = p1;
                    L.head->next = L.tail;
                }
                else{
                    L.tail->next = p1;
                    L.tail = L.tail->next;
                }
            }
            p1 = p1->next;
        }
        else if (p1->num > p2->num) {
            if (L.head == nullptr)
                L.head = p2;
            else {
                if (L.tail == nullptr) {
                    L.tail = p2;
                    L.head->next = L.tail;
                }
                else {
                    L.tail->next = p2;
                    L.tail = L.tail->next;
                }
            }
            p2 = p2->next;
        }
        
    }
    if (p1) {
        L.tail->next = p1;
    }
    if (p2) {
        L.tail->next = p2;
    }
    return L;
}
int main() {
    List L1;
    int tmp;
    int n1, n2;
    cin >> n1 >> n2;
    for (int i = 0; i < n1; i++) {
        cin >> tmp;
        L1.Insert(tmp);
    }
    List L2;
    for (int i = 0; i < n2;i++) {
        cin >> tmp;
        L2.Insert(tmp);//构造好初始链表
    }
    List L = JoinList(L1, L2);
    L.Print();
    return 0;
}
