#include <stdio.h>
#include <stdlib.h>

// Define the structure of a node in the tree
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (!newNode) {
        printf("Memory allocation failed\n");
        return NULL;
    }
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Function to find the path from the root to a given node
bool findPath(Node* root, int n, vector<int>& path) {
    if (root == nullptr) return false;

    // Add the current node's data to the path
    path.push_back(root->data);

    // Check if the current node is the target node
    if (root->data == n) return true;

    // Recur for left and right subtrees
    if ((root->left && findPath(root->left, n, path)) || 
        (root->right && findPath(root->right, n, path))) {
        return true;
    }

    // If the node is not found in either subtree, backtrack
    path.pop_back();
    return false;
}

// Function to find the Lowest Common Ancestor (LCA)
int findLCA(Node* root, int n1, int n2) {
    vector<int> path1, path2;

    // Find paths from root to n1 and n2
    if (!findPath(root, n1, path1) || !findPath(root, n2, path2)) {
        return -1; // If either n1 or n2 is not present
    }

    // Compare the paths to find the first different value
    int i;
    for (i = 0; i < path1.size() && i < path2.size(); i++) {
        if (path1[i] != path2[i]) break;
    }

    // Return the last common value
    return path1[i - 1];
}
// Function to find the Lowest Common Ancestor (LCA) of two nodes
struct Node* findLCA(struct Node* root, int n1, int n2) {
    if (root == NULL) return NULL;

    // If the current node matches one of the nodes, return it
    if (root->data == n1 || root->data == n2) return root;

    // Recursively find LCA in the left and right subtrees
    struct Node* leftLCA = findLCA(root->left, n1, n2);
    struct Node* rightLCA = findLCA(root->right, n1, n2);

    // If both subtrees return non-NULL, this is the LCA
    if (leftLCA && rightLCA) return root;

    // Otherwise, return the non-NULL subtree
    return (leftLCA != NULL) ? leftLCA : rightLCA;
}

int main() {
    // Create the binary tree
    struct Node* root = createNode(3);
    root->left = createNode(5);
    root->right = createNode(1);
    root->left->left = createNode(6);
    root->left->right = createNode(2);
    root->right->left = createNode(0);
    root->right->right = createNode(8);
    root->left->right->left = createNode(7);
    root->left->right->right = createNode(4);

    // Find LCA of two nodes
    int n1 = 5, n2 = 1;
    struct Node* lca = findLCA(root, n1, n2);
    if (lca != NULL)
        printf("LCA of %d and %d is %d\n", n1, n2, lca->data);
    else
        printf("LCA of %d and %d does not exist\n", n1, n2);

    return 0;
}
