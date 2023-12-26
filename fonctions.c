#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stddef.h>
#include<ctype.h>


char* binary_translate(int numero){
	
	if (numero < 0 || numero > 31) {
        printf("Error: Number out of range for 5-bit representation.\n");
        exit(EXIT_FAILURE);
    }
	char* binaryString = (char*)malloc(6 * sizeof(char));
	 for (int i = 4; i >= 0; i--) {
        int bit = (numero >> i) & 1;
        binaryString[4 - i] = bit + '0'; 
    }
	binaryString[5]='\0';

	return binaryString;
}

char* decToBin16B(int n) {
    static char Imme[17]; 
    char* imme = Imme;

    for (int i = 15; i >= 0; i--) {
        int bit = (n >> i) & 1;
        Imme[15 - i] = bit + '0';  // Convert the bit to character '0' or '1'
    }
    Imme[16] = '\0'; 
    return imme;
}

void hexa(char* code){
    int num=strtol(code,NULL,2);
    char hexadecimal_result[10];
	sprintf(hexadecimal_result, "%x", num);
    printf("0x");
    if(num<16){                 printf("0000000");  }
    else if(num<256){           printf("000000");   }
    else if(num<4096){          printf("00000");    }
    else if(num<65536){         printf("0000");     }
    else if(num<1048576){       printf("000");      }
    else if(num<16777216){      printf("00");       }
    else if (num<268435456){    printf("0");        }

    printf("%s\n",hexadecimal_result);
    
    return;
}

char* upper_bits(double adress){
	char* upper_bits=(char*)malloc(5*sizeof(char));
	char hexadecimal_result[8];
	sprintf(hexadecimal_result, "%lX",(unsigned long) adress);
    
	for(int i=0;i<4;i++){
		upper_bits[i]=hexadecimal_result[i];
	}
	upper_bits[4]='\0';
	return upper_bits;
}

char* lower_bits(double adress){
	char* lower_bits=(char*)malloc(5*sizeof(char));
	char hexadecimal_result[8];
	sprintf(hexadecimal_result, "%lX",(unsigned long) adress);
    
	for(int i=0;i<4;i++){
		lower_bits[i]=hexadecimal_result[i+4];
	}
	lower_bits[4]='\0';
	return lower_bits;
}


char* R_format(char* instruction,char* registers){
	char des[5],src[5],tar[5];
	const char *regdes= des;
	const char *regsrc= src; 
	const char *regtar= tar; 

	if(strcmp(instruction,"jr")==0){
		regsrc=reg_search(registers);
	}
	else {
		sscanf(registers, "%3s,%3s,%3s", regdes, regsrc, regtar);
		regsrc=reg_search(regsrc);
		regdes=reg_search(regdes);
    }

	char reg[32]={};
	char *registre =reg;
	strcat(reg,"000000");	//! op_code 

	if(strcmp(instruction,"sll")==0){
		strcat(reg,"00000");
		strcat(reg,regsrc);  
		strcat(reg,regdes); 
		strcat(reg,binary_translate(atoi(regtar)));
	}
	else if(strcmp(instruction,"jr")==0){
		strcat(reg,regsrc); 
		strcat(reg,"000000000000000"); 
	}
	else{
		regtar=reg_search(regtar);
		strcat(reg,regsrc);
		strcat(reg,regtar);
		strcat(reg,regdes);
		strcat(reg,"00000");
	}

	strcat(reg,R_search(instruction));  //! funct_code
	
	return registre;
}


char* I_format(char* instruction,char* regdes,char* regsrc,char* immed){
	
	char reg[32]={};
	char *registre =reg;	
	
	if(strcmp(instruction,"addi")==0 || strcmp(instruction,"slti")==0){
			strcat(registre,I_search(instruction));
			strcat(registre,reg_search(regsrc));
			strcat(registre,reg_search(regdes));
			strcat(registre,decToBin16B(atoi(immed)));
	}
	else if(strcmp(instruction,"andi")==0 || strcmp(instruction,"ori")==0){
			strcat(registre,I_search(instruction));
			strcat(registre,reg_search(regsrc));
			strcat(registre,reg_search(regdes));
			strcat(registre,decToBin16B(atoi(immed)));
	}
	else if(strcmp(instruction,"lw")==0 || strcmp(instruction,"sw")==0){
		
		if(regsrc[0]=='-' || regsrc[0]=='(' || isdigit(regsrc[0]))
		{
			printf("lw not label\n");
		}
		else printf("lw label\n");
	}
	
	else if(strcmp(instruction,"beq")==0){

	}
	else{
        //! lui
		strcat(registre,I_search(instruction));
		strcat(registre,"00000");
		strcat(registre,reg_search(regdes));
		strcat(registre,decToBin16B(atoi(regsrc)));
	}
	return registre;
}