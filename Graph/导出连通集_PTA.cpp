#include<iostream>
#include<unordered_map>
#include<queue>
using namespace std;
int START = 0;
int V, E;
class Node {
public:
    int vertex;
    Node* next;//下一个邻居
    Node() { vertex = 0; next = NULL; }
    Node(int v) {
        vertex = v;
        next = NULL;
    }
};
class List{
public:
    Node* head;
    Node* tail;
    int NodeCount;
    List() { head = tail = NULL; NodeCount = 0; }
    void Insert(int v);
    void Print();
    
};
void List::Insert(int v) {
    Node *NewNode=new Node(v);
    if (!head) {
        head = tail= NewNode;
        NodeCount++;
        return;
    }
    else {
        Node* pointer = head;
        while (true) {
            if (head->vertex > v) {//插到队头
                head = NewNode;
                head->next = pointer;
                NodeCount++;
                return;
            }
            else {
                if (pointer->next && v > pointer->next->vertex)
                    pointer = pointer->next;
                else if (!pointer->next) {
                    pointer->next = NewNode;
                    tail = NewNode;
                    NodeCount++;
                    return;
                }
                else if (v > pointer->vertex && v < pointer->next->vertex) {
                    NewNode->next = pointer->next;
                    pointer->next = NewNode;
                    NodeCount++;
                    return;
                }
            }
        }
    }
}
void DFS(List *L, int start,unordered_map<int,int>& visited,bool& judge) {
    if (judge) {
        cout << '{';
        if (!visited[start]) {
            cout << ' ' << start;
            visited[start] = 1;
        }
    }
    Node* tmp = L[start].head;
    /*for (int i = 0; i < L[start].NodeCount; i++)*/ while(tmp) {
        if (!visited[tmp->vertex]) {
            cout << ' ' << tmp->vertex;
            visited[tmp->vertex] = 1;
            judge = false;
            DFS(L, tmp->vertex, visited, judge);
        }
        else {
            tmp = tmp->next;
        }
    }
    if (start == START) {
        cout << " }" << endl;
        judge = true;
        for (int i = 0; i < V; i++) {
            if (!visited[i]) {
                START = i;
                DFS(L, i, visited, judge);
            }
        }
    }
}
void BFS(List* L, int start, unordered_map<int, int>& visited, bool& judge) {
    if (judge) {
        cout << '{';
        if (!visited[start]) {
            cout << ' ' << start;
            visited[start] = 1;
        }
    }
    Node* tmp = L[start].head;
    queue<Node*> q;
    while (tmp) {
        if (!visited[tmp->vertex]) {
            q.push(tmp);
            visited[tmp->vertex] = 1;
        }
        judge = false;
        tmp = tmp->next;
    }
    while (!q.empty()) {

        cout << ' ' << q.front()->vertex;
        visited[q.front()->vertex] = 1;
        tmp = L[q.front()->vertex].head;
        while (tmp) {
            if (!visited[tmp->vertex]) {
                q.push(tmp);
                visited[tmp->vertex] = 1;
            }
            judge = false;
            tmp = tmp->next;
        }
        q.pop();
    }
    cout << " }" << endl;
    judge = true;
    for (int i = 0; i < V; i++) {
        if (!visited[i]) {
            BFS(L, i, visited, judge);
        }
    }

}
int main() {
    int v1,v2;
    unordered_map <int,int> visited;//此图用于存储结点是否存在，并且记录最大值
    cin >> V >> E;
    for (int i = 0; i < V; i++) {
        visited[i] = 0;
    }
    List* L=new List[V];
    for (int i = 0; i < E; i++) {
        cin >> v1>>v2;
        L[v1].Insert(v2);
        L[v2].Insert(v1);
    }
    bool judge = true;
    DFS(L, START, visited, judge);
    for (int i = 0; i < V; i++) 
        visited[i] = 0;
    BFS(L, 0,visited, judge);
    return 0;
}

