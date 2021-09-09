#include <pqueue_1.h>
#include <pqueue_n.h>
#include <ring.h>
#include <stdio.h>
#include <assert.h>

#define MAX_RING_SIZE 15

struct pqueue_1 *pq1 = NULL;
struct pqueue_n *pqn = NULL;
struct ring *rb = NULL;

void set_up(void)
{
	pq1 = pq1_create();
    pqn = pqn_create();
    rb = rb_create(15);
}

void tear_down(void)
{
	if(pq1)
	{
		pq1_delete(pq1);
		pq1 = NULL;
	}
    if(pqn)
    {
        pqn_delete(pqn);
        pqn = NULL;
    }
    if(rb)
    {
        rb_delete(rb);
        rb = NULL;
    }
}

static void test_pq1_create(void)
{
    pq1 = pq1_create();
    assert(pq1 != NULL);
    assert(pq1_delete(pq1) == 0);
}

static void test_pqn_create(void)
{
    pqn = pqn_create();
    assert(pqn != NULL);
    assert(pqn_delete(pqn) == 0);
}

static void test_rb_create(void)
{
    rb = rb_create(15);
    assert(rb != NULL);
    assert(rb_delete(rb) == 0);
}

static void test_pq1_delete_empty_queue(void)
{
    pq1 = pq1_create();
    assert(pq1_delete(pq1) == 0);
    pq1_delete(pq1);
}

static void test_pqn_delete_empty_queue(void)
{
    pqn = pqn_create();
    assert(pqn_delete(pqn) == 0);
    pqn_delete(pqn);
}

static void test_rb_delete_empty_ring(void)
{
    rb = rb_create(0);
    assert(rb_delete(rb) == 0);
    rb_delete(rb);
}

static void test_pq1_delete_of_filled_queue(void)
{
    void *value;
    unsigned int priority = 0;
    pq1 = pq1_create();
    pq1_enqueue(pq1, &value, priority);
    assert(pq1_delete(pq1) == -1);
    pq1_dequeue(pq1);
    pq1_delete(pq1);
}

static void test_pqn_delete_of_filled_queue(void)
{
    void *value;
    unsigned int priority = 0;
    pqn = pqn_create();
    pqn_enqueue(pqn, &value, priority);
    assert(pqn_delete(pqn) == -1);
    pqn_dequeue(pqn);
    pqn_delete(pqn);
}

static void test_rb_delete_of_filled_ring(void)
{
    void *value;
    rb = rb_create(15);
    rb_enqueue(rb, &value);
    assert(rb_delete(rb) == -1);
    rb_dequeue(rb);
    rb_delete(rb);
}

static void test_pq1_enqueue_and_dequeue_multiple_items(void)
{
    void *value;
    unsigned int priority1 = 0;
    unsigned int priority2 = 2;

    pq1 = pq1_create();

    pq1_enqueue(pq1, &value, priority1);
    pq1_enqueue(pq1, &value, priority2);

    pq1_dequeue(pq1);
    pq1_dequeue(pq1);

    assert(pq1_delete(pq1) == 0);
}

static void test_pqn_enqueue_and_dequeue_multiple_items(void)
{
    void *value;
    unsigned int priority = 15;
    unsigned int priority2 = 0;
    unsigned int priority3 = 2;
    unsigned int priority4 = 7;

    pqn = pqn_create();

    for (int i = priority; i > 0; i--)
    {
        pqn_enqueue(pqn, &value, i);
    }

    pqn_enqueue(pqn, &value, priority2);
    pqn_enqueue(pqn, &value, priority3);
    pqn_enqueue(pqn, &value, priority4);

    for (int i = 0; i < 18; i++)
    {
        value = pqn_dequeue(pqn);
    }

    assert(pqn_delete(pqn) == 0);
}

static void test_rb_enqueue_and_dequeue_multiple_items(void)
{   
    void *value;
    int arr[15];
    rb = rb_create(MAX_RING_SIZE);

    printf("\nValues added: \n");

	for (int i = 0; i < 15; i++)
	{
		//Add elements to linked list
		value = &arr[i];
		printf("%p ", value);
		rb_enqueue(rb, value);
	}

	printf("\n\nValues removed: \n");

	for(int i = 0; i < 15; i++)
	{
		value = rb_dequeue(rb);
		printf("%p ", value);
	}

	printf("\n\n");

	assert(rb_isempty(rb) == 1);
    assert(rb_delete(rb) == 0);
}

static void test_rb_is_empty_returns_true(void)
{
    rb = rb_create(MAX_RING_SIZE);
    assert(rb_isempty(rb) == 1);
    rb_delete(rb);
}

static void test_rb_is_empty_returns_false(void)
{
    void *value;
    rb = rb_create(MAX_RING_SIZE);
    rb_enqueue(rb, &value);
    assert(rb_isempty(rb) == 0  );
    rb_dequeue(rb);
    rb_delete(rb);
}

static void test_rb_is_full_returns_true(void)
{
    void *value;
    int arr[15];
    rb = rb_create(MAX_RING_SIZE);

	for (int i = 0; i < 15; i++)
	{
		//Add elements to linked list
		value = &arr[i];
		rb_enqueue(rb, value);
	}

    assert(rb_isfull(rb) == 1);

    for(int i = 0; i < 15; i++)
	{
		value = rb_dequeue(rb);
	}

	assert(rb_isempty(rb) == 1);
    assert(rb_delete(rb) == 0);

}

static void test_rb_is_full_returns_false(void)
{
    void *value;
    rb = rb_create(MAX_RING_SIZE);
    rb_enqueue(rb, &value);
    assert(rb_isfull(rb) == 0);
    rb_dequeue(rb);
    rb_delete(rb);    
}

int main(void)
{
    test_pq1_create();
    test_pqn_create();
    test_rb_create();
    test_pq1_delete_empty_queue();
    test_pqn_delete_empty_queue();
    test_rb_delete_empty_ring();
    test_pq1_delete_of_filled_queue();
    test_pqn_delete_of_filled_queue();
    test_rb_delete_of_filled_ring();
    test_pq1_enqueue_and_dequeue_multiple_items();
    test_pqn_enqueue_and_dequeue_multiple_items();
    test_rb_enqueue_and_dequeue_multiple_items();
    test_rb_is_empty_returns_true();
    test_rb_is_empty_returns_false();
    test_rb_is_full_returns_true();
    test_rb_is_full_returns_false();

    printf("\nALL TESTS PASSED\n");

    return 0;
}