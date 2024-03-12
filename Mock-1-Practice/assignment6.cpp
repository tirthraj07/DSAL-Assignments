#include <iostream>
#include <list>
#include <unordered_map>
#include <queue>
using namespace std ;

class Graph{
    public:
        unordered_map<int,list<int>>adjlist;

        void addEdges(int u , int v , bool direction){
            if(direction){
                // directed graph 
                // u-->v
                adjlist[u].push_back(v);
            }
            else{
                 adjlist[u].push_back(v);
                 adjlist[v].push_back(u);
            }
        }

        void printadjlist(){
            for(auto i : adjlist){
                cout << i.first << "--> {";
                for( auto nbr : i.second){
                    cout<< nbr << " ,";
                }
                cout<<"}"<<endl;
            }
        }

        // BFS Travesal
        void BfsTraversal(int src ,unordered_map<int,bool> &visited)
        {
            // Adj list will be given already
            // Visited child 
            // unordered_map<int , bool>visited;
            queue<int> q ;

            // Initial cond
            q.push(src);
            visited[src] = true ;
            while( !q.empty()){
                // Step 1 : Save src , print it and pop it 
                int frontNode = q.front();
                cout<< frontNode << " ";
                q.pop();

                // step2 : Go to Adjlist to get its child 

                for(auto nbrs : adjlist[frontNode]){
                    int child = nbrs ;
                    // Step3 : Check it is visited or not

                    if(!visited[child]){
                        q.push(child);
                        visited[child] = true ;
                    }
                }
            }
        }

        // DFS Traversal 
        void Dfstraversal(int src , unordered_map<int,bool> &dfsVisited){
            dfsVisited[src] = true ;
            cout << src <<" ";
            // Goto to child list by Adj list
            for( auto nbrs : adjlist[src]){
                int child = nbrs ;

                if(!dfsVisited[child]){
                    Dfstraversal(child , dfsVisited);
                }
            }
        }
};
int main(){
    // cout<<"Hello world"<<endl;
    Graph g ;
    unordered_map<int, bool> visited;
    unordered_map<int, bool> dfsVisited;

    int choice;
    do {
        cout << "\nMenu:\n";
        cout << "1. Add Edges\n";
        cout << "2. Print Adjacency List\n";
        cout << "3. Perform BFS Traversal\n";
        cout << "4. Perform DFS Traversal\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            int u, v;
            bool direction;
            cout << "Enter edge (u , v) and direction (0 for undirected, 1 for directed): ";
            cin >> u >> v >> direction;
            g.addEdges(u, v, direction);
            break;
        }
        case 2:
            cout << "Adjacency List:\n";
            g.printadjlist();
            break;
        case 3:
            cout << "Performing BFS Traversal: ";
            for (int node = 1; node <= 5; node++) {
                if (!visited[node]) {
                    g.BfsTraversal(node, visited);
                }
            }
            visited.clear(); // Clearing visited map for next traversal
            cout << endl;
            break;
        case 4:
            cout << "Performing DFS Traversal: ";
            for (int node = 1; node <= 5; node++) {
                if (!dfsVisited[node]) {
                    g.Dfstraversal(node, dfsVisited);
                }
            }
            dfsVisited.clear(); // Clearing dfsVisited map for next traversal
            cout << endl;
            break;
        case 5:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
            break;
        }
    } while (choice != 5);

    return 0;

}
