/*********************************************************************************************************************************************
 * File Name	: Lab3.c

 * Description	: This file is the skeleton for lab 3 (Binary Search Tree)
 *
 * Instructions	: 
			- Complete binarySearchTree_AddNode(), binarySearchTree_PrintTreeInOrder(), and binarySearchTree_EditNode() functions.
 *
 * Student Name: Amar Singh
 * Student Number: 8935727
*********************************************************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARRAY_SIZE(a)   (sizeof(a)/sizeof(a[0]))

typedef struct
{
	char key[10];	// A string representing a key
	int value;
} data_t;

// Structure defining a binary tree node.  Lower sorted values will go the the left, higher to the pRight.
typedef struct node
{
	data_t data;		// Contains data and a key
	struct node* pLeft;
	struct node *pRight;
}node_t;


// Data to be stored in tree.
data_t inputData[] =
{
    {{ "orange"}, 275},
	{{ "blue"}, 85},
	{{ "red"}, 77},
	{{ "yellow"}, -4},
	{{ "white"}, 152},
	{{ "black"}, 0},
	{{ "green"}, -33},
	{{ "purple"}, 654},
	{{ "brown"}, 99},
	{{ "grey"}, -5}
};


void binarySearchTree_AddNode(node_t **ppRoot, data_t *pData);
void binarySearchTree_PrintTreeInOrder(node_t *pRoot);
void binarySearchTree_deleteTree(node_t** ppNode);
void binarySearchTree_EditNode(node_t* pRoot, const char * pKey, const int input);

/**
 * @brief Function to add a new node to the binary search tree
 * @param [in/out] ppRoot - Pointer to the root's reference
 * @param[in] - Pointer to the data to be inserted 
 **/
void binarySearchTree_AddNode(node_t** ppRoot, data_t* pData)
{
    if (ppRoot == NULL || pData == NULL){
	    return;       // Invalid input
    }

    node_t* current = (node_t*)malloc(sizeof(node_t));
            
    if(current == NULL){
            printf("\nMemory allocation failed.\n");
            return;
    }

        current->data = *pData;                          // direct structure copy
        //memcpy(current->data,pData, sizeof(data_t));        // it was not working...
        current->pLeft = NULL;
        current->pRight = NULL;
    
    //if tree is empty then new node will be the root node.
    if(*ppRoot == NULL) {
        *ppRoot = current;
         return;  
    }
    
            
    node_t* temp = *ppRoot;
            
    while(temp != NULL){

            int i = strcmp(current->data.key, temp->data.key);
            
            if(i >= 0){
                if(temp->pRight == NULL){
                    temp->pRight = current;
                    return;
                }
                temp = temp->pRight;
                
            }
            else{
               if(temp->pLeft == NULL){
                   temp->pLeft = current;
                   return;
               }
                temp = temp->pLeft;
           
            }
               
        }    
           
            
}

/**
 * @brief Function to print the contents of the binary search tree in ascending order (smaller to greater).
 * @param[in] pRoot - Pointer to root node.
 **/
void binarySearchTree_PrintTreeInOrder(node_t* pRoot)
{
    if(pRoot == NULL){
        return;   // Invalid input
    }
    
    node_t* temp = pRoot;
    
    int stackSize = ARRAY_SIZE(inputData);   
    node_t* stack[stackSize];
    int top = -1;

    while (temp != NULL || top != -1) {
        while (temp != NULL) {
            stack[++top] = temp;
            temp = temp->pLeft;
        }

        temp = stack[top--];
        printf("%s %d\n", temp->data.key, temp->data.value);
        temp = temp->pRight;
    }
 
    
      
}

/**
 * @brief This function edits the data of an existing node. A key is used to search for the target node.
 * @param [in] pRoot - Pointer to the root node.
 * @param [in] pKey - Pointer to the key used for searching
 * @param [in] value - Value to be copied into the target node
 **/
void binarySearchTree_EditNode(node_t* pRoot, const char * pKey, const int input)
{   
    if(pRoot == NULL || pKey == NULL){
        return;       // Invalid input
    }

    node_t* temp = pRoot;
    
    while(temp != NULL){
        int i = strcmp(temp->data.key, pKey);
        if(i == 0){
            temp->data.value = input;
            printf("Value of %s is changed to %d\n",temp->data.key,input);
            return;
        }
        else if(i >0)
        temp = temp->pLeft;
        else
        temp = temp->pRight;
    }
    
    printf("Key not found\n");
    return;
  
}

/**
* Brief: This function deletes all the nodes in the binary search tree
* @param [in/out] ppRoot - Pointer to the root's reference
*/
void binarySearchTree_deleteTree(node_t** ppRoot)
{
    if (ppRoot == NULL) {
	    return; // Invalid input
    }
    
    if(*ppRoot == NULL) {
        return; // Empty tree, nothing to delete
    }
    
    // Create a stack to help with iterative traversal
    int stackSize = ARRAY_SIZE(inputData);   
    node_t* stack[stackSize];
    int top = -1;
    
    node_t* current = *ppRoot;
    node_t* temp = NULL;

    while (current != NULL || top != -1) {
        while (current != NULL) {
            if (top < stackSize) {
                stack[++top] = current;
                current = current->pLeft;
            }
            else {
                return; // Stack overflow
            }
        }

        current = stack[top--]; // Pop a node from the stack and free it
        temp = current;
        current = current->pRight;
        free(temp);
    }

    *ppRoot = NULL; // Set the root pointer to NULL to indicate an empty tree
}

int main()
{
    node_t* root = NULL;

    // Insert all the data into the binary tree
    int i;
    for (i = 0; i < ARRAY_SIZE(inputData); i++)
    {
        binarySearchTree_AddNode(&root, &inputData[i]);
    }

    // Print the entire tree. It should come out in alphabetical order.
    binarySearchTree_PrintTreeInOrder(root);
    
    binarySearchTree_EditNode(root, "green", 44);
    binarySearchTree_EditNode(root, "orange", -10);
    binarySearchTree_EditNode(root, "silver", 99);
    
    binarySearchTree_PrintTreeInOrder(root);

    binarySearchTree_deleteTree(&root);

    return 0;
}
