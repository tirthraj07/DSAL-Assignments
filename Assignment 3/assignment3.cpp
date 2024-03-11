#include<iostream>
#include<vector>
using namespace std;

class Node{
private:
    int data;
    Node* left;
    Node* right;
    bool lThread;
    bool rThread;
public:
    Node(int data=0):data(data),left(NULL),right(NULL),lThread(true),rThread(true){}
    friend class TBST;
};

class TBST{
private:
    Node* root;
public:
    TBST():root(nullptr){}
   
    void insert(int data){
        if(root == NULL){
            root = new Node(data);
            return;
        }
       
        Node* curr = root;
        Node* prev = NULL;
       
        while(curr){
            prev = curr;
            if(curr->data>data) {
                if(curr->lThread){
                    break;
                }
                curr = curr->left;
            }
            else{
                if(curr->rThread){
                    break;
                }
                curr = curr->right;
            }
        }
       
        curr = new Node(data);

        if(prev->data>curr->data){
            curr->lThread = prev->lThread;
            curr->left = prev->left;
            prev->lThread = false;
            prev->left = curr;
            curr->rThread = true;
            curr->right = prev;
        }
        else{
            curr->rThread = prev->rThread;
            curr->right = prev->right;
            prev->rThread = false;
            prev->right = curr;
            curr->lThread = true;
            curr->left = prev;
        }
       
    }
   
    Node* leftmost(Node* node){
        if(node==NULL) return node;
        while(node->left != NULL && node->lThread == false){
            node = node->left;
        }
        return node;
    }

    void travseralInorder(){
        if(!root) return;
        Node* curr = leftmost(root);
        while(curr != NULL){
            cout<<curr->data<<" ";
            if(curr->rThread) curr = curr->right;
            else curr = leftmost(curr->right);
        }
    }

    void preorder(){
        if(root==NULL){
            cout<<" Tee is Empty"<<endl;
        }
        else{
            Node* curr = root;
            while(curr!=NULL){
                cout<<curr->data<<" ";
                if(!curr->lThread){
                    curr = curr->left;
                }
                else if(!curr->rThread){
                    curr = curr->right;
                }
                else{
                    while(curr && curr->rThread){
                        curr = curr->right;
                    }
                    if(curr){
                        curr = curr->right;
                    }
                }
            }
        }
    }
   
    void deletion(int a) {
        if (root == nullptr) {
            return;
        }
        int found = 0;
        Node* par = nullptr;
        Node* curr = root;
        do {
            if (curr->data == a) {
                found = 1;
                break;
            }
            par = curr;
            if (curr->data < a) {
                curr = curr->right;
            } else {
                curr = curr->left;
            }
        } while (curr != root);
        if (found == 0) {
            return;
        }
        if (curr->lThread && curr->rThread) {
            caseA(par, curr);
        } else if (!curr->lThread && !curr->rThread) {
            caseC(par, curr);
        } else {
            caseB(par, curr);
        }
    }
   
    void caseA(Node* par, Node* curr) {
        if (par == nullptr) {
            delete root;
            root = nullptr;
            return;
        }
        if (par->right == curr) {
            par->right = curr->right;
            par->rThread = curr->rThread;
            delete curr;
        } else {
            par->left = curr->left;
            par->lThread = curr->lThread;
            delete curr;
        }
    }
   
    Node* pred(Node* curr) {
        return curr->left;
    }
   
    Node* inorder_Successor(Node* p) {
        if (p == nullptr) {
            return nullptr;
        }
        if (p->rThread) {
            return p->right;
        }
        p = p->right;
        while (!p->lThread) {
            p = p->left;
        }
        return p;
    }
   
    Node* rightmost(Node* node) {
        Node* p = node;
        while (p->right != node) {
            p = p->right;
        }
        return p;
    }
   
    void caseB(Node* par, Node* curr) {
        Node* p = pred(curr);
        Node* s = inorder_Successor(curr);
        Node* child = nullptr;
        if (!curr->lThread) {
            child = curr->left;
            if (curr == root) {
                leftmost(curr)->left = child;
                root = child;
                p->right = root;
                delete curr;
                return;
            }
            p->right = s;
            if (curr == par->left) {
                par->left = child;
            } else {
                par->right = child;
            }
            delete curr;
        } else {
            child = curr->right;
            if (curr == root) {
                rightmost(curr)->right = child;
                root = child;
                s->left = root;
                delete curr;
                return;
            }
            s->left = p;
            if (curr == par->left) {
                par->left = child;
            } else {
                par->right = child;
            }
            delete curr;
        }
    }
   
    void caseC(Node* par, Node* curr) {
        Node* parsucc = curr;
        Node* succ = curr->right;
        while (!succ->lThread) {
            parsucc = succ;
            succ = succ->left;
        }
        curr->data = succ->data;
        if (succ->lThread && succ->rThread) {
            caseA(parsucc, succ);
        } else {
            caseB(parsucc, succ);
        }
    }


};


class Menu{
private:
    int choice;
    TBST* treePtr;
public:
    Menu(){
        treePtr = nullptr;
        askChoice();
        initiateOperation();
    }
   
    void askChoice(){
        cout<<"\n\nWhat do you want to do?"<<endl;
        cout<<"1. Create Empty TBST"<<endl;
        cout<<"2. Insert a value in TBST"<<endl;
        cout<<"3. Enter Array of numbers in TBST"<<endl;
        cout<<"4. Inorder Traversal of TBST"<<endl;
        cout<<"5. Preorder Traversal of TBST"<<endl;
        cout<<"6. Delete Node from TBST"<<endl;
        cout<<"7. Exit"<<endl;
        cout<<">> ";
        cin>> choice;
        cout<<endl;
    }

    void initiateOperation(){
        bool ch;
        int count, num;
        
        switch(choice){
            case 1:
                if(treePtr!=nullptr){
                    cout<<"Do you want to delete the existsing tree? (1/0)"<<endl;
                    cin>> ch;
                    if(ch){
                        treePtr = new TBST();
                    }
                    break;
                }
                else{
                    treePtr = new TBST();
                }

                break;
            case 2:
                if(treePtr==nullptr){
                    cout<<"Please create an empty tree first"<<endl;
                    break;
                }
                cout<<"Enter the number to be inserted"<<endl;
                cin>>num;
                treePtr->insert(num);
                break;
            case 3:
                if(treePtr==nullptr){
                    cout<<"Please create an empty tree first"<<endl;
                    break;
                }
                cout<<"How many numbers do you want to enter?"<<endl;
                cin>>count;
                cout<<">> ";
                for(int i=0; i<count; i++){
                    cin>> num;
                    treePtr->insert(num);
                }
                cout<<endl;
                break;
            case 4:
                if(treePtr==nullptr){
                    cout<<"Please create an empty tree first"<<endl;
                    break;
                }
                cout<<"Inorder traversal"<<endl;
                treePtr->travseralInorder();
                cout<<endl;
                break;
            case 5:
                if(treePtr==nullptr){
                    cout<<"Please create an empty tree first"<<endl;
                    break;
                }
                cout<<"Preorder Traversal"<<endl;
                treePtr->preorder();
                cout<<endl;
                break;
            case 6:
                if(treePtr==nullptr){
                    cout<<"Please create an empty tree first"<<endl;
                    break;
                }
                cout<<"Enter the node to be deleted : "<<endl;
                cin>>num;
                treePtr->deletion(num);
                cout<<endl;
                break;
            case 7:
                cout<<"Thank you for using ;)"<<endl;    
                return;
                break;
            default:
                cout<<"Enter a valid choice!"<<endl;
        }
        retry();
    }

    void retry(){
        askChoice();
        initiateOperation();
    }
   


   
};


int main(){
    Menu m;


    // TBST tree;
    // tree.insert(28);
    // cout<<endl;
    // tree.insert(15);
    // cout<<endl;
    // tree.insert(85);
    // cout<<endl;
    // tree.insert(49);
    // cout<<endl;
    // tree.insert(55);
    // cout<<endl;
    // tree.insert(100);
    // cout<<endl;
    // tree.insert(98);
    // cout<<endl;
    // tree.insert(102);
    // tree.travseralInorder();
    // cout<<endl;

    // tree.preorder();
    // cout<<endl;
   
    // tree.deletion(28);
    // tree.travseralInorder();
   
    return 0;
}