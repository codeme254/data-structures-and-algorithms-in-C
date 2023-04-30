#include <stdio.h>
#include <stdlib.h>

/*
 * Implementation of a singly linked list
 * In this flavor, no singly linked list struct
 * Just working with the nodes and taking a reference of a head of a list
 */


/*
 * ListNode - node structure of a singly linked list
 * @value: integer value that is being held by the node
 * @next: pointer to the next ListNode element in a singly linked list
 */
typedef struct ListNode {
	int value;
	struct ListNode *next;
} ListNode;


/*
 * INITIALIZE_NODE - helper function to initialize the node of a list
 * @node_value: value of the node to be initialized
 * Return: the created node or NULL on failure
 */
ListNode *INITIALIZE_NODE(int node_value)
{
	ListNode *new_node = malloc(sizeof(ListNode));
	if (new_node == NULL)
		return (NULL);
	new_node->value = node_value;
	new_node->next = NULL;
	return (new_node);
}

/*
 * push - adds a new node to the end of a given list
 * @head: the first node of the list where the new node is being pushed
 * @new_node_value: the value of the new node being pushed to the list
 * Return: the pushed node or NULL if anything goes wrong (on failure)
 */
ListNode *push(ListNode **head, int new_node_value)
{
	ListNode *new_node = INITIALIZE_NODE(new_node_value);
	if (new_node == NULL)
		return NULL;
	/*If the current list is empty, this node becomes the head node*/
	if (*head == NULL)
	{
		*head = new_node;
		return (new_node);
	}
	/*Otherwise, loop to the end of the list and add this new node there*/
	ListNode *current = *head;
	while (current->next != NULL)
		current = current->next;
	current->next = new_node;
	return (new_node);
}

/*
 * pop - removes a node at the end of the list
 * @head: the first node of the list whose last node is being removed
 * Return: NULL if there are no elements in the list or the removed node
 */
ListNode *pop(ListNode **head)
{
	/*Check if the list is empty, if it is, return NULL*/
	if (*head == NULL)
		return (NULL);
	/*Otherwise, loop to the end of the list and remove the node*/
	/*Use two pointers technique to do this*/
	ListNode *temp_node = *head;
	ListNode *current_node = *head;
	while (current_node->next != NULL)
	{
		temp_node = current_node;
		current_node = current_node->next;
	}
	/*current_node is pointing to the node we want to removed*/
	/*temp_node is pointing at the node previous to it*/
	/*We loose reference of current_node by setting next of temp_node to NULL*/
	temp_node->next = NULL;
	/*TODO: Free the memory being occupied by current_node as we are removing it*/
	/*
	 * We also need to check if the list has only one node and it is the one node we are trying to remove
	 * In this case, the list will be left with no elements
	 * We know if it is the only element if temp_node and current_node are ponting to the same thing
	 */
	if (temp_node == current_node)
		/*set the list to null since it has no elements*/
		/*TODO: Free the memory being occupied by the node*/
		*head = NULL;
	return (current_node);
}

/*
 * unshift - adds a new node to the beginning of a list
 * @head: pointer to the current first node of the list to unshift to
 * @new_node_value: value of the new node to unshift to the list
 * Return: the new node or null on failure
 */
ListNode *unshift(ListNode **head, int new_node_value)
{
	ListNode *new_node = INITIALIZE_NODE(new_node_value);
	if (new_node == NULL)
		return (NULL);
	/*If, the list is empty, the new node becomes the head*/
	if (*head == NULL)
	{
		*head = new_node;
		return (NULL);
	}
	new_node->next = *head;
	*head = new_node;
	return (new_node);
}


/*
 * shift - removes the first node of a given list
 * @head: pointer to the first node of the list we are shiftting
 * Return: the removed node or null on failure
 */
ListNode *shift(ListNode **head)
{
	/*If the list is empty, return NULL*/
	if (*head == NULL)
		return (NULL);
	ListNode *current_head = *head;
	/*Just an edge case handling: If the head is the only node (one node)*/
	if (current_head->next == NULL)
	{
		*head = NULL;
		return (current_head);
		/*TODO: Free the memory being held by current head*/
	}
	*head = current_head->next;
	/*clear the reference being held by the current head*/
	current_head->next = NULL;
	/*TODO: Free the memory being held by current_head*/
	return (current_head);
}

/*
 * get_list_length - gets the number of nodes of a list
 * @head: pointer to the first node of the list we are getting the length
 * Return: 0 if the list has no nodes, or the number of nodes in the list
 */
int get_list_length(ListNode **head)
{
	if (*head == NULL)
		return (0);
	int length = 0;
	ListNode *current_node = *head;
	while (current_node != NULL)
	{
		length += 1;
		current_node = current_node->next;
	}
	return (length);
}


/*
 * get_node - retrieves a node from a list using zero based indexing
 * @head: pointer to the first element of the list we are retrieving this node from
 * @node_index: the index of the node we are want to retrieve
 * Return: the node retrieved or NULL if there is any failure
 * Description: uses zero-based indexing, the first element is index 0 and the last element is index length of the list minus 1
  */
ListNode *get_node(ListNode **head, int node_index)
{
	/*If the list is empty, we return NULL*/
	if (*head == NULL)
		return (NULL);
	/*Check if the index is between 0 and length of the list minus 1*/
	int list_length = get_list_length(head);
	if (node_index < 0 || node_index >= list_length)
		return (NULL);
	int current_index = 0;
	ListNode *current_node = *head;
	while (current_index != node_index)
	{
		current_node = current_node->next;
		current_index += 1;
	}
	return (current_node);
}

ListNode *update_node(ListNode **head, int node_index, int new_value)
{
	/*check if the list is empty*/
	if (*head == NULL)
		return (NULL);
	ListNode *node_to_update = get_node(head, node_index);
	if (node_to_update == NULL)
		return (NULL);
	node_to_update->value = new_value;
	return (node_to_update);
}

/*
 * insert - inserts a node in the middle of a list
 * @insert_index: the index at which to insert the node
 * @new_node_value: the value of the new node to insert to the list
 * Return: the inserted node or NULL on failure
 */
ListNode *insert(ListNode **head, int insert_index, int new_node_value)
{
	/*validate that the insert index is within ranges*/
	int list_length = get_list_length(head);
	if (insert_index < 0 || insert_index >= list_length)
		return (NULL);
	/*If the index is 0, the insert at head*/
	if (insert_index == 0)
		return (unshift(head, new_node_value));
	/*if the index is list_length - 1, insert at the end*/
	if (insert_index == list_length - 1)
		return (push(head, new_node_value));
	ListNode *new_node = INITIALIZE_NODE(new_node_value);
	if (new_node == NULL)
		return (NULL);
	/*Get the element previous to the insert index*/
	ListNode *node_previous_to_insert_index = get_node(head, insert_index - 1);
	/*Store the node next to it to avoid loosing referece*/
	ListNode *temp_next = node_previous_to_insert_index->next;
	/*Set the node_previous_ to_insert_index's next to be the new node*/
	node_previous_to_insert_index->next = new_node;
	/*Set the new node to point to the temp_next*/
	new_node->next = temp_next;
	return (new_node);
}

/*
 * remove - removes a node from the middle of a list
 * @head: pointer to the first element of the list we are removing from
 * @removal_index: the index of the node we want to remove
 * Return: the removed node or NULL on failure
 * */
ListNode *remove_middle(ListNode **head, int removal_index)
{
	if (*head == NULL)
		return (NULL);
	/*do removal index validation*/
	int list_length = get_list_length(head);
	if (removal_index < 0 || removal_index >= list_length)
		return (NULL);
	/*If the index is 0, shift*/
	if (removal_index == 0)
		return (shift(head));
	if (removal_index == list_length - 1)
		return (pop(head));
	/*Store the node to be removed*/
	ListNode *node_to_be_removed = get_node(head, removal_index);
	/*Get the node previous to the node to be removed*/
	ListNode *temp_previous = get_node(head, removal_index - 1);
	/*Get the node next to the node to be removed*/
	ListNode *temp_next = get_node(head, removal_index + 1);
	temp_previous->next = temp_next;
	node_to_be_removed->next = NULL;
	/*TODO: Free the memory occupied by node_to_be_removed*/
	return (node_to_be_removed);
}

/*
 * traverse_list - traverses a given singly linked list
 * @head: pointer to the first element of the list to traverse
 * Return: 0 if there are no nodes to traverse and 1 if traversal has been done
 */
int traverse_list(ListNode **head)
{
	if (*head == NULL)
		return (0);

	ListNode *current = *head;
	while (current != NULL)
	{
		printf("%d -> ", current->value);
		current = current->next;
	}
	printf("NULL");
	return (1);
}


int main()
{
	printf("===Singly Linked Lists===\n");
	ListNode *head = NULL;
	push(&head, 20);
	push(&head, 25);
	push(&head, 30);
	push(&head, 35);


	pop(&head);

	unshift(&head, 10);
	unshift(&head, 5);
	unshift(&head, 3);
	unshift(&head, 0);

	shift(&head);
	shift(&head);

	update_node(&head, 1, 9);
	update_node(&head, 4, 35);

	insert(&head, 2, 15);
	insert(&head, 0, 1);
	insert(&head, 6, 40);
	insert(&head, 6, 30);

	remove_middle(&head, 0);
	remove_middle(&head, 7);
	remove_middle(&head, 2);
	remove_middle(&head, 1);

	printf("val: %d\n", get_node(&head, 4)->value);

	printf("Length of the list: %d\n", get_list_length(&head));
	traverse_list(&head);
	return (0);
}
