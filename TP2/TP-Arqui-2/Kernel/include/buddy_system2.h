// #ifndef BUDDY
// #define BUDDY

// #include <libC.h>
// #include <consoleManager.h>

// #define MAX_HEIGHT 14

// #define MEMORY_SIZE 4096 * 16
// #define SMALLEST_BLOCK_SIZE 4

// #define MAX_BLOCKS 32767

// typedef struct
// {
//     int id;
//     int isSplited; //1 YES - 0 NO
//     char *startOfMemoryAddress;
//     int sizeOfMemory;
//     int sizeOfMemoryFree;
//     struct node *leftN;
//     struct node *rightN;
// } node;

// void initializeMemory();
// node * initMemoryRec(char *memoryAddress, int memorySize, int height);
// void *mallocNUESTRO(int size);
// int getMinBlockSize(int sizeOfMemoryRequested);
// void *searchMemoryRec(node *n, int sizeRequired);
// void freeMemory(char *ptr);
// int freeMemoryRec(node * n, char * ptr);
// int getTotalMemorySize();
//  int getMemoryAvailable();
//  int getMemoryUsed();
//  void *memsetNUESTRO(char *ptr, int toWrite, int size);
//  void getMemoryInfo(char *buffer);

// #endif