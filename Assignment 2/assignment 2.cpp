/*

Assignment 2: Binary Search Tree

1. Begin with an empty binary tree
2. Construct tree by inserting values
3. Insert a new node
4. Find numbers of node in longest path
5. Minimum and Maximum data value found in tree
4. Invert Binary Tree
5. Search an element

*/


#include <iostream>
#include <vector>
#include <stack>
#include <queue>
using namespace std;

class Node{
public:
    int data;
    Node* left;
    Node* right;
    Node(int data):data(data),left(nullptr),right(nullptr){}
};


class BST{
private:
    Node* root;
public:
    BST():root(nullptr){}

    Node* getRoot() const{
        return root;
    }

    void insertViaValue(int val){
        if(root==nullptr){
            root = new Node(val);
            return;
        }

        Node* prev = nullptr;
        Node* curr = root;
        while(curr){
            prev = curr;
            if(curr->data>=val){
                curr = curr->left;
            }
            else{
                curr = curr->right;
            }
        }
        if(prev->data>=val){
            prev->left = new Node(val);
        }else{
            prev->right = new Node(val);

        }
       
    }

    void insertViaArr(vector<int> nums){
        for(int i: nums){
            insertViaValue(i);
        }
    }

    void insertViaNode(Node* node){
        if(root==nullptr){
            root = node;
            return;
        }

        Node* prev = nullptr;
        Node* curr = root;
        while(curr){
            prev = curr;
            if(curr->data>=node->data){
                curr = curr->left;
            }
            else{
                curr = curr->right;
            }
        }
        if(prev->data>=node->data){
            prev->left = node;
        }else{
            prev->right = node;

        }
    }

    int height(Node* root){
        if(root==nullptr){
            return 0;
        }
        int lHeight = height(root->left);
        int rHeight = height(root->right);

        return lHeight>rHeight?lHeight+1:rHeight+1;
    }

    void longestPathNodes(){
        queue<Node*> q;
        stack<Node*> st;
        q.push(root);
        q.push(NULL);
        while(!q.empty()){
            Node* curr = q.front();
            st.push(curr);
            q.pop();
            if(curr){
                if(curr->right) q.push(curr->right);
                if(curr->left) q.push(curr->left);
            }
            else{
                if(!q.empty()){
                    q.push(NULL);
                }
            }
        }
        if(!st.empty()){
            st.pop();
            while(!st.empty()&&st.top()){
                cout<<st.top()->data<<" ";
                st.pop();
            }  
        }
       
    }

    int minTree(){
        if(root==nullptr){
            cout<<"Tree Empty"<<endl;
            return 0;
        }
        Node* curr = root;
        while(curr->left!=nullptr){
            curr=curr->left;
        }
        return curr->data;
    }

    int maxTree(){
        if(root==nullptr){
            return 0;
        }
        Node* curr = root;
        while(curr->right!=nullptr){
            curr = curr->right;
        }
        return curr->data;
    }

    void invertTree(Node* node){
        if(!node) return;
        Node* temp = node->right;
        node->right = node->left;
        node->left = temp;
        invertTree(node->left);
        invertTree(node->right);
    }

    void searchViaValue(int key){
        if(root==nullptr){
            cout<<"Empty Tree"<<endl;
            return;
        }

        Node* curr = root;
        string path = "";
        while(curr){
            if(curr->data == key){
                if(path!="") cout<<"Element Found! "<<key<<" Path : "<<path<<endl;
                else cout<<"Element Found! "<<key<<" Root Node"<<endl;
                return;
            }
            else if(curr->data < key){
                curr = curr->right;
                path = path + "1";
            }  
            else{
                curr = curr->left;
                path = path + "0";
            }


        }
        cout<<"Element "<< key <<" Not Found!"<<endl;
        return;
    }

    void preOrder(Node* root){
        if(root==nullptr) return;
        cout<<root->data<<" ";
        preOrder(root->left);
        preOrder(root->right);
    }
   
    void inOrder(Node* root){
        if(root==nullptr) return;
        inOrder(root->left);
        cout<<root->data<<" ";
        inOrder(root->right);
    }
   
    void postOrder(Node* root){
        if(root==nullptr) return;
        postOrder(root->left);
        postOrder(root->right);
        cout<<root->data<<" ";
    }

    void displayTreeViaLOT(){
        Node* curr = root;
        queue<Node*> q;
        q.push(curr);
        q.push(NULL);
        while(!q.empty()){
            curr = q.front();
            q.pop();
            if(curr){
                cout<<curr->data<<" ";
                if(curr->left) q.push(curr->left);
                if(curr->right) q.push(curr->right);
            }else{
                cout<<endl;
                if(!q.empty()){
                    q.push(NULL);
                }
            }
        }
    }

    Node* deleteNode(Node* root, int k){
        if(root==NULL){
            return root;
        }

        if(root->data>k){
            root->left = deleteNode(root->left,k);
            return root;                
        }

        else if(root->data < k){
            root->right = deleteNode(root->right,k);
            return root;
        }

        if(root->left == NULL){
            Node* temp = root->right;
            delete root;
            return temp;
        }
        else if(root->right == NULL){
            Node* temp = root->left;
            delete root;
            return temp;
        }
        else{
            Node* succParent = root;
            Node* succ = root->right;
            while(succ->left != NULL){
                succParent = succ;
                succ = succ->left;
            }
            if (succParent != root)
                succParent->left = succ->right;
            else
                succParent->right = succ->right;
    
            // Copy Successor Data to root
            root->data = succ->data;
    
            // Delete Successor and return root
            delete succ;
            return root;
        }
     
    }

    void deleteBST(Node* &root){
        if(!root) return;
        deleteBST(root->left);
        deleteBST(root->right);
        root->left = NULL;
        root->right = NULL;
        delete root;
        root = NULL;
    }   
   
    friend class Menu;

};

class Menu{
private:
    BST* tree;
    int choice;
public:
    Menu():tree(nullptr){
        initOptions();
        askChoice();
        initChoice();
    }
   
    void initOptions(){
        cout<<"\n\n\nWhat do you want to perform?"<<endl;
        cout<<"1. * Create Empty Binary Search Tree"<<endl;
        cout<<"2. * Construct tree by inserting values"<<endl;
        cout<<"3. * Insert an Element by Value in tree"<<endl;
        cout<<"4. * Insert a new node"<<endl;
        cout<<"5. * Find Height of Tree"<<endl;
        cout<<"6. * Find numbers in node having the longest path"<<endl;
        cout<<"7. * Minimum and Maximum data value found in tree"<<endl;
        cout<<"8. * Invert Binary Search Tree"<<endl;
        cout<<"9. * Search an element"<<endl;
        cout<<"10. * Display Level Order Tree"<<endl;
        cout<<"11. * Display Inorder, Preorder and Postorder"<<endl;
        cout<<"12. * Delete a Node from BST"<<endl;
        cout<<"13. * Delete all Nodes of BST"<<endl;
        cout<<"14. * Exit"<<endl;
        cout<<"( BST ) >>> ";
    }
   
    void askChoice(){
        try{
            cin>>choice;
            cout<<endl;
        }
        catch(...){
            cout<<"There was an error while you entered choice. Please Try again"<<endl;
            retry();
        }
    }
   
    void initChoice(){
        vector<int> nums;
        int length;
        int num;
        Node* newNode = NULL;
        switch(choice){
            case 1:
                if(tree==NULL){
                    cout<<"Creating an Empty Tree...."<<endl;
                    tree = new BST();
                    cout<<"New Tree Created Successfully!"<<endl;
                    break;
                }
                cout<<"Tree Already Exists! Please Delete the Tree First!"<<endl;
                break;
            case 2:
                if(tree==NULL){
                    cout<<"Please Construct an Empty Tree First!"<<endl;
                    break;
                }
                nums.clear();
                cout<<"How many Nodes do you want to enter?"<<endl;
                cin>>length;
                cout<<"Enter Node values in Space Seperated Form"<<endl;
                while(length>0){
                    cin>>num;
                    nums.push_back(num);
                    length--;
                }
                tree->insertViaArr(nums);
                cout<<"Nodes Entered Successfully!"<<endl;
                break;
            case 3:
                if(tree==NULL){
                    cout<<"Please Construct an Empty Tree First!"<<endl;
                    break;
                }
                cout<<"Enter the value of data to be inserted: ";
                cin>>num;
                cout<<endl;
                tree->insertViaValue(num);
                cout<<"Value entered successfully"<<endl;
                break;
            case 4:
                if(tree==NULL){
                    cout<<"Please Construct an Empty Tree First!"<<endl;
                    break;
                }
                cout<<"Enter the value of Node to be inserted: ";
                cin>>num;
                cout<<endl;
                newNode = new Node(num);
                tree->insertViaNode(newNode);
                cout<<"Node entered successfully"<<endl;
               
                break;
            case 5:
                if(tree==NULL){
                    cout<<"Please Construct an Empty Tree First!"<<endl;
                    break;
                }
                cout<<"Height of the Tree is: "<<tree->height(tree->root)<<endl;
                break;
            case 6:
                if(tree==NULL){
                    cout<<"Please Construct an Empty Tree First!"<<endl;
                    break;
                }
                cout<<"The Nodes with the longest path are: ";
                tree->longestPathNodes();
                cout<<endl;

                break;
            case 7:
                if(tree==NULL){
                    cout<<"Please Construct an Empty Tree First!"<<endl;
                    break;
                }
                if(!tree->root){
                    cout<<"The tree does not have any nodes!"<<endl;
                    break;
                }
                cout<<"The minimum number in BST is "<<tree->minTree()<<endl;
                cout<<"The maximum number in BST is "<<tree->maxTree()<<endl;

                break;
            case 8:
                if(tree==NULL){
                    cout<<"Please Construct an Empty Tree First!"<<endl;
                    break;
                }
                tree->invertTree(tree->root);
                cout<<"Tree Inverted Successfully"<<endl;
                break;
            case 9:
                if(tree==NULL){
                    cout<<"Please Construct an Empty Tree First!"<<endl;
                    break;
                }
                if(!tree->root){
                    cout<<"The tree does not have any nodes"<<endl;
                    break;
                }
                cout<<"Which element do you want to search?"<<endl;
                cin>>num;
                tree->searchViaValue(num);
                cout<<endl;
                break;
            case 10:
                if(tree==NULL){
                    cout<<"Please Construct an Empty Tree First!"<<endl;
                    break;
                }
                cout<<"Displaying Tree in Level Order Traversal"<<endl;
                tree->displayTreeViaLOT();
                cout<<endl;
                break;
            case 11:
                if(tree==NULL){
                    cout<<"Please Construct an Empty Tree First!"<<endl;
                    break;
                }
                cout<<"Displaying Tree Using Depth First Search"<<endl<<endl;

                cout<<"Preorder: ";
                tree->preOrder(tree->root);
                cout<<"\nInorder: ";
                tree->inOrder(tree->root);
                cout<<"\nPostorder: ";
                tree->postOrder(tree->root);
                cout<<endl;

                break;
            case 12:
                if(tree==NULL){
                    cout<<"Please Construct an Empty Tree First!"<<endl;
                    break;
                }
                cout<<"Which Node do you want to delete?"<<endl;
                cin>>num;
                tree->root = tree->deleteNode(tree->root,num);
                cout<<"Node Deleted Successfully"<<endl;

                break;
            case 13:
                if(tree==NULL){
                    cout<<"Please Construct an Empty Tree First!"<<endl;
                    break;
                }
                tree->deleteBST(tree->root);
                tree->root = nullptr;
                delete tree;
                tree = nullptr;
                cout<<"Tree Deleted Successfully"<<endl;
                break;
            case 14:
                cout<<"Thanks for using ;)"<<endl;
                return;
                break;
            default:
                cout<<"Invalid Option. Try Again"<<endl;
        }
        retry();
    }
   
   
    void retry(){
        initOptions();
        askChoice();
        initChoice();
    }
   
   
};


int main(){
    Menu m;


    return 0;
}