#include <stdio.h>
#include <stdlib.h>
#include "list_t.h"

void init(list_t* l)		//O(1)
{
	l->head = NULL;
	l->tail = NULL;
	l->size = 0;
}

void destroy(list_t* l)		//O(n)
{
	node_t* cur = l->head;
	node_t* perv = NULL;
	while (cur != NULL)
	{
		perv = cur;
		cur = cur->next;
		free(perv);
	}
}

void push_back(list_t* l, int val)	//O(1)
{
	node_t* n;
	node_t* cur;
	n = (node_t*) malloc(sizeof(node_t));
	n->value = val; n->next = NULL;
	if (l->head == NULL)
	{ 
		n->prev = NULL;
		l->head = n;
	}
	else 
	{
		cur = l->tail;
		cur->next = n;
		n->prev = cur;
	}
	l->tail = n;
	++l->size;
}

void print(list_t* l)		//O(n)
{
	node_t*cur = l->head;
	while (cur != NULL)
	{
		printf("%d ", cur->value);
		cur = cur->next;
	}
	printf("\n");
}

int set(list_t* l, int i, int val)	//O(n)
{
	node_t* cur = l->head;
	int count = 0;
	if (i >= 0 && i < l->size)
	{
		while (count++ != i)
			cur = cur->next;
		cur->value = val;
		return 1;
	}
	return 0;
}

int get(list_t* l, int i, int* ans)	//O(n)
{
	node_t* cur = l->head;
	int count = 0;
	if (i >= 0 && i < l->size)
	{
		while (count++ != i)
			cur = cur->next;
		*ans = cur->value;
		return 1;
	}
	return 0;
}

void insert(list_t* l, node_t* cur, int val)	//O(1)
{
	node_t* n = (node_t*) malloc(sizeof(node_t));
	if (cur == l->tail)
		l->tail = n;
	n->value = val;
	n->next = cur-> next;
	n->prev = cur;
	cur->next->prev = n;
	cur->next = n;
	++l->size;
}

void erase(list_t* l, node_t* cur)	//O(1)
{
	if (cur == l->tail)
		l->tail = cur->prev;
	if (cur == l->head)
	{
		l->head = cur->next;
		if (cur->next != NULL) cur->next->prev = NULL; 
		free(cur);
	}
	else
	{
		cur->prev->next = cur->next;
		if (cur->next != NULL) cur->next->prev = cur->prev;
		free(cur);
	}
	--l->size;
}

void push_front(list_t* l, int val)	//O(1)
{
	node_t* n = (node_t*) malloc(sizeof(node_t));
	if (l->tail == l->head)
		l->tail = n;
	n->value = val;
	n->prev = NULL;
	n->next = l->head;
	l->head->prev = n;
	l->head = n;
	++l->size;
}

int find(list_t* l, int val, node_t** n)
{
	node_t* cur = (node_t*) malloc(sizeof(node_t));
	cur->next = l->head;
	cur->prev = NULL;
	cur->value = !(val) ;
	while (cur->value != val && cur->next != NULL)
	{
		cur->value = cur->next->value;
		cur->prev = cur->next->prev;
		cur->next = cur->next->next;
	}
	if (cur->value == val)
	{
		if (!cur->prev)
			*n = l->head;

		else
			*n = cur->prev->next;

		return 1;
	}
	else
	{
		cur->next = NULL;
		cur->value = 0;
		cur->prev = NULL;
		*n = NULL;
	}

	return 0;
}

