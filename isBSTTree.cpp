#include <iostream>
#include <climits>
using namespace std;

// Define the structure for a tree node
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

// Helper function to check if the tree is a BST
bool isBSTUtil(TreeNode* root, int minValue, int maxValue) {
    // If the current node is NULL, it's valid (base case)
    if (!root) {
        return true;
    }

    // Check if the current node's value is within the valid range
    if (root->val <= minValue || root->val >= maxValue) {
        return false; // The value is out of range
    }

    // Recursively check the left and right subtrees
    return isBSTUtil(root->left, minValue, root->val) &&
           isBSTUtil(root->right, root->val, maxValue);
}

// Function to check if the tree is a BST
bool isBST(TreeNode* root) {
    return isBSTUtil(root, INT_MIN, INT_MAX);
}

// Helper function to create a sample tree
TreeNode* createSampleTree() {
    TreeNode* root = new TreeNode(10);
    root->left = new TreeNode(5);
    root->right = new TreeNode(15);
    root->left->left = new TreeNode(2);
    root->left->right = new TreeNode(7);
    root->right->left = new TreeNode(12);
    root->right->right = new TreeNode(20);
    return root;
}

int main() {
    TreeNode* root = createSampleTree();

    if (isBST(root)) {
        cout << "The tree is a Binary Search Tree (BST).\n";
    } else {
        cout << "The tree is not a Binary Search Tree (BST).\n";
    }

    return 0;
}
