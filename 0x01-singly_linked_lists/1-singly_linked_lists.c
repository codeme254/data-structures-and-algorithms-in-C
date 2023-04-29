#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

/*
 * ListNode - structure of a ListNode
 * @value: the value of a node
 * @next: pointer to the next element in the list
 */

typedef struct ListNode
{
	int value;
	struct ListNode *next;
} ListNode;

/*
 * INITIALIZE_NODE: initializes the node of a singly linked list
 * @node_value: value of the node to be initialized by this function
 * Return: pointer to the created node or NULL on failure
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
 * append_node_to_list - appends a node to a given list
 * @head: pointer to the first node of the list we are appending to
 * @new_node_value: the value of the new node appended to the list
 * Return: the node that was appended to the list or NULL on failure
 */
ListNode *append_node_to_list(ListNode **head, int new_node_value)
{
	ListNode *new_node = INITIALIZE_NODE(new_node_value);
	if (new_node == NULL)
		return (NULL);

	/*If the list is empty, this node should become the head*/
	if (*head == NULL)
	{
		*head = new_node;
		return (new_node);
	}
	/*Otherwise, loop to the end of the list and add this node there*/
	ListNode *current = *head;
	while (current->next != NULL)
		current = current->next;
	current->next = new_node;
	return (new_node);
}

/*
 * prepend_node_to_list - adds a new node at start of a singly linked list
 * @new_node_value: value of the new node being prepended
 * Return: pointer to the created node or NULL on failure
 */
ListNode *prepend_node_to_list(ListNode **head, int new_node_value)
{
	ListNode *new_node = INITIALIZE_NODE(new_node_value);

	if (new_node == NULL)
		return (NULL);
	/*if the list is empty, the new node becomes the head and tail*/
	if (*head == NULL)
	{
		*head = new_node;
		return (new_node);
	}
	/*Otherwise, make the new node point to the current head*/
	/*Then make the new node to be the new head of the list*/
	new_node->next = *head;
	*head = new_node;
	return (new_node);
}


/*
 * remove_at_end - removes a node at the end of a singly linked list
 * @head: pointer to the head of the list we are removing at
 * Return: ponter to the removed node or NULL if the list is empty
 */
ListNode *remove_at_end(ListNode **head)
{
	if (*head == NULL)
		return (NULL);
	/*Use two pointers algorithm to remove the last node*/
	ListNode *tmp_node = *head;
	ListNode *current = *head;
	while (current->next != NULL)
	{
		tmp_node = current;
		current = current->next;
	}
	tmp_node->next = NULL;
	/*Also check if there is one element remaining*/
	/*If so, we make the head point to null i.e making the list empty*/
	/*We know one element is reamining when tmp_node pointer and head
	 * pointer are both pointing to the same thing*/
	if (tmp_node == *head)
		*head = NULL;
	return (current);
}

/*
 * remove_at_beginning - removes a node at the start of a singly linked list
 * @head: pointer to the first node of the list we are removing a node
 * Return: pointer to the removed node or NULL if the list is empty
 */
ListNode *remove_at_beginning(ListNode **head)
{
	if (*head == NULL)
		return (NULL);
	ListNode *current_head = *head;

        /*Checking if only one element is remaining*/
	if (current_head->next == NULL)
	{
		*head = NULL;
		return (current_head);
	}
	*head = current_head->next;
	current_head->next = NULL;
	return (current_head);
}

/*
 * get_list_length - gets the length of a singly linked list
 * @head: pointer to the first node of the list we are getting the length
 * Return: the length of the list or zero if the list is empty
 */
int get_list_length(ListNode **head)
{
	int length_of_list;
	length_of_list = 0;
	if (*head == NULL)
		return (length_of_list);

	ListNode *current_node = *head;
	while (current_node != NULL)
	{
		current_node = current_node->next;
		++length_of_list;
	}
	return (length_of_list);
}

/*
 * get_node - retrieves a node from a list using zero indexing
 * @head: pointer to the first node of the list we are getting from
 * @node_index: the index of the node to be retrieved
 * Return: the retrieved node or NULL on failure
 */
ListNode *get_node(ListNode **head, int node_index)
{
	/*If the list is empty, we return null*/
	if (*head == NULL)
		return (NULL);

	/*If the given index is greater than length of list, return null*/
	/*And if it is also less than zero, return null*/
	int list_length = get_list_length(head);
	if (node_index >= list_length || node_index < 0)
	{ printf("bad index\n");
		return (NULL);
	}

	int current_index = 0;
	ListNode *current_node = *head;
	while (current_index != node_index)
	{
		current_node = current_node->next;
		++current_index;
	}
	return (current_node);
}

/*
 * change_node_value - changes the value of a given node in the list
 * @head: pointer to the first node of the list where this node is
 * @new_value: the new value for the node
 * @node_index: the index of the node to change
 * Return: the altered node or NULL on failure
 */
ListNode *change_node_value(ListNode **head, int new_value, int node_index)
{
	if (*head == NULL)
		return (NULL);
	ListNode *node_to_change = get_node(head, node_index);
	if (node_to_change == NULL)
		return (NULL);

	node_to_change->value = new_value;
	return (node_to_change);
}

/*
 * insert_in_the_middle - inserts a node in the middle of the list
 * @head: pointer to the first node of the list to insert into
 * @node_value: the value of the new node to be inserted
 * @index: the index of insertion
 * Return: the inserted node or NULL on failure
 */
ListNode *insert_in_the_middle(ListNode **head, int node_value, int index)
{
	/*Check if the index is within the ranges*/
	int list_length = get_list_length(head);
	if (index < 0 || index >= list_length)
		return (NULL);

	/*If the index is zero, we insert at the beggining*/
	if (index == 0)
		return(prepend_node_to_list(head, node_value));

	ListNode *new_node = INITIALIZE_NODE(node_value);
	if (new_node == NULL)
		return (NULL);
	/*We use get_node to get the node at index - 1*/
	/*Then make all the possible connections*/
	ListNode *temp_node = get_node(head, index - 1);
	ListNode *temp_node_next = temp_node->next;

	temp_node->next = new_node;
	new_node->next = temp_node_next;

	return (new_node);
}

/*
 * remove_from_the_middle - removes a node from the middle of a list
 * @head: pointer to the first element of the list we are removing from
 * @removal_index: the index of the node we want to remove
 * Return: the removed node or null on failure
 */
ListNode *remove_from_the_middle(ListNode **head, int removal_index)
{
	/*If the list is empty, return NULL*/
	if (*head == NULL)
		return (NULL);
	/*Check if the removal index is within range*/
	int list_length = get_list_length(head);
	if (removal_index < 0 || removal_index >= list_length)
		return (NULL);

	/*If the removal index is zero, we remove at beginning*/
	if (removal_index == 0)
		return(remove_at_beginning(head));

	/*if removal index is equal to length of list minus 1, remove at end*/
	if (removal_index == list_length - 1)
		return(remove_at_end(head));

	/*Otherwise, get the node at removal index minus 1 and index plus 1
	 * and then change the connections approriately*/
	ListNode *node_before = get_node(head, removal_index - 1);
	ListNode *node_after = get_node(head, removal_index + 1);
	ListNode *removed_node = get_node(head, removal_index);
	node_before->next = node_after;
	removed_node->next = NULL;
	return (removed_node);
}


/*
 * traverse_list - goes through each node in the singly linked list
 * @head: pointer to the first node of the list to traverse
 */
void traverse_list(ListNode **head)
{
	if (*head == NULL)
		printf("There are no nodes to traverse\n");
	ListNode *current = *head;
	while (current != NULL)
	{
		printf("%d -> ", current->value);
		current = current->next;
	}
	printf("NULL\n");
}

int main(void)
{
	printf("===SINGLY LINKED LISTS===\n");
	ListNode *head = NULL;
	append_node_to_list(&head, 10);
	append_node_to_list(&head, 20);
	append_node_to_list(&head, 30);
	append_node_to_list(&head, 40);

	prepend_node_to_list(&head, 5);
	prepend_node_to_list(&head, 3);
	prepend_node_to_list(&head, 2);
	prepend_node_to_list(&head, 0);
       
	remove_at_end(&head);
	remove_at_end(&head);

	remove_at_beginning(&head);
	remove_at_beginning(&head);
	remove_at_beginning(&head);

	ListNode *node = get_node(&head, 1);

	insert_in_the_middle(&head, 3, 0);
	insert_in_the_middle(&head, 4, 1);
	insert_in_the_middle(&head, 15, 4);

	remove_from_the_middle(&head, 3);

	change_node_value(&head, 10, 2);

	traverse_list(&head);
	printf("Length of the list %d\n", get_list_length(&head));
	return (0);
}
