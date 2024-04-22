/*
To write a program for Graph creation and find its minimum cost using

Prim’s or Kruskal’s algorithm.
*/


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
    Node(int vertex=0, int weight=1, Node* next=NULL):vertex(vertex),weight(weight),next(next){}
    friend class Graph;
};

class Graph{
private:
    Node** adj;
    string* cityNames;
    int nodes;
public:
    Graph(int nodes):nodes(nodes){
        adj = new Node*[nodes];
        cityNames = new string[nodes];
        for(int i=0; i<nodes; i++){
            adj[i] = NULL;
            cityNames[i] = to_string(i);
        }
    }


    void addCities(string* cities){
        for(int i=0; i<nodes; i++){
            cityNames[i] = cities[i];
        }
    }

    void addEdge(int u, int v, int weight=1){
        // base condition
        if(u<0||v<0||u>=nodes||v>=nodes){
            cout<<"Invalid entry"<<endl;
            return;
        }

        // undirected graph
        push_back(u,v,weight);
        push_back(v,u,weight);
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

    void print(){
        for(int i=0; i<nodes; i++){
            cout<<cityNames[i]<<" : ";
            Node* curr = adj[i];
            while(curr){
                cout<<cityNames[curr->vertex]<<" ("<<curr->weight<<") ";
                curr = curr->next;
            }
            cout<<endl;
        }
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
        parent[start] = -1;
        int totalWeight = 0;

        for(int i=0; i<nodes; i++){
            int min = INT_MAX;
            int minVertex = -1;
            for(int j=0; j<nodes; j++){
                if(keys[j]<min&&visited[j]==false){
                    min = keys[j];
                    minVertex = j;
                }
            }

            visited[minVertex] = true;
            totalWeight += min;

            Node* curr = adj[minVertex];
            while(curr){
                if(visited[curr->vertex]==false&&curr->weight<keys[curr->vertex]){
                    keys[curr->vertex] = curr->weight;
                    parent[curr->vertex] = minVertex;
                }

                curr = curr->next;
            }

            cout<<"Total Weight = "<<totalWeight<<endl;

            cout<<"Min Tree Edges"<<endl;

            for(int i=0; i<nodes; i++){
                if(parent[i]==-1) continue;

                cout<<cityNames[parent[i]]<<" -- "<<cityNames[i];
                cout<<" ("<<keys[i]<<") "<<endl;
                
            }


        }    

    }


};


int main(){
    cout<<"Hello World"<<endl;
}