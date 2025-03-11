#include <iostream>
#include <vector>
using namespace std;

struct TreeNode {
    int data;
    std::vector<TreeNode*> children;
    TreeNode(int val) : data(val) {}
};

void addChild(TreeNode* parent, TreeNode* child) {
    if(parent)
        parent->children.push_back(child);
}

void printTree(TreeNode* root, int level = 0) {
    if(!root)
        return;
    for (int i = 0; i < level; i++) 
        cout << "  ";
    cout << root->data << "\n";
    for (auto child : root->children)
        printTree(child, level + 1);
}

int main() {
    TreeNode* root = new TreeNode(1);
    TreeNode* child1 = new TreeNode(2);
    TreeNode* child2 = new TreeNode(3);
    addChild(root, child1);
    addChild(root, child2);
    addChild(child1, new TreeNode(4));
    addChild(child1, new TreeNode(5));
    cout << "General Tree:" << endl;
    printTree(root);
    // (In production code, free the allocated memory.)
    return 0;
}
