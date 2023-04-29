#include <stdio.h>
#include <stdlib.h>


/**
 * Stack - representation of a stack
 * @size: the size of the stack so far, i.e how many elements it has so far
 * @capacity: The max number of elements that a stack can hold
 * @collection: Pointer to dynamically allocated array of integers
 * Description: uses dynamically allocated array to store the values
*/
typedef struct Stack{
    int size;
    int capacity;
    int *collection;
} Stack;


/**
 * create_stack - creates a stack
 * @capacity: the size of the stack being created
 * Return: pointer to the created stack
*/
Stack *create_stack(int capacity){
    // allocate memory for the new stack
    Stack *new_stack = malloc(sizeof(Stack));
    // check if the memory allocation was successful
    if(new_stack == NULL) return NULL;

    // allocate size for the dynamically allocated array
    new_stack->collection = malloc(sizeof(int) * capacity);
    // check if the memory was successfully allocated
    // if not, free the memory that was allocated for the stack
    if (new_stack->collection == NULL){
        free(new_stack);
        return NULL;
    }
    // at this point, it means everything was successful, set everything up
    new_stack->capacity = capacity;
    new_stack->size = 0;
    return new_stack;
}

/**
 * push - adds an element to the top of the stack
 * @stack: the stack where we are pushing
 * @value: the we are placing at the top of the stack
 * Return: the updated stack
*/
Stack *push(Stack *stack, int value){
    // if the stack is full, return null
    if (stack->size == stack->capacity) return NULL;
    stack->collection[stack->size] = value;
    stack->size++;
    return stack;
}

/**
 * pop - removes the top value of the stack
 * @stack: the stack at which the top value is being removed
 * Return: the updated stack
*/
Stack *pop(Stack *stack){
    // if the stack is empty, we return null
    if (stack->size == 0) return NULL;
    stack->size--;
}

/**
 * free_stack - deallocates a stack
 * @stack: the stack we are deallocating
*/
void free_stack(Stack *stack){
    // deallocate the dynamically allocated array and the stack itself
    free(stack->collection);
    free(stack);
}

int main(void){
    // Implementation of a stack data structure

    // creating the stack
    Stack *stack = create_stack(8);
    push(stack, 5);
    push(stack, 10);
    push(stack, 15);
    push(stack, 20);
    push(stack, 25);
    push(stack, 30);
    push(stack, 35);
    push(stack, 40);
    pop(stack);
    pop(stack);
    push(stack, 56);
    printf("Top element of the stack: %d\n", stack->collection[stack->size-1]);
    printf("Capacity of new stack: %d\n", stack->capacity);
    printf("Size of the stack so far: %d\n", stack->size);

    free_stack(stack);

    // size_t size = sizeof(stack);
    // printf("%ld\n", size);
}