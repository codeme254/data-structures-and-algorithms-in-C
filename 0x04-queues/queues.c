#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*
 * Q_Node - structure of a node in the queue
 * @value: the value held by that node
 * @next: pointer to the next node in the queue
 */
typedef struct QueueNode {
    int value;
    struct QueueNode *next;
}Q_Node;

/*
 * Queue - structure of a queue
 * @first: pointer to the first element in that queue
 * @last: pointer to the last element in that queue
 * @length: the length of the queue
 */
typedef struct{
    Q_Node *first;
    Q_Node *last;
    size_t length;
} Queue;

/*
 * INITIALIZE_Q_NODE - initializes the node of a queue
 * @new_node_value: the value held by this new node
 * Return: the new node or NULL if it fails
 */
Q_Node *INITIALIZE_Q_NODE(int new_node_value)
{
    Q_Node *new_node = malloc(sizeof(Q_Node));
    if (new_node == NULL)
    {
        return (NULL);
    }
    new_node -> value = new_node_value;
    new_node -> next = NULL;
    return (new_node);
}

bool isEmpty(Queue *queue)
{
    if (queue->length == 0 || queue->first == NULL)
    {
        return (true);
    } else {
        return (false);
    }
}

/*
 * add_node - adds a node at the end of the queue
 * @queue: pointer to the queue
 * @new_node_value: value of the new node being added
 * Return: the updated queue or NULL if there is any failure
 */
Queue *add_node(Queue *queue, int new_node_value)
{
    Q_Node *new_node = INITIALIZE_Q_NODE(new_node_value);
    if (new_node == NULL)
    {
        return (NULL);
    }
    /*If the queue is empty, the new node becomes the first and the last*/
    /*Otherwise, just add the node to the end*/
    if (isEmpty(queue))
    {
        queue->first = new_node;
        queue->last = new_node;
    } else {
        /*Add node to the end*/
        Q_Node *current_last_node = queue -> last;
        current_last_node -> next = new_node;
        queue -> last = new_node;
    }
    /*increase the length of the queue and return it*/
    queue->length ++;
    return (queue);
}

/*
 * peek_rear - returns the last node of the queue without removing it
 * @queue: the queue where we are looking at the last node
 * Return: NULL if the queue is empty or the last node if the queue is not empty
 */
Q_Node *peek_rear(Queue *queue)
{
    if (isEmpty(queue))
    {
        return (NULL);
    }
    return (queue -> last);
}

/*
 * peek_front - returns the first node of the queue without removing it
 * queue: the queue where we are looking at the first node
 * Return: NULL if the queue is empty or the first node if the queue is not empty
 */
Q_Node *peek_front(Queue *queue)
{
    if (isEmpty(queue))
    {
        return (NULL);
    }
    return (queue -> first);
}

/*
 * remove - removes the first node in the queue
 * @queue: the queue where the first element is being removed
 * Return: the updated queue or NULL if the queue is empty
 */
Queue *remove_node(Queue *queue)
{
    if (isEmpty(queue))
    {
        return (NULL);
    }
    Q_Node *current_first_node = queue->first;
    queue->first = current_first_node -> next;
    queue->length--;
    free(current_first_node);
    return (queue);
}

int main()
{
    printf("QUEUES IN C\n");
    Queue *q = malloc(sizeof(Queue));
    if (q == NULL)
    {
        return (-1);
    }

    add_node(q, 10);
    add_node(q, 8);
    add_node(q, 25);
    add_node(q, 30);
    remove_node(q);
    remove_node(q);
    if (isEmpty(q))
    {
        printf("Queue is empty\n");
    } else {
        printf("Queue has element(s)\n");
        printf("The last node in the queue %d\n", peek_rear(q)->value);
        printf("The first node in the queue %d\n", peek_front(q)->value);
        printf("Length of the queue: %zu\n", q->length);
    }
    return (0);
}

