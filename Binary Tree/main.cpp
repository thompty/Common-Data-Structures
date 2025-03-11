#include <algorithm>
#include <queue>

class Node {
    public:
        int data;
        Node *left;
        Node *right;
    
        Node(int val) {
            data = val;
            left = nullptr;
            right = nullptr;
        }
    };
    
//Find the max depth of the binary tree
int height(Node *root) {
    //Check if tree is empty
    if (root == nullptr)
        return -1;

    //Compute the height of left and right subtrees
    int lHeight = height(root->left);
    int rHeight = height(root->right);

    return std::max(lHeight, rHeight) + 1;
}

Node* insertNode(Node* root, int data) {
  
    //If the tree is empty, assign new
      //Node address to root
    if (root == nullptr) {
        root = new Node(data);
        return root;
    }

    std::queue<Node*> q;
    q.push(root);

    while (!q.empty()) {
      
          //From a front element in queue
        Node* curr = q.front();
        q.pop();
        
          //First check left if left is null 
          //Insert node in left otherwise chaeck for right
        if (curr->left != nullptr)
            q.push(curr->left);
        else {
            curr->left = new Node(data);
            return root;
        }
    
        if (curr->right != nullptr)
            q.push(curr->right);
        else {
            curr->right = new Node(data);
            return root;
        }
    }
}

// Function to delete the deepest node in binary tree
void deleteDeepest(Node* root, Node* dNode) {
    std::queue<Node*> q;
    q.push(root);

    Node* curr;
    while (!q.empty()) {
        curr = q.front();
        q.pop();

        // If current node is the deepest
          // node, delete it
        if (curr == dNode) {  
            curr = nullptr;
            delete (dNode);
            return;
        }

        // Check the right child first
        if (curr->right) {
          
            // If right child is the deepest
              // node, delete it
            if (curr->right == dNode) {
                curr->right = nullptr;
                delete (dNode);
                return;
            } 
            q.push(curr->right);
        }

        // Check the left child
        if (curr->left) {
          
            // If left child is the deepest 
              // node, delete it
            if (curr->left == dNode) {
                curr->left = nullptr;
                delete (dNode);
                return;
            } 
            q.push(curr->left);
        }
    }
}

// Function to delete the node with the given key
Node* deletion(Node* root, int key) {
  
    // If the tree is empty, return null
    if (root == nullptr)
        return nullptr;

    // If the tree has only one node
    if (root->left == nullptr && root->right == nullptr) {
      
        // If the root node is the key, delete it
        if (root->data == key)
            return nullptr;
        else
            return root;
    }

    std::queue<Node*> q;
    q.push(root);

    Node* curr;
    Node* keyNode = nullptr;

    // Level order traversal to find the deepest
      // node and the key node
    while (!q.empty()) {
        curr = q.front();
        q.pop();

        // If current node is the key node
        if (curr->data == key)
            keyNode = curr;

        if (curr->left)
            q.push(curr->left);

        if (curr->right)
            q.push(curr->right);
    }

    // If key node is found, replace its data
      // with the deepest node
    if (keyNode != nullptr) {
      
          // Store the data of the deepest node
        int x = curr->data;  
      
          // Replace key node data with deepest
          // node's data
        keyNode->data = x;  
      
          // Delete the deepest node
        deleteDeepest(root, curr);  
    }
    return root;
}