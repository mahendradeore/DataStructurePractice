#include <iostream>
#include <queue>
#include <map>
using namespace std;

// Define a structure for a tree node
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

// Function to print the top view of the binary tree
void topView(TreeNode* root) {
    if (root == NULL) return;
    
    // Map to store the first node at each horizontal distance
    map<int, int> topNodes;
    
    // Queue for level order traversal (BFS)
    queue<pair<TreeNode*, int>> q;  // Pair: (node, horizontal distance)
    
    q.push({root, 0});
    
    while (!q.empty()) {
        auto front = q.front();
        q.pop();
        
        TreeNode* node = front.first;
        int hd = front.second;  // horizontal distance
        
        // If the horizontal distance is not already in the map, add the node's value
        if (topNodes.find(hd) == topNodes.end()) {
            topNodes[hd] = node->val;
        }
        
        // Enqueue left and right children
        if (node->left) {
            q.push({node->left, hd - 1});
        }
        if (node->right) {
            q.push({node->right, hd + 1});
        }
    }
    
    // Print the top view nodes
    for (auto& node : topNodes) {
        cout << node.second << " ";
    }
    cout << endl;
}

// Function to print the bottom view of the binary tree
void bottomView(TreeNode* root) {
    if (root == NULL) return;
    
    // Map to store the last node at each horizontal distance
    map<int, int> bottomNodes;
    
    // Queue for level order traversal (BFS)
    queue<pair<TreeNode*, int>> q;  // Pair: (node, horizontal distance)
    
    q.push({root, 0});
    
    while (!q.empty()) {
        auto front = q.front();
        q.pop();
        
        TreeNode* node = front.first;
        int hd = front.second;  // horizontal distance
        
        // Always update the bottom-most node for this horizontal distance
        bottomNodes[hd] = node->val;
        
        // Enqueue left and right children
        if (node->left) {
            q.push({node->left, hd - 1});
        }
        if (node->right) {
            q.push({node->right, hd + 1});
        }
    }
    
    // Print the bottom view nodes
    for (auto& node : bottomNodes) {
        cout << node.second << " ";
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
    root->right->left = new TreeNode(6);
    root->right->right = new TreeNode(7);
    root->left->left->left = new TreeNode(8);
    root->right->right->right = new TreeNode(9);
    return root;
}

int main() {
    TreeNode* root = createSampleTree();
    
    // Print the top view of the tree
    cout << "Top View: ";
    topView(root);
    
    // Print the bottom view of the tree
    cout << "Bottom View: ";
    bottomView(root);
    
    return 0;
}
