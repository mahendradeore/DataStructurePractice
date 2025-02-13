#include <stdio.h>
#include <stdlib.h>

// Define a structure for a linked list node
struct ListNode {
    int val;
    struct ListNode* next;
    
    // Constructor to create a new node
    struct ListNode(int x) : val(x), next(NULL) {}
};

// Function to detect a loop in the linked list
int detectLoop(struct ListNode* head) {
    struct ListNode* slow = head;
    struct ListNode* fast = head;
    
    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;            // Move slow by 1 step
        fast = fast->next->next;      // Move fast by 2 steps
        
        if (slow == fast) {
            return 1;  // Loop detected
        }
    }
    
    return 0;  // No loop
}

// Function to remove the loop in the linked list
void removeLoop(struct ListNode* head) {
    struct ListNode* slow = head;
    struct ListNode* fast = head;
    
    // Detect if there's a loop
    if (!detectLoop(head)) {
        printf("No loop found.\n");
        return;
    }
    
    // Move slow pointer to the start and keep fast at meeting point
    slow = head;
    while (slow != fast) {
        slow = slow->next;
        fast = fast->next;
    }
    
    // slow and fast are now at the start of the loop
    struct ListNode* loopStart = slow;
    
    // Move fast to the end of the loop to find the last node
    while (fast->next != loopStart) {
        fast = fast->next;
    }
    
    // Break the loop by setting the last node's next pointer to NULL
    fast->next = NULL;
    printf("Loop removed.\n");
}

// Function to create a new node
struct ListNode* newNode(int val) {
    struct ListNode* node = (struct ListNode*)malloc(sizeof(struct ListNode));
    node->val = val;
    node->next = NULL;
    return node;
}

// Function to print the linked list
void printList(struct ListNode* head) {
    struct ListNode* current = head;
    while (current != NULL) {
        printf("%d -> ", current->val);
        current = current->next;
    }
    printf("NULL\n");
}

// Main function to test the code
int main() {
    // Create a linked list with a loop
    struct ListNode* head = newNode(1);
    head->next = newNode(2);
    head->next->next = newNode(3);
    head->next->next->next = newNode(4);
    head->next->next->next->next = newNode(5);
    head->next->next->next->next->next = head->next->next;  // Create loop (5 -> 3)
    
    printf("Original List (with loop): \n");
    printList(head);  // It will print infinite loop, so just for visualization

    removeLoop(head);  // Removes the loop
    
    printf("List after removing loop: \n");
    printList(head);  // Now the list will print correctly
    
    return 0;
}
