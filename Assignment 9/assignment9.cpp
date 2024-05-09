/*
Name: Tirthraj Mahajan
Class: SE-02
Roll: 21242

A Dictionary stores keywords and its meanings. Provide facility for adding new keywords. 
Provide facility to display whole data sorted in ascending/ Descending order. Also find 
how many maximum comparisons may require for finding any keyword. 

Use Height balanced (AVL) tree.
*/

#include<iostream>
using namespace std;

class Node{
private:
    string data;
    string value;
    Node* left;
    Node* right;
    int height;
public:
    Node(){};
    Node(string data, string value):data(data),value(value){
        left = NULL;
        right = NULL;
        height = 1;
    }
    friend class AVLTree;
};

class AVLTree{
private:
    Node* root;

    Node* rotateRight(Node* A){
        Node* B = A->left;
        Node* C = B->right;

        A->left = C;
        B->right = A;

        A->height = 1 + max(getHeight(A->left),getHeight(A->right));
        B->height = 1 + max(getHeight(B->left),getHeight(B->right));
        
        return B;
    }

    Node* rotateLeft(Node* A){
        Node* B = A->right;
        Node* C = B->left;

        A->right = C;
        B->left = A;

        A->height = 1 + max(getHeight(A->left),getHeight(A->right));
        B->height = 1 + max(getHeight(B->left),getHeight(B->right));

        return B;
    }

    int getHeight(Node* node){
        if(!node) return 0;
        return node->height;
    }

    int getBalanceFactor(Node* node){
        if(!node) return 0;
        return getHeight(node->left) - getHeight(node->right);
    }


    Node* insert(Node* node, string data, string value){
        if(!node) return new Node(data, value);

        if(node->data > data){
            node->left = insert(node->left, data, value);
        }
        else if(node->data < data){
            node->right = insert(node->right, data, value);
        }
        else{
            return node;
        }

        node->height = 1 + max(getHeight(node->left),getHeight(node->right));

        int bf = getBalanceFactor(node);

        if(bf > 1 && data < node->left->data){
            cout<<"Performing LL Rotation"<<endl;
            return rotateRight(node);
        }
        else if(bf > 1 && data > node->left->data){
            cout<<"Performing LR Rotation"<<endl;
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        else if(bf < -1 && data > node->right->data){
            cout<<"Performing RR Rotation"<<endl;
            return rotateLeft(node);
        }
        else if(bf < -1 && data < node->right->data){
            cout<<"Performing RL Rotation"<<endl;
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    void inorder(Node* node){
        if(!node) return;
        inorder(node->left);
        cout<<node->data<<" : "<<node->value<<endl;
        inorder(node->right);
    }

    void preorder(Node* node){
        if(!node) return;
        cout<<node->data<<" : "<<node->value<<endl;
        preorder(node->left);
        preorder(node->right);
    }

public:
    AVLTree():root(NULL){}

    void insert(string data, string value){
        root = insert(root, data, value);
    }
    
    void inorder(){
        cout<<"==== Inorder ===="<<endl;
        inorder(root);
        cout<<endl;
    }

    void preorder(){
        cout<<"==== Preorder ===="<<endl;
        preorder(root);
        cout<<endl;
    }

    void search(string data){
        Node* curr = root;
        while(curr){
            if(curr->data == data){
                cout<<"Element Found!"<<endl;
                cout<<curr->data<<" : "<<curr->value<<endl;
                return;
            }
            else if(curr->data > data){
                curr = curr->left;
            }
            else{
                curr = curr->right;
            }
        }
        cout<<"Element not in the dictionary"<<endl;
        return;
    }


};


int main(){
    // Make it menu driven in the practical exam

    AVLTree tree;
    // insert some actual word-meanings. These were for testing purposes only
    tree.insert("a","apple");
    tree.insert("b","ball");
    tree.insert("c","cat");
    tree.insert("d","dog");
    tree.insert("e","elephant");
    tree.insert("f","frog");
    tree.insert("g","girl");
    tree.insert("h","horse");
    tree.insert("i","india");
    tree.insert("j","joker");
    tree.insert("k","knife");
    tree.insert("l","lamp");
    tree.insert("m","mango");
    tree.insert("n","noon");
    tree.insert("o","orange");


    tree.inorder();
    tree.preorder();

}