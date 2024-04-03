#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<limits.h>

using namespace std;

class Edge{
    int i, j, weight;
public:
    Edge(int i, int j, int weight):i(i),j(j),weight(weight){}

    bool operator>(const Edge& e2) const {
        return weight > e2.weight;
    }

    bool operator<(const Edge& e2) const {
        return weight < e2.weight;
    }
    static void sortEdges(vector<Edge>& vec){
        for(int i=0; i<vec.size()-1; i++){
            for(int j=0; j<vec.size()-i-1; j++){
                if(vec[j]>vec[j+1]){
                    Edge temp = vec[j];
                    vec[j] = vec[j+1];
                    vec[j+1] = temp;
                }
            }
        }
    }

    friend class Graph;
};

class Graph{
    int nodeNumber;
    int** matrix;
    vector<string> Nodes;
    vector<Edge> edges;
public:
    Graph(int nodeNumber):nodeNumber(nodeNumber){
        matrix = new int*[nodeNumber];
        for(int i=0; i<nodeNumber; i++){
            matrix[i] = new int[nodeNumber];
            for(int j=0; j<nodeNumber; j++){
                matrix[i][j] = INT_MAX;
            }
        }  
    }

    ~Graph() {
        for (int i = 0; i < nodeNumber; ++i)
            delete[] matrix[i];
        delete[] matrix;
    }

    void addNode(string node){
        if(Nodes.size() < nodeNumber){
            Nodes.push_back(node);
            return;
        }
        cout<<"Cannot add more nodes"<<endl;
    }

    int getIndex(string node){
        for(int i=0; i<Nodes.size();i++){
            if(Nodes[i]==node) return i;
        }
        return -1;
    }

    string atIndex(int index){
        if(index<nodeNumber && index<Nodes.size()){
            return Nodes[index];
        }
        return "";
    }

    void addEdge(string n1, string n2, int weight){
        int index_1 = getIndex(n1);
        int index_2 = getIndex(n2);
        if(index_1 != -1 && index_2 != -1){
            matrix[index_1][index_2] = weight;
            matrix[index_2][index_1] = weight;
            edges.push_back(Edge(index_1,index_2,weight));
        }
    }

    void displayMatrix(){
        for(int i=0; i<nodeNumber; i++){
            cout<<atIndex(i)<<" : ";
            for(int j=0; j<nodeNumber; j++){
                if(matrix[i][j] != INT_MAX){
                    cout<<atIndex(j)<<" ";
                }
            }
            cout<<endl;
        }
    }   

    bool isPresent(vector<int>&visited, Edge e){
        bool condition1 = false;
        bool condition2 = false;
        for(int i=0; i<visited.size(); i++){
            if(visited[i] == e.i) condition1 = true;
            if(visited[i] == e.j) condition2 = true;
        }

        if(condition1&&condition2) return true;

        if(!condition1){
            visited.push_back(e.i);
        }
        if(!condition2){
            visited.push_back(e.j);
        }

        return condition1&&condition2;
    }

    int kruskal(){
        Edge::sortEdges(edges);
        vector<int> visited;
        int totalWeight = 0;

        for(int i=0; i<edges.size(); i++){
            if(!isPresent(visited,edges[i])){
                totalWeight += edges[i].weight;
            }
        }

        return totalWeight;
    }

    
};


int main(){

    Graph g(6);
    g.addNode("A");
    g.addNode("B");
    g.addNode("C");
    g.addNode("D");   
    g.addNode("E");
    g.addNode("F");


    g.addEdge("A","B",4);
    g.addEdge("B","C",2);
    g.addEdge("A","C",4);
    g.addEdge("C","D",3);
    g.addEdge("C","F",2);
    g.addEdge("C","E",4);
    g.addEdge("D","E",3);
    g.addEdge("F","E",3);

    g.displayMatrix();

    cout<<"Total Cost : "<<g.kruskal();


}
