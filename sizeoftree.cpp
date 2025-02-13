#include <iostream>
using namespace std;

// Define a node structure
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

// Function to calculate the size of the tree
int sizeRecursive(TreeNode* root) {
    if (root == NULL) {
        return 0; // Base case: empty tree has size 0
    }

    // Recursive calculation
    return 1 + sizeRecursive(root->left) + sizeRecursive(root->right);
}
int sizeIterative(TreeNode* root) {
    if (root == NULL) {
        return 0; // Base case: empty tree has size 0
    }

    queue<TreeNode*> q;
    q.push(root);
    int count = 0;

    // Perform level-order traversal
    while (!q.empty()) {
        TreeNode* node = q.front();
        q.pop();
        count++;

        // Add child nodes to the queue
        if (node->left) q.push(node->left);
        if (node->right) q.push(node->right);
    }

    return count;
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

    cout << "Size of the tree: " << sizeRecursive(root) << endl;
    cout << "Size of the tree: " << sizeIterative(root) << endl;

    return 0;
}
