#include <stdio.h>
#include <stdlib.h>
#include <string.h>


long long int toDecimal(char *str);
int conversion(char ch);
float power(int num, int ex );

int main( int argc, char **argv )  {
   if( argc != 3 ) {
      fprintf(stderr, "ERROR, invalid number of arguments!" );
      return 0;
   }

    char *inputBit = argv[1];
    char *type = argv[2];
    long long int number1;
    int neg = 1;

 	if(inputBit[0] == '1') {
    	neg = -1;
    }
    inputBit = &inputBit[1];

    if (strcmp( argv[2], "int") == 0 ) {
    	number1 = toDecimal(inputBit);
        number1 *=neg;
        
    	printf("%d", number1);



    } else if(strcmp( argv[2], "float") == 0 ) {
        char expStr[9];
        int exponent;
        int i = 0;
        float total;
        float temp;
        float ex;
        float mantissa = 0;
        

        memcpy(expStr, &inputBit[0], 8);
        inputBit = &inputBit[8];
        exponent = toDecimal(expStr);
        exponent = exponent - 127;
        if(inputBit[0] == '1'){
            mantissa = 0.5f;
        }
        
        for (i = 1; i <= 22; i++){
            if (inputBit[i] == '1') {
                temp = 1/(power(2, i));
                mantissa += temp;
            }
        }
        mantissa += 1;
        ex = power(2, exponent);
        total = (ex*mantissa)/2;
        total *= neg;
        printf("%fe0", total);

    } else {
        fprintf(stderr, "ERROR, invalid argument!");
    }
	return 0;
}

float power(int num, int ex ){
    float total = 2;
    int i;
    for(i = 0; i < ex; i++) {
        total = total*num;
    }
    return total;

}

long long int toDecimal(char *str) {
    int length = strlen(str);
    int on = 1;
    int i = 0;
    long long int value = 0;  
    int base = 2;
 
    for (i = length - 1; i >= 0; i--) {
        value += conversion(str[i]) * on;
        on = on * base;
    }
 
    return value;
}

int conversion(char ch) {
    if (ch >= '0' && ch <= '9'){
        return (int)ch - '0';
    }
    else{
        return (int)ch - 'A' + 10;
    }
}
