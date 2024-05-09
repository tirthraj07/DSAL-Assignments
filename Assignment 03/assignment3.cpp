#include <iostream>
using namespace std;

/*

Name: Tirthraj Mahajan
Class: SE2 
RollNo: 21242

Creating the binary tree following the following diagram
https://examradar.com/wp-content/uploads/2016/10/Threaded-Binary-Tree-3.png

Steps of creating a Threaded Binary Search Tree

1. Create a node class with the following attributes, data, left ptr, right ptr, lbit and rbit

2. When you create a new node, make that node a leaf node by default, cause you always enter leaf nodes into the tree

3. In the TBST class, make a header node what will not be printed, It's left pointer points to the first node inserted


*/



class Node{
private:
    int data;
    Node* left;
    Node* right;
    bool lthread;
    bool rthread; 
public:
    // Create a leaf node initially
    Node(int data):data(data){
        left = nullptr;
        right = nullptr;
        lthread = true;
        rthread = true;
    }
    friend class Pair;
    friend class TBST;
};


/*
You'll see later why we are making this class
basically it is for optimizations and readability
in the future, we when we want to search for a node, we will require its parent for say deletion purposes, then this data structure will give us both at once
*/
class Pair{
private:
    Node* parent;
    Node* child;
public:
    Pair(Node* parent, Node* child):parent(parent),child(child){}
    friend class TBST;
    
};

class TBST{
    
// Tip: Read the public functions first and then come back to see the private functions
// When you check the algorithm, you'll understand why i decided to create the functions in the private field
// So just check the algorithms in the public field and then come back here

private:
    Node* header;
    
    Node* leftmost(Node* node){
        if(!node) return NULL;
        while(!node->lthread){
            node = node->left;
        }
        return node;
    }
    
    Node* rightmost(Node* node){
        if(!node) return NULL;
        while(!node->rthread){
            node = node->right;
        }
        return node;
    }
    
    /*
    
        When you are inserting in the left,
        Step 1: Copy all the left attributes of the parent to the child
        Therefore, copy the lthread and left
    
        Step 2: Now Point the right ptr of child to parent
        
        Step 3: Make the left pointer of parent point to child and make lthread false
    
    */
    
    void insertAtLeft(Node *parent, Node* child){
        // Step 1
        child->lthread = parent->lthread;
        child->left = parent->left;
        
        // Step 2
        child->right = parent;
        
        // Step 3
        parent->left = child;
        parent->lthread = false;
    }
    
    
    /*
        When you are inserting to the right
        Step 1: Copy all the right attributes of parent to the child
        Therefore copy rthread and right ptr
    
        Step 2: Point the left pointer of child to parent
        
        Step 3: Point the right ptr of parent to child and make the rthread false
    
    */
    
    void insertAtRight(Node *parent, Node* child){
        // Step 1
        child->rthread = parent->rthread;
        child->right = parent->right;
        
        // Step 2
        child->left = parent;
        
        // Step 3
        parent->right = child;
        parent->rthread = false;
    }
    
    // It is similar to insertion, but if we encounter thread while traversing, we return NULL, NULL which means that element does not exists
    // It will return the parent and the actual node in the Pair. 
    
    Pair search(int data){
        if(header->lthread){
            return Pair(NULL,NULL);
        }
        
        Node* parent = header;
        Node* curr = header->left;
        while(curr->data != data){
            parent = curr;
            if(curr->data > data && curr->lthread) return Pair(NULL, NULL);
            else if(curr->data > data) curr = curr->left;
            else if(curr->data < data && curr->rthread) return Pair(NULL,NULL);
            else curr = curr->right;
        }
        return Pair(parent, curr);
    }
    
    
public:
    TBST(){
        header = new Node(-1);
        header->left = header;
        header->right = header;
    }
    
    void insert(int data){
        Node* newNode = new Node(data);

        // For the first node only

        if(header->lthread){
            insertAtLeft(header, newNode);
            return;
        }
        
        Node* curr = header->left;
        while(curr){
            if(curr->data>data && curr->lthread){
                insertAtLeft(curr, newNode);
                return;
            }
            else if(curr->data>data){
                curr = curr->left;
            }
            else if(curr->data<data && curr->rthread){
                insertAtRight(curr, newNode);
                return;
            }
            else if(curr->data<data){
                curr = curr->right;
            }
            else{
                cout<<"Cannot insert duplicates"<<endl;
                return;
            }
        }
    }
    
    void searchData(int data){
        if(header->lthread){
            cout<<"Tree is empty. Thus element not found"<<endl;
            return;
        }
        Pair p = search(data);
        if(!p.child){
            cout<<"Element does not exists"<<endl;
        }
        else{
            cout<<"Element Found!"<<endl;
        }
    }
    
    void inorder(){
        if(header->lthread){
            cout<<"Tree Empty"<<endl;
            return;
        }
        
        Node* curr = header->left;
        curr = leftmost(curr);
        while(curr!=header){
            cout<<curr->data<<" ";
            if(curr->rthread) curr = curr->right;
            else curr = leftmost(curr->right);
        }
    }
    
    void preorder(){
        if(header->lthread){
            cout<<"Tree Empty"<<endl;
            return;
        }
        
        Node* curr = header->left;
        while(curr!=header){
            cout<<curr->data<<" ";
            if(!curr->lthread){
                curr = curr->left;
            }
            else if(!curr->rthread){
                curr = curr->right;
            }
            else{
                while(curr!=header&&curr->rthread){
                    curr = curr->right;
                }
                if(curr==header) break;
                curr = curr->right;
            }
        }
    }
    
    void deleteNode(int data){
        Pair p = search(data);
        if(!p.child){
            cout<<"Element does not exist in the tree"<<endl;
            return;
        }
        Node* parent = p.parent;
        Node* curr = p.child;
        if(curr->lthread && curr->rthread){
            noChildCase(parent, curr);
        }
        else if(curr->lthread || curr->rthread){
            oneChildCase(parent, curr);
        }
        else{
            bothChildrenCase(curr);
        }
    }
    
    void noChildCase(Node* parent, Node* curr){
        if(parent->left == curr){
            parent->left = curr->left;
            parent->lthread = true;
        }
        else{
            parent->right = curr->right;
            parent->rthread = true;
        }
    }
    
    void oneChildCase(Node* A,Node* B){
        Node* C;
        if(!B->lthread) C = B->left;
        else C = B->right;
        
        if(A->left == B && B->left == C){
            A->left = C;
            C = rightmost(C);
            C->right = A;
        }
        else if(A->left == B && B->right == C){
            A->left = C;
            C = leftmost(C);
            C->left = B->left;
        }
        else if(A->right == B && B->left == C){
            A->right = C;
            C = rightmost(C);
            C->right = B->right;
        }
        else if(A->right == B && B->right == C){
            A->right = C;
            C = leftmost(C);
            C->left = A;
        }
        
    }
    
    
    void bothChildrenCase(Node* curr){
        Node* inorderSuccessor = curr->right;
        Node* parentOfInorderSuccessor = curr;
        while(!inorderSuccessor->lthread){
            parentOfInorderSuccessor = inorderSuccessor;
            inorderSuccessor = inorderSuccessor->left;
        }
        
        curr->data = inorderSuccessor->data;
        
        if(!inorderSuccessor->lthread&&!inorderSuccessor->rthread){
            noChildCase(parentOfInorderSuccessor, inorderSuccessor);
        }
        else if(!inorderSuccessor->lthread || !inorderSuccessor->rthread){
            oneChildCase(parentOfInorderSuccessor, inorderSuccessor);
        }
        
    }
    
};

int main(){
    // Make it menu driven in practical exam


    TBST tree;
    
    // Insertion

    tree.insert(5);
    tree.insert(3);
    tree.insert(25);
    tree.insert(15);
    tree.insert(35);
    tree.insert(20);
    tree.insert(28);
    tree.insert(26);
    tree.insert(29);
    tree.insert(27);
    
    // traversal

    tree.inorder();
    cout<<endl;
    tree.preorder();


    cout<<endl<<endl;

    // searching

    tree.searchData(5);
    tree.searchData(3);
    tree.searchData(25);
    tree.searchData(15);
    tree.searchData(35);
    tree.searchData(20);
    tree.searchData(-1);
    tree.searchData(30);
    
    
    cout<<endl<<endl;
    
    // deletion

    /*
        test cases for case A:
        Test Case 1:
        tree.deleteNode(3);

        Test Case 2:
        tree.deleteNode(20);

        
    */

    /*
        Test Cases for Case B

        Test Case 1:
        tree.deleteNode(15);

        Test Case 2:
        tree.deleteNode(35);

    */
    

   /*
        Test Case for Case C

        Test Case 1:
        tree.deleteNode(5);

        Test Case 2:
        tree.deleteNode(25)

   */

    tree.deleteNode(25);


    tree.inorder();
    cout<<endl;
    tree.preorder();


    cout<<endl<<endl;

    // All Cases Passed Successfully!

    
}