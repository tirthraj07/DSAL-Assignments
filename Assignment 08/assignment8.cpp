/*
Name: Tirthraj Mahajan
Class: SE-02
Roll: 21242

Problem Statement
Given sequence k = k1 <k2 < … <kn of n sorted keys, with a successful and unsuccessful 
search probability pi and qi for each key ki. Build the Binary search tree that has the least 
search cost given the access probability for each key
*/

#include <iostream>
#include <limits.h>
using namespace std;

class Node{
private:
    int k;
    int p;
    int q;
    Node* left;
    Node* right;
public:
    Node(){};
    Node(int k, int p, int q):k(k),p(p),q(q),left(NULL),right(NULL){}
    friend class OBST;
};

class MatrixElement{
private:
    int weight;
    int cost;
    int root;
public:
    MatrixElement(){}
    MatrixElement(int weight, int cost, int root):weight(weight),cost(cost),root(root){}
    friend class OBST;
};

class OBST{
private:
    MatrixElement** matrix;
    Node* nodeList;
    int nodes;
    Node* root;

    void instantiateNodeList(){
        int k = -1 ,p = -1, q = -1;
        cout<<"Enter values of k(i), p(i) and q(i) accordingly"<<endl;
        for(int i=0; i<nodes; i++){
            if(i!=0){
                cout<<"k"<<i<<" : ";
                cin>>k;
                cout<<"p"<<i<<" : ";
                cin>>p;
            }
            cout<<"q"<<i<<" : ";
            cin>>q;
            nodeList[i] = Node(k,p,q);
        }
    }

    void instantiateMatrix(){
        for(int i=0; i<nodes; i++){
            for(int j=0; j<nodes; j++){
                if(i==j){
                    matrix[i][j] = MatrixElement(nodeList[i].q,0,-1);
                }
                else{
                    matrix[i][j] = MatrixElement(-1, -1, -1);
                }
            }
        }
    }
    
    void optimize(){
        for(int diff=0; diff<nodes; diff++){
            for(int i=0; i<nodes; i++){
                for(int j=0; j<nodes; j++){
                    if(j-i==diff){
                        C(i,j);
                    }

                }
            }

        }
    }

    int C(int i, int j){
        if(i>=j) return 0;

        if(matrix[i][j].cost!=-1) return matrix[i][j].cost;

        int minCost = INT_MAX;
        int minRoot = -1;
        
        for(int k = i+1; k<=j; k++){
            int cost = C(i,k-1) + C(k,j) + W(i,j);
            if(cost<minCost){
                minCost = cost;
                minRoot = k;
            }
        }

        matrix[i][j].cost = minCost;
        matrix[i][j].root = minRoot;

        return matrix[i][j].cost;
    }

    int W(int i, int j){
        if(i>j) return 0;
        if(i==j) return matrix[i][j].weight;

        if(matrix[i][j].weight!=-1) return matrix[i][j].weight;

        matrix[i][j].weight = W(i,j-1) + nodeList[j].p + nodeList[j].q;

        return matrix[i][j].weight;
    }

    Node* constructTree(int i, int j){
        if(i>=j) return NULL;
        
        int k = matrix[i][j].root;
        Node* node = &nodeList[k];
        node->left = constructTree(i,k-1);
        node->right = constructTree(k,j);
        return node;
    }

    void inorder(Node* node){
        if(!node) return;
        inorder(node->left);
        cout<<node->k<<" ";
        inorder(node->right);
    }

    void preorder(Node* node){
        if(!node) return;
        cout<<node->k<<" ";
        preorder(node->left);
        preorder(node->right);
    }

    void printMatrix(){
        for(int i=0; i<nodes; i++){
            for(int j=0; j<nodes; j++){
                cout<<matrix[i][j].cost<<"    ";
            }
            cout<<endl;
        }
    }

    int sumProbabilities(){
        int sum = 0;
        for(int i=0; i<nodes; i++){
            if(i!=0){
                sum += nodeList[i].p;
            }
            sum += nodeList[i].q;
        }
        return sum;
    }


public: 
    OBST(int n):nodes(n+1){
        matrix = new MatrixElement*[nodes];
        nodeList = new Node[nodes];
        for(int i=0; i<nodes; i++){
            matrix[i] = new MatrixElement[nodes];
        }
        instantiateNodeList();
        instantiateMatrix();
        optimize();
        root = constructTree(0,nodes-1);
    }

    void displayCost(){
        int summationOfProbabilities = sumProbabilities();
        float costOfOBST = (float)matrix[0][nodes-1].cost;
        if(summationOfProbabilities!=0){
            costOfOBST = costOfOBST/summationOfProbabilities;
        }

        cout<<"==== Cost of OBST ===="<<endl;
        cout<<"Total Cost : "<<matrix[0][nodes-1].cost<<endl;
        cout<<"Probability Sum : "<<summationOfProbabilities<<endl;
        cout<<"Therefore final cost of OBST : "<<costOfOBST<<endl;
        cout<<endl; 
    }

    void inorderTraversal(){
        cout<<"=== Inorder Traversal ==="<<endl;
        inorder(root);
        cout<<endl<<"----- END -----"<<endl;
    }

    void preorderTraversal(){
        cout<<"=== Preorder Traversal ==="<<endl;
        preorder(root);
        cout<<endl<<"----- END -----"<<endl;
    }

    void print(){
        printMatrix();
    }

};


int main(){

/*
Reference Question:
https://youtu.be/wAy6nDMPYAE?si=Pf7gucJCdujIrt3P&t=3141

    0   1   2   3   4
k   x   10  20  30  40
p   x   3   3   1   1
q   2   3   1   1   1

Total Cost = 36
Summation of Probabilities = 16
Final Cost => 36/16 = 2


direct i/p : 2 10 3 3 20 3 1 30 1 1 40 1 1
*/

    OBST tree(4);
    tree.displayCost();
    tree.inorderTraversal();
    tree.preorderTraversal();
    tree.print();
}
