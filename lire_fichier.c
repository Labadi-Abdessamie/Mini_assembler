#include<stdio.h>
#include<stdlib.h>
#include<string.h>



int main(){
    FILE *ptr_file;
    
    //! open the file 
    ptr_file=fopen("code_test.txt","r");
    
    if(ptr_file==NULL){
        printf("Problem to open the file");
        return -1;
    }

    char buffer[100];
    int begin=1;

    while(fgets(buffer,2,ptr_file)!=NULL)
        {
            //! The case of the assembler directive (will be in the beginning of the line then '.')
            if(begin==1){

                if(!strcmp(buffer,".")){
                    while(fgets(buffer,2,ptr_file)!=NULL && strcmp(buffer,"\n")){
                    }
                    fgets(buffer,2,ptr_file);
                }
            }
                //? the case of the comment 
                if(!strcmp(buffer,"#")){
                    while(fgets(buffer,2,ptr_file)!=NULL && strcmp(buffer,"\n")){
                    }
                }

            printf("%s",buffer);
            if(!strcmp(buffer,"\n")) begin=1;   //! here linked with the directives to know that we are in newLine 
            else begin=0;
        }

    return 0;
}