/*
 * Assignment 1:
 * Construct an empty binary tree
 * Construct tree by inserting values
 * Inorder, preorder, postorder
 * Invert Tree
 * Height of Tree
 * Copy Tree to another Tree (Constructor)
 * Count No of leaves
 * Count No of internal Leaves
 * Erase all nodes of the tree
 *
 */

#include <iostream>
#include <vector>
#include <stack>
#include <queue>
using namespace std;

class Node{
private:
    int data;
    Node *left, *right;
public:
    Node(int data):data(data),left(nullptr),right(nullptr){}
    friend class Tree;
};

class Tree{
public:
    Node* createTree(Node* &root){
        cout<<"Enter Data (-1 : NULL)"<<endl;
        int data;
        cin>>data;
        if(data == -1) return nullptr;
        root = new Node(data);
        
        cout<<"Enter value to left of "<<data<<endl;
        root->left = createTree(root->left);

        cout<<"Enter value to right of "<<data<<endl;
        root->right = createTree(root->right);
        
        return root;
    }

    Node* createTreeUsingArr(vector<int>arr){
        if(arr.size()==0) return NULL;
        if(arr.size()==1) return new Node(arr[0]);
        Node* root = new Node(arr[0]);
        int i=1;
        for(;i<arr.size(); i=i+2){
            Node* newNode = new Node(arr[i]);
            newNode->left = root;
            root = newNode;
        };
        Node* curr = root;
        int j = arr.size()-1;
        if(arr.size()%2==0){
            curr = root->left;
            j = arr.size()-2;
        } 

        for(;j>1;j=j-2){
            curr->right = new Node(arr[j]);
            curr = curr->left;
        }
        return root;
    }

    void inorder(Node* root){
        if(root==nullptr) return;
        inorder(root->left);
        cout<<root->data<<" ";
        inorder(root->right);
    }

    void preorder(Node* root){
        if(root==nullptr) return;
        cout<<root->data<<" ";
        preorder(root->left);
        preorder(root->right);
    }

    void postorder(Node* root){
        if(root==nullptr) return;
        postorder(root->left);
        postorder(root->right);
        cout<<root->data<<" ";
    }


    void invertTree(Node* &root){
        if(root==nullptr) return;
        Node* temp = root->left;
        root->left = root->right;
        root->right = temp;
        invertTree(root->left);
        invertTree(root->right);
    }

    void invertTreeIterative(Node* &root){
        if(root==nullptr) return;
        stack<Node*> st;
        st.push(root);
        while(!st.empty()){
            Node* curr = st.top();
            st.pop();
            Node* temp = curr->left;
            curr->left = curr->right;
            curr->right = temp;
            if(curr->left) st.push(curr->left);
            if(curr->right) st.push(curr->right);
        }
    }

    void inorderIterative(Node* root){
        stack<Node*> st;
        Node* curr = root;
        while(curr||!st.empty()){
            while(curr){
                st.push(curr);
                curr = curr->left;
            }
            cout<<st.top()->data<<" ";
            curr = st.top()->right;
            st.pop();
        }
        cout<<endl;
    }


    void preorderIterative(Node* root){
        stack<Node*>st;
        Node* curr = root;
        while(curr || !st.empty()){
            while(curr){
                cout<<curr->data<<" ";
                st.push(curr);
                curr = curr->left;
            }
            curr = st.top()->right;
            st.pop();
        }
        cout<<endl;
    }

    void postorderIterative(Node* root){
        stack<Node*>mainStack;
        stack<Node*>rightChildStack;
        Node* curr = root;

        while(curr || !mainStack.empty()){
            if(curr){
                mainStack.push(curr);
                if(curr->right){
                    rightChildStack.push(curr->right);
                }
                curr = curr->left;  
            }
            else{
                curr = mainStack.top();
                if(!rightChildStack.empty()&&(curr->right==rightChildStack.top())){
                    curr = curr->right;
                    rightChildStack.pop();
                }
                else{
                    cout<<curr->data<<" ";
                    mainStack.pop();
                    curr = NULL;
                }

            }
        }
        cout<<endl;
        

    }

    int countInternalNodes(Node* root){
        if(root==nullptr) return 0;
        if(root->left==nullptr&&root->right==nullptr) return 0;
        
        int ltree = countInternalNodes(root->left);
        int rtree = countInternalNodes(root->right);

        return ltree+rtree+1;
    }

    int countLeafNodes(Node* root){
        if(root==nullptr) return 0;
        if(root->left==nullptr&&root->right==nullptr) return 1;
        int ltree = countLeafNodes(root->left);
        int rtree = countLeafNodes(root->right);
        return ltree+rtree;
    }

    int height(Node* root){
        if(root==nullptr) return 0;
        int ltree = height(root->left);
        int rtree = height(root->right);
        return max(ltree,rtree)+1;
    }

    void levelorder(Node* root){
        queue<Node*> q;
        q.push(root);
        q.push(NULL);
        while(!q.empty()){
            Node* curr = q.front();
            q.pop();
            if(curr){
                cout<<curr->data<<" ";
                if(curr->left) q.push(curr->left);
                if(curr->right) q.push(curr->right);
            }
            else{
                cout<<endl;
                if(!q.empty()) q.push(NULL);
            }

        }

        cout<<endl;

    }

    void eraseAllNodes(Node* &root){
        if(root==nullptr) return;
        eraseAllNodes(root->left);
        eraseAllNodes(root->right);
        root->left = nullptr;
        root->right = nullptr;
        root = nullptr;
        delete root;
    }


    Node* clone(Node* root){
        if(root==nullptr) return nullptr;
        Node* newNode = new Node(root->data);
        newNode->left = clone(root->left);
        newNode->right = clone(root->right);
        return newNode;
    }
    


};


int main(){
    Tree t;
    Node* root = NULL;
    // vector<int> arr = {1,7,2,6,5,11,9,9,5};
    // root = t.createTreeUsingArr(arr);
    // 1 7 2 -1 -1 6 5 -1 -1 11 -1 -1 9 -1 9 5 -1 -1 -1
    root = t.createTree(root);
    t.invertTree(root);
    t.invertTreeIterative(root);
    cout<<root<<endl;
    t.preorder(root);
    cout<<endl;
    t.preorderIterative(root);
    cout<<endl;
    t.inorder(root);
    cout<<endl;
    t.inorderIterative(root);
    cout<<endl;
    t.postorder(root);
    cout<<endl;
    t.postorderIterative(root);
    cout<<endl;
    t.levelorder(root);
    cout<<endl;
    cout<<"Height: "<<t.height(root)<<endl;
    cout<<"Leaf Nodes: "<<t.countLeafNodes(root)<<endl;
    cout<<"Internal Nodes: "<<t.countInternalNodes(root)<<endl;
    cout<<endl;

    cout<<"Clone Tree"<<endl;
    Node* newNode = t.clone(root);
    t.invertTree(newNode);
    t.invertTreeIterative(newNode);
    t.preorder(newNode);
    cout<<endl;
    t.preorderIterative(newNode);
    cout<<endl;
    t.inorder(newNode);
    cout<<endl;
    t.inorderIterative(newNode);
    cout<<endl;
    t.postorder(newNode);
    cout<<endl;
    t.postorderIterative(newNode);
    cout<<endl;
    t.levelorder(newNode);
    cout<<endl;
    cout<<"Height: "<<t.height(newNode)<<endl;
    cout<<"Leaf Nodes: "<<t.countLeafNodes(newNode)<<endl;
    cout<<"Internal Nodes: "<<t.countInternalNodes(newNode)<<endl;
    cout<<endl;
    
    
    
    t.eraseAllNodes(root);
    cout<<"root: "<<root<<endl;
    cout<<endl;
    return 0;
}