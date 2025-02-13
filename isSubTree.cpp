#include <iostream>
using namespace std;

// Define a structure for a tree node
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

// Helper function to check if two trees are identical
bool isIdentical(TreeNode* root1, TreeNode* root2) {
    // If both are NULL, the trees are identical
    if (!root1 && !root2) {
        return true;
    }

    // If one is NULL and the other is not, the trees are not identical
    if (!root1 || !root2) {
        return false;
    }

    // Check if the current nodes are equal and recursively check left and right subtrees
    return (root1->val == root2->val) &&
           isIdentical(root1->left, root2->left) &&
           isIdentical(root1->right, root2->right);
}

// Function to check if T2 is a subtree of T1
bool isSubtree(TreeNode* T1, TreeNode* T2) {
    // If T2 is NULL, it's always a subtree
    if (!T2) {
        return true;
    }

    // If T1 is NULL and T2 is not, T2 can't be a subtree
    if (!T1) {
        return false;
    }

    // Check if the tree rooted at T1 is identical to T2
    if (isIdentical(T1, T2)) {
        return true;
    }

    // Recursively check the left and right subtrees of T1
    return isSubtree(T1->left, T2) || isSubtree(T1->right, T2);
}

// Helper function to create a sample tree
TreeNode* createSampleTree() {
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    return root;
}

// Helper function to create a subtree
TreeNode* createSubtree() {
    TreeNode* root = new TreeNode(2);
    root->left = new TreeNode(4);
    root->right = new TreeNode(5);
    return root;
}

int main() {
    TreeNode* T1 = createSampleTree();  // Main tree
    TreeNode* T2 = createSubtree();     // Subtree to check

    if (isSubtree(T1, T2)) {
        cout << "T2 is a subtree of T1.\n";
    } else {
        cout << "T2 is not a subtree of T1.\n";
    }

    return 0;
}
