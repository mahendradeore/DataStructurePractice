#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct tree{
  int data;
  struct tree *left;
  struct tree *right;
}Tree;

Tree * createNode(int data){
  Tree *node = (Tree*)malloc(sizeof(Tree));
  if(node){
    node->data = data;
    node->left = NULL;
    node->right = NULL;
  }
  return node;
}

int getHeight(Tree *root){
  if(root == NULL){
    return 0;
  }
  int lefth = getHeight(root->left);
  int righh = getHeight(root->right);

  if(lefth> righh){
    return 1+lefth;
  }
  else{
    return 1 + righh;
  }
  
}

void getLevelSum(Tree *root, int level, int *sum){
  if(root == NULL)
    return;

  if (1 == level){
     *sum = *sum + root->data;
  }else {
      getLevelSum(root->left, level-1, sum);
      getLevelSum(root->right, level -1,sum);
  }
}
void getSumEachLevel(Tree*root, int height){

  for(int i = 1 ; i <= height; i++) {
    int sum = 0;
    getLevelSum(root,i,&sum);
    printf("\n Level = %d, sum = %d",i,sum);
  }


}
void createTree(Tree *root,Tree *node){
  if(node == NULL) {
    printf("\n node is nULL");
    return;
  }
  if(root == NULL){
    printf("\n root is nULL,");
    root = node;
  }else {
    Tree *temp = root;
    while(temp!=NULL){
      if(temp->data <= node->data){
        printf("\n temp->data, = %d,node->data =%d",temp->data, node->data);
          if(temp->left == NULL){
            temp->left = node;
            break;
          }else{
            temp=temp->left;
          }
      }else {
       if(temp->right == NULL){
            temp->right = node;
             break;
        }else{
          temp=temp->right;
        }

      }
    }
  }
}


void printNode(Tree *root, int height,bool odd){
    if(!root){
        return;
    }
    if(height==1){
        printf("%d ",root->data);
    }else {
        if(odd) {
            printNode(root->right,height-1,odd);
            printNode(root->left,height-1,odd);
        } else {
            printNode(root->left,height-1,odd);
            printNode(root->right,height-1,odd);
            
        }
        
          
    }
}
void printZigZag(Tree *root,int height){
    
    bool odd = false;
    for(int i = 1; i <= height ; i++){
        printf("\n");
        if(i%2 == 0){
         printNode(root,i,true);
        }else {
         printNode(root,i,false);
        }
        
    }
}
int main() {
  Tree *root = createNode(1);

  Tree *Temp = createNode(2);
  root->left = Temp;
  root->right = createNode(3);
  root->left->left = createNode(4);
  root->left->right = createNode(5);
  root->right->left = createNode(6);
  root->right->right = createNode(7);
  root->right->right->left = createNode(8);
  root->right->right->right = createNode(9);
  root->right->left->left = createNode(10);
  root->right->left->right = createNode(11);
  root->left->left->left = createNode(12);
  root->left->left->right = createNode(13);
  root->left->right->left = createNode(14);
  root->left->right->right = createNode(15);
  //Tree *node = createNode(2);
 
  // createTree(root,createNode(2));
  // //createTree(root,createNode(2));
  // createTree(root,createNode(3));
  // createTree(root,createNode(4));
  // createTree(root,createNode(5));
  // createTree(root,createNode(6));
  // createTree(root,createNode(7));
  printf("\n Get Height");
  int height = getHeight(root);
  printf("\n height = %d",height);
  getSumEachLevel(root,height);
  
  printZigZag(root,height);

  return 0;
}
 


// Your previous Plain Text content is preserved below:

// This is just a simple shared plaintext pad, with no execution capabilities.

// When you know what language you'd like to use for your interview,
// simply choose it from the dots menu on the tab, or add a new language
// tab using the Languages button on the left.

// You can also change the default language your pads are created with
// in your account settings: https://app.coderpad.io/settings

// Enjoy your interview!