#include <stdio.h>
#include <stdlib.h>

/**
 * ListNode - the structure of a node
 * @value : the value of a node/value held by a node/data
 * @next : pointer to the next node of the same type
 * @previous : pointer to a previous node of the same type
*/

typedef struct ListNode{
    int value;
    struct ListNode *next;
    struct ListNode *previous;
} ListNode;

/**
 * push - adds a node at the end of the list
 * @head: pointer to the head of the list where we are adding
 * @value: the value of the node that we are adding
 * Return: the node that was added to the list
*/

ListNode *push(ListNode **head, int value){
    // allocate memory for new node and check if it was allocated succesfully
    ListNode *new_node = malloc(sizeof(ListNode));
    if (new_node == NULL)
    {
        return NULL;
    }
    // set the values for new node, next and previous null by default
    new_node->value = value;
    new_node->next = NULL;
    new_node->previous= NULL;
    // if the list is empty, this node becomes the head
    if (*head == NULL){
        *head = new_node;
        return new_node;
    }
    // otherwise, loop to the end and add the new node there
    ListNode *current = *head;
    while (current->next != NULL){
        current = current->next;
    }
    current->next = new_node;
    new_node->previous = current;
    return new_node;
}

/**
 * list_length - function that gets the length of the list
 * @head: the head of the list we want to get the length
 * Return: the length of the list, 0 if the list is empty
*/
int list_length(ListNode **head){
    // if the list is empty, return 0
    if (*head == NULL){
        return 0;
    }
    // otherwise, count all the nodes in the list
    int length = 0;
    ListNode *current = *head;
    while (current != NULL){
        current = current->next;
        length++;
    }
    return length;
}

/**
 * pop - removes a node at the end of the list
 * @head: pointer to the first node of the list
 * Return: the removed node
*/

ListNode *pop(ListNode **head){
    // if the list is empty, return null
    if (*head == NULL){
        return NULL;
    }
    // otherwise, loop to the end to get the last node
    ListNode *current = *head;
    while(current->next != NULL){
        current = current->next;
    }
    // get the node that is previous to the last node
    ListNode *tmp = current->previous;
    // make it's next property to be null
    tmp->next = NULL;
    // make the previous property of current (whic is last) node to be null
    current->previous = NULL;
    // make it's next property to be null
    current->next = NULL;
    // free the memory held by this node
    free(current);
    // return the removed node
    return current;
}

/**
 * shift - removes a node at beginning of the list (removes current head node)
 * @head : pointer to the current head node
 * Return: the removed node (though freed)
*/
ListNode *shift(ListNode **head){
    // if the list is empty, return null
    if (*head == NULL){
        return (NULL);
    }
    // get access to the current head;
    ListNode *current_head = *head;
    // the new head is the next node of the current head
    ListNode *new_head = current_head->next;
    // explicitly set that next node to be the head
    *head = new_head;
    // make the new head previous to be null
    new_head->previous = NULL;
    // make the current head next to be null
    current_head->next = NULL;
    printf("Removed node value: %d\n", current_head->value);
    printf("Removed node next: %p\n", current_head->next);
    printf("Removed node previous: %p\n", current_head->previous);
    // free the memory occupied by the removed node
    free(current_head);
    return current_head;
}

/**
 * unshift - adds a node at the beginning of the list
 * @head: pointer to the head of the list where we are adding this node
 * @value: value of the node we are adding
 * Return: the node that has been added to the list
*/
ListNode *unshift(ListNode **head, int value){
    // allocating memory fo the new node
    ListNode *new_node = malloc(sizeof(ListNode));
    // checking if tmemory was allocated successfully and returning null if not
    if(new_node == NULL){
        return (NULL);
    }
    // otherwise, set the properties of this new node
    new_node->value = value;
    new_node->next = NULL;
    new_node->previous = NULL;

    // set this new node's next to be the current head
    new_node->next = *head;
    // set the previous property of the current head to be this new node
    (*head)->previous = new_node;
    // explicitly set this new node to be the head
    *head = new_node;
    return new_node;
}

/**
 * get - gets a node at a give position in the list
 * @head: pointer to the first node of the list
 * @idx: the index of the node we want to get
 * Return: the node at the given index
 * Description: the function uses zero based indexing to get the node
*/
ListNode *get(ListNode **head, int idx){
    // printf("value: %d\n", (*head)->value);
    
    // if the list is empty we return null
    // also return null if idx is < zero or >= length of list
    if (*head == NULL || idx < 0 || idx >= list_length(head)){
        return NULL;
    }
    
    ListNode *current = *head;
    int i = 0;
    while (current->next != NULL){
        if (i == idx) return current;
        current = current->next;
        i++;
    }
    // if we are here, it means the idx is overflowing
    return NULL;
}

/**
 * set - function that changes the value of a node in the list
 * @head: pointer to the head of the list we want to do the operation
 * @idx: index of the node that we want to change
 * Return: the changed node
*/
ListNode *set(ListNode **head, int value, int idx){
    // we use get to get the node
    ListNode *node_to_change = get(head, idx);
    if (node_to_change == NULL){
        return NULL;
    }
    node_to_change->value = value;
    return node_to_change;
}

/**
 * insert - adding a node at a certain position in the list
 * @head: pointer to the head of the list we want to add
 * @value: value of the node we want to add
 * @idx: position in the list where we want to add this node
 * Return: the added node
 * Description: since we are using custom get method, it is zero indexing based
*/
ListNode *insert(ListNode **head, int value, int idx){
    // IMPORTANT
    // =========
    // if the index is zero, we add at the beginning
    if (idx == 0){
        return unshift(head, value);
    }

    // allocate memory for the new node
    ListNode *new_node = malloc(sizeof(ListNode));
    if (new_node == NULL){
        return (NULL);
    }
    // setting the values for the new node
    new_node->value = value;
    new_node->next = NULL;
    new_node->previous = NULL;
    // we use get to access idx -1 and set its next to be this new node
    ListNode *tmp = get(head, idx-1);
    // get the node that tmp was pointing to
    ListNode *tmp_next = tmp->next;
    // make connections for the new node to stay in the middle
    tmp->next = new_node;
    new_node->previous = tmp;
    new_node->next = tmp_next;
    tmp_next->previous = new_node;
    return new_node;
}

/**
 * remove_node - removes a node in the middle of the list
 * @head: pointer to the head of the list where the node is being removed
 * @idx: index of the node we are removing
 * Return: the removed node
 * Description: uses zero indexing
*/

ListNode *remove_node(ListNode **head, int idx){
    // if the list is empty, return null
    if (*head == NULL){
        return NULL;
    }
    // if the index is zero, we remove at the beginning of the list
    if (idx == 0){
        return shift(head);
    }
    // if the index is equal to length - 1, we pop
    if (idx == list_length(head)){
        return pop(head);
    }

    // we use get to get the node to be removed
    ListNode *node_to_be_removed = get(head, idx);
    // change the connections
    node_to_be_removed->previous->next = node_to_be_removed->next;
    node_to_be_removed->next->previous = node_to_be_removed->previous;

    node_to_be_removed->next = NULL;
    node_to_be_removed->previous = NULL;

    printf("==Remove Method removing index %d==\n", idx);
    printf("Removed node is %d\n", node_to_be_removed->value);
    printf("Removed node next %p\n", node_to_be_removed->next);
    printf("Removed node previous %p\n", node_to_be_removed->previous);
    free(node_to_be_removed);
    return node_to_be_removed;
}

/**
 * traverse_list - traverses the list in both forward and backward direction
 * @head: pointer to the head of list that is to be traversed
*/
void traverse_list(ListNode **head){
    ListNode *current = *head;
    while (current != NULL)
    {
        printf("%d ->", current->value);
        current = current->next;
    }
    printf("NULL\n");
    
    // taking the current pointer to the end of the list to traverse back
    current = *head;
    while (current->next != NULL){
        current = current->next;
    }

    while (current != NULL){
        printf("%d ->", current->value);
        current = current->previous;
    }
    printf("NULL\n");
}

int main(void){
    /*initializing the list*/
    ListNode *head = NULL;
    push(&head, 10);
    push(&head, 20);
    push(&head, 30);
    push(&head, 40);
    push(&head, 50);

    // removing the last node
    // printf("Removed node: %d\n", pop(&head)->value);
    // printf("Removed node previous: %p\n", pop(&head)->previous);
    // printf("Removed node next: %p\n", pop(&head)->next);
    pop(&head);

    // removing the first node
    shift(&head);

    // adding at the beginning of the list
    unshift(&head, 8);
    unshift(&head, 5);

    // getting a node
    printf("Getting node at index 2: %d\n", get(&head, 2)->value);
    printf("Getting node at index 0: %d\n", get(&head, 0)->value);
    // printf("Getting node at index 100000: %p\n", get(&head, 100000)->value);

    // using set to change value
    set(&head, 25, 3);

    // inserting in the middle of the list
    insert(&head, 30, 4);
    insert(&head, 3, 0);

    // calling the remove method
    remove_node(&head, 2);
    remove_node(&head, 1);

    // printing the length of the list
    printf("Length of the list: %d\n", list_length(&head));
    // traversing the list
    traverse_list(&head);
    traverse_list(&head);
}