#include <iostream>
#include <string>
#include <limits.h>
using namespace std;

class GraphNode{
private:
    int vertex;
    int weight;
    GraphNode* next;
public:
    GraphNode(int vertex=0, int weight=1, GraphNode* next=NULL):vertex(vertex),weight(weight),next(next){}

    friend class Graph;
};

class Graph{
private:
    GraphNode** adj;
    string* cityNames;
    int nodes;
    bool direction;

    void push_back(int u, int v, int weight){
        GraphNode* newNode = new GraphNode(v,weight);
        newNode->next = adj[u];
        adj[u] = newNode;
    }

public:
    Graph(int nodes, bool direction = 0):nodes(nodes), direction(direction){
        adj = new GraphNode*[nodes];
        cityNames = new string[nodes];
        for(int i=0; i<nodes; i++){
            adj[i] = NULL;
            cityNames[i] = to_string(i);
        }
    }

    void addCities(string* cities){
        if(cities == NULL){
            cout<<"Error: Cities array is NULL"<<endl;
            return;
        }
        for(int i=0; i<nodes; i++){
            cityNames[i] = cities[i];
        }
    }


    void addEdge(int u, int v, int weight = 1){
        if(u < 0 || v < 0 || u >= nodes || v >= nodes){
            cout<<"Error: invalid edge entered"<<endl;
            return;
        }

        if(direction){
            push_back(u,v,weight);
        }
        else{
            push_back(u,v,weight);
            push_back(v,u,weight);
        }

    }

    void printAdjacencyList(){
        cout<<"---------- Adjacency List ----------"<<endl;
        for(int i=0; i<nodes; i++){
            cout<<cityNames[i]<<" -> ";
            GraphNode* curr = adj[i];
            while(curr){
                cout<<cityNames[curr->vertex]<<" ";
                curr = curr->next;      
            }
            cout<<endl;
        } 
        cout<<"---------- END ----------"<<endl;
    }

    void prims(int start=0){
        int* keys = new int[nodes];
        bool* visited = new bool[nodes];
        int* parent = new int[nodes];

        for(int i=0; i<nodes; i++){
            keys[i] = INT_MAX;
            visited[i] = false;
            parent[i] = -1;
        }

        keys[start] = 0;

        int totalWeight = 0;

        for(int i = 0; i<nodes; i++){

            int min = INT_MAX;
            int minVertex = -1;

            for(int j=0; j<nodes; j++){
                if(keys[i]<min && visited[i] == false){
                    min = keys[i];
                    minVertex = i;
                }
            }

            visited[minVertex] = true;
            totalWeight += min;

            GraphNode* curr = adj[minVertex];
            while(curr){
                if(visited[curr->vertex]==false && curr->weight < keys[curr->vertex]){
                    keys[curr->vertex] = curr->weight;
                    parent[curr->vertex] = minVertex;
                }
                curr = curr->next;
            }

        }

        cout<<"---------- PRIM'S MST ALGORITHM ----------"<<endl<<endl;

        for(int i=0; i<nodes; i++){
            if(parent[i]==-1) continue;
            cout<<cityNames[parent[i]] << " - "<<cityNames[i] << " ("<<keys[i]<<") "<<endl;
        }

        cout<<"--- TOTAL WEIGHT = "<<totalWeight<<" ---"<<endl<<endl;

        cout<<"---------- END ----------"<<endl;

    }

    
};

int main(){

    /*
    Why Prim’s Algorithm Fails for Directed Graph ?

    Prim’s algorithm assumes that all vertices are connected. But in a directed graph, every node is not reachable from every other node. So, Prim’s algorithm fails due to this reason.
    
    */


    Graph G(9);
    
    string cities[] = {"Pune","Mumbai","Nashik","Thane","Latur","Kolhapur","Solapur","Sangli","Ratnagiri"};
    
    G.addCities(cities);
    
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

    G.printAdjacencyList();
    
    G.prims(0);

}