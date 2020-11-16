#include "function.h"

int binarySearchForZero(Function<int, int> * f, int low, int high){
        int mid = low + (high - low) / 2;
        int target = f->invoke(mid);
        if(low == high){
            if (target == 0){
                return mid;
            }else if(target > 0){
                return low;
            }else{
                return high - 1;
            }
        }
        if (target == 0){
            return mid;
        }else if(target > 0){
            return binarySearchForZero(f, low, mid - 1);
        }else{
            return binarySearchForZero(f, mid + 1, high);
        }
    }
