#include <iostream>
#include <limits.h>
using namespace std;


class Node{
private:
    int vertex;
    Node* next;
    
public:
    Node(int vertex=0, Node* next=NULL):vertex(vertex),next(next){}
    friend class Graph;
    friend class Queue;
    friend class Stack;
};

class Queue{
private:
    Node* head;
    Node* tail;
    int length;
public:
    Queue():head(NULL),tail(NULL),length(0){}

    bool empty(){
        if(length==0) return true;
        return false;
    }

    void push(int data){
        length = length+1;
        if(head==NULL){
            head = new Node(data);
            tail = head;
            return;
        }
        Node* newNode = new Node(data);
        tail->next = newNode;
        tail = newNode;
    }

    void pop(){
        if(length==0){
            cout<<"Error: Underflow"<<endl;
            return;
        }
        Node* temp = head;
        head = head->next;
        length--;
        delete temp;
    }

    int front(){
        if(length==0){
            cout<<"Error: Underflow"<<endl;
            return INT_MIN;
        }
        return head->vertex;
    }

};

class Stack{
private:
    Node* head;
    int length;
public:
    Stack():head(NULL),length(0){}

    bool empty(){
        if(length==0) return true;
        return false;
    }

    void push(int data){
        Node* newNode = new Node(data);
        newNode->next = head;
        head = newNode;
        length++;
    }

    void pop(){
        if(length==0){
            cout<<"Error: Underflow"<<endl;
            return;
        }
        Node* temp = head;
        head = head->next;
        length--;
    }

    int top(){
        if(length==0){
            cout<<"Error: Underflow"<<endl;
            return INT_MIN;
        }
        return head->vertex;
    }

    void print(){
        if(length==0){
            cout<<"Empty Stack"<<endl;
            return;
        }
        Node* curr = head;
        while(curr){
            cout<<curr->vertex<<" ";
            curr = curr->next;
        }
        cout<<endl;
    }
};


class Graph{
private:
    Node** adj;
    int nodes;
    bool direction;     // direction = 0 -> UNDIRECTED and 1 -> DIRECTED

    void push_back(int u, int v){
        Node* newNode = new Node(v);
        newNode->next = adj[u];
        adj[u] = newNode;
    }

    void recursiveDFS(int source, bool* &visited){
        cout<<source<<" ";
        visited[source] = true;

        Node* curr = adj[source];
        while(curr){
            if(visited[curr->vertex]==false){
                recursiveDFS(curr->vertex, visited);
            }
            curr = curr->next;
        }

    }

public:
    Graph(int nodes=0, bool direction=0):nodes(nodes),direction(direction){
        adj = new Node*[nodes];
        for(int i=0; i<nodes;i++){
            adj[i] = NULL;
        }
    }


    void addEdge(int u, int v){
        if( u < 0 || v < 0 || u >= nodes || v >= nodes ){
            cout<<"Invalid edge u = "<<u<<" v = "<<v<<endl;
            return;
        }

        if(direction){
            push_back(u,v);
        }
        else{
            push_back(u,v);
            push_back(v,u);
        }

    }

    void printAdjacencyList(){
        for(int i=0; i<nodes; i++){
            cout<<i<<" -> ";
            Node* curr = adj[i];
            while(curr){
                cout<<curr->vertex<<" ";
                curr = curr->next;
            }
            cout<<endl;
        }
    }

    void bfs(int start = 0){
        if(start<0 || start>=nodes){
            cout<<"Error: Invalid starting edge"<<endl;
            return;
        }

        bool* visited = new bool[nodes];
        for(int i=0; i<nodes; i++){
            visited[i] = false;
        }

        cout<<"---------- BFS (Non-Recursive) ----------"<<endl;

        Queue q;
        q.push(start);
        visited[start] = true;
        
        while(!q.empty()){
            int vertex = q.front();
            q.pop();
            cout<<vertex<<" ";
            
            Node* curr = adj[vertex];
            while(curr){
                if(visited[curr->vertex]==false){
                    q.push(curr->vertex);
                    visited[curr->vertex] = true;
                }
                curr = curr->next;
            }

        }

        cout<<endl;
        cout<<"---------- END BFS ----------"<<endl;
    }

    void dfs(int start){
        if(start<0 || start>=nodes){
            cout<<"Error: Invalid Starting Edge"<<endl;
            return;
        }

        bool* visited = new bool[nodes];
        for(int i=0; i<nodes; i++){
            visited[i] = false;
        }

        Stack st;
        st.push(start);

        cout<<"---------- DFS (Non-Recursive) ----------"<<endl;


        while(!st.empty()){
            int vertex = st.top();
            st.pop();
            
            if(visited[vertex]==false){
                cout<<vertex<<" ";
                visited[vertex] = true;

                Node* curr = adj[vertex];
                while(curr){
                    if(visited[curr->vertex]==false){
                        st.push(curr->vertex);
                    }
                    curr = curr->next;
                }
            
            }
        }

        cout<<endl;
        cout<<"---------- END DFS ----------"<<endl;


    }

    void recursiveDfsHelperFunction(int start = 0){
        bool* visited = new bool[nodes];
        for(int i=0; i<nodes; i++){
            visited[i] = false;
        }
        cout<<"---------- DFS (Recursive) ----------"<<endl;
        recursiveDFS(start, visited);
        cout<<endl;
        cout<<"---------- END ----------"<<endl;
    }


};


int main(){
    Graph G(7,1);
    G.addEdge(0,1);
    G.addEdge(0,2);
    G.addEdge(1,3);
    G.addEdge(1,4);
    G.addEdge(2,5);
    G.addEdge(2,6);    
    G.printAdjacencyList();
    G.bfs(0);
    G.dfs(0);
    G.recursiveDfsHelperFunction();
    

}