#include <iostream>
#include <vector>
using namespace std;

// Define a structure for a tree node
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

// Function to convert the sorted array to a balanced BST
TreeNode* sortedArrayToBST(const vector<int>& nums, int start, int end) {
    // Base case: if the start index is greater than the end, return NULL
    if (start > end) {
        return NULL;
    }
    
    // Find the middle element
    int mid = start + (end - start) / 2; // Avoid overflow
    
    // Create the root node with the middle element
    TreeNode* root = new TreeNode(nums[mid]);
    
    // Recursively build the left and right subtrees
    root->left = sortedArrayToBST(nums, start, mid - 1);  // Left half
    root->right = sortedArrayToBST(nums, mid + 1, end);   // Right half
    
    return root;
}

// Helper function to print the inorder traversal of the tree (for verification)
void inorderTraversal(TreeNode* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        cout << root->val << " ";
        inorderTraversal(root->right);
    }
}

// Main function to test the conversion
int main() {
    // Example sorted array
    vector<int> nums = {-10, -3, 0, 5, 9};
    
    // Convert sorted array to BST
    TreeNode* root = sortedArrayToBST(nums, 0, nums.size() - 1);
    
    // Print the inorder traversal of the BST (should print sorted array)
    cout << "Inorder traversal of the BST: ";
    inorderTraversal(root);
    cout << endl;
    
    return 0;
}
