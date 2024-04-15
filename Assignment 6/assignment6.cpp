/*
Name - Tirthraj Mahajan
SE - 02 Roll No: 21242
Represent a given graph using adjacency list to perform DFS and BFS.
*/

#include <iostream>
#include <limits.h>
#include <queue>
#include <stack>
using namespace std;

/*

This implementation assumes that the vertex name maps with the array index
So if you want to modify that, then you'd have to create a function for the name to index conversion

*/

class Node {
private:
    int vertex;
    int weight;
    Node *next;

public:
    Node() : vertex(0), weight(INT_MAX), next(nullptr) {}
    Node(int vertex, int weight) : vertex(vertex), weight(weight), next(nullptr) {}
    Node(int vertex, int weight, Node *next) : vertex(vertex), weight(weight), next(next) {}
    friend class Graph;
};

class Graph {
private:
    Node **adj; // Array of List of Nodes
    int nodes;  // Total number of Nodes
    bool direction; // direction = 0 Undirected and direction = 1 Directed

public:    
    Graph(int nodes = 0, bool direction = 0):nodes(nodes), direction(direction){

        // Initializing the adjacency list

        for(int i=0; i<nodes; i++){
            adj[i] = NULL;
        }

    }

    void addEdge(int u, int v, int weight=1){

        // Checking for an invalid edge just in case so no run-time or logical errors

        if(u<0 || v<0 || u >= nodes || v >= nodes){
            cout<<"You Entered : "<<u<<" -> "<<v<<endl;
            cout<<"Invalid Edge"<<endl;
            return;
        }

        // Directed Graph
        if(direction){
            push_back(u, v, weight);
        }
        else{       // Undirected
            push_back(u, v, weight);
            push_back(v, u, weight);
        }
    }

    // This function will add a new node containing v in the list at index u
    void push_back(int u, int v, int weight){
        // No need to error check as we are already doing that in addEdge function

        if( adj[u] == NULL ){
            adj[u] = new Node( v , weight );
            return;
        }

        Node* newNode = new Node( v, weight );
        newNode->next = adj[u];
        adj[u] = newNode;    
    }


    // prints the adjacency list along with the weights in the brackets
    void print(){
        cout<<"Printing the adjacency list of the graph"<<endl;
        cout<<"Vertices: "<<endl;
        for(int i=0; i<nodes; i++){
            cout<<i<<" -> ";
            Node* curr = adj[i];
            while(curr!=NULL){
                cout<<curr->vertex<<" ";
                // cout<<curr->vertex<<" ("<<curr->weight<<") ,";
                curr = curr->next;
            }
            cout<<endl;
        }
    }
    
    void bfs(int start = 0){
        // Since we are mapping index to vertex, we can directly do this
        bool* visited = new bool[nodes];
        for(int i=0; i<nodes; i++){
            visited[i] = false;
        }
        
        // This will allow us to check if a vertex has been visited or not in O(1) rather than O(n)
        
        queue<int> q;
        q.push(start);
        visited[start] = true;
        while(!q.empty()){
            int vertex = q.front();
            
            cout<<vertex<<" ";
            
            q.pop();
            
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
    }

    void dfs(int start=0){
        // Since we are mapping index to vertex, we can directly do this
        bool* visited = new bool[nodes];
        for(int i=0; i<nodes; i++){
            visited[i] = false;
        }
        
        // This will allow us to check if a vertex has been visited or not in O(1) rather than O(n)
        
        stack<int> st;
        st.push(start);
        visited[start] = true;
        
        while(!st.empty()){
            int vertex = st.top();
            st.pop();
            
            // if(vertex[visited]==false){
            cout<<vertex<<" ";
                // visited[vertex] = true;
            // }
            
            Node* curr = adj[vertex];
            
            while(curr){
                if(visited[curr->vertex]==false){
                    st.push(curr->vertex);
                    visited[curr->vertex] = true;
                }
                
                curr = curr->next;
            }
            
        }
        
        cout<<endl;
        
        
    }

};


int main(){
    //https://www.javatpoint.com/bfs-vs-dfs
    Graph G(7,0);
    G.addEdge(0,1);
    G.addEdge(0,3);
    G.addEdge(1,3);
    G.addEdge(1,2);
    G.addEdge(2,3);
    G.addEdge(1,5);
    G.addEdge(2,5);
    G.addEdge(1,6);
    G.addEdge(6,4);
    G.addEdge(4,2);
    G.addEdge(4,3);
    G.print();
    G.bfs();
    G.dfs();
    
}
