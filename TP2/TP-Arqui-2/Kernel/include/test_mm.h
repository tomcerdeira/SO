#ifndef TEST_MM
#define TEST_MM

#include <memory_manager.h>
#include <buddy_system2.h>
#include "test_util.h"
#include <libC.h>
// #define MAX_BLOCKS (int)MAX_MEMORY / BLOCK --> memory manager descomentar

#define MAX_MEMORY 4096 * 5

typedef struct MM_rq
{
  void *address;
  uint32_t size;
} mm_rq;

void test_mm();

#endif