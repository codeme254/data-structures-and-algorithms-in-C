#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct BSTNode {
    int data;
    struct BSTNode *left;
    struct BSTNode *right;
} BSTNode;

/**
 * INITIALIZE_NODE - initializes the node of a bst
 * @new_node_value: value of the new node being created
 * Return: the initialized node or null on failure
*/
static BSTNode *INITIALIZE_NODE(int new_node_value)
{
    BSTNode *new_node = malloc(sizeof(BSTNode));
    if (new_node == NULL) return NULL;
    new_node->data = new_node_value;
    new_node->left = NULL;
    new_node->right = NULL;
}

/**
 * insert_node - inserts a node to the BST
 * @root: pointer to the root of the tree that the node is being inserted to
 * Description: all items less than a node are kept to the left of it and
 * all items greater than a node are kept to the right of it
 * Return: inserted node or null on failure
*/
static BSTNode *insert_node(BSTNode **root, int value)
{
    BSTNode *new_node = INITIALIZE_NODE(value);
    if (new_node == NULL) return (NULL);
    // if there is no root, the node becomes the root
    if(*root == NULL)
    {
        *root = new_node;
        printf("made node root\n");
        return (new_node);
    }
    // go through the tree until you find where to add this node
    BSTNode *current = *root;
    while (current != NULL)
    {
        // if the value already exists in the bst, return NULL
        if (value == current->data) return (NULL);
        // if the value of the new node is greater than current, go right
        if (value > current->data){
            if (current->right == NULL) 
            {
                current->right = new_node;
                break;
            }
            else current = current->right;
        }
        else if (value < current->data){
            if (current->left == NULL)
            {
                current->left = new_node;
                break;
            }
            else current = current->left;
        }
    }
    return (new_node);
}


/**
 * breadth_first_traversal - traverses the tree leve wise
 * @root: pointer to the root node of the tree being traversed
 * @func: function to call on each node during traversal
 * Description: visit every node at the same level, i.e visit every
 * sibling node before the children
*/
void breadth_first_traversal(BSTNode **root, void (*func)(int))
{
    if (*root == NULL) return;
    // BSTNode *traversalQue[100];
    BSTNode **traversalQue = calloc(100, sizeof(BSTNode));
    int insert_index = 0;
    int check_index = 0;
    traversalQue[insert_index] = *root;
    while (traversalQue[check_index] != NULL)
    {
        BSTNode *current_node = traversalQue[check_index];
        func(current_node->data);
        if (current_node->left){
            insert_index += 1;
            traversalQue[insert_index] = current_node->left;
        }
        if (current_node->right){
            insert_index += 1;
            traversalQue[insert_index] = current_node->right;
        }
        check_index += 1;
    }
}

/**
 * preorder_traversal - performs a preorder traversal on the tree
 * @root: pointer to the root node of the tree
 * @function: function to be run on each node's value
 * Description: traverse the entire left of a node then the entire right
*/
void preorder_traversal(BSTNode *root, void (*function)(int))
{
    if (root == NULL) return;
    function(root->data);
    if (root->left){
        preorder_traversal(root->left, function);
    }
    if (root->right){
        preorder_traversal(root->right, function);
    }
}

/**
 * postorder_traversal - performs a postorder traversal on the tree
 * @root: pointer to the root node of the tree
 * @function: function to be called on each node's value
 * Description: visit all the chidlren nodes of a node before visiting the node itself
*/
void postorder_traversal(BSTNode *root, void (*function)(int))
{
    if (root == NULL) return;
    if (root->left){
        postorder_traversal(root->left, function);
    }
    if (root->right){
        postorder_traversal(root->right, function);
    }
    function(root->data);
}

/**
 * inorder_traversal - performs inorder traversal on the tree
 * @root: pointer to the root node of the tree
 * @function: functtion to be called on each node's value
 * Description: traverse the left child, then the parent then the right child
 * output should be sorted, since we are doing this on a BST
*/
void inorder_traversal(BSTNode *root, void (*function)(int))
{
    if (root == NULL) return;
    if (root->left){
        inorder_traversal(root->left, function);
    }
    function(root->data);
    if (root->right){
        inorder_traversal(root->right, function);
    }
}

/**
 * printTree - tries to print the tree graphically to the console
 * @root: pointer to the root node of the tree
 * @space: space
*/
void printTree(BSTNode *root, int space)
{
    if (root == NULL)
    {
        return;
    }
    // increase the distance between levels
    space += 5;
    // print the right child first
    printTree(root->right, space);
    // print current node after space
    printf("\n");
    for (int i = 5; i < space; i++)
    {
        printf(" ");
    }
    printf("|");
    printf("%d\n", root->data);
    // print the left child
    printTree(root->left, space);
}

void print_number(int n)
{
    printf("%d ", n);
}

int main()
{
    printf("BST in C\n");
    BSTNode *root = NULL;
    insert_node(&root, 20);
    insert_node(&root, 11);
    insert_node(&root, 28);
    insert_node(&root, 30);
    insert_node(&root, 26);
    insert_node(&root, 9);
    insert_node(&root, 15);
    insert_node(&root, 20);
    insert_node(&root, 8);
    insert_node(&root, 10);
    insert_node(&root, 14);
    insert_node(&root, 16);
    insert_node(&root, 24);
    insert_node(&root, 29);

    printf("Breadth first traversal: ");
    breadth_first_traversal(&root, &print_number);

    printf("\nPreorder traversal: ");
    preorder_traversal(root, &print_number);

    printf("\nPostorder traversal: ");
    postorder_traversal(root, &print_number);

    printf("\nInorder traversal: ");
    inorder_traversal(root, &print_number);
    printTree(root, 5);
}