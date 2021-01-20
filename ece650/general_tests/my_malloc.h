#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

// void * malloc(size_t size){
//     return sbrk(size);
// }

struct header_t{
    struct header_t *next;
    size_t size;
};
typedef struct header_t header;


header* requestSpace(unsigned nums);
void * ff_malloc(size_t size);

void * bf_malloc(size_t size);
void ff_free(void * ptr);
void bf_free(void * ptr){
  ff_free(ptr);
}