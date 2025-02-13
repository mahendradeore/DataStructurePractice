#include <iostream>
#include <algorithm>
using namespace std;

// Define a structure for a tree node
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

// Helper function to check if a tree is balanced
int checkHeight(TreeNode* root) {
    if (!root) {
        return 0; // Base case: height of an empty tree is 0
    }

    // Recursively check the height of the left and right subtrees
    int leftHeight = checkHeight(root->left);
    int rightHeight = checkHeight(root->right);

    // If any subtree is unbalanced, propagate -1 upwards
    if (leftHeight == -1 || rightHeight == -1 || abs(leftHeight - rightHeight) > 1) {
        return -1;
    }

    // Return the height of the current tree
    return 1 + max(leftHeight, rightHeight);
}

// Function to check if the binary tree is balanced
bool isBalanced(TreeNode* root) {
    return checkHeight(root) != -1;
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

int main() {
    TreeNode* root = createSampleTree();

    if (isBalanced(root)) {
        cout << "The tree is balanced.\n";
    } else {
        cout << "The tree is not balanced.\n";
    }

    return 0;
}
