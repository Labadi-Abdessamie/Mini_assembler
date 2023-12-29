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
        Imme[15 - i] = bit + '0';
    }
    Imme[16] = '\0'; 
    return imme;
}
int binaryToDecimal(char* binaryString) {
    int decimal = 0;
    int length = strlen(binaryString);

    for (int i = length - 1, j = 0; i >= 0; i--, j++) {
        if (binaryString[i] == '1') {
            decimal += (1 << j);
        }
    }
    return decimal;
}

char* hexa(char* bin_value) {
	char* hex_value=(char*)malloc(11*sizeof(char));
	long decimal_value = strtoul(bin_value, NULL, 2);
    snprintf(hex_value, 11, "0x%08lx", decimal_value);
    return hex_value;
}

unsigned int hexToDecimal(char *hexValue) {
    return (unsigned int)strtol(hexValue, NULL, 16);
}

char* decimalToBinary26Bits(double decimalValue) {
	char *binaryString=(char*)malloc(27*sizeof(char));
	unsigned long long intVal = (unsigned long long)decimalValue;
    int remainingBits = 26;

    for (int i = 25; i >= 0; --i) {
        binaryString[i] = (intVal & 1) + '0';
        intVal >>= 1;
        remainingBits--;
    }
    while (remainingBits > 0) {
        binaryString[remainingBits - 1] = '0';
        remainingBits--;
    }
    binaryString[26] = '\0';
	return binaryString;
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
			strcat(registre,I_search(instruction));
			if(strcmp(reg_search(regsrc),"null")==0)
			strcat(registre,"00000");
			else 
			strcat(registre,reg_search(regsrc));
			strcat(registre,reg_search(regdes));
			strcat(registre,decToBin16B(atoi(immed)));
	}
	else if(strcmp(instruction,"beq")==0){
			strcat(registre,I_search(instruction));
			strcat(registre,reg_search(regdes));
			strcat(registre,reg_search(regsrc));
			strcat(registre,decToBin16B(atoi(immed)));
	}
	else if(strcmp(instruction,"addiu")==0){
			strcat(registre,"001001");
			strcat(registre,regsrc);
			strcat(registre,reg_search(regdes));
			strcat(registre,decToBin16B(atoi(immed)));
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

char* J_format(char* instruction,char* adress){
	char reg[32]={};
	char *registre =reg;
	strcat(registre,J_search(instruction));
	strcat(registre,adress);
	return registre;
}

void Out(char* code ,double prg_cntr,FILE* out){
	char hexa_program_counter[11];
	sprintf(hexa_program_counter, "0x%08lX",(unsigned long) prg_cntr);
	fputs(hexa_program_counter,out);
	fputs(" : ",out); 
	fputs(code,out);
	fputs("\n",out);
}	