// Implementing a queue with a singly linked list data structure

#include <stdio.h>
#include <stdlib.h>

/**
 * QueueNode - the structure of a node of a queue
 * @value: the integer value of the queue
 * @next: pointer to the next element of similar structure
*/
typedef struct QueueNode{
    int value;
    struct QueueNode *next;
} Q_Node;

/**
 * Queue - structuer of a queue data structure
 * @first: pointer to the first node of the queue
 * @last: pointer to the last node of the queue
*/
typedef struct Queue{
    Q_Node *first;
    Q_Node *last;
    int length;
} Q_struct;

/**
 * create_queue - creates a queue
 * Return: pointer to the queue created
*/
Q_struct *create_queue(){
    // allocating memory to the new queue being created
    Q_struct *new_queue = malloc(sizeof(Q_struct));
    // check if the memory was allocated succesfully
    // Return null if not
    if (new_queue == NULL) return NULL;
    // otherwise, set the first and last to be null
    // set the lengt of the queue to be zero
    // return a pointer to the queue created
    new_queue->first = NULL;
    new_queue->last = NULL;
    new_queue->length = 0;
    return new_queue;
}

/**
 * enqueue - adds an element at the end of the queue
 * @queue: the queue where we are adding the element
 * @value: the value of the node that is about to be added to the queue
 * Return: pointer to the created node
*/
Q_Node *enqueue(Q_struct *queue, int value){
    // create a new node and allocate memory to it
    Q_Node *new_node = malloc(sizeof(Q_Node));
    // check if the memory has been successfully allocated
    // return null if not
    if(new_node == NULL) return NULL;
    // otherwise, set the values of the new node
    // next should be null
    new_node->value = value;
    new_node->next = NULL;

    // if the queue passed is empty, make this node the first and last
    if (queue->length == 0 || !queue->first){
        queue->first = new_node;
        queue->last = new_node;
    }else{
        // loop to the end and add this new node there
        Q_Node *current = queue->first;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = new_node;
        // set this node to be the last node of the queue
        queue->last = new_node;
    }
    // increment the length of the queue and return the new node
    queue->length++;
    return new_node;
    // if we do return *new_node, we are dereferencing the new_node
    // this does not match the return type of the function
    // because for the return type, we want to return a pointer
}

/**
 * dequeue - removes the first node of the queue
 * @queue: the queue where we are removing the first node
 * Return: the removed/dequeued node
*/
Q_Node *dequeue(Q_struct *queue){
    // if the queue has no elements, return null
    if (queue->length == 0 || !queue->first) return NULL;
    // otherwise, save the current first node in a variable to return it later
    Q_Node *first_node = queue->first;
    // if the queue has only one element, remove it, reset the queue
    // and return that node, i.e the first node
    if (queue->length == 1){
        queue->first = NULL;
        queue->last = NULL;
        queue->length = 0;
    }else {
        // set first node of queue to be the node next to current first node
        queue->first = first_node->next;
        // set the next of the node removed to be null
        first_node->next = NULL;
        // reduce the length of the queue
        queue->length--;
    }
    // return the removed node
    return first_node;
}

int main(void){
    // implementation of a queue data structure

    // creating the queue
    Q_struct *que = create_queue();
    // if the function returns null, we exit the program
    if (que == NULL) exit(1);

    // adding elements to the queue
    enqueue(que, 10);
    enqueue(que, 20);
    enqueue(que, 30);
    enqueue(que, 40);
    enqueue(que, 50);

    // removing from the queue
    dequeue(que);
    dequeue(que);
    dequeue(que);
    dequeue(que);

    // the queue data
    printf("First queue node val: %d\n", que->first->value);
    printf("Last queue node val: %d\n", que->last->value);
    printf("Length of the queue: %d\n", que->length);
}