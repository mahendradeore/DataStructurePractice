#include <iostream>
#include <queue>
#include <vector>
using namespace std;

// Define a structure for a tree node
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

// Function to print the left view of the binary tree
void leftView(TreeNode* root) {
    if (root == NULL) return;
    
    // Queue for level order traversal (BFS)
    queue<TreeNode*> q;
    q.push(root);
    
    while (!q.empty()) {
        int levelSize = q.size();
        
        // Traverse the nodes of the current level
        for (int i = 0; i < levelSize; i++) {
            TreeNode* node = q.front();
            q.pop();
            
            // Print the first node of each level (left view)
            if (i == 0) {
                cout << node->val << " ";
            }
            
            // Enqueue left and right children
            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }
    }
    cout << endl;
}

// Function to print the right view of the binary tree
void rightView(TreeNode* root) {
    if (root == NULL) return;
    
    // Queue for level order traversal (BFS)
    queue<TreeNode*> q;
    q.push(root);
    
    while (!q.empty()) {
        int levelSize = q.size();
        
        // Traverse the nodes of the current level
        for (int i = 0; i < levelSize; i++) {
            TreeNode* node = q.front();
            q.pop();
            
            // Print the last node of each level (right view)
            if (i == levelSize - 1) {
                cout << node->val << " ";
            }
            
            // Enqueue left and right children
            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }
    }
    cout << endl;
}

// Helper function to create a sample tree
TreeNode* createSampleTree() {
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    root->right->right = new TreeNode(6);
    root->left->left->left = new TreeNode(7);
    root->right->right->right = new TreeNode(8);
    return root;
}

int main() {
    TreeNode* root = createSampleTree();
    
    // Print the left view of the tree
    cout << "Left View: ";
    leftView(root);
    
    // Print the right view of the tree
    cout << "Right View: ";
    rightView(root);
    
    return 0;
}
