/*

Assignment 2: Binary Search Tree

1. Begin with an empty binary tree
2. Construct tree by inserting values
3. Minimum and Maximum data value found in tree
4. Search an element

*/

#include<iostream>
#include <vector>
using namespace std;


class Node{
private:
    int data;
    Node *left, *right;
public:
    Node(int data):data(data),left(nullptr),right(nullptr){}
    friend class BST;
};

class BST{
private:
    Node* root;
public:
    BST():root(nullptr){}
    void insert(int data){
        if(!root){
            root = new Node(data);
            return;
        }
        Node* curr = root;
        Node* parent = NULL;
        while(curr){
            parent = curr;
            if(curr->data>data){
                curr = curr->left;
            }else{
                curr = curr->right;
            }
        }
        if(parent->data>data){
            parent->left = new Node(data);
        }else{
            parent->right = new Node(data);
        }
    }

    void search(int data){
        if(!root){
            cout<<"Node "<<data<<" not found!"<<endl;
            return;
        }
        Node* curr = root;
        while(curr){
            if(curr->data == data){
                cout<<"Node "<<data<<" found!"<<endl;
                return;
            }
            if(curr->data>data){
                curr = curr->left;
            }else{
                curr = curr->right;
            }
        }
        cout<<"Node "<<data<<" not found!"<<endl;
        return;
    }

    int minNode(){
        if(!root) return -1;
        Node* curr = root;
        while(curr->left){
            curr = curr->left;
        }
        return curr->data;
    }

    int maxNode(){
        if(!root) return -1;
        Node* curr = root;
        while(curr->right){
            curr = curr->right;
        }
        return curr->data;
    }

    void inorder(Node* root){
        if(root==nullptr) return;
        inorder(root->left);
        cout<<root->data<<" ";
        inorder(root->right);
    }


    void deleteNode(int data){
        if(!root) return;

        Node* curr = root;
        Node* parent = NULL;

        while(curr){
            if(curr->data==data){
                break;
            }
            parent = curr;
            if(curr->data>data){
                curr = curr->left;
            }
            else{
                curr = curr->right;
            }
        }

        if(!curr){
            cout<<"Node "<<data<<" not found";
            return;
        }

        if(!curr->left&&!curr->right) caseA(parent,curr);
        else if(!curr->left||!curr->right) caseB(parent, curr);
        else caseC(parent, curr);

    }

    void caseA(Node* &parent, Node* &curr){
        if(parent==NULL){
            root=NULL;
            return;
        }
        if(parent->left==curr) parent->left = NULL;
        else parent->right = NULL;
        delete curr;
    }

    void caseB(Node* &parent, Node* &curr){
        Node* child;
        if(curr->left) child = curr->left;
        else child = curr->right;

        if(parent==NULL){
            root = child;
            return;
        }


        if(parent->left == curr) parent->left = child;
        else parent->right = child;

        curr->left = NULL;
        curr->right = NULL;
        curr = NULL;
        delete curr;
    }

    void caseC(Node* &parent, Node* &curr){
        Node* inorderSucc = inorderSuccessor(curr->right);
        curr->data = inorderSucc->data;
        parent = curr;
        curr = curr->right;
        if(!curr->left){
            parent->right = curr->right;
            return;
        }
        while(curr->left){
            parent = curr;
            curr = curr->left;
        }

        if(parent->left == curr){
            parent->left = nullptr;
            curr = NULL;
            delete curr;
        }   
        else{
            parent->right = nullptr;
            curr = NULL;
            delete curr;
        }
        
    }

    Node* inorderSuccessor(Node* node){
        if(!node) return NULL;
        while(node->left){
            node = node->left;
        }
        return node;
    }

    Node* getRoot(){
        return root;
    }

};


int main(){
    BST t;
    vector<int> arr = {8,3,1,6,4,7,10,14,13};
    for(int i=0; i<arr.size(); i++){
        t.insert(arr[i]);
    }
    for(int i=0; i<arr.size(); i++){
        t.deleteNode(arr[i]);
    }



    t.inorder(t.getRoot());
    cout<<endl;


    
}

