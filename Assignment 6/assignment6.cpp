/*
Assignment 6: 
Represent a given graph using adjacency list to perform DFS and BFS.
Use the map of the area around the college as the graph. 
Identify the prominent landmarks as nodes and perform DFS and BFS on that.
*/

#include <iostream>
#include <vector>
#include <queue>
#include <stack>
using namespace std;
class Graph{
private:
    int nodeNumber;
    int** arr;
    vector<string> Nodes;
public:
    Graph(int nodeNumber):nodeNumber(nodeNumber){
        arr = new int*[nodeNumber];
        for(int i=0; i<nodeNumber; i++){
            arr[i] = arr[i] = new int[nodeNumber]; 
            for (int j = 0; j < nodeNumber; j++) {
                arr[i][j] = 0;
            }
        }
        addNodes();
    }

    ~Graph(){
        for (int i = 0; i < nodeNumber; i++) {
            delete[] arr[i];
        }
        delete[] arr; 
    }
    
    void addNodes(){
        cout<<"Add Node Names"<<endl;
        string name;
        for(int i=0; i<nodeNumber; i++){
            cin>>name;
            Nodes.push_back(name);
        }
    }

    int index(string name){
        for(int i=0; i<nodeNumber; i++){
            if(Nodes[i]==name) return i;
        }
        return -1;
    }

    string indexOf(int index){
        if(index>=0&&index<nodeNumber) return Nodes[index];
        return "";
    }

    void addEdge(string n1, string n2, bool directed){
        int index1 = index(n1);
        int index2 = index(n2);
        if(index1==-1||index2==-1){
            cout<<"Invalid Vertice Entered"<<endl;
            return;
        }

        if(!directed){
            arr[index1][index2] = 1;
            arr[index2][index1] = 1;
        }
        else{
            arr[index1][index2] = 1;
        }
    }

    void displayList(){
        
        for(int i=0; i<nodeNumber; i++){
            cout<<indexOf(i)<<" : { ";
            for(int j=0; j<nodeNumber; j++){
                if(arr[i][j]==1){
                    cout<<indexOf(j)<<" ";
                }
            }
            cout<<" }"<<endl;
        }

    }

    bool notVisited(string node, vector<string>&visited){
        for(int i=0; i<visited.size(); i++){
            if(visited[i]==node) return false;
        }
        return true;
    }

    void bfs(){
        vector<string> visited = {};
        queue<string>q;
        q.push(Nodes[0]);
        while(!q.empty()){
            int in = index(q.front());
            q.pop();
            if(notVisited(indexOf(in),visited)){
                cout<<indexOf(in)<<" ";
                visited.push_back(indexOf(in));
                for(int j=0; j<nodeNumber; j++){
                    if(arr[in][j]==1){
                        q.push(indexOf(j));
                    }
                }
            }
        }
        cout<<endl;
    }

    void dsf(){
        vector<string> visited = {};
        stack<string> st;
        st.push(Nodes[0]);
        while(!st.empty()){
            int in = index(st.top());
            st.pop();
            if(notVisited(indexOf(in),visited)){
                cout<<indexOf(in)<<" ";
                visited.push_back(indexOf(in));
                for(int j=nodeNumber-1; j>-1; j--){
                    if(arr[in][j]==1){
                        st.push(indexOf(j));
                    }
                }
            }
        }
        cout<<endl;
    }

};


int main(){
/*

Graph : https://static.javatpoint.com/ds/images/bfs-vs-dfs.png

7

A B C D E F G

A B 0 A D 0 B C 0 B D 0 C D 0 D E 0 E C 0 B G 0 C F 0 B F 0 E G 0

*/


    Graph g(7);
    string n1,n2;
    bool directed;
    while(true){
        cout<<"Add Edge. (u, v) and directed (0/1)"<<endl;
        cin>>n1;
        if(n1=="-1") break;
        cin>>n2>>directed;
        g.addEdge(n1,n2,directed);
    }

    g.displayList();
    g.bfs();
    g.dsf();
}
