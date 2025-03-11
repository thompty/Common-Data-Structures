#include <bits/stdc++.h> 

// An AVL tree node 
struct Node { 
    int key; 
    Node *left; 
    Node *right; 
    int height; 

    Node(int k) { 
        key = k; 
        left = nullptr; 
        right = nullptr; 
        height = 1; 
    }
}; 

// A utility function to 
// get the height of the tree 
int height(Node *N) { 
    if (N == nullptr) 
        return 0; 
    return N->height; 
} 

// A utility function to right 
// rotate subtree rooted with y 
Node *rightRotate(Node *y) { 
    Node *x = y->left; 
    Node *T2 = x->right; 

    // Perform rotation 
    x->right = y; 
    y->left = T2; 

    // Update heights 
    y->height = 1 + std::max(height(y->left), 
                    height(y->right)); 
    x->height = 1 + std::max(height(x->left), 
                        height(x->right)); 

    // Return new root 
    return x; 
} 

// A utility function to left rotate 
// subtree rooted with x 
Node *leftRotate(Node *x) { 
    Node *y = x->right; 
    Node *T2 = y->left; 

    // Perform rotation 
    y->left = x; 
    x->right = T2; 

    // Update heights 
    x->height = 1 + std::max(height(x->left), 
                        height(x->right)); 
    y->height = 1 + std::max(height(y->left), 
                        height(y->right)); 

    // Return new root 
    return y; 
} 

// Get balance factor of node N 
int getBalance(Node *N) { 
    if (N == nullptr) 
        return 0; 
    return height(N->left) - height(N->right); 
} 

Node * minValueNode(Node* node) {
    Node* current = node;

    // loop down to find the leftmost leaf
    while (current->left != nullptr)
        current = current->left;

    return current;
}

// Recursive function to insert a key in 
// the subtree rooted with node 
Node* insert(Node* node, int key) { 
  
    // Perform the normal BST insertion
    if (node == nullptr) 
        return new Node(key); 

    if (key < node->key) 
        node->left = insert(node->left, key); 
    else if (key > node->key) 
        node->right = insert(node->right, key); 
    else // Equal keys are not allowed in BST 
        return node; 

    // Update height of this ancestor node 
    node->height = 1 + std::max(height(node->left),
                           height(node->right)); 

    // Get the balance factor of this ancestor node 
    int balance = getBalance(node); 

    // If this node becomes unbalanced, 
    // then there are 4 cases 

    // Left Left Case 
    if (balance > 1 && key < node->left->key) 
        return rightRotate(node); 

    // Right Right Case 
    if (balance < -1 && key > node->right->key) 
        return leftRotate(node); 

    // Left Right Case 
    if (balance > 1 && key > node->left->key) { 
        node->left = leftRotate(node->left); 
        return rightRotate(node); 
    } 

    // Right Left Case 
    if (balance < -1 && key < node->right->key) { 
        node->right = rightRotate(node->right); 
        return leftRotate(node); 
    } 

    // Return the (unchanged) node pointer 
    return node; 
} 

Node* deleteNode(Node* root, int key) {
    // STEP 1: PERFORM STANDARD BST DELETE
    if (root == nullptr)
        return root;

    // If the key to be deleted is smaller 
    // than the root's key, then it lies in 
    // left subtree
    if (key < root->key)
        root->left = deleteNode(root->left, key);

    // If the key to be deleted is greater 
    // than the root's key, then it lies in 
    // right subtree
    else if (key > root->key)
        root->right = deleteNode(root->right, key);

    // if key is same as root's key, then 
    // this is the node to be deleted
    else {
        // node with only one child or no child
        if ((root->left == nullptr) || 
            (root->right == nullptr)) {
            Node *temp = root->left ? 
                         root->left : root->right;

            // No child case
            if (temp == nullptr) {
                temp = root;
                root = nullptr;
            } else // One child case
                *root = *temp; // Copy the contents of 
                               // the non-empty child
            free(temp);
        } else {
            // node with two children: Get the 
            // inorder successor (smallest in 
            // the right subtree)
            Node* temp = minValueNode(root->right);

            // Copy the inorder successor's 
            // data to this node
            root->key = temp->key;

            // Delete the inorder successor
            root->right = deleteNode(root->right, temp->key);
        }
    }

    // If the tree had only one node then return
    if (root == nullptr)
        return root;

    // STEP 2: UPDATE HEIGHT OF THE CURRENT NODE
    root->height = 1 + std::max(height(root->left), 
                   height(root->right));

    // STEP 3: GET THE BALANCE FACTOR OF THIS 
    // NODE (to check whether this node 
    // became unbalanced)
    int balance = getBalance(root);

    // If this node becomes unbalanced, then 
    // there are 4 cases

    // Left Left Case
    if (balance > 1 && 
        getBalance(root->left) >= 0)
        return rightRotate(root);

    // Left Right Case
    if (balance > 1 && 
        getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Right Right Case
    if (balance < -1 && 
        getBalance(root->right) <= 0)
        return leftRotate(root);

    // Right Left Case
    if (balance < -1 && 
        getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// A utility function to print 
// preorder traversal of the tree 
void preOrder(Node *root) { 
    if (root != nullptr) { 
        std::cout << root->key << " "; 
        preOrder(root->left); 
        preOrder(root->right); 
    } 
} 