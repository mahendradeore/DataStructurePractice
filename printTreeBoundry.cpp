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

// Function to print the left boundary (excluding leaf nodes)
void printLeftBoundary(TreeNode* root) {
    if (root == NULL) return;
    
    if (root->left) {
        cout << root->val << " ";
        printLeftBoundary(root->left);
    } else if (root->right) {
        cout << root->val << " ";
        printLeftBoundary(root->right);
    }
}

// Function to print the leaf nodes
void printLeafNodes(TreeNode* root) {
    if (root == NULL) return;
    
    if (root->left == NULL && root->right == NULL) {
        cout << root->val << " ";
        return;
    }
    
    printLeafNodes(root->left);
    printLeafNodes(root->right);
}

// Function to print the right boundary (excluding leaf nodes) in reverse order
void printRightBoundary(TreeNode* root) {
    if (root == NULL) return;
    
    if (root->right) {
        printRightBoundary(root->right);
        cout << root->val << " ";
    } else if (root->left) {
        printRightBoundary(root->left);
        cout << root->val << " ";
    }
}

// Function to perform boundary traversal
void boundaryTraversal(TreeNode* root) {
    if (root == NULL) return;

    // Print the root node (this is a special case)
    cout << root->val << " ";
    
    // Print the left boundary
    printLeftBoundary(root->left);
    
    // Print the leaf nodes
    printLeafNodes(root);
    
    // Print the right boundary
    printRightBoundary(root->right);
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
    root->left->left->left = new TreeNode(8);
    root->right->right->right = new TreeNode(9);
    return root;
}

int main() {
    TreeNode* root = createSampleTree();
    
    // Perform the boundary traversal and print the nodes
    cout << "Boundary Traversal: ";
    boundaryTraversal(root);
    cout << endl;

    return 0;
}
