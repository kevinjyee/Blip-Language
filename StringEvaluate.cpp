#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Parse.h"
#include "String.h"
#include "Parse.h"
#include "String.h"
#include "Operators.h"
#include "HashMap.h"
#include "LinkedStack.h"

symbols s;
StackusingList stack(1000000);

void reverse(char* str, int len){
	if(len == 1){
		return;
	}
	char x[len];
	int k =0;
	for(int i=len-1; i >=0 ; i--){
		x[k++] = str[i];
	}
	for(int i =0; i<len;i++){
		str[i] = x[i];
	}
}


char* itoa(int num,  int base){
	int copy = num;
	int count =0;
	while(copy != 0){
		copy = copy/10;
		count++;
	}
	char str[count];
    int i = 0;
    bool isNegative = false;
    /* Handle 0 explicitely, otherwise empty string is printed for 0 */
    if (num == 0)
    {
        str[i++] = '0';
        str[i] = '\0';
        return str;
    }

    // In standard itoa(), negative numbers are handled only with
    // base 10. Otherwise numbers are considered unsigned.
    if (num < 0 && base == 10)
    {
        isNegative = true;
        num = -num;
    }

    // Process individual digitsutp
    while (num != 0)
    {
        int rem = num % base;
        str[i++] = (rem > 9)? (rem-10) + 'a' : rem + '0';
        num = num/base;
    }

    // If number is negative, append '-'
    if (isNegative)
        str[i++] = '-';

    str[i] = '\0'; // Append string terminator

    // Reverse the string
    reverse(str, i);

    return str;
}

constexpr unsigned int str2int(const char* str, int h = 0){
    return !str[h] ? 5381 : (str2int(str, h+1)*33) ^ str[h];
}


int32_t utstrcmp(const char* s1, const char* s2) {

char TempChar_1;
char TempChar_2;
int difference =0;

	do
	      {
	      TempChar_1 = *(s1)++;
	      TempChar_2 = *(s2)++;
	      } while(TempChar_1 && TempChar_1 == TempChar_2);

	      difference= TempChar_1 - TempChar_2;
	      if(difference ==0){
	    	  return 1;
	      }else {return 0;}


}
bool isnumber(char c) {
	return c >= '0' && c <='9';
}

int whitespacepos =0;

char token[8] = {0,0,0,0,0,0,0,0};

int StackString(String x){
	int length = x.size();
	int count =0;
	for(int k=0;k<length-1;k++){
	if (x[k] == ' '){
		count++;
	}
	}

	whitespacepos = length-1;
	for(int k=0; k<count+1; k++){
	char token[8] = {0,0,0,0,0,0,0,0};
	int i =0;

	while(x[whitespacepos] != ' ' && whitespacepos >= 0){
		token[i++] = x[whitespacepos--];
	}
	token[i] = 0;
	whitespacepos--;


if(isnumber(*token)){
	reverse(token,i);
	int a= atoi(token);
	stack.push(a);
}
		if(*token =='+')
        {
            int a = stack.topofstack();
            stack.pop();
            int b = stack.topofstack();
            stack.pop();
            int result = a+b;
            stack.push(result);
        }

        if(*token == '-')
        {
            int a = stack.topofstack();
            stack.pop();
            int b = stack.topofstack();
            stack.pop();
            int result = a-b;
            stack.push(result);
        }
        if(*token =='*')
        {
            int a = stack.topofstack();
            stack.pop();
            int b = stack.topofstack();
            stack.pop();
            int result = a*b;
            stack.push(result);
        }
        if(*token =='/')
        {
            int a = stack.topofstack();
            stack.pop();
            int b= stack.topofstack();
            stack.pop();
            int result = a/b;
            stack.push(result);
        }

        if(*token == '%'){
        	int a = stack.topofstack();
        	stack.pop();
        	int b = stack.topofstack();
        	stack.pop();
        	int result = a%b;
        	stack.push(result);
        }

        if(str2int(token) == str2int("&&")){
        	int a = stack.topofstack();
        	stack.pop();
        	int b = stack.topofstack();
        	stack.pop();
        	int result = a&&b;
        	stack.push(result);
            }
        if(str2int(token) == str2int("||")){
        					int a = stack.topofstack();
            	            stack.pop();
            	            int b = stack.topofstack();
            	            stack.pop();
            	            int result = a||b;
            	            stack.push(result);
            }
        if(*token == '>'){
            	 int a = stack.topofstack();
            	            stack.pop();
            	            int b = stack.topofstack();
            	            stack.pop();
            	            int result = a>b;
            	            stack.push(result);
            }
        if(*token == '<'){
            	 int a = stack.topofstack();
            	            stack.pop();
            	            int b = stack.topofstack();
            	            stack.pop();
            	            int result = a<b;
            	            stack.push(result);
            }
        if(str2int(token) == str2int("==")){
            	 int a = stack.topofstack();
            	            stack.pop();
            	            int b = stack.topofstack();
            	            stack.pop();
            	            int result = a==b;
            	            stack.push(result);
            }
        if(str2int(token) == str2int("=!")){
            	 int a = stack.topofstack();
            	            stack.pop();
            	            int b = stack.topofstack();
            	            stack.pop();
            	            int result = a!=b;
            	            stack.push(result);
            }
        if(str2int(token) == str2int("=<")){
            	 int a = stack.topofstack();
            	            stack.pop();
            	            int b = stack.topofstack();
            	            stack.pop();
            	            int result = a<=b;
            	            stack.push(result);
            }
        if(str2int(token) == str2int("=>")){
            	 int a = stack.topofstack();
            	            stack.pop();
            	            int b = stack.topofstack();
            	            stack.pop();
            	            int result = a>=b;
            	            stack.push(result);
            }

        if(*token == '!'){
            	 int a = stack.topofstack();
            	            stack.pop();

            	            int result = !a;
            	            stack.push(result);
            }
        if(*token == '~'){
            	 int a = stack.topofstack();
            	            stack.pop();

            	            int result = a * -1;
            	            stack.push(result);
            }
    }
whitespacepos = 0;
return stack.topofstack();

	}

bool IS_NUMBER(char c) {
	return c >= '0' && c <='9';
}

 bool IS_LETTER(char c) {
	return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

 bool IS_SPACE(char c) {
	return c == ' ' || c == '\t' || c == '\n';
}







