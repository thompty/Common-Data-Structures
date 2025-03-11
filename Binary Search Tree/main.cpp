#include <iostream>
#include <vector>

struct Node {
    int key;
    Node* left;
    Node* right;
    Node(int item) {
        key = item;
        left = right = NULL;
    }
};

// function to search a key in a BST
Node* search(Node* root, int key) {
  
    // Base Cases: root is null or key 
    // is present at root
    if (root == NULL || root->key == key)
        return root;

    // Key is greater than root's key
    if (root->key < key)
        return search(root->right, key);

    // Key is smaller than root's key
    return search(root->left, key);
}

Node* insert(Node* node, int key) {
  
    // If the tree is empty, return a new node
    if (node == NULL) 
        return new Node(key);    
    
    // If the key is already present in the tree,
    // return the node
    if (node->key == key) 
        return node;
    
    // Otherwise, recur down the tree/ If the key
    // to be inserted is greater than the node's key,
    // insert it in the right subtree
    if (node->key < key) 
        node->right = insert(node->right, key);
    
    // If the key to be inserted is smaller than 
    // the node's key,insert it in the left subtree
    else 
        node->left = insert(node->left, key);
    
    // Return the (unchanged) node pointer
    return node;
}

Node* getSuccessor(Node* curr){
    curr = curr->right;
    while (curr != nullptr && curr->left != nullptr)
        curr = curr->left;
    return curr;
}

Node* delNode(Node* root, int x){

    // Base case
    if (root == nullptr)
        return root;

    // If key to be searched is in a subtree
    if (root->key > x)
        root->left = delNode(root->left, x);
    else if (root->key < x)
        root->right = delNode(root->right, x);

    // If root matches with the given key
    else {

        // Cases when root has 0 children
        // or only right child
        if (root->left == nullptr) {
            Node* temp = root->right;
            delete root;
            return temp;
        }

        // When root has only left child
        if (root->right == nullptr) {
            Node* temp = root->left;
            delete root;
            return temp;
        }

        // When both children are present
        Node* succ = getSuccessor(root);
        root->key = succ->key;
        root->right = delNode(root->right, succ->key);
    }
    return root;
}

void inorder(Node* root, std::vector<int>& sortedInorder) {
  
    // Base Case
    if (root == nullptr) return;

    // Traverse left subtree
    inorder(root->left, sortedInorder);

    // Store the current node's data
    sortedInorder.push_back(root->key);

    // Traverse right subtree
    inorder(root->right, sortedInorder);
}

// Function to find the minimum value in BST
int minValue(Node* root) {
    if (root == nullptr) {
        return -1;
    }
    
    std::vector<int> sortedInorder;
    
    // Call the recursive inorder function
    inorder(root, sortedInorder);
    
    // Return the first element, which is the minimum
    return sortedInorder[0];
}

int maxValue(Node* root) {
    if (root == nullptr) return -1;

    // Using a vector to hold inorder elements
    std::vector<int> sorted_inorder;

    // Call the recursive inorder function
    inorder(root, sorted_inorder);

    // Return the last element, which is the maximum
    return sorted_inorder.back();
}