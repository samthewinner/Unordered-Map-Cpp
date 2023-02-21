#include <bits/stdc++.h>
typedef std::vector<int> veci;
#define eb emplace_back
#define print(a) for(auto it:a) std::cout<<it<<" ";
#define ll long long 

using namespace std;

class node{
    public:
    node* next;
    node* prev;
    pair<ll,ll>p;
    
    node(pair<ll,ll>p){
        next = prev = NULL;
        this->p.first = p.first;
        this->p.second = p.second;
    }
};

class hmap{
    private:
    node* a[10];
    int m_size;
           
    int hash_function(ll key){
        return key%m_size;
    }
    void deleteNode(node* temp,int pos){
        // only element in the bucket
        if(temp->next == NULL and temp->prev == NULL){delete temp;a[pos] = NULL;}
        // head of the bucket
        if(temp->prev == NULL){
            node* n = temp->next;
            n->prev = NULL;
            temp->next = NULL;
            a[pos] = n;
            delete temp;
            
        }
        // for last element
        if(temp->next == NULL){
            temp->prev->next = NULL;
            temp->prev = NULL;
            delete temp;
                      
        }
        // for middle elements
        else if(temp->next and temp->prev){
            temp->next->prev = temp->prev;
            temp->prev->next = temp->next;
            delete temp;
            
        }
        temp=NULL;
        return;
    }

    
    public:

    hmap(){        
        m_size = 10;
        for(int i=0;i<m_size;i++)
            a[i] = NULL;
    } 

    void printMap(){
        for(int i=0;i<m_size;i++){
            node* temp = a[i];
            while(temp){
                cout<<temp->p.first<<" "<<temp->p.second<<endl;
                temp = temp->next;
            }
        }
    }

    void insert(pair<ll,ll> ppair){
        node * n = new node(ppair);
        int pos = hash_function(ppair.first);
        if(a[pos] == NULL){
            a[pos] = n;
            return;
        }
        node* temp = a[pos];
        while(temp){
            if( temp->p.first == ppair.first){temp->p.second = ppair.second;return;}
            temp = temp->next;
            }
        temp->next = n;
        n->prev = temp;
        return;
    }
    bool finD(ll key){
        
            int pos = hash_function(key);
            node* temp = a[pos];
            while (temp)
            {
                if(temp->p.first == key) return true;
                temp = temp->next;
            }
            return false;        
    }
    void deleteKey(ll key){
        bool found = false;
        int pos = hash_function(key);
        node* temp = a[pos];
        try{
            while(temp){
            if(temp->p.first == key){
                deleteNode(temp,pos);
                found = true;
                break;
            }
            temp= temp->next;
        }
            if(found == false)
                {throw " doesn't exist!";}
        }
        // element is absent in the map        
        catch(const char* e){
            cerr<<key<<e<<endl;
        }
        return;
    }
};

int main(){         
    hmap m1;
    cout<<"Size of map: "<<sizeof(m1)<<endl;
    m1.insert({3,4});
    m1.insert({9,4});
    m1.insert({5,6});
    m1.insert({3,4});
    m1.insert({3,5});
   if(m1.finD(3))cout<<"Found 3"<<"\n";
   if(!m1.finD(18))cout<<"18 absent"<<"\n";
   cout<<"MAP b4 deletion\n";       
    m1.printMap();
    m1.deleteKey(31);
    m1.deleteKey(5);
    cout<<"MAP after deletion\n";  
    m1.printMap();
    
}