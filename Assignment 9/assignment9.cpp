/*
Name : Tirthraj Mahajan
Class: SE-02
Roll No: 21242
To write a program for implementing dictionary using Height balance tree.

Do note: More optimisation can be done, especially with the getHeight function. But I am really tired. :)
*/

#include <iostream>
using namespace std;

class Node{
private:
    int key;
    int height;
    int bf;
    Node* left;
    Node* right;
public:
    Node(int key, int height=1, int bf=0, Node*left=NULL, Node*right=NULL):key(key),height(height),bf(bf),left(left),right(right){}
    friend class AVLTree;
};

class AVLTree{
private: 
    Node* root;

public:
    AVLTree():root(nullptr){}

    void insert(int key){
        root = insertUtil(root,key);
    }

    int getHeight(Node* node){
        if(!node) return 0;
        return max(getHeight(node->left), getHeight(node->right)) + 1;
    }

    int getBF(Node* node){
        if(!node) return 0;
        int left_height =  getHeight(node->left);
        int right_height = getHeight(node->right);
        return left_height-right_height;
    }

    // We will traverse postorder and then update the tree
    void updateTree(Node* node){
        if(!node) return;
        updateTree(node->left);
        updateTree(node->right);
        node->height = max(getHeight(node->left),getHeight(node->right))+1;
        node->bf = getBF(node);

    }   

    Node* getRoot(){
        return root;
    }

    Node* insertUtil(Node* node, int key){
        if(!node) return new Node(key);

        if(key < node->key){
            node->left = insertUtil(node->left, key);
        }
        else if(key > node->key){
            node->right = insertUtil(node->right, key);
        }
        else{
            return node;
        }
        
        

        node->height = max(getHeight(node->left),getHeight(node->right))+1;
        node->bf = getHeight(node->left)-getHeight(node->right);

        return balance(node);

    }

    Node* balance(Node* node){
        // Right Heavy
        if (node->bf < -1){
            // Right - Left Case
            if(getBF(node->right)>0){
                node->right = rotateRight(node->right);
            }
            // Right - Right Case            
            return rotateLeft(node);
        }

        // Left Heavy
        else if (node->bf > 1){

            // Left - Right Case
            if(getBF(node->left)<0){
                node->left = rotateLeft(node->left);
            }
            // Left - Left Case    
            return rotateRight(node);

        }
        return node;

    }

/*
    A                       B
        B       -->     A       D
    C       D             C

*/

    Node* rotateLeft(Node* A){
        Node* B = A->right;
        Node* C = B->left;

        B->left = A;
        A->right = C;

        A->height = getHeight(A);
        B->height = getHeight(B);

        A->bf = getBF(A);
        B->bf = getBF(B);

        return B;
    }

/*
            A                       B
        B           -->         D       A
    D       C                         C 
*/

    Node* rotateRight(Node* A){
        Node* B = A->left;
        Node* C = B->right;

        B->right = A;
        A->left = C;

        A->height = getHeight(A);
        B->height = getHeight(B);    

        A->bf = getBF(A);
        B->bf = getBF(B);

        return B;
    }

    void inorder(Node* node){
        if(!node) return;
        inorder(node->left);
        cout<<node->key<<" ";
        inorder(node->right);
    }

    void preorder(Node* node){
        if(!node) return;
        cout<<node->key<<" ("<<node->bf<<") ";
        preorder(node->left);
        preorder(node->right);
    }

};



int main(){
    // Inserting in ascending order to generate skewed BST

    AVLTree tree;
    tree.insert(12);
    tree.insert(8);
    tree.insert(5);
    tree.insert(4);
    tree.insert(11);
    tree.insert(18);
    tree.insert(17);

    tree.inorder(tree.getRoot());
    cout<<endl;
    tree.preorder(tree.getRoot());
    cout<<endl;
    

}
