#include<bits/stdc++.h>
using namespace std;

class node{
    public: 
        int val;
        node *next,*prev;
        node(int v){
            val=v;
        }
};

class LRUCache {
public:
    
    node *head=new node(-1);
    node *tail=new node(-1);
    int cap;
    map<int,node*> m;
    
    LRUCache(int capacity) {
        cap=capacity;
        head->next=tail;
        tail->prev=head;
        head->prev=tail->next=NULL;
    }
    
    void insert(int val){
        node *temp=new node(val);
        temp->next=head->next;
        temp->prev=head;
        head->next=temp;
        temp->next->prev=temp;
        cap--;
        m[val]=temp;
    }
    
    void Delete(node *t){
        t->prev->next=t->next;
        t->next->prev=t->prev;
        cap++;
        m[t->val]=NULL;
    }
    
    void put(int value) {
        if(m[value]!=NULL) Delete(m[value]);
        else if(!cap) Delete(tail->prev);
        insert(value);
    }
};

int main(){
    int capacity, n;
    cout<<"Enter the maximum number of frames possible: ";
    cin>>capacity;
    LRUCache lru(capacity);
    cout<<"Enter the number of pages invoked: ";
    cin>>n;
    vector<int> v(n);
    cout<<"Enter the sequence of pages invoked: ";
    for(int i=0; i<n; i++) cin>>v[i];
    cout<<"The sequence of pages stored in the frames of physical memory after each page is invoked is :\n";
    for(int i=0; i<n; i++){
        lru.put(v[i]);
        node* temp = lru.head->next;
        while(temp->val != -1){
            cout<<temp->val<<" ";
            temp = temp->next;
        }
        cout<<"\n";
    }
    return 0;
}