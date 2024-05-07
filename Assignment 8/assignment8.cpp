/*
Name: Tirthraj Mahajan
Class: SE-02
Roll No: 21242

TITLE:
To write a program for implementing optimal binary search tree

PROBLEM STATEMENT DEFINITION

Given sequence k = k1 <k2 < ... < kn of n sorted keys, with a search
probability pi for each key ki . Build the Binary search tree that has

*/

#include <iostream>
#include <limits.h>
using namespace std;

class Node{
private:
    int k;
    int p;
    int q;
    Node *left;
    Node *right;
public:
    Node(){}
    Node(int k, int p, int q, Node *left=NULL, Node* right=NULL):k(k),p(p),q(q),left(left),right(right){}
    friend class Pair;
    friend class OBST;
};

class Pair{
private:    
    int cost;
    int root;
    int weight;
public:
    Pair(){}
    Pair(int cost, int root=-1, int weight=-1):cost(cost),root(root),weight(weight){};
    friend class OBST;
};


class OBST{
private:
    Pair **matrix;         // 2D Array
    Node *indexTable;      
    int nodes;

    int W(int i, int j){
        if(i>j) return 0;   
        if(i==j){
            return matrix[i][j].weight;
        } 
        if(matrix[i][j].weight!=-1) return matrix[i][j].weight;
        matrix[i][j].weight = W(i,j-1) + indexTable[j].p + indexTable[j].q;
        return matrix[i][j].weight;
    }

    int C(int i, int j){
        if(i>=j) return 0;
        
        // Check if it is already inserted

        if(matrix[i][j].cost!=-1) return matrix[i][j].cost;         // Using memorization in dynamic programming

        int result = INT_MAX;
        int curr = 0;
        int root = -1;
        for(int k=i+1; k<=j; k++){
            curr = C(i,k-1) + C(k,j) + W(i,j);
            if(curr<result){
                result = curr;
                root = k;
            }
        }
        matrix[i][j].cost = result;
        matrix[i][j].root = root;
        return result;
    }    


    void optimize(){

        for(int i=0; i<nodes; i++){
            for(int j=0; j<nodes; j++){
                if(i==j){
                    matrix[i][j] = Pair(0,-1,indexTable[i].q);
                }
                else{
                    matrix[i][j] = Pair(-1,-1);
                }
            }
        }
        
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


public:
    OBST(int n):nodes(n+1){
        matrix = new Pair*[nodes];
        indexTable = new Node[nodes];
        for(int i=0; i<nodes; i++){
            matrix[i] = new Pair[nodes];
        }
    }

    void enterNodes(){
        cout<<"Enter k(i), p(i) and q(i)"<<endl;
        int k = -1;
        int p = -1;
        int q = -1;
        indexTable[0] = Node(-1,-1,-1);

        for(int i=0; i<nodes; i++){
            if(i!=0){
                cout<<"k"<<i<<" : ";
                cin>>k;
                cout<<"p"<<i<<" : ";
                cin>>p;
            }
            cout<<"q"<<i<<" : ";
            cin>>q;
            indexTable[i] = Node(k,p,q);
        }

        optimize();
    }

    void print(){
        cout<<endl;
        for(int i=0; i<nodes; i++){
            for(int j=0; j<nodes; j++){
                cout<<matrix[i][j].cost<<" ("<<matrix[i][j].root<<") ("<<matrix[i][j].weight<<") ";
            }
            cout<<endl;
        }
    }


    Node* constructTree(int i, int j){
        if(i>=j) return NULL;
        
        int k = matrix[i][j].root;
        Node* root = &indexTable[k];
        root->left = constructTree(i,k-1);
        root->right = constructTree(k, j);
        return root;
    }

    int totalCost(){
        return matrix[0][nodes-1].cost;
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

};


int main(){
    OBST tree(4);
    tree.enterNodes();
    tree.print();
    Node* root = tree.constructTree(0,4);
    cout<<"Total cost : "<<tree.totalCost()<<endl;
    tree.inorder(root);
    cout<<endl;
    tree.preorder(root);

}

