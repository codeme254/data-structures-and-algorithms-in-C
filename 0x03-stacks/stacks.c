#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*
 * StackNode - structure of a give stack node or stack element
 * @value: the integer data value held by a node
 * @next: pointer to the next stack element
 */
typedef struct StackNode {
    int value;
    struct StackNode *next;
} StackNode;

/*
 * Stack - the structure of a stack
 * @top: the current top most element of the stack
 * @size: the size of the stack
 */
typedef struct Stack {
    StackNode *top;
    size_t size;
} Stack;

/*
 * INITIALIZE_STACK_NODE - initializes a stack node
 * @new_node_value: the value of the new node
 * Return: the new node or NULL in case of failure
 */
StackNode *INITIALIZE_STACK_NODE(int new_node_value)
{
    StackNode *new_node = malloc(sizeof(StackNode));
    if (new_node == NULL)
    {
        return (NULL);
    }
    new_node -> value = new_node_value;
    new_node -> next = NULL;
    return (new_node);
}

/*
 * isEmpty - checks whether the stack has element(s)
 * @stack: pointer to the stack
 * Return: true if the stack has no elements and false if the stack has elements
 */
bool isEmpty(Stack *stack)
{
    if (stack->top == NULL || stack -> size == 0)
    {
        return (true);
    } else {
        return (false);
    }
}

/*
 * add_node - adds a stack element/node to the top of the stack
 * @stack: pointer to the stack where the node is being added
 * @new_node_value: the value of the new node being added to the stack
 * Return: the updated stack or NULL on failure
 */
Stack *add_node(Stack *stack, int new_node_value)
{
    /* Initialize the node */
    StackNode *new_node = INITIALIZE_STACK_NODE(new_node_value);
    if (new_node == NULL)
    {
        return (NULL);
    }
    StackNode *current_top_element = stack -> top;
    new_node -> next = current_top_element;
    stack -> top  = new_node;
    stack -> size ++;
    return (stack);
}

/*
 * remove_node - removes the top most node from the stack
 * @stack: pointer to the stack
 * Return: the updated stack or null on failure
 */
Stack *remove_node(Stack *stack)
{
    /*If the stack is empty, the removal operation cannot proceed*/
    if (stack->top == NULL || stack->size == 0)
    {
        return (NULL);
    }
    StackNode *current_top_node = stack -> top;
    stack -> top = current_top_node -> next;
    stack -> size --;
    free(current_top_node);
    return (stack);
}

/*
 * peek - retrieve the top element of the stack without removing it
 * @stack: pointer to the stack
 * Return: the top element of a stack without removing it or NULL if the stack is empty
 */
StackNode *peek(Stack *stack)
{
    if (isEmpty(stack))
    {
        return (NULL);
    }
    return (stack->top);
}

int main()
{
    printf("STACKS IN C\n");

    Stack *stack = malloc(sizeof(Stack));

    if (stack == NULL){
        printf("Cannot create stack\n");
        return (-1);
    }

    add_node(stack, 10);
    add_node(stack, 20);
    add_node(stack, 8);
    add_node(stack, 5);
    add_node(stack, 80);
    remove_node(stack);
    remove_node(stack);
    remove_node(stack);
    remove_node(stack);
    if (isEmpty(stack)){
        printf("Stack is empty\n");
    } else {
        printf("Stack has element(s)\n");
        printf("Current top element: %d\n", stack->top->value);
        printf("Length of the stack: %zu\n", stack->size);
        printf("Current top element: %d\n", peek(stack)-> value);
    }
    return (0);
}








