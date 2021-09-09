#ifndef PQUEUE_N_H
#define PQUEUE_N_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct node {
    struct node *next;
    unsigned int priority;
    void *value;
};

struct pqueue_n{
    struct node *head, *tail;
};

static inline struct pqueue_n *
pqn_create(void)
{
    //Allocate memory for new queue
    struct pqueue_n *new_queue = (struct pqueue_n*)(malloc(sizeof(struct pqueue_n*)));
    //If memory could not be allocated, return NULL
    if (new_queue == NULL) return NULL;

    new_queue->head = NULL;
    new_queue->tail = NULL;

    return new_queue; 
}

static inline int
pqn_delete(struct pqueue_n *pq)
{
    //Check if queue exists
    if (pq != NULL)
    {
        struct node *ptr = pq->head;
        //Check that head is null
        if (ptr == NULL)
        {
            free(pq);
            return 0;
        }
        else return -1;
    } 
    return -1;
}

static inline void 
pqn_enqueue(struct pqueue_n *pq, void *value, unsigned int priority)
{
    struct node *ptr;
    struct node *ptr2;

    ptr = pq->head;

    if(ptr != NULL){
        ptr2 = pq->head->next;
    }
    

    struct node *new_node = (struct node*)(malloc(sizeof(struct node)));

    new_node->value = value;
    new_node->priority = priority;
    new_node->next = NULL;

    //Empty list insertion
    if(ptr == NULL)
    {
        pq->head = new_node;
        pq->tail = new_node;
        return;
    }

    //Head of list if new node is highest priority
    if(ptr->priority > new_node->priority){
        new_node->next = ptr;
        pq->head = new_node;
        return;
    }
 
    //Anywhere in the middle of the list
    while (ptr2 != NULL)
    {
        if(ptr2->priority > new_node->priority)
        {
            new_node->next = ptr2;
            ptr->next = new_node;
            return;
        }
        ptr = ptr->next;
        ptr2 = ptr2->next;
    }
    //Insert at the end of the list
    ptr->next = new_node;
    return;
}

static inline void* 
pqn_dequeue(struct pqueue_n *pq)
{
    if (pq == NULL) return NULL;
    
    struct node *temp;
	void *value;

	if(pq->head != NULL)
	{
        value = pq->head->value;
        temp = pq->head;
        pq->head = pq->head->next;
		free(temp);
		return value;
	}
	else return NULL;
}

#endif /* PQUEUE_N_H */
