#include<iostream>
using namespace std;
class Child{
public:
    int id;
    Child* next;
    Child(int n){
        id=n;
    }
};
class List{
public:
    Child *first;
    Child *last;
    int nodecount;
    List(){}
    List(int n){
        nodecount=n;
        first=new Child(1);
        first->next=last;
        last->next=first;
        for(int i=2;i<=n;i++){
            Child* tmp=new Child(i);
            last->next=tmp;
            last=last->next;
            last->next=first;
        }
    }
    void CountRemove(int count);
};
void List :: CountRemove(int count){
    Child* tmp=first;
    bool IsFirst=true;
    while(nodecount--){
        for(int i=0;i<count-2;i++){
            tmp=tmp->next;
        }
        if(IsFirst){
            IsFirst=false;
            cout<<tmp->next->id;
            tmp->next=tmp->next->next;
        }
        else{
            cout<<"->"<<tmp->next->id;
            tmp->next=tmp->next->next;
        }
    }
}
int main(){
    int n,k;
    cin >> n >> k;
    List Children(n);
    Children.CountRemove(k);
    return 0;
}