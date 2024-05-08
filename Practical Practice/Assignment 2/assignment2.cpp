/*
A dictionary stores keywords and its meanings. 
Provide facility for adding new  keywords, updating values of any entry, delete any entry. 
Provide facility to display whole data sorted in ascending/ Descending order using recursive and non-recursive traversal. 
Also find how many maximum comparisons may require for finding any keyword. 
Use Binary Search Tree for implementation. 
*/

#include <iostream>

using namespace std;




class Node{
private:
    string word;
    string meaning;
    Node* left;
    Node* right;
public:
    Node(string word, string meaning, Node* left = NULL, Node* right = NULL):word(word),meaning(meaning),left(left),right(right){}
    
    bool operator< (Node* obj){
        return this->word<obj->word;
    }

    bool operator> (Node* obj){
        return this->word>obj->word;
    }
    
    friend ostream& operator << (ostream& out, Node* &node);
    
    friend class BST;
};

ostream& operator << (ostream& out, Node* &node){
    out<<node->word<<" : "<<node->meaning;
    return out;
}

class ListNode{
private:
    Node* data;
    ListNode* next;
public:
    ListNode(Node* data, ListNode* next = NULL):data(data),next(next){}
    friend class Stack;
};

class Stack{
private:
    ListNode* head;
    int length;
public: 
    Stack():head(NULL),length(0){}

    void push(Node* data){
        ListNode* newNode = new ListNode(data);
        newNode->next = head;
        head = newNode;
        length++;
    }

    void pop(){
        if(length == 0){
            cout<<"Error: Stack Underflow"<<endl;
            return;
        }
        length--;
        ListNode* temp = head;
        head = head->next;
        delete temp;
    }

    bool empty(){
        if(length==0) return true;
        return false;
    }

    Node* top(){
        if(length == 0){
            cout<<"Error: Stack Underflow"<<endl;
            return NULL;
        }
        return head->data;
    }

};

class Pair{
private:
    Node* parent;
    Node* child;
public:
    Pair(Node* parent = NULL, Node* child = NULL):parent(parent),child(child){}
    friend class BST;
};

class BST{
private:
    Node* root;

    void insertIterative(string word, string meaning){
        if(root==NULL){
            root = new Node(word, meaning);
            return;
        }
        Node* newNode = new Node(word, meaning);
        Node* curr = root;
        while(curr){
            if(curr->word > newNode->word && !curr->left){
                curr->left = newNode;
                return;
            }
            else if(curr->word > newNode->word){
                curr = curr->left;
            }
            else if(curr->word < newNode->word && !curr->right){
                curr->right = newNode;
                return;
            }
            else if(curr->word < newNode->word){
                curr = curr->right;
            }
            else{
                cout<<"Word has already been inserted"<<endl;
                return;
            }

        }
        // this should never run
        cout<<"Error while inserting item"<<endl;
        return;
    }

    Node* insertRecursive(Node* node, string word, string meaning){
        if(node==NULL) return new Node(word, meaning);

        if(node->word > word){
            node->left = insertRecursive(node->left, word, meaning);
        }
        else if(node->word < word){
            node->right = insertRecursive(node->right, word, meaning);
        }
        
        return node;
    }

    Node* searchNode(string word){
        Node* curr = root;
        while(curr){
            if(curr->word == word){
                return curr;
            }
            else if(curr->word > word){
                curr = curr->left;
            }
            else curr = curr->right;
        }
        return NULL;
    }

    Pair searchNodeWithParent(string word){
        Node* curr = root;
        Node* prev = NULL;
        while(curr){
            if(curr->word == word){
                return Pair(prev, curr);
            }
            prev = curr;
            if(curr->word > word){
                curr = curr->left;
            }
            else{
                curr = curr->right;
            }
        }

        return Pair();
    }

    void noChildCase(Node* parent, Node* child){
        if(parent->left == child){
            parent->left = NULL;
        }
        else{
            parent->right = NULL;
        }
    }

    void oneChildCase(Node* A, Node* B){
        Node* C;
        if(B->left) C = B->left;
        else C = B->right;

        if(A->left == B) A->left = C;
        else A->right = C;
    }

    void bothChildCase(Node* child){
        Node* parentOfInorderSuccessor = child;
        Node* inorderSuccessor = parentOfInorderSuccessor->right;
        
        while(inorderSuccessor->left){
            parentOfInorderSuccessor = inorderSuccessor;
            inorderSuccessor = inorderSuccessor->left;
        }

        child->word = inorderSuccessor->word;
        child->meaning = inorderSuccessor->meaning;

        if(!inorderSuccessor->left && !inorderSuccessor->right){
            noChildCase(parentOfInorderSuccessor, inorderSuccessor);
        }
        else if(!inorderSuccessor->left || !inorderSuccessor->right){
            oneChildCase(parentOfInorderSuccessor, inorderSuccessor);
        }
    }

    void inorderRecursive(Node* node){
        if(!node) return;
        inorderRecursive(node->left);
        cout<<node<<endl;
        inorderRecursive(node->right); 
    }

    void reverseInorderRecursive(Node* node){
        if(!node) return;
        reverseInorderRecursive(node->right);
        cout<<node<<endl;
        reverseInorderRecursive(node->left);
    }

    void inorderIterative(){
        Node* curr = root;
        Stack st;
        while(!st.empty() || curr){
            while(curr){
                st.push(curr);
                curr = curr->left;  
            }
            cout<<st.top()->word<<" : "<<st.top()->meaning<<endl;
            curr = st.top()->right;
            st.pop();
        }   
        
    }

    void reverseInorderIterative(){
        Node* curr = root;
        Stack st;
        while(!st.empty() || curr){
            while(curr){
                st.push(curr);
                curr = curr->right;
            }
            curr = st.top();
            cout<<curr<<endl;
            curr = st.top()->left;
            st.pop();
        }
    }

public:
    BST():root(NULL){}

    void insert(bool recursive, string word, string meaning){
        if(recursive){
            root = insertRecursive(root, word, meaning);            
        }
        else{
            insertIterative(word, meaning);
        }
    }

    void search(string word){
        Node* node = searchNode(word);
        if(!node){
            cout<<"Word does not exist in dictionary"<<endl;
            return;
        }
        cout<<"Element Found!"<<endl;
        cout<<node<<endl;
    }

    void update(string word){
        Node* node = searchNode(word);
        if(!node){
            cout<<"Word "<<word<<" does not exist in dictionary"<<endl;
            return;
        }
        cout<<"=== Current ==="<<endl;
        cout<<node<<endl;
        string meaning;
        cout<<"Update Meaning: ";
        getline(cin, meaning);
        node->meaning = meaning;
        cout<<"=== Updated ==="<<endl;
        cout<<node<<endl;
    }

    void deleteNode(string word){
        Pair p = searchNodeWithParent(word);
        if(p.child == NULL){
            cout<<"Could not find the word in dictionary"<<endl;
            return;
        }
        Node* child = p.child;
        Node* parent = p.parent;
        // if root then handle separately    
        if(child==root){
            if(!child->left&&!child->right){
                root = NULL;
            }
            else if(child->right){
                // Replace by inorder successor
                Node* parentOfInorderSuccessor = root;
                Node* inorderSuccessor = parentOfInorderSuccessor->right;
                while(inorderSuccessor->left){
                    parentOfInorderSuccessor = inorderSuccessor;
                    inorderSuccessor = inorderSuccessor->left;
                }
                root->word = inorderSuccessor->word;
                root->meaning = inorderSuccessor->meaning;
                if(!inorderSuccessor->left&&!inorderSuccessor->right){
                    noChildCase(parentOfInorderSuccessor, inorderSuccessor);
                }
                else{
                    oneChildCase(parentOfInorderSuccessor, inorderSuccessor);
                }
            }
            else{
                // Replace by inorder predecessor
                Node* parentOfInorderPredecessor = root;
                Node* inorderPredecessor = parentOfInorderPredecessor->left;
                while(inorderPredecessor->right){
                    parentOfInorderPredecessor = inorderPredecessor;
                    inorderPredecessor = inorderPredecessor->right;
                }
                root->word = inorderPredecessor->word;
                root->meaning = inorderPredecessor->meaning;
                if(!inorderPredecessor->left&&!inorderPredecessor->right){
                    noChildCase(parentOfInorderPredecessor, inorderPredecessor);
                }
                else{
                    oneChildCase(parentOfInorderPredecessor, inorderPredecessor);
                }
            }
            return;
        }


        if(!child->left&&!child->right){
            noChildCase(parent, child);
        }
        else if(!child->left || !child->right){
            oneChildCase(parent, child);
        }
        else{
            bothChildCase(child);
        }

    }

    void inorder(bool recursive){
        if(recursive){
            inorderRecursive(root);
            cout<<endl;
        }
        else{
            inorderIterative();
            cout<<endl;
        }
    }

    void reverseInorder(bool recursive){
        if(recursive){
            reverseInorderRecursive(root);
            cout<<endl;
        }   
        else{
            reverseInorderIterative();
            cout<<endl;
        }
    }

};

int main(){
    BST tree;
    tree.insert(1,"apple","a fruit");
    tree.insert(0,"banana","a fruit");
    tree.insert(1,"football","a sport");
    tree.insert(0,"cricket", "a sport");
    tree.insert(1,"chelsea","pride of london");
    tree.insert(1,"game","an activity that one engages in for fun");
    tree.inorder(0);
    tree.inorder(1);
    tree.reverseInorder(0);
    tree.reverseInorder(1);
    tree.search("chelsea");
    tree.search("man u");
    tree.update("football");
    tree.deleteNode("apple");
    tree.inorder(0);
    tree.inorder(1);

}