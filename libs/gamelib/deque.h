#ifndef DEQUE_H
# define DEQUE_H

typedef struct s_deque_node {
	void *content;
	struct s_deque_node *next;
	struct s_deque_node *prev;
} t_deque_node;

typedef struct s_deque {
	struct s_deque_node *first;
	struct s_deque_node *last;
} t_deque;

t_deque *dequeInit(void);
int isEmpty(t_deque *deque);
void pushFront(t_deque *deque, void *content);
void pushBack(t_deque *deque, void *content);
void *popFront(t_deque *deque);
void *popBack(t_deque *deque);
void *peekFront(t_deque *deque);
void *peekBack(t_deque *deque);

#endif
