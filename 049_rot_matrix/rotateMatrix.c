#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>


int reverse(FILE *f);

int main(int argc, char ** argv){



  if(argc != 2){
    fprintf(stderr,"please indicate the input file");
    return EXIT_FAILURE;
  }

  FILE *f = fopen(argv[1], "r");

  if (f == NULL){
    fprintf(stderr,"count not find the file ");
     return EXIT_FAILURE;
  }
  
 
  reverse(f);

  return 0;
}


int reverse(FILE *f){
  int col = 0;
  int row = 0;
   char arr[10][10];
  char c;
  int count = 0;
 
   while ( (c = fgetc(f)) != EOF ){
     if(c < 0 && c > 255){

      perror("invalid characters");
       exit(EXIT_FAILURE);
     }
     if(row < 10){
     if(c == '\n'){
       if(col != 10){
	  perror("incorrect col");
       exit(EXIT_FAILURE);
       }
       row++;
       col = 0;
	 
	

     }else{
       
     arr[col][9-row] = c;
     col++;
    

     }
     }
 count++;
     
       if(count > 110){
       
	 perror("over rows");
       exit(EXIT_FAILURE);
       }
       
  }  

  
   if(row <= 9){
 perror("less rows");
       exit(EXIT_FAILURE);

   }
//printf("%d\n",count);

   for(int i = 0; i < 10; i++){

     for(int j = 0; j < 10; j++){
       printf("%c", arr[i][j]);
     }
     printf("\n");

   }
   return 0;

  }


