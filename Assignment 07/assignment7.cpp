#include <iostream>
#include <string>
#include <limits.h>
using namespace std;

class Node{
private:
    int vertex;
    int weight;
    Node* next;
public:
    Node(int vertex=0,int weight=1, Node* next=NULL):vertex(vertex),weight(weight),next(next){}
    
    friend class Graph;
};

class Graph{
private:
    Node** adj;
    int nodes;
    bool direction; // 0->undirected, 1->directed
    string* cityNames;
public:
    Graph(int nodes, bool direction=0):nodes(nodes),direction(direction){
        adj = new Node*[nodes];
        
        for(int i=0; i<nodes; i++){
            adj[i] = NULL;
        }
        
        
        cityNames = new string[nodes];
        for(int i=0; i<nodes; i++){
            cityNames[i] = to_string(i);
        }
    }
    
    void addCities(string *cities){
        for(int i=0; i<nodes; i++){
            cityNames[i] = cities[i];
        }
    }
    
    void addEdge(int u, int v, int weight=1){
        if(u<0 || v<0 || u >= nodes || v >= nodes){
            cout<<"You Entered : "<<u<<" -> "<<v<<endl;
            cout<<"Invalid Edge"<<endl;
            return;
        }
        
        if(direction){     // directed
            push_back(u,v,weight);    
        }
        else{   // undirected
            push_back(u,v,weight);
            push_back(v,u,weight);
        }
    
    }
    
    void push_back(int u, int v, int weight){
        if(adj[u]==NULL){
            adj[u] = new Node(v,weight);
            return;
        }
        Node* newNode = new Node(v,weight);
        newNode->next = adj[u];
        adj[u] = newNode;
    }
    
    void print(Node** adj){
        for(int i=0; i<nodes; i++){
            cout<<cityNames[i]<<" : ";
            Node* curr = adj[i];
            while(curr){
                cout<<cityNames[curr->vertex]<<" ("<<curr->weight<<"), ";
                curr = curr->next;
            }
            cout<<endl;
        }
    }
    
    Node** getAdj(){
        return adj;
    }
    
    void prims(int start=0){
        int *key = new int[nodes];
        bool *visited = new bool[nodes];
        int *parent = new int[nodes];
        
        for (int i = 0; i < nodes; i++) {
            key[i] = INT_MAX;
            visited[i] = false;
            parent[i] = -1;
        }
        
        key[start] = 0;
        parent[start] = -1;
        
        int totalWeight = 0;
        
        for(int i=0; i<nodes; i++){
            int min = INT_MAX;
            int minVertex = -1;
            for(int j=0; j<nodes; j++){
                if(key[j]<min&&visited[j]==false){
                    min = key[j];
                    minVertex = j;
                }
            }
            visited[minVertex] = true;
            totalWeight += min;
            Node* curr = adj[minVertex];
            while(curr){
                if(visited[curr->vertex]==false&&curr->weight < key[curr->vertex]){
                    key[curr->vertex] = curr->weight;
                    parent[curr->vertex] = minVertex;
                }
                curr = curr->next;
            }
        }
        
        cout<<"MST Edges"<<endl;
        
        for(int i=0; i<nodes; i++){
            if(parent[i]==-1) continue;
            
            cout<<cityNames[parent[i]]<<" -- "<<cityNames[i];
            cout<<" ("<<key[i]<<") "<<endl;
                
        }
        
        cout<<"Total Weight : "<<totalWeight<<endl;
    }
    
};


int main(){
    Graph G(9);
    
    string cities[] = {"Pune","Mumbai","Nashik","Thane","Latur","Kolhapur","Solapur","Sangli","Ratnagiri"};
    
    G.addCities(cities);
    
    // Note: The graph vertex maps to the index of the cities in array
    
    G.addEdge(0,1,4);
    G.addEdge(0,7,8);
    G.addEdge(1,7,11);
    G.addEdge(1,2,8);
    G.addEdge(2,3,7);
    G.addEdge(2,8,2);
    G.addEdge(2,5,4);
    G.addEdge(3,5,14);
    G.addEdge(3,4,9);
    G.addEdge(4,5,10);
    G.addEdge(5,6,2);
    G.addEdge(6,8,6);
    G.addEdge(6,7,1);
    G.addEdge(7,8,7);

    G.print(G.getAdj());
    
    G.prims(0);
}
