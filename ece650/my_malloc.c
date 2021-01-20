#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "my_malloc.h"
void checkFreeBlocks();
/*

struct header_t{
    struct header_t *next;
    size_t size;
};
typedef struct header_t header;
*/
#define MIN_ALLOCATE 10
static header start;
static header *freeHeader = NULL;
static header *from;
static header *to;
static header *preFreeHeader;
static header *currFreeHeader;


void checkMerge(){

  header* temp = freeHeader->next;
  while(temp != NULL && temp->next != NULL){
    while(temp + temp->size == temp->next){
      //printf("merge\n");
      temp->size += temp->next->size;
      temp->next = temp->next->next;
      if(temp->next == NULL){
        break;
      }
    }
    temp = temp->next;
  }
}

header* requestSpace(size_t nums){
    size_t allocate = MIN_ALLOCATE > nums ? MIN_ALLOCATE : nums;
    header *p = sbrk(allocate * sizeof(header));
    to = p + nums;
    if(p == (void*) -1){
        return NULL;
    }
    p->next = NULL;
    p->size = nums;
    preFreeHeader->next = p;
    //tail->next = p;
    return p;
}

void * ff_malloc(size_t size){
    if(size == 0){
        return NULL;
    }
    
    if(freeHeader == NULL){
        freeHeader = &start;
        start.next = NULL;
        start.size = 0;
        from = sbrk(0);
        to = sbrk(0);
        printf("FF\n");
    }
    //printf("maloc\n");
     //checkFreeBlocks();
    unsigned nums = 1 + size / sizeof(header);
    if(size > (nums - 1) * sizeof(header)){
        ++nums;
    }
    //printf("request %d\n", nums);
    preFreeHeader = freeHeader;
    currFreeHeader = freeHeader->next;
   
    while(1){
        if(currFreeHeader == NULL){
            currFreeHeader = requestSpace(nums);
            //printf("request space");
            if(currFreeHeader == NULL){
                //fprintf(stderr, "np space");
                return NULL;
            }
            //currFreeHeader->next = currFreeHeader + 1;
            //return (void *)(currFreeHeader + 1);
        }
        if(nums == currFreeHeader->size){
            //printf("request size equals to free blocks\n");
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
        preFreeHeader = currFreeHeader;
        currFreeHeader = currFreeHeader->next;

    }
   
}

void * bf_malloc(size_t size){
    //printf("malloc\n");
    if(freeHeader == NULL){
        freeHeader = &start;
        start.next = NULL;
        start.size = 0;
        printf("BF\n");
    }
    //printf("BF\n");
    //checkFreeBlocks();
    unsigned nums = 1 + size / sizeof(header);
    if(size > (nums - 1) * sizeof(header)){
        ++nums;
    }
    //printf("request %d\n", nums);
    preFreeHeader = freeHeader;
    currFreeHeader = freeHeader->next;
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
        size_t currSize = currFreeHeader->size;
        if(currSize == nums){
            bestPreFreeHeader = preFreeHeader;
            bestFreeHeader = currFreeHeader;
            difference = 0;
            break;
        }
        if(currSize > nums && (currSize - nums) < difference){
            bestPreFreeHeader = preFreeHeader;
            bestFreeHeader = currFreeHeader;
            difference = currSize - nums;
        }
        preFreeHeader = currFreeHeader;
        currFreeHeader = currFreeHeader->next;
    }

    if(bestFreeHeader == NULL){
        bestFreeHeader = requestSpace(nums);
        bestPreFreeHeader = preFreeHeader;
        
        if(bestFreeHeader == NULL){
            return NULL;
        }
        //bestFreeHeader->size = nums;
        //bestFreeHeader->next = bestFreeHeader + 1;
        //return (void *)(bestFreeHeader + 1);
        difference = bestFreeHeader->size - nums;
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
    // printf("free\n");
    header * temp = (header*) ptr;
    header *hp = temp - 1;
    //printf("free size is %ld\n", hp->size);
    if(hp < from || hp >= to || (hp + 1) != hp->next ){
        //printf("from %p to %p, %p\n", from, to, hp);
        fprintf(stderr, "invalid free\n");
        exit(EXIT_FAILURE);
    }
    header *currFree = freeHeader->next;
    if(currFree == NULL){
        
        freeHeader->next = hp;
        hp->next = NULL;
       // printf("freeHeader is null\n");
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
                //printf("A\n");
            }
            return;
        }
        if(currFree < hp && hp < currFree->next){
            //if(currFree + currFree->size == hp && hp + hp->size == currFree->next){
              //  currFree->size = hp->size + currFree->next->size;
                //currFree->next = currFree->next->next;
            //}else 
            int flag = 0;
            if(currFree + currFree->size == hp){
                currFree->size += hp->size;
                hp = currFree;
                ++flag;
            }
            if(hp + hp->size == currFree->next){
                ++flag;
                hp->size += currFree->next->size;
                hp->next = currFree->next->next;
                if(currFree != hp){
                  currFree->next = hp;
                }
            }
            if(flag == 0){
                hp->next = currFree->next;
                currFree->next = hp;
            }
            return;
        }
        currFree = currFree->next;
    }
}

void checkFreeBlocks(){
  header * temp = freeHeader;
  while(temp!=NULL){
    printf("free block size is %ld\n", temp->size);
    temp = temp->next;
  }

}

unsigned long get_largest_free_data_segment_size(){
    header *curr = freeHeader;
    unsigned long maxSize = 0;
    while(curr != NULL){
        maxSize = maxSize > curr->size ? maxSize : curr->size;
        curr = curr->next;
    }
    return  (maxSize - 1) * sizeof(header) ;
}

unsigned long get_total_free_size(){
    header *curr = freeHeader;
    unsigned long totalSize = 0;
    while(curr != NULL){
        totalSize = totalSize + curr->size - 1;
        curr = curr->next;
    }
    return totalSize * sizeof(header);
}

int main(){
  int i = 0;
  printf("%p\n", sbrk(2));
  printf("%p\n", sbrk(2));
  printf("%p\n", sbrk(2));
  printf("%p\n", sbrk(2));
  printf("%p\n", sbrk(2));
  return 0;
  

}



