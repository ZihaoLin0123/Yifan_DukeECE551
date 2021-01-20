#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "my_malloc.h"

/*

struct header_t{
    struct header_t *next;
    size_t size;
};
typedef struct header_t header;
*/
static header start;
static header *freeHeader = NULL;
static header *from;
static header *to;

header* requestSpace(unsigned nums){
    header *p = sbrk(nums * sizeof(header));
    to = p;
    if(p == (void*) -1){
        return NULL;
    }
    p->next = NULL;
    p->size = nums;
    //tail->next = p;
    return p;
}

void * ff_malloc(size_t size){
    if(freeHeader == NULL){
        freeHeader = &start;
        start.next = NULL;
        start.size = 0;
        from = sbrk(0);
        to = sbrk(0);
    }
    unsigned nums = 1 + size / sizeof(header);
    if(size > (nums - 1) * sizeof(header)){
        ++nums;
    }
    header *preFreeHeader = freeHeader;
    header *currFreeHeader = freeHeader->next;
   
    while(1){
        if(currFreeHeader == NULL){
            currFreeHeader = requestSpace(nums);
            if(currFreeHeader == NULL){
                return NULL;
            }
            //preFreeHeader->next = currFreeHeader;
            currFreeHeader->next = currFreeHeader + 1;
            return (void *)(currFreeHeader + 1);
        }
        if(nums == currFreeHeader->size){
            preFreeHeader->next = currFreeHeader->next;
            currFreeHeader->next = currFreeHeader + 1;
            return (void *)(currFreeHeader + 1);
        }else if(nums < currFreeHeader->size){
            currFreeHeader->size -= nums;
            currFreeHeader += currFreeHeader->size;
            currFreeHeader->size = nums;
            currFreeHeader->next = currFreeHeader + 1;
            return (void *)(currFreeHeader + 1);
        }
        preFreeHeader = currFreeHeader->next;
        currFreeHeader = currFreeHeader->next;

    }
   
}

void * bf_malloc(size_t size){
    if(freeHeader == NULL){
        freeHeader = &start;
        start.next = NULL;
        start.size = 0;
    }
    unsigned nums = 1 + size / sizeof(header);
    if(size > (nums - 1) * sizeof(header)){
        ++nums;
    }
    header *preFreeHeader = freeHeader;
    header *currFreeHeader = freeHeader->next;
    header *bestPreFreeHeader = NULL;
    header *bestFreeHeader = NULL;
    size_t difference = 0xFFFFFFFF;
    // if(currFreeHeader == NULL){
    //     currFreeHeader = requestSpace(nums, NULL);
    //     if(currFreeHeader == NULL){
    //         return NULL;
    //     }
    //     currFreeHeader->size = nums;
    //     currFreeHeader->next = currFreeHeader + 1;
    //     return (void *)(currFreeHeader + 1);
    // }
    while(currFreeHeader != NULL){
        if(currFreeHeader->size >= nums && (currFreeHeader->size - nums) < difference){
            bestPreFreeHeader = preFreeHeader;
            bestFreeHeader = currFreeHeader;
            difference = currFreeHeader->size - nums;
        }
        preFreeHeader = currFreeHeader->next;
        currFreeHeader = currFreeHeader->next;
    }

    if(bestFreeHeader == NULL){
        bestFreeHeader = requestSpace(nums);
        if(bestFreeHeader == NULL){
            return NULL;
        }
        bestFreeHeader->size = nums;
        bestFreeHeader->next = bestFreeHeader + 1;
        return (void *)(bestFreeHeader + 1);
    }

    if(difference == 0){
        bestPreFreeHeader->next = bestFreeHeader->next;
        bestFreeHeader->next = bestFreeHeader + 1;
        return (void *)(bestFreeHeader + 1);
    }else{
        bestFreeHeader->size -= nums;
        bestFreeHeader += bestFreeHeader->size;
        bestFreeHeader->size = nums;
        bestFreeHeader->next = bestFreeHeader + 1;
        return (void *)(bestFreeHeader + 1);
    }
    
    
}

void ff_free(void * ptr){
    header *hp = (header*)(ptr) - 1;
    if(hp < from || hp > to || hp->next != (hp + 1)){
        fprintf(stderr, "invalid free");
        exit(EXIT_FAILURE);
    }
    header *currFree = freeHeader->next;
    if(currFree == NULL){
        freeHeader->next = hp;
        hp->next = NULL;
        return;
    }
    while(currFree != NULL){
        if(hp < currFree){
            if(hp + hp->size == currFree){
                hp->size += currFree->size;
                freeHeader->next = hp;
                hp->next = currFree->next;
            }else{
                freeHeader->next = hp;
                hp->next = currFree;
            }
            return;
        }
        if(currFree < hp && currFree->next == NULL){
            if(currFree + currFree->size == hp){
                currFree->size += hp->size;
            }else{
                currFree->next = hp;
                hp->next = NULL;
            }
            return;
        }
        if(currFree < hp && hp < currFree->next){
            if(currFree + currFree->size == hp && hp + hp->size == currFree->next){
                currFree->size = hp->size + currFree->next->size;
                currFree->next = currFree->next->next;
            }else if(currFree + currFree->size == hp){
                currFree->size += hp->size;
            }else if(hp + hp->size == currFree->next){
                hp->size += currFree->next->size;
                hp->next = currFree->next->next;
                currFree->next = hp;
            }else{
                hp->next = currFree->next;
                currFree->next = hp;
            }
            return;
        }
        currFree = currFree->next;
    }
}

