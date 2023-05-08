#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
/*
 * Implementing doubly linked list in C
 */

/*
 * ListNode - structure of a list node
 * @next: pointer to a next element of the same type
 * @previous: pointer to a previous element of the same type
 * @value: value held by a node
 */
typedef struct ListNode {
	int value;
	struct ListNode *next;
	struct ListNode *previous;
} ListNode;


/*
 * INITIALIZE_NODE - initialises the node of a list
 * @node_value: the value of the new node being initialized
 * Return: the initialized node or NULL on failure
 */
ListNode *INITIALIZE_NODE(int node_value)
{
	ListNode *new_node = malloc(sizeof(ListNode));
	if (new_node == NULL)
		return (NULL);
	new_node -> value = node_value;
	new_node -> next = NULL;
	new_node -> previous = NULL;
	return (new_node);
}

/*
 * push - appends a new node at the end of a doubly linked list
 * @head: pointer to the first node of the list being pushed to
 * @new_node_value: the value of the new node being pushed
 * Return: the pushed node or NULL on failure
 */
ListNode *push(ListNode **head, int new_node_value)
{
	ListNode *new_node = INITIALIZE_NODE(new_node_value);
	if (new_node == NULL)
		return (NULL);
	if (*head == NULL)
	{
		*head = new_node;
		return (new_node);
	}
	/*Loop to the end of the file and add it there*/
	ListNode *current = *head;
	while (current -> next != NULL)
		current = current -> next;
	current -> next = new_node;
	new_node -> previous = current;
	return (new_node);
}

/*
 * pop - removes the last node of a list
 * @head: pointer to the first element of the list to pop
 * Return: the removed node or NULL on failure
 */
ListNode *pop(ListNode **head)
{
	if (*head == NULL)
		return (NULL);
	/*Use two pointer to remove the last node*/
	ListNode *current = *head;
	ListNode *temp_node = *head;

	while (current->next != NULL)
	{
		temp_node = current;
		current = current -> next;
	}
	/*
	 * if current and temp_node are still pointing on the same element
	 * it means the list had one element, so we check for that
	 */
	if (current == temp_node)
	{
		*head = NULL;
		return (current);
	}
	/*Otherwise, remove the specific node*/
	temp_node -> next = NULL;
	current -> previous = NULL;
	//free(current);
	return (current);
}

/*
 * unshift - adds a new node at the beginning of a list
 * @head: pointer to the first element of the list to unshif to
 * @new_node_value: the value of the new node that is being unshifted
 * Return: the unshifted node or NULL on failure
 */
ListNode *unshift(ListNode **head, int new_node_value)
{
	ListNode *new_node = INITIALIZE_NODE(new_node_value);
	if (new_node == NULL)
		return (NULL);
	/*If the list has no elements, this node becomes the head*/
	if (*head == NULL)
	{
		*head = new_node;
		return (new_node);
	}
	/*Otherwise, do necessary connections*/
	new_node -> next = *head;
	(*head) -> previous = new_node;
	*head = new_node;
	return (new_node);
}

/*
 * shift - removes the first node of a list
 * @head: pointer to the first element of the list we are removing from
 * Return: removed node or NULL on failure
 */
ListNode *shift(ListNode **head)
{
	if (*head == NULL)
		return (NULL);
	ListNode *current_head = *head;
	/*The list has only one element, i.e this head*/
	if (current_head -> next == NULL)
	{
		/*TODO: there is a bug here, you cannot free it and return it*/
		/*But I need to return something of type ListNode*/
		free (current_head);
		return (current_head);
	}
	ListNode *tmp_head = current_head -> next;
	tmp_head -> previous = NULL;
	current_head -> next = NULL;
	*head = tmp_head;
	return (current_head);
}

/*
 * get_list_length - finds the length of a list
 * @head: pointer to the first element of the list to find the length of
 * Return: the length of the list, 0 if there are no elements in the list
 * Description: the length of a list is the number of nodes available in the list
 */
int get_list_length(ListNode **head)
{
	/*No elements? return 0*/
	if (*head == NULL)
		return (0);
	int length = 0;
	ListNode *current = *head;
	while (current != NULL)
	{
		length++;
		current = current -> next;
	}
	return (length);
}

/*
 * get_node - finds a node in a list and returns it
 * @head: pointer to the first node of the list we are trying to get the node from
 * @index: index of this node in the list
 * Return: the node or NULL if there is any failure
 * Description: uses zero based indexing, first element has index of 0 and last element has an index of list_length - 1
 */
ListNode *get_node(ListNode **head, int index)
{
	if (*head == NULL)
		return (NULL);
	/*If the index is outside the ranges, return NULL*/
	if (index < 0 || index >= get_list_length(head))
		return (NULL);
	int i = 0;
	ListNode *current = *head;
	while (i < index)
	{
		current = current -> next;
		i++;
	}
	return (current);
}

/*
 * insert - inserts a node in the middle of a list
 * @index: index to insert
 * @new_node_value: the value of the new node to insert
 * Return: the inserted node or NULL on failure
 */
ListNode *insert(ListNode **head, int index, int new_node_value)
{
	/*validate the index*/
	if (index < 0 || index >= get_list_length(head))
		return (NULL);
	/*If the index is zero, insert at the beginning*/
	if (index == 0)
		return (unshift(head, new_node_value));
	/*If the index is equal to length - 1, we push*/
	if (index == get_list_length(head) - 1)
		return (push(head, new_node_value));

	ListNode *new_node = INITIALIZE_NODE(new_node_value);
	if (new_node == NULL)
		return (NULL);
	/*Get the node after insert index*/
	ListNode *node_before = get_node(head, index - 1);
	ListNode *node_at_index = get_node(head, index);
	node_before -> next = new_node;
	new_node -> previous = node_before;

	new_node -> next = node_at_index;
	node_at_index -> previous = new_node;
	return (new_node);
}

/*
 * remove - removes a node in the middle of a list
 * @head: pointer to the first element of the list we are removing from
 * @index: index of the node to be removed
 * Return: the removed node or NULL if there is any failure
 */
ListNode *remove_node(ListNode **head, int index)
{
	if (*head == NULL)
		return (NULL);
	if (index < 0 || index >= get_list_length(head))
		return (NULL);
	/*If the index is zero, shift*/
	if (index == 0)
		return (shift(head));
	/*If the index is equal to list length minus 1, pop*/
	if (index == get_list_length(head) - 1)
		return (pop(head));

	/*Get the node to be removed*/
	ListNode *node_to_be_removed = get_node(head, index);
	ListNode *node_before = get_node(head, index - 1);
	ListNode *node_after = get_node(head, index + 1);

	node_before -> next = node_after;
	node_after -> previous = node_before;

	node_to_be_removed -> next = NULL;
	node_to_be_removed -> previous = NULL;

	return (node_to_be_removed);
}


/*
 * traverse_list - goes through the doubly linked list both ways printing node vals
 * @head: pointer to the first element of the list to traverse
 * Return: 0 on success and 1 on failure
 */
int traverse_list(ListNode **head)
{
	if (*head == NULL)
		return (1);

	printf("Forward traversing\n");
	ListNode *current = *head;
	while (current != NULL)
	{
		printf("%d -> ", current->value);
		current = current -> next;
	}
	printf ("NULL\n");
	
	/*Move to the last node and start iterating coming to the first node*/
	/*Because right now, current is at NULL and NULL has no next or previous*/
	/*So there is no way of traversing backwards*/

	printf("Backward traversing\n");
	current = *head;
	while (current -> next != NULL)
		current = current -> next;
	while (current != NULL)
	{
		printf("%d -> ", current -> value);
		current = current -> previous;
	}
	printf("NULL\n");
	return (0);
}


int main()
{
	printf("Implementing doubly linked list in C\n");

	ListNode *head = NULL;
	push(&head, 10);
	push(&head, 20);
	push(&head, 30);

        pop(&head);

	unshift(&head, 5);
	unshift(&head, 3);
	unshift(&head, 2);

	shift(&head);
	shift(&head);

	insert(&head, 0, 1);
	insert(&head, 3, 25);
	insert(&head, 2, 8);

	remove_node (&head, 0);
	remove_node (&head, 4);
	remove_node (&head, 1);

        printf("Node at index 2 is %d\n", get_node(&head, 2)-> value);
	traverse_list (&head);
	printf("Length of the list %d\n", get_list_length(&head));
	return (0);
}
