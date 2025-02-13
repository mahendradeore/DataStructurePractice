#include <iostream>
#include <queue>
using namespace std;

// Define a structure for a tree node
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

// Function to calculate the sum of nodes at Kth level
int sumAtKthLevel(TreeNode* root, int K) {
    if (root == NULL) return 0;  // If the tree is empty, return 0
    
    queue<TreeNode*> q;
    q.push(root);
    int level = 0;
    int sum = 0;

    // Level order traversal
    while (!q.empty()) {
        int levelSize = q.size();  // Number of nodes at the current level
        sum = 0;  // Reset sum at each level

        for (int i = 0; i < levelSize; ++i) {
            TreeNode* node = q.front();
            q.pop();

            // If we're at the Kth level, add the node's value to sum
            if (level == K) {
                sum += node->val;
            }

            // Push the children into the queue for the next level
            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }

        // If we've processed the Kth level, break
        if (level == K) break;

        ++level;
    }

    return sum;
}

// Helper function to create a sample binary tree
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
    int K = 2;
    cout << "Sum of nodes at level " << K << ": " << sumAtKthLevel(root, K) << endl;
    return 0;
}
