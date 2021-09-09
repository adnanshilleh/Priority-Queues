#ifndef PQUEUE_1_H
#define PQUEUE_1_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pqueue_n.h>

#define PQ1_LOWEST_PRIORITY 15
#define PQ1_HIGHEST_PRIORITY 0

struct node_1 {
    struct node_1 *next;
    unsigned int priority;
    void *value;
};

struct pqueue_1{
    struct node_1 *head, *tail;
    void *parr[PQ1_LOWEST_PRIORITY];
};

static inline struct pqueue_1 *
pq1_create(void)
{
    //Allocate memory for new queue
    struct pqueue_1 *new_queue = (struct pqueue_1*)malloc(sizeof(struct pqueue_1));
    if(new_queue == NULL) return NULL;

    for (int i = 0; i < PQ1_LOWEST_PRIORITY; i++)
    {
        //Create array of queues for O(1) queue
        new_queue->parr[i] = pqn_create();
    }

    return new_queue;
}

static inline int 
pq1_delete(struct pqueue_1 *pq)
{
    if (pq != NULL)
    {
        if (pq->parr[PQ1_LOWEST_PRIORITY] == NULL)
        {
            for (int i = 0; i < PQ1_LOWEST_PRIORITY; i++)
            {
                pqn_delete(pq->parr[i]);
            }
            free(pq);
            return 0;
        }
        else return -1;
    } 
    return -1;
}

static inline void 
pq1_enqueue(struct pqueue_1 *pq, void *value, unsigned int priority)
{
    //NULL Queue check
    if(pq == NULL) return;
    if(priority > PQ1_LOWEST_PRIORITY) return;

    struct node_1 *new_node = (struct node_1*)malloc(sizeof(struct node_1));

    new_node->value = value;
    new_node->priority = priority;
    
    //Checks if tail is empty
    if(pq->tail == NULL){
        pq->parr[priority] = new_node;
        pq->head = pq->tail = new_node;
        pq->head->next = NULL;
  } else if(pq->tail != NULL){
      //If tail is not empty
      pq->head = pq->parr[priority];
      pq->parr[priority] = new_node;
  } else return;
}

static inline void* 
pq1_dequeue(struct pqueue_1 *pq)
{
    if (pq == NULL) return NULL;
    
    struct node_1 *temp;
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

#endif	/* PQUEUE_1_H */
