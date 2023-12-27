#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stddef.h>
#include<ctype.h>

//! Variables
typedef struct Variable variable;
struct Variable {
    char nom[20];
    double adress;
    variable* suiv;
};
variable* data=NULL;
variable* Insertion_variable(variable* tete,char* nom,double adress){
	variable* new=(variable*)malloc(sizeof(variable));
	
	strcpy(new->nom,nom);
	new->adress=adress;
	new->suiv=tete;
	tete=new;
	return tete;
}
double Var_search(char* nom){
	variable* current =data;
	while (current!=NULL)
	{
		if(strcmp(nom,current->nom)==0) return current->adress;
		else current=current->suiv; 
	}
	return -1;
}
//! labels
typedef struct Label label;
struct Label {
    char nom[20];
    double adress;
    label* suiv;
};
label* labels=NULL;
label* insertion_label(label* tete,char* nom,double adress){
	label* new=(label*)malloc(sizeof(label));
	
	strcpy(new->nom,nom);
	new->adress=adress;
	new->suiv=tete;
	tete=new;
	return tete;
}
double label_search(char* nom){
	label* current =labels;
	while (current!=NULL)
	{
		if(strcmp(nom,current->nom)==0) return current->adress;
		else current=current->suiv; 
	}
	return -1;
}

int compile()
{
    FILE *ptr_file;
    
    ptr_file = fopen("code.txt", "r");
    if (ptr_file == NULL)
    {
        printf("Problem to open the file");
        return -1;
    }
    char buffer[257];
    double Program_counter;
    double data_counter=268500992;
    while (fgets(buffer, 256, ptr_file) != NULL)
    {
        if (buffer[0] == '.')
        {
            if (buffer[1] == 't')
            {
                text :
                Program_counter=4194304;
                continue;
            }
            if (buffer[1] == 'd')
            {   
                while(fgets(buffer, 256, ptr_file) != NULL ){
                
                if(buffer[0]=='.' && buffer[1]=='t') goto text;
                
                char* nom=(char*)malloc(10*sizeof(char));
                char* type=(char*)malloc(10*sizeof(char));
                    //! the variable syntax must be var_name : .type 
                if(sscanf(buffer,"%s : .%s",nom,type)==2){
                    data=Insertion_variable(data,nom,data_counter);
                    
                    if(strcmp(type,"word")==0) data_counter+=4;
                    else if(strcmp(type,"half")==0) data_counter+=2;
                    else if(strcmp(type,"byte")==0) data_counter+=1;
                    else if(strcmp(type,"asciiz")==0) {
                        char* value=(char*)malloc(50*sizeof(char));
                        sscanf(buffer,"%*s : .%*s %[^\n]", value);
                        int len=strlen(value)-1;
                        data_counter+=len;
                    }
                    else if(strcmp(type,"space")==0) {
                        char* value=(char*)malloc(20*sizeof(char));
                        sscanf(buffer,"%*s : .%*s %s", value);
                        int len=atoi(value);
                        data_counter+=len;
                    }      
                }
                }
                continue;
            }
        }
        char registers[20];
        char instruction[20];

        if (sscanf(buffer, "%s", instruction) == 1)
        {
            if(strcmp(R_search(instruction), "null"))
            {
                    Program_counter+=4;
            }
            else if (strcmp(I_search(instruction), "null") || strcmp(instruction,"la")==0)
            {
                    if (sscanf(buffer, "%s %s ", instruction,registers) == 2){
                        char des[10],src[15],imm[15];
                        char *regdes= des;
                        char *regsrc= src;
                        char *immed= imm;
                        sscanf(registers,"%3[^,],%14[^,],%s",regdes,regsrc,immed); 
                        
                        if(strcmp(instruction,"andi")==0 || strcmp(instruction,"ori")==0){
                            if(immed[0]=='-'){
                                Program_counter+=12;
                            }
                            else{
                                Program_counter+=4;
                            }
                        }
                        else if(strcmp(instruction,"lw")==0 || strcmp(instruction,"sw")==0){
                            if(regsrc[0]=='-' || regsrc[0]=='(' || isdigit(regsrc[0]))
                            {   
                                Program_counter+=4;
                            }
                            else{
                                Program_counter+=8;
                            }
                        }
                        else if(strcmp(instruction,"beq")==0){
                                Program_counter+=4;
                        }
                        else if(strcmp(instruction,"la")==0){
                                if(regsrc[0]=='-' || regsrc[0]=='(' || isdigit(regsrc[0])){
                                    if(regsrc[0]=='('){
                                        Program_counter+=4;      
                                    }        
                                    else{
                                        sscanf(registers,"%3[^,],%9[^(](%3[^)]",regdes,immed,regsrc);
                                        if(strcmp(regsrc,immed)==0){
                                        Program_counter+=4;  
                                        }
                                        else{
                                        Program_counter+=8;
                                        }
                                    }
                                }
                                else{
                                    Program_counter+=8;
                                }
                        }
                        else{
                                Program_counter+=4;                            
                        }
                    }
            }
            else if (strcmp(J_search(instruction), "null"))
            {
                    Program_counter+=4;
            }
            else if (!strcmp(instruction, "syscall"))
            {
                    Program_counter+=4;
            }
            else
            {       
                    labels=insertion_label(labels,instruction,Program_counter);
            }
        }
    }
    fclose(ptr_file);

    return 0;
}
