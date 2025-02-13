#include <iostream>
#include <queue>
using namespace std;

// Define a node structure
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

// Function to calculate the height of the tree using a while loop
int height(TreeNode* root) {
    if (root == NULL) {
        return 0; // Base case: empty tree has height 0
    }

    queue<TreeNode*> q; // Queue for level-order traversal
    q.push(root);
    int height = 0;

    while (!q.empty()) {
        int levelSize = q.size(); // Number of nodes at the current level

        // Process all nodes at the current level
        for (int i = 0; i < levelSize; i++) {
            TreeNode* node = q.front();
            q.pop();

            // Add the child nodes to the queue
            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }

        // Increment height after processing each level
        height++;
    }

    return height;
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
