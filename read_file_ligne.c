#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_LENGTH_LINE 256

int main(){
    FILE *ptr_file;
    
    //! open the file 
    ptr_file=fopen("code.txt","r");
    
    if(ptr_file==NULL){
        printf("Problem to open the file");
        return -1;
    }


    char buffer[257];

    while(){

    }





    return 0;
}