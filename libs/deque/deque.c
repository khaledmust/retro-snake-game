#include <stdlib.h>
#include "deque.h"

t_deque *dequeInit(void)
{
	t_deque *deque;

	deque = malloc(sizeof(t_deque));
	deque->first = NULL;
	deque->last = NULL;
	return deque;
}

int isEmpty(t_deque *deque)
{
	return !deque->first || !deque->last;
}

void pushFront(t_deque *deque, void *content)
{
	t_deque_node *node = malloc(sizeof(t_deque_node));
	node->content = content;
	node->prev = NULL;
	node->next = deque->first;
	if (isEmpty(deque))
		deque->last = node;
	else
		deque->first->prev = node;
	deque->first = node;
}

void pushBack(t_deque *deque, void *content)
{
	t_deque_node *node = malloc(sizeof(t_deque_node));
	node->content = content;
	node->prev = deque->last;
	node->next = NULL;
	if (isEmpty(deque))
		deque->first = node;
	else
		deque->last->next = node;
	deque->last = node;
}

void *popFront(t_deque *deque)
{
	t_deque_node *node;
	void *content;
	if (isEmpty(deque))
		return NULL;
	node = deque->first;
	deque->first = node->next;
	if (!deque->first)
		deque->last = NULL;
	else
		deque->first->prev = NULL;
	content = node->content;
	free(node);
	return content;
}

void *popBack(t_deque *deque)
{
	t_deque_node *node;
	void *content;
	if (isEmpty(deque))
		return NULL;
	node = deque->last;
	deque->last = node->prev;
	if (!deque->last)
		deque->first = NULL;
	else
		deque->last->next = NULL;
	content = node->content;
	free(node);
	return content;
}

void *peekFront(t_deque *deque)
{
	if(isEmpty(deque))
		return NULL;
	return deque->first->content;
}

void *peekBack(t_deque *deque)
{
	if(isEmpty(deque))
		return NULL;
	return deque->last->content;
}
