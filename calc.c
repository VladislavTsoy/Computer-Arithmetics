#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int toDecimal(char *numVal, int base);
int conversion(char ch);
char* fromDecimal(char result[], int base, int convNum);
char reConv(int value);
void reverseVal(char *numVal);


//takes input calc <op> <number1> <number2> <output base>
//takes two arguments (number1, number2 in the form of (b|o|d|x|num...) 
//calculates based on op(+|-|*)
//outputs based on output base(b|o|d|x)
int main( int argc, char **argv )  {
   if( argc != 5 ) {
      fprintf(stderr, "ERROR, invalid number of arguments!" );
      return 0;
   }
   
    char *op = argv[1];
    char *num1 = argv[2];
    char *num2 = argv[3];
    char *output = argv[4];

    int neg1 = 1;
    int neg2 = 1;
    int sum, number1, number2;

    //checks for negative number
    if(num1[0] == '-') {
    
    	num1 = &num1[1];
    	neg1 = -1;
    }
    if(num2[0] == '-') {
    
    	num2 = &num2[1];
    	neg2 = -1;
    }

    //checks the base for numbers and calls funtions for conversion
    if(num1[0] == 'd') {
    	num1 = &num1[1];
    	number1 = toDecimal(num1, 10);
    	
    } else if(num1[0] == 'x') {
    	num1 = &num1[1];
    	number1 = toDecimal(num1, 16);


    } else if(num1[0] == 'o') {
    	num1 = &num1[1];
    	number1 = toDecimal(num1, 8);

    } else if(num1[0] == 'b'){
    	num1 = &num1[1];
    	number1 = toDecimal(num1, 2);
    } else {
    	fprintf(stderr, "ERROR, invalid argument!");
    }
	number1 = number1 * neg1;  


    if(num2[0] == 'd') {
    	num2 = &num2[1];
    	number2 = toDecimal(num2, 10);
    } else if(num2[0] == 'x') {
    	num2 = &num2[1];
    	number2 = toDecimal(num2, 16);


    } else if(num2[0] == 'o') {
    	num2 = &num2[1];
    	number2 = toDecimal(num2, 8);

    } else if(num2[0] == 'b'){
    	num2 = &num2[1];
    	number2 = toDecimal(num2, 2);
    } else {
    	fprintf(stderr,"ERROR, invalid argument!");
    }
	number2 = number2 * neg2;

    //calculates number 1 and 2 based on the operator
    if (*op == '+'){
    	sum = number1 + number2;
    } else if (*op == '-') {
		sum = number1 - number2;
    } else if (*op == '*') {
		sum = number1 * number2;
    } else {
    	fprintf(stderr,"ERROR, invalid operator");
    }
    char result[100];

    //outputs the calculations in appropriate format to the output base

    if(*output == 'd') {
    	printf("d%s \n", fromDecimal(result, 10, sum));
    } else if (*output == 'x') {
    	printf("x%s \n", fromDecimal(result, 16, sum));

    } else if (*output == 'o') {
    	printf("o%s \n", fromDecimal(result, 8, sum));
    } else if (*output == 'b') {
    	if (sum < 0){
    		sum = sum* (-1);
    		sum = sum ^ 2147483647;
    		sum++;
    	}
    	printf("b%s \n", fromDecimal(result, 2, sum));
    } else {
    	fprintf(stderr,"ERROR! invalid argument!");
    }
return 0;

}

//takes number and base 
//returns value based on given base
int toDecimal(char *numVal, int base) {
    int length = strlen(numVal);
    int on = 1;
    int i = 0;
    int value = 0;  
   
 
    for (i = length - 1; i >= 0; i--) {
        value += conversion(numVal[i]) * on;
        on = on * base;
    }
 
    return value;
}
//converts value
//if 5, returns 5. if 10, returns A
int conversion(char ch) {
    if (ch >= '0' && ch <= '9'){
        return (int)ch - '0';
    }
    else{
        return (int)ch - 'A' + 10;
    }
}




//takes return array, base, and value
//converts value based on base and returns the char array
//by dividing the val, storing the nnumber 
char* fromDecimal(char result[], int base, int val) {
    int count = 0;  
    while (val > 0)
    {
        result[count++] = reConv(val % base);
        val /= base;
    }
    result[count] = '\0';
    reverseVal(result);
    return result;
}
//takes value and converts it
//if A, returns 10, if 5, returns 5
char reConv(int value) {
    if (value >= 0 && value <= 9) {
        return (char)(value + '0');
    }
    else {
        return (char)(value - 10 + 'A');
    }
}
 
//takes the string
//reverses the string for output
void reverseVal(char *numVal) {
    int i = 0;
    int length = strlen(numVal);
    for (i = 0; i < length/2; i++){
        char temp = numVal[i];
        numVal[i] = numVal[length-i-1];
        numVal[length-i-1] = temp;
    }
}
 

