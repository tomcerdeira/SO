#ifndef TEST_MM
#define TEST_MM

#include <memory_manager.h>
#include "test_util.h"
#define MAX_BLOCKS (int)MAX_MEMORY / BLOCK
#define MAX_MEMORY 4096 * 10

typedef struct MM_rq
{
  void *address;
  uint32_t size;
} mm_rq;

void test_mm();

#endif