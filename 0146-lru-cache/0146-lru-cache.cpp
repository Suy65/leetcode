class LRUCache {
public:
    class node{
        public:
        int key;
        int value;
        node *next;
        node *prev;
        node(int _key ,int _val){
            key=_key;
            value=_val;
        }
    };
    node *head=new node(-1,-1);
    node *tail=new node(-1,-1);
    int cap;
    unordered_map<int,node*>m;
    
    LRUCache(int capacity) {
        cap=capacity;
        head->next=tail;
        tail->prev=head;
    }
    void addNode(node *newnode){
        node *temp=head->next;
        newnode->next=temp;
        newnode->prev=head;
        head->next=newnode;
        temp->prev=newnode;
    } 
    void deleteNode(node* delnode){
        node*delprev=delnode->prev;
        node*delnext=delnode->next;
        delprev->next=delnext;
        delnext->prev=delprev;
    }
    
    int get(int key) {
        if(m.find(key)!=m.end()){
            node *resnode= m[key];
            int res=resnode->value;
            m.erase(key);
            deleteNode(resnode);
            addNode(resnode);
            m[key]=head->next;
            return res;
        }
        return -1;
    }
    
    void put(int key, int value) {
        if(m.find(key)!=m.end()){
            node*existingnode=m[key];
            m.erase(key);
            deleteNode(existingnode);
        }
        if(m.size()==cap){
            m.erase(tail->prev->key);
            deleteNode(tail->prev);
        }
        addNode(new node(key,value));
        m[key]=head->next;
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */