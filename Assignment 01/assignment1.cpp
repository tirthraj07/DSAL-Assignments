/*
Name: Tirthraj Mahajan
Class: SE-02
Roll No: 21242

Beginning with an empty binary tree, construct binary tree by inserting the values in the 
order given. After constructing a binary tree perform following operations on it-
• Perform preorder recursive traversal 
• Postorder, Inorder non-recursive traversal
• Count number of leaves, number of internal nodes. 
• Perform post order recursive traversal 
• Inorder, Preorder non-recursive traversal 
• Find the height of tree
• Perform inorder, recursive traversal 
• Preorder, post-order non-recursive traversal
• Find mirror image of a tree
• Perform non-recursive inorder traversal, recursive postorder
• Level wise printing
• Display and count leaf nodes
• Display and count internal nodes
*/


#include <iostream>
using namespace std;

// Used for binary tree
class Node{
private:
    int data;
    Node* left;
    Node* right;
public:
    Node(int data, Node* left = NULL, Node* right = NULL):data(data),left(left),right(right){};
    friend class Tree;
    friend class ListNode;
    friend ostream& operator<< (ostream& out, Node* &node);
    
};

ostream& operator<< (ostream& out, Node* &node){
    out<<node->data;
    return out;
}

// Used for stack and queue
class ListNode{
private:
    Node* data;
    ListNode* next;
public:
    ListNode(Node* data = NULL, ListNode* next = NULL):data(data),next(next){}
    friend class Stack;
    friend class Queue;
    friend ostream& operator<< (ostream& out, ListNode& node);
};

ostream& operator<< (ostream& out, ListNode& node){
    out<<(node.data);
    return out;
}

class Stack{
private:
    ListNode* head;
    int length;
public:
    Stack():head(NULL),length(0){};
    void push(Node* data){
        ListNode* newNode = new ListNode(data);
        newNode->next = head;
        head = newNode;
        length++;
    }

    void pop(){
        if(length==0){
            cout<<"Error: Stack Underflow"<<endl;
            return;
        }
        length--;
        ListNode* temp = head;
        head = head->next;
        delete temp;
    }

    Node* top(){
        if(length == 0){
            cout<<"Error: Stack Underflow"<<endl;
            return NULL;
        }
        return head->data;
    }

    bool empty(){
        if(length==0) return true;
        return false;
    }

    void print(){
        if(length == 0){
            cout<<"Stack Empty"<<endl;
            return;
        }
        ListNode* curr = head;
        while(curr){
            cout<<*curr<<" ";
            curr = curr->next;
        }
        cout<<endl;
    }
};


class Queue{
private:
    ListNode* head;
    ListNode* tail;
    int length;
public:
    Queue():head(NULL),tail(NULL),length(0){}
    void push(Node* data){
        length++;
        if(head==NULL){
            head = new ListNode(data);
            tail = head;
            return;
        }

        ListNode* newNode = new ListNode(data);
        tail->next = newNode;
        tail = newNode;
        return;
    }

    void pop(){
        if(length==0){
            cout<<"Error: Queue Underflow"<<endl;
            return;
        }
        ListNode* temp = head;
        head = head->next;
        length--;
        delete temp;
    }

    Node* front(){
        if(length == 0){
            cout<<"Error: Queue Underflow"<<endl;
            return NULL;
        }
        return head->data;
    }

    bool empty(){
        if(length==0) return true;
        return false;
    }

    void print(){
        if(length == 0){
            cout<<"Queue Empty"<<endl;
            return;
        }
        ListNode* curr = head;
        while(curr){
            cout<<*curr<<" ";
            curr = curr->next;
        }
        cout<<endl;
    }
};


class Tree{
private:
    Node* root;

    Node* copyTree(Node* root){
        if(root == nullptr ) return nullptr;
        Node* newNode = new Node(root->data);
        newNode->left = copyTree(root->left);
        newNode->right = copyTree(root->right);
        return newNode;
    }

    Node* constructTree(Node* &node){
        int data;
        cout<<"Enter Data (-1 to stop)"<<endl;
        cin>>data;
        if(data == -1) return NULL;

        node = new Node(data);

        cout<<"Enter value to left of "<<data<<endl;
        node->left = constructTree(node->left);

        cout<<"Enter value to right of "<<data<<endl;
        node->right = constructTree(node->right);

        return node;
    }

    void inorderRecursive(Node* node){
        if(node==NULL) return;
        inorderRecursive(node->left);
        cout<<node->data<<" ";
        inorderRecursive(node->right);
    }

    void inorderIterative(Node* node){
        Stack st;
        while(!st.empty() || node){
            while(node){
                st.push(node);
                node = node->left;
            }

            cout<<st.top()->data<<" ";
            node = st.top()->right;
            st.pop();
        }
    }

    void preorderRecursive(Node* node){
        if(node==NULL) return;
        cout<<node->data<<" ";
        preorderRecursive(node->left);
        preorderRecursive(node->right);
    }

    void preorderIterative(Node* node){
        Stack st;
        while(!st.empty() || node){
            while(node){
                cout<<node->data<<" ";
                st.push(node);
                node = node->left;
            }
            node = st.top()->right;
            st.pop();
        }
    }

    void postorderRecursive(Node* node){
        if(node==NULL) return;
        postorderRecursive(node->left);
        postorderRecursive(node->right);
        cout<<node->data<<" ";
    }

    void postorderIterative(Node* node){
        if(node==NULL) return;
        Stack st1;
        Stack st2;
        st1.push(node);
        while(!st1.empty()){
            node = st1.top();
            st1.pop();
            st2.push(node);
            if(node->left) st1.push(node->left);
            if(node->right) st1.push(node->right);
        }

        while(!st2.empty()){
            cout<<st2.top()->data<<" ";
            st2.pop();
        }
    }

    int getHeight(Node* node){
        if(node == nullptr) return 0;
        int leftSubtreeHeight = getHeight(node->left);
        int rightSubtreeHeight = getHeight(node->right);
        return max(leftSubtreeHeight, rightSubtreeHeight) + 1;
    }

    Node* invertTreeRecursive(Node* node){
        if(node == NULL) return NULL;
        Node* temp = node->left;
        node->left = node->right;
        node->right = temp;
        invertTreeRecursive(node->left);
        invertTreeRecursive(node->right);
        return node;
    }

    void invertTreeIterative(){
        Node* curr = root;
        Stack st;
        st.push(root);
        while(!st.empty()){
            curr = st.top();
            st.pop();

            Node* temp = curr->left;
            curr->left = curr->right;
            curr->right = temp;
            
            if(curr->left) st.push(curr->left);

            if(curr->right) st.push(curr->right);
        }
    }

    int leafNodes(Node* node, bool display){
        if(node==NULL) return 0;
        if(node->left == NULL && node->right == NULL){
            if(display) cout<<node->data<<" ";
            return 1;
        }
        int leafNodesInLeftSubtree = leafNodes(node->left, display);
        int leafNodesInRightSubtree = leafNodes(node->right, display);
        return leafNodesInLeftSubtree + leafNodesInRightSubtree;
    }

    int internalNodes(Node* node, bool display){
        if(node==NULL) return 0;
        if(node->left==NULL && node->right==NULL) return 0;
        
        if(display){
            cout<<node->data<<" ";
        }

        int internalNodesInLeftSubtree = internalNodes(node->left, display);
        int internalNodesInRightSubtree = internalNodes(node->right, display);

        return internalNodesInLeftSubtree + internalNodesInRightSubtree + 1;
    }

public:
    Tree():root(NULL){}
    
    Tree(Node* &cpy, Node* root){
        cpy = copyTree(root);
    }

    void createTree(){
        root = constructTree(root);
    }

    void inorder(bool recursive){
        if(recursive){
            cout<<"===== Inorder (Recursive) ====="<<endl;
            inorderRecursive(root);
            cout<<endl<<"----- END -----"<<endl;
        }
        else{
            cout<<"===== Inorder (Iterative) ====="<<endl;
            inorderIterative(root);
            cout<<endl<<"----- END -----"<<endl;
        }

    }

    void preorder(bool recursive){
        if(recursive){
            cout<<"===== Preorder (Recursive) ====="<<endl;
            preorderRecursive(root);
            cout<<endl<<"----- END -----"<<endl;
        }
        else{
            cout<<"===== Preorder (Iterative) ====="<<endl;
            preorderIterative(root);
            cout<<endl<<"----- END -----"<<endl;
        }

    }

    void postorder(bool recursive){
        if(recursive){
            cout<<"===== Postorder (Recursive) ====="<<endl;
            postorderRecursive(root);
            cout<<endl<<"----- END -----"<<endl;
        }
        else{
            cout<<"===== Postorder (Iterative) ====="<<endl;
            postorderIterative(root);
            cout<<endl<<"----- END -----"<<endl;
        }

    }

    void levelOrderTraversal(){
        cout<<"===== Level Order Traversal ====="<<endl;
        Node* node = root;
        Queue q;
        q.push(node);
        q.push(NULL);
        while(!q.empty()){
            node = q.front();
            q.pop();
            if(node){
                cout<<node->data<<" ";
                if(node->left) q.push(node->left);
                if(node->right) q.push(node->right);
            }
            else{
                cout<<endl;
                if(!q.empty()) q.push(NULL);
            }
        }
        cout<<"----- END -----"<<endl;
    }

    void printHeight(){
        cout<<"** Height of Tree is : "<<getHeight(root)<<" **"<<endl;
    }

    void mirror(bool recursive){
        if(recursive){
            root = invertTreeRecursive(root);
            cout<<"-- Mirrored Recursively --"<<endl;
        }
        else{
            invertTreeIterative();
            cout<<"-- Mirrored Iteratively --"<<endl;
        }
    }

    void getLeafNodes(bool display){
        if(display){
            cout<<"=== Displaying Leaf Nodes ==="<<endl;
            int count = leafNodes(root,true);
            cout<<endl<<"----- END -----"<<endl;
            cout<<"** Total Leaf Nodes : "<<count<<" **"<<endl; 
        }
        else{
            int count = leafNodes(root,false);
            cout<<"** Total Leaf Nodes : "<<count<<" **"<<endl;
        }
    }

    void getInternalNodes(bool display){
        if(display){
            cout<<"=== Displaying Internal Nodes ==="<<endl;
            int count = internalNodes(root, true);
            cout<<endl<<"----- END -----"<<endl;
            cout<<"** Internal Nodes : "<<count<<" **"<<endl;
        }
        else{
            int count = internalNodes(root, false);
            cout<<"** Internal Nodes : "<<count<<" **"<<endl;
        }
    }

};

int main(){
    // Make it menu driven in the practicals

    // 1 7 2 -1 -1 6 5 -1 -1 11 -1 -1 9 -1 9 5 -1 -1 -1
    Tree t;
    t.createTree();
    t.preorder(0);
    t.preorder(1);
    t.inorder(0);
    t.inorder(1);
    t.postorder(0);
    t.postorder(1);
    t.levelOrderTraversal();
    t.printHeight();
    t.getLeafNodes(0);
    t.getLeafNodes(1);
    t.getInternalNodes(0);
    t.getInternalNodes(1);
    t.mirror(0);
    t.preorder(0);
    t.mirror(1);
    t.preorder(1);
}