/******************************************************************************

Welcome to GDB Online.
  GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
  C#, OCaml, VB, Perl, Swift, Prolog, Javascript, Pascal, COBOL, HTML, CSS, JS
  Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>
#include<stdlib.h>


typedef struct Tree {
    struct Tree* left;
    struct Tree* right;
    int data;
    
}Node;

Node * createNode(int data){
    
    Node *node = (Node*)malloc(sizeof(Node));
    if(node){
    node->left = NULL;
    node->right = NULL;
    node->data = data;
    }else {
        printf("unable to crate node\n");
    }
    return node;
}

void printPredecAndSucc(Node *root, int key, Node **suc, Node **pre){
    if(root == NULL){
        printf("not found\n");   
    }
    
    while(root != NULL){
        //if key is root
        if(root->data == key){
            if(root->right) {
                *suc = root->right;
                while((*suc)->left){
                    *suc = (*suc)->left;
                }
            }
            //and predecessor in left side of tree
            if(root->left){
                *pre = root->left;
                while((*pre)->right){
                    *pre = (*pre)->right;
                }
            }
            return;
        }else if(root->data <= key ){
            //if key is greater than root then root might be pre. and let search in right side of tree
                *pre = root;
                root = root->right;
        }else{
            //if key is smaller than root then root might be successor, then let search in left side of tree.
                *suc = root;
                root = root->left;
         }
    
    }
}
Node* insertNode(Node *root,int data){
    
    if(root == NULL){
      return  createNode(data);
    }
    
    if(root->data >= data){
        root->left = insertNode(root->left,data);
    }else {
        root->right= insertNode(root->right, data);
    }
    
    return root;
    
}

void inorder(Node *root){

   if(!root)
        return;
        
    inorder(root->left);
    printf("\n %d",root->data);
    inorder(root->right);
}
int main()
{
    Node *root = NULL;
    root = insertNode(root, 50);
    insertNode(root, 30);
    insertNode(root, 20);
    insertNode(root, 40);
    insertNode(root, 70);
    insertNode(root, 60);
    insertNode(root, 80);
   // inorder(root);
    /* Let us create following BST
                 50
                /  \
               /    \
              30     70
             / \     / \
            /   \   /   \
           20   40 60   80
*/
    Node *suc = NULL,*pre = NULL;
    printPredecAndSucc(root,20,&suc,&pre);
    if(pre)
        printf("for node %d , pred = %d , \n",20,pre->data);
    else 
    printf ("No  pre- found \n");
    
    if(suc)
     printf("for node %d , succ  %d \n",20,suc->data);
    else
    printf ("No succ found \n");
    
     suc = NULL; pre = NULL;
     printPredecAndSucc(root,30,&suc,&pre);
     if(pre)
        printf("for node %d , pred = %d , \n",30,pre->data);
    else 
    printf ("No  pre- found \n");
    if(suc)
     printf("for node %d , succ  %d \n",30,suc->data);
      else
    printf ("No succ found \n");
    
     // Construct a BST
    //            20
    //          /    \
    //         8      22
    //       /   \
    //      4    12
    //          /  \
    //         10   14
    Node *node2 = createNode(20);
    node2->left = createNode(8);
    node2->right = createNode(22);
    node2->left->left = createNode(4);
    node2->left->right = createNode(12);
    node2->left->right->left = createNode(10);
    node2->left->right->right = createNode(14);
    suc = NULL; pre = NULL;
    int key  = 4;
    printPredecAndSucc(node2,key,&suc,&pre);

    if(pre)
        printf("for node %d , pred = %d , \n",key,pre->data);
    else 
    printf ("No  pre- found \n");
    if(suc)
     printf("for node %d , succ  %d \n",key,suc->data);
      else
    printf ("No succ found \n");
    suc = NULL, pre = NULL;
    key  = 22;
     printPredecAndSucc(node2,key,&suc,&pre);
    
    if(pre)
        printf("for node %d , pred = %d , \n",key,pre->data);
    else 
    printf ("No  pre- found \n");
    if(suc)
     printf("for node %d , succ  %d \n",key,suc->data);
      else
    printf ("No succ found \n");
       suc = NULL, pre = NULL;
    key  = 20;
     printPredecAndSucc(node2,key,&suc,&pre);
    
    if(pre)
        printf("for node %d , pred = %d , \n",key,pre->data);
    else 
    printf ("No  pre- found \n");
    if(suc)
     printf("for node %d , succ  %d \n",key,suc->data);
      else
    printf ("No succ found \n");
        suc = NULL, pre = NULL;
    key  = 14;
     printPredecAndSucc(node2,key,&suc,&pre);
    
    if(pre)
        printf("for node %d , pred = %d , \n",key,pre->data);
    else 
    printf ("No  pre- found \n");
    if(suc)
     printf("for node %d , succ  %d \n",key,suc->data);
      else
    printf ("No succ found \n");
    return 0;
}