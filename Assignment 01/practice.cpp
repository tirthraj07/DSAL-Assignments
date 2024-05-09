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
#include <stack>
#include <queue>
#include <vector>
using namespace std;

class Node{
public:
    int data;
    Node* left;
    Node* right;
    Node(int data):data(data),left(nullptr),right(nullptr){}
};


class Tree{
public:
    Tree(){}

    Tree(Node* &cpy, Node* root){
        cpy = copyTree(root);
    }

    Node* copyTree(Node* root){
        if(root == nullptr ) return nullptr;
        Node* newNode = new Node(root->data);
        newNode->left = copyTree(root->left);
        newNode->right = copyTree(root->right);
        return newNode;
    }

    void insertViaPrefixCode(Node* root, string prefixCode,int data){
        for(int i=0; i<prefixCode.length()-1&&root!=nullptr; i++){
            if(root==nullptr){
                cout<<"Invalid Prefix Code"<<endl;
                return;
            }
            else if(prefixCode[i]=='0'){
                root = root->left;
            }
            else{
                root = root->right;
            }
        }
        if(root==nullptr) {
            cout<<"Invalid Prefix Code"<<endl;
            return;
        }

        if(prefixCode[prefixCode.length()-1]=='0'){
            root->left = new Node(data);
        }
        else{
            root->right = new Node(data);
        }

    }

    void insert(Node**root, int data){
        Node* newNode = new Node(data);
        *root = newNode;
    }

    void inorderRecursive(Node* root){
        if (root == nullptr) return;
        inorderRecursive(root->left);
        cout<<root->data<<" ";
        inorderRecursive(root->right);
    }

    void preorderRecursive(Node* root){
        if (root == nullptr) return;
        cout<<root->data<<" ";
        preorderRecursive(root->left);
        preorderRecursive(root->right);
    }

    void postorderRecursive(Node* root){
        if (root == nullptr) return;
        postorderRecursive(root->left);
        postorderRecursive(root->right);
        cout<<root->data<<" ";
    }

    void inorderIterative(Node* root){
        stack<Node*> st;
        while( root!=nullptr || !st.empty() ){
            while(root != nullptr ){
                st.push(root);
                root = root->left;
            }
            cout<<st.top()->data<<" ";
            root = st.top()->right;
            st.pop();
        }
    }

    void preorderIterative(Node* root){
        stack<Node*> st;
        while( root!=nullptr || !st.empty() ){
            while(root!=nullptr){
                cout<<root->data<<" ";
                st.push(root);
                root = root->left;
            }
            root = st.top()->right;
            st.pop();
        }
    }

    void postorderIterative(Node* root){
        stack<Node*> mainStack;
        stack<Node*> rightChild;

        while( root!=nullptr || !mainStack.empty() ){
            if( root!=nullptr ){
                if( root->right!=nullptr ){
                    rightChild.push(root->right);
                }

                mainStack.push(root);
                root = root->left;

            }
            else{
                root = mainStack.top();

                if( !rightChild.empty() && root->right == rightChild.top() ){

                    root = rightChild.top();
                    rightChild.pop();

                }
                else{

                    cout<<root->data<<" ";
                    mainStack.pop();
                    root = nullptr;

                }
            }
        }
    }

    void invertTreeRecursive(Node* root){
        if( root == nullptr ) return;
        Node* temp = root->right;
        root->right = root->left;
        root->left = temp;
        invertTreeRecursive(root->left);
        invertTreeRecursive(root->right);
    }

    void invertTreeIterative(Node* root){
        if(root == nullptr ) return;
        stack<Node*> st;
        st.push(root);

        while( !st.empty() ){
            Node* curr = st.top();
            st.pop();

            Node* temp = curr->right;
            curr->right = curr->left;
            curr->left = temp;

            if(curr->right){
                st.push(curr->right);
            }
            if(curr->left){
                st.push(curr->left);
            }

        }

    }

    int heightTreeRecursive(Node* root){
        if(root == nullptr) return 0;
        int lTreeHeight = heightTreeRecursive(root->left);
        int rTreeHeight = heightTreeRecursive(root->right);
        return lTreeHeight>rTreeHeight?(lTreeHeight+1):(rTreeHeight+1);
    }

    int countLeaves(Node* root){
        if(root==nullptr) return 0;
        if(root->left == nullptr && root->right == nullptr) return 1;
        return countLeaves(root->left)+countLeaves(root->right);
    }

    int countInternalNodes(Node* root){
        if(root==nullptr||(root->left==nullptr&&root->right==nullptr)) return 0;
        return countInternalNodes(root->left)+countInternalNodes(root->right)+1;
    }

    void eraseTree(Node* &root){
        if(root==nullptr) return;
        eraseTree(root->left);
        eraseTree(root->right);
        root->left = nullptr;
        root->right = nullptr;
        root = nullptr;
        delete root;
    }

    void constructLeftSkewedTreeUsingArray(Node *&root, vector<int>val){
        Node* prev = nullptr;;
        for(int i=0; i<val.size(); i++){
            prev = root;
            root = new Node(val[i]);
            root->left = prev;
        }
    }

    void constructTreeUsingArray(Node* &root, vector<int>val){
        if(val.size()==0) return;
        else if(val.size()==1){
            root = new Node(val[0]);
            return;
        }

        root = new Node(val[0]);
        Node* newNode = NULL;
        for(int i=1; i<val.size();i=i+2){
            newNode = new Node(val[i]);
            newNode->left = root;
            root = newNode;
        }
        int j;
        Node* curr = NULL;
        if(val.size()%2==0){
            j = val.size()-2;
            curr = root->left;
        }
        else{
            j = val.size()-1;
            curr = root;

        }

        while(j>1){
            newNode = new Node(val[j]);
            curr->right = newNode;
            curr = curr->left;
            j = j - 2;
        }

    }

    void displayTreeUsingLOT(Node* root){
        if(!root) return;
        cout<<"\nDisplaying Tree: "<<endl;
        queue<Node*> q;
        q.push(root);
        q.push(NULL);

        while(!q.empty()){
            Node* curr = q.front();
            q.pop();

            if(curr){
                cout<<curr->data<<' ';
                if(curr->left) q.push(curr->left);
                if(curr->right) q.push(curr->right);
            }
            else{
                cout<<endl;
                if(!q.empty()) q.push(NULL);
            }

        }
    }


};

class Menu{
Tree* t;
Node* root;
Node* cpy;
int choice;
public:
    Menu():t(nullptr),root(nullptr),cpy(nullptr){
        initOptions();
        askChoice();
        initChoice();
    }

    void initOptions(){
        cout<<"\n\n\nWhat do you want to do?"<<endl;
        cout<<"1. * Construct an empty binary tree"<<endl;
        cout<<"2. * Construct tree by inserting values"<<endl;
        cout<<"3. * Inorder, preorder, postorder"<<endl;
        cout<<"4. * Invert Tree"<<endl;
        cout<<"5. * Height of Tree"<<endl;
        cout<<"6. * Copy Tree to another Tree (Constructor)"<<endl;
        cout<<"7. * Count No of leaves"<<endl;
        cout<<"8. * Count No of internal Leaves"<<endl;
        cout<<"9. * Erase all nodes of the tree"<<endl;
        cout<<"10. * Construct an inorder Tree using Array"<<endl;
        cout<<"11. * Construct Skewed inorder Tree using Array"<<endl;
        cout<<"12. * Display Tree using Level Order Traversal"<<endl;
        cout<<"13. Exit"<<endl;
    }

    void askChoice(){
        cout<<">>> ";
        cin>>choice;
        cout<<endl;
    }

    void initChoice(){
        int ch;
        int data;
        int it;
        string prefixCode;
        vector<int> val;
        switch(choice){
            case 1:
                cout<<"New Tree Created"<<endl;
                t = new Tree();
                break;

            case 2:
                if(t==nullptr){
                    cout<<"Please Create an Empty Tree First!"<<endl;
                }
                else{
                    if(root==nullptr){
                        cout<<"Enter Root Data: "<<endl;
                        cin>>data;
                        root = new Node(data);
                    }
                    else{
                        cout<<"How many nodes do you want to enter?"<<endl;
                        cin>>it;
                        while(it--){
                            cout<<"Enter Prefix Code of Leaf to be Entered"<<endl;
                            cin>>prefixCode;
                            cout<<"Enter The Data to be Inserted"<<endl;
                            cin>>data;
                            t->insertViaPrefixCode(root,prefixCode,data);
                        }
                    }
                }

                break;

            case 3:
                if(t==nullptr){
                    cout<<"Please Create an Empty Tree First!"<<endl;
                }
                else{
                    cout<<"** Depth First Search via Recursive Approach **"<<endl;
                    cout<<"Preorder: ";
                    t->preorderRecursive(root);
                    cout<<endl;
                    cout<<"Inorder: ";
                    t->inorderRecursive(root);
                    cout<<endl;
                    cout<<"Postorder: ";
                    t->postorderRecursive(root);
                    cout<<endl;

                    cout<<"********************"<<endl;

                    cout<<"** Depth First Search via Iterative Approach **"<<endl;
                    cout<<"Preorder: ";
                    t->preorderIterative(root);
                    cout<<endl;
                    cout<<"Inorder: ";
                    t->inorderIterative(root);
                    cout<<endl;
                    cout<<"Postorder: ";
                    t->postorderIterative(root);
                    cout<<endl;
                }

                break;

            case 4:
                if(t==nullptr){
                    cout<<"Please Create an Empty Tree First!"<<endl;
                }
                else{
                    cout<<"How Do you want to invert the tree?"<<endl;
                    cout<<"1. via Recursive Approach\n2. via Iterative Approach"<<endl;
                    cin>> ch;
                    switch(ch){
                        case 1:
                            t->invertTreeRecursive(root);
                            cout<<"Tree Inverted Successfully"<<endl;
                            break;
                        case 2:
                            t->invertTreeIterative(root);
                            cout<<"Tree Inverted Successfully"<<endl;
                            break;
                        default:
                            cout<<"Invalid Choice"<<endl;
                    }
                }              

                break;

            case 5:
                if(t==nullptr){
                    cout<<"0"<<endl;
                }
                else{
                    cout<<"Height of the tree is : "<<t->heightTreeRecursive(root);
                }

                break;

            case 6:
                if(t==nullptr){
                    cout<<"Please Create an Empty Tree First!"<<endl;
                }
                else{
                    t = new Tree(cpy, root);
                    cout<<"Inorder Traversal of Copied Tree: "<<endl;
                    t->inorderRecursive(cpy);
                    cout<<endl;

                }

                break;

            case 7:
                if(t==nullptr){
                    cout<<"Please Create an Empty Tree First!"<<endl;
                }
                else{
                    cout<<"No. of leaf nodes are: "<<t->countLeaves(root)<<endl;
                }

                break;

            case 8:
                if(t==nullptr){
                    cout<<"Please Create an Empty Tree First!"<<endl;
                }
                else{
                    cout<<"No. of internal nodes are: "<<t->countInternalNodes(root)<<endl;

                }

                break;

            case 9:
                if(t==nullptr){
                    cout<<"Please Create an Empty Tree First!"<<endl;
                }
                else{
                    t->eraseTree(root);
                    t=nullptr;
                    cout<<"Tree Erased Successfully"<<endl;
                }

                break;
            case 10:
                if(t==nullptr){
                    cout<<"Please Create an Empty Tree First!"<<endl;
                }
                else{
                    if(root!=nullptr){
                        cout<<"Do you want to overwrite Existing Tree? (1/0)"<<endl;
                        cin>>ch;
                        if(ch==0){
                            cout<<"No Changes Applied"<<endl;
                            break;
                        }
                    }
                    val.clear();
                    cout<<"How many values do you want to enter?"<<endl;
                    cin>>it;
                    cout<<"Enter values: ";
                    while(it--){
                        cin>>data;
                        val.push_back(data);
                    }
                    t->constructTreeUsingArray(root,val);
                    cout<<"Tree Constructed Successfully!"<<endl;

                }
                break;

            case 11:
                if(t==nullptr){
                    cout<<"Please Create an Empty Tree First!"<<endl;
                }
                else{
                    if(root!=nullptr){
                        cout<<"Do you want to overwrite Existing Tree? (1/0)"<<endl;
                        cin>>ch;
                        if(ch==0){
                            cout<<"No Changes Applied"<<endl;
                            break;
                        }
                    }
                    val.clear();
                    cout<<"How many values do you want to enter?"<<endl;
                    cin>>it;
                    cout<<"Enter values: ";
                    while(it--){
                        cin>>data;
                        val.push_back(data);
                    }
                    t->constructLeftSkewedTreeUsingArray(root, val);
                    cout<<"Left Skewed Tree Constructed Successfully!"<<endl;

                }
                break;

            case 12:
                if(t==nullptr){
                    cout<<"Please Create an Empty Tree First!"<<endl;
                }
                else{
                    t->displayTreeUsingLOT(root);
                }

                break;
            case 13:
                cout<<"Thanks for using!"<<endl;
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


int main() {
/*
 *              10
 *             /   \
 *          8        2
 *        /  \       /
 *       3     5    2
 */

    Menu m;
    return 0;
}