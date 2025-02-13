#include <stdio.h>
#include <stdlib.h>

// Define a structure for a tree node
struct TreeNode {
    int val;
    struct TreeNode* left;
    struct TreeNode* right;

    // Constructor to create a new node
    struct TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

// Function to find the minimum node in a tree
struct TreeNode* minValueNode(struct TreeNode* node) {
    struct TreeNode* current = node;
    while (current && current->left != NULL) {
        current = current->left;
    }
    return current;
}

// Function to delete a node from a binary search tree
struct TreeNode* deleteNode(struct TreeNode* root, int key) {
    if (root == NULL) {
        return root;
    }

    // If the key to be deleted is smaller than the root's key, it lies in the left subtree
    if (key < root->val) {
        root->left = deleteNode(root->left, key);
    }
    // If the key to be deleted is larger than the root's key, it lies in the right subtree
    else if (key > root->val) {
        root->right = deleteNode(root->right, key);
    }
    // If key is the same as root's key, this is the node to be deleted
    else {
        // Node with only one child or no child
        if (root->left == NULL) {
            struct TreeNode* temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            struct TreeNode* temp = root->left;
            free(root);
            return temp;
        }

        // Node with two children: Get the inorder successor (smallest in the right subtree)
        struct TreeNode* temp = minValueNode(root->right);

        // Copy the inorder successor's content to this node
        root->val = temp->val;

        // Delete the inorder successor
        root->right = deleteNode(root->right, temp->val);
    }

    return root;
}

// Helper function to insert a new node in the tree
struct TreeNode* insert(struct TreeNode* node, int key) {
    if (node == NULL) {
        return new struct TreeNode(key);
    }

    if (key < node->val) {
        node->left = insert(node->left, key);
    } else if (key > node->val) {
        node->right = insert(node->right, key);
    }

    return node;
}

// Helper function to print the inorder traversal of the tree
void inorder(struct TreeNode* root) {
    if (root == NULL) return;

    inorder(root->left);
    printf("%d ", root->val);
    inorder(root->right);
}

// Main function to test the delete operation
int main() {
    struct TreeNode* root = NULL;

    // Insert nodes into the binary search tree
    root = insert(root, 50);
    root = insert(root, 30);
    root = insert(root, 20);
    root = insert(root, 40);
    root = insert(root, 70);
    root = insert(root, 60);
    root = insert(root, 80);

    printf("Inorder traversal of the BST: ");
    inorder(root);
    printf("\n");

    // Delete a node with value 20 (leaf node)
    root = deleteNode(root, 20);
    printf("Inorder traversal after deleting 20: ");
    inorder(root);
    printf("\n");

    // Delete a node with value 30 (node with one child)
    root = deleteNode(root, 30);
    printf("Inorder traversal after deleting 30: ");
    inorder(root);
    printf("\n");

    // Delete a node with value 50 (node with two children)
    root = deleteNode(root, 50);
    printf("Inorder traversal after deleting 50: ");
    inorder(root);
    printf("\n");

    return 0;
}
