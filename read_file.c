#include<stdio.h>
#include<stdlib.h>
#include<string.h>


int main(){
    FILE *ptr_file;
    
    //! open the file 
    ptr_file=fopen("code.txt","r");
    
    if(ptr_file==NULL){
        printf("Problem to open the file");
        return -1;
    }

    char buffer;
    int begin=1;

    while((buffer=fgetc(ptr_file))!=EOF)
        {
            //! The case of the assembler directive (will be in the beginning of the line then '.')
            if(begin==1){

                if(buffer=='.'){
                    while((buffer=fgetc(ptr_file))!=EOF && buffer!='\n'){
                    }
                    buffer=fgetc(ptr_file);
                }
            }
                //? the case of the comment 
                if(buffer=='#'){
                    while((buffer=fgetc(ptr_file))!=EOF && buffer!='\n'){
                    }
                }

            printf("%c",buffer);
            if(buffer=='\n') begin=1;   //! here linked with the directives to know that we are in newLine 
            else begin=0;
        }
    
    printf("\n");
    system("pause");
    return 0;
}