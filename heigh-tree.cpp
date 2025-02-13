#include <iostream>
using namespace std;

// Define a node structure
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

// Function to calculate the height of the tree
int height(TreeNode* root) {
    if (root == NULL) {
        return 0; // Base case: empty tree has height 0
    }

    // Calculate the height of left and right subtrees
    int leftHeight = height(root->left);
    int rightHeight = height(root->right);

    // Height of the tree is 1 (current node) + max of left and right subtree heights
    return 1 + max(leftHeight, rightHeight);
}

// Helper function to create a sample tree
TreeNode* createSampleTree() {
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    root->right->left = new TreeNode(6);
    root->right->right = new TreeNode(7);
    return root;
}

int main() {
    TreeNode* root = createSampleTree();

    cout << "Height of the tree: " << height(root) << endl;

    return 0;
}
