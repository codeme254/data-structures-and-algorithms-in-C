#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
/*
 * Another flavor of implementation for singly linked list
 * Here, we keep track of the list
 */

/*
 * ListNode - structure of a single node in the list
 * @value: the value held by that node
 * @next: a pointer to a node similar to ListNode
 */
typedef struct ListNode{
	int value;
	struct ListNode *next;
} ListNode;

/*
 * SinglyLinkedList - structure of a singly linked list
 * @head: first node in the list
 * @tail: last node in the list
 * @length: number of nodes in the list
 */
typedef struct SinglyLinkedList{
	ListNode *head;
	ListNode *tail;
	int length;
} SL_List;

/*
 * INITIALIZE_NODE - reusable function to initialize a node
 * @value: the value of the new node
 * Return: the initialized node or null on failure
 */
ListNode *INITIALIZE_NODE(int value)
{
	ListNode *new_node = malloc(sizeof(ListNode));
	if (new_node == NULL)
		return (NULL);
	new_node->value = value;
	new_node->next = NULL;
	return (new_node);
}

/*
 * reset_list - resets a lists back to its defaults
 * @list: the list to be reset
 * Description: resets the head and tail to NULL and length to 0*/
void reset_list(SL_List *list)
{
	list->head = NULL;
	list->tail = NULL;
	list->length = 0;
}

/*
 * push - adds a new node to the end of a given list
 * @list: the list to which we are adding the new node
 * @new_node_value: the value of the new node we are adding to the list
 * Return: the updated node or NULL on failure
 */
ListNode *push(SL_List *list, int new_node_value)
{
	ListNode *new_node = INITIALIZE_NODE(new_node_value);
	if (new_node == NULL)
		return (NULL);
	/*If the list is empty, make this node the head and the tail*/
	if (!list->head || list->length == 0)
	{
		list->head = new_node;
		list->tail = new_node;
	} else {
		/*
		 * If the list has elements, then
		 * make the current tail to point to the new node
		 * then make the new node the tail
		 */
		list->tail->next = new_node;
		list->tail = new_node;
	}
	/*Whichever path taken, increase the length and return the new node*/
	list->length++;
	return (new_node);
}

/*
 * pop - removes the last node of a list
 * @list: the list from which the last node is being removed
 * Return: the removed node or NULL if there are no nodes
 */
ListNode *pop(SL_List *list)
{
	/*If there are no elements in the lis, return NULL*/
	if (!list->head || list->length == 0)
		return (NULL);
	/*Use two pointers to removed the last node*/
	ListNode *tmp_pointer = list->head;
	ListNode *current_pointer = list->head;
	/*If the list has only one element, after removing it, the list will be empty
	 * so we reset it*/
	if (list->length == 1)
	{
		reset_list(list);
		return (current_pointer);
		/*TODO: free the memory*/
	}
	/*Otherwise, we will work with the two pointer algorithm to get the last node*/
	while (current_pointer->next != NULL)
	{
		tmp_pointer = current_pointer;
		current_pointer = current_pointer->next;
	}
	tmp_pointer->next = NULL;
	list->length--;
	list->tail = tmp_pointer;
	return (current_pointer);
}

/*
 * unshift - adds a new node to the start of the list
 * @list: the list to which the new node is being added
 * @new_node_value: the value to be held by the new node
 * Return: the new node or NULL on failure
 */
ListNode *unshift(SL_List *list, int new_node_value)
{
	ListNode *new_node = INITIALIZE_NODE(new_node_value);
	if (new_node == NULL)
		return (NULL);
	/*If the list is empty, this node becomes the head and the tail*/
	if (!list->head || list->length == 0)
	{
		list->head = new_node;
		list->tail = new_node;
	} else {
		/*Make the new node point to the current head*/
		/*Make the new node the new head of the list*/
		new_node->next = list->head;
		list->head = new_node;
	}
	/*update the length and return the added node*/
	list->length++;
	return (new_node);
}

/*
 * shift - removes the first node of a list
 * @list: the list from which the first node is being removed
 * Return: the removed node or null on failure
 */
ListNode *shift(SL_List *list)
{
	/*If there are no elements in the list, return NULL*/
	if (!list->head || list->length == 0)
		return (NULL);
	/*Save the first element in a variable*/
	ListNode *current_first = list->head;
	/*If the list has a length of 1, reset it and return the removed element*/
	if (list->length == 1)
	{
		reset_list(list);
		return (current_first);
		/*TODO: free the memory*/
	}
	/*Otherwise, set the head to be next of the current head*/
	/*Then set the next of the being removed head to NULL*/
	/*Reduce the length by 1 and return it*/
	list->head = current_first->next;
	current_first->next = NULL;
	list->length--;
	return (current_first);
	/*TODO: free the memory*/
}

/*
 * get_node - finds a node in the list and returns it
 * @list: the list from which we are querying the node
 * @index: the index of the node we want to get
 * Return: the node if it is there or NULL if it is not there
 * Description: uses zero based indexing, first element has index 0
 * and last element has index length_of_its_list - 1
 */
ListNode *get_node(SL_List *list, int index)
{
	/*If there are no elements in the list, return NULL regardless*/
	if (!list->head || list->length == 0)
		return (NULL);
	/*Check if the index is within ranges, return NULL if not*/
	if (index < 0 || index >= list->length)
		return (NULL);
	/*If the index is zero, return the first element*/
	if (index == 0)
		return (list->head);
	/*If the index is equal to length_of_list - 1, return the last element*/
	if (index == list->length - 1)
		return (list->tail);
	/*Otherwise, loop till you get the element*/
	int i = 0;
	ListNode *current_node = list->head;
	while (i < index)
	{
		current_node = current_node->next;
		i++;
	}
	return (current_node);
}

/*
 * update_node - updates the node of a list
 * @list: the list in which the node is being updated
 * @new_node_value: the new value of the node to be updated
 * @index: the index of the node in a list
 */
ListNode *update_node(SL_List *list,int index, int new_node_value)
{
	ListNode *node_to_update = get_node(list, index);
	if (node_to_update == NULL)
		return (NULL);
	node_to_update->value = new_node_value;
	return (node_to_update);
}

/*
 * insert_middle - inserts a node in the middle of a list
 * @list: the list in which the node is to be inserted
 * @index: the index to insert the node
 * @node_value: the value of the new node to be inserted
 * Return: the inserted node or NULL on failure
 */
ListNode *insert_middle(SL_List *list, int index, int node_value)
{
	/*If the index is outside range, return NULL*/
	if (index < 0 || index >= list->length)
		return (NULL);
	/*If the index is 0, insert at the beginning*/
	if (index == 0)
		return (unshift(list, node_value));
	/*If the index is equal to length-1 insert at the end*/
	if (index == list->length - 1)
		return (push(list, node_value));
	/*Use get_node method to get_node to get the node before the insert index*/
	/*Make it point to the new_node*/
	/*Make the new node point to what the other node was pointing to*/
	ListNode *new_node = INITIALIZE_NODE(node_value);
	if (new_node == NULL)
		return (NULL);
	ListNode *node_before = get_node(list, index - 1);
	ListNode *tmp_next = node_before->next;
	node_before->next = new_node;
	new_node->next = tmp_next;
	list->length++;
	return (new_node);
}

/*
 * remove_from_middle - removes a node from the middle of a list
 * @list: the list from which a node is being removed at the middle
 * @index: the index of the node to be removed
 * Return: the removed node or null on failure
 */
ListNode *remove_from_middle(SL_List *list, int index)
{
	/*If the list is empty, return NULL*/
	if (!list->head || list->length == 0)
		return (NULL);
	/*validate the index*/
	if (index < 0 || index >= list->length)
		return (NULL);
	/*If the index is 0, shift*/
	if (index == 0)
		return (shift(list));
	/*If the index equal to length - 1, pop*/
	if (index == list->length - 1)
		return (pop(list));
	/*Get the node to be removed, the node before and the node after*/
	ListNode *node_to_be_removed = get_node(list, index);
	ListNode *node_before = get_node(list, index - 1);
	ListNode *node_after = get_node(list, index + 1);

	/*Make the node before to point to the node after*/
	/*Make the node to be removed's next to be NULL*/
	/*Reduce the length and return the removed node*/
	node_before->next = node_after;
	node_to_be_removed->next = NULL;
	list->length--;
	return (node_to_be_removed);
}

/*
 * traverse - goes through the list printing each element
 * @list: the list being traversed
 * Return: 0 in case the list has no elements or 1 if the list has been successfully traversed*/
int traverse(SL_List *list)
{
	if (!list->head || list->length == 0)
		return (0);
	ListNode *current = list->head;
	while (current != NULL)
	{
		printf("%d -> ", current->value);
		current = current->next;
	}
	printf("NULL\n");
}

int main()
{
	printf("Singly Linked List flavor 2\n");
	SL_List *list = malloc(sizeof(SL_List));
	if (list == NULL)
	{
		printf("Cannot create list\n");
		return (1);
	}
	push(list, 10);
	push(list, 20);
	push(list, 30);
	push(list, 40);
	push(list, 50);
	push(list, 60);
	push(list, 70);
	push(list, 80);

	pop(list);

	unshift(list, 5);
	unshift(list, 3);

	shift(list);
	shift(list);

	update_node(list, 2, 25);

	printf("Node at idx 0 is: %d\n", get_node(list, 0)->value);
	printf("Node at idx 4 is: %d\n", get_node(list, 4)->value);

	insert_middle(list, 3, 35);
	insert_middle(list, 0, 5);

	remove_from_middle(list, 0);
	remove_from_middle(list, 7);
	remove_from_middle(list, 2);
	traverse(list);


	printf("==LIST INFO==\n");
	printf("First Node: %d\n", list->head->value);
	printf("Last Node: %d\n", list->tail->value);
	printf("Length of the list: %d\n", list->length);
	return (0);
}
