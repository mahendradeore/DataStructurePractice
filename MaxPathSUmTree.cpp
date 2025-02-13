#include <iostream>
#include <climits> // For INT_MIN
using namespace std;

// Define a node structure
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

// Helper function to calculate the maximum path sum
int maxPathSumHelper(TreeNode* root, int& globalMax) {
    if (root == NULL) {
        return 0;
    }

    // Recursively calculate the maximum sum of paths in the left and right subtrees
    int leftSum = max(0, maxPathSumHelper(root->left, globalMax)); // Max of 0 or left path sum
    int rightSum = max(0, maxPathSumHelper(root->right, globalMax)); // Max of 0 or right path sum

    // Update the global maximum path sum
    globalMax = max(globalMax, root->val + leftSum + rightSum);

    // Return the maximum sum of the path ending at this node
    return root->val + max(leftSum, rightSum);
}

// Function to find the maximum path sum in the binary tree
int maxPathSum(TreeNode* root) {
    int globalMax = INT_MIN; // Initialize to the smallest possible value
    maxPathSumHelper(root, globalMax);
    return globalMax;
}

// Helper function to create a sample tree
TreeNode* createSampleTree() {
    TreeNode* root = new TreeNode(-10);
    root->left = new TreeNode(9);
    root->right = new TreeNode(20);
    root->right->left = new TreeNode(15);
    root->right->right = new TreeNode(7);
    return root;
}

int main() {
    TreeNode* root = createSampleTree();

    cout << "Maximum Path Sum: " << maxPathSum(root) << endl;

    return 0;
}
