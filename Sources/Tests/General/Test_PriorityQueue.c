#include "General/PriorityQueue.h"
#include "unity.h"
#include "unity_fixture.h"
#include <stdlib.h>

TEST_GROUP(PriorityQueue);

TEST_SETUP(PriorityQueue)
{
}

TEST_TEAR_DOWN(PriorityQueue)
{
}

TEST(PriorityQueue, PriorityQueue_Tests)
{
  int i, p;
  const char *c, *tasks[] ={
    "Clear drains", "Feed cat", "Make tea", "Solve libafis", "Tax return" };
  int pri[] = { 3, 4, 5, 1, 2 };
 
  /* make two queues */
  Queue* q = priq_new(0);
  Queue* q2 = priq_new(0);
 
  /* push all 5 tasks into q */
  for (i = 0; i < 5; i++)
    priq_push(q, (void*)tasks[i], pri[i]);
 
  // pop them and assert
  c = priq_pop(q, &p);
  TEST_ASSERT_EQUAL_STRING("Solve libafis", c);
  c = priq_pop(q, &p);
  TEST_ASSERT_EQUAL_STRING("Tax return", c);
  c = priq_pop(q, &p);
  TEST_ASSERT_EQUAL_STRING("Clear drains", c);
  c = priq_pop(q, &p);
  TEST_ASSERT_EQUAL_STRING("Feed cat", c);
  c = priq_pop(q, &p);
  TEST_ASSERT_EQUAL_STRING("Make tea", c); 

  TEST_ASSERT_EQUAL(0, priq_size(q));
  
  // put a million random tasks in each queue
  for (i = 0; i < 1 << 20; i++) {
    p = rand() / ( RAND_MAX / 5 );
    priq_push(q, (void*)tasks[p], pri[p]);
 
    p = rand() / ( RAND_MAX / 5 );
    priq_push(q2, (void*)tasks[p], pri[p]);
  }

  TEST_ASSERT_EQUAL(1 << 20, priq_size(q));
  TEST_ASSERT_EQUAL(1 << 20, priq_size(q2));
 
  // merge q2 into q; q2 is empty 
  priq_combine(q, q2);
  TEST_ASSERT_EQUAL(2 * (1 << 20), priq_size(q));
  TEST_ASSERT_EQUAL(0, priq_size(q2));
  
  // pop q until it's empty
  for (i = 0; (c = priq_pop(q, 0)); i++);

  TEST_ASSERT_EQUAL(2097152, i);
}
