#ifndef RING_H
#define RING_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct ring {
    size_t head;
    size_t tail;
    size_t num_items; //size
    size_t current_items; //current number that are in ring buffer
    void **value;
};

static inline struct ring * 
rb_create(size_t num_items)
{
    struct ring* rb;
    rb = (struct ring*)(malloc(sizeof(struct ring)));
    
    if(rb == NULL){
        return NULL;
    }else {
        rb->tail = 0;
        rb->head = 0;
        rb->current_items = 0;
        rb->num_items = num_items;
        rb->value = (void*)(malloc(sizeof(void*)*(num_items)));

        return rb;
    }
}

static inline int 
rb_isempty(struct ring *rb)
{
    if (rb == NULL)
    {
        return -1;
    }else if(rb->current_items == 0){
        return 1;
    }else {
        return 0;
    }
}

static inline int 
rb_isfull(struct ring *rb)
{
    if(rb == NULL){
        return -1;
    }else if(rb->current_items == rb->num_items){
        return 1;
    }else {
        return 0;
    }
}

static inline int 
rb_delete(struct ring *rb)
{
   if (rb_isempty(rb) == 1)
   {
       free(rb->value);
       free(rb);
       return 0;
   } else return -1;
}

static inline int 
rb_enqueue(struct ring *rb, void *value)
{
    if (rb == NULL || rb_isfull(rb) == 1){
			return -1;
		}else {
            rb->value[rb->tail] = value;
            rb->tail = (rb->tail + 1) % rb->num_items; 
		    rb->current_items++;
		    return 0;
		}
}

static inline void* 
rb_dequeue(struct ring *rb)
{
    void *value;

    if (rb == NULL){
        printf("\nIm here\n");
		return 0;
	}else if (rb_isempty(rb) == 1){
        printf("\nImhere\n");
		return NULL;
	}else{
		// first capture the item
        value = rb->value[rb->head];
		rb->head = (rb->head + 1) % rb->num_items;
		// decrease size by 1
		rb->current_items--;

		return value;
	}
}

static inline size_t 
rb_size(struct ring *rb)
{
    if (rb == NULL)
    {
        return 0;
    } else {
        return rb->current_items;
    }
}

#endif	/* RING_H */
