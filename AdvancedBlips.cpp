/*
 * AdvancedBlips.cpp
 *
 *  Created on: Nov 29, 2015
 *      Author: kevin
 */

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <assert.h>
#include "Parse.h"
#include "String.h"
#include "Operators.h"
#include "HashMap.h"
#include "HashFunction.h"
#include "StringEvaluate.h"
#include "LinkedStack.h"
#include "Vector.h"
#include "Blip.h"
#include "AdvancedBlips.h"


/*******Function: loopPrintString******
 * PrintString for a loop
 */



void loopPrintString(void){
	blockpos = blockpos+1;
	char* temp = statement();
	    while (!utstrcmp(temp, " ")) {
	        if ( utstrcmp(temp, "od")) {
	            blockpos = blockpos - 2;
	            break;
	        }
	        if(utstrcmp(peek(),"KEYWORD")){
	        	blockpos=blockpos-2;
	        	break;
	        }
	        printf("%s", temp);
	        temp = statement();
	    };
	    blockpos = blockpos -1;
}

/*******Function: loopPrintNumb******
 * PrintNum for a loop
 */
void loopPrintNum(void){
	blockpos = blockpos+1;
		char* temp = statement();
		if(next_token_type == NUMBER){
			printf("%d",token_number_value);
		}
		else if(utstrcmp(temp,"call")){
					int value = loopfuncJumpto(block, &blockpos);
					printf("%d",value);
				}

		else if(next_token_type == NAME){
			//String key(next_token());
			int value = Map.get(temp);
			if(value == -1){printf("WARNING Variable is undeclared\n");}
			else{

			printf("%d",value);
			}
		}

		else if(next_token_type == SYMBOL){
			String evaluate(temp);
			evaluate =looptoSubString(evaluate);
			int value= StackString(evaluate);
			//whitespacepos =0;
			printf("%d",value);
			//ParseTree eval;

}

}

void funcPrintNum(Vector* evaluatefun, uint32_t* funpos){
	*funpos = *funpos+2;
		char* temp = whatsnext(evaluatefun,funpos);
		if(next_token_type == NUMBER){
			printf("%d",token_number_value);
		}
		else if(utstrcmp(temp,"call")){
			funcJumpto(evaluatefun, funpos);
		}

		else if(next_token_type == NAME){
			//String key(next_token());
			int value = Map2.get(temp);
			if(value == -1){printf("WARNING Variable is undeclared\n");}
			else{

			printf("%d",value);
			}
		}

		else if(next_token_type == SYMBOL){
			String evaluate(temp);
			evaluate = functoSubString(evaluate, evaluatefun, funpos);
			int value= StackString(evaluate);
			//whitespacepos =0;
			printf("%d",value);


}
		*funpos = *funpos -1;
}

void loopDeclareVariable(void){

}

void funcDeclareVariable(Vector* evaluatefun, uint32_t* funpos){

*funpos = *funpos + 2;
String variable(whatsnext(evaluatefun,funpos));


if(utstrcmp(peeknext(evaluatefun,funpos),"NUMBER")){
	LinkedHashEntry Entry(variable, token_number_value);
	if(!Map2.put(Entry)){
		printf("WARNING. Variable has already been declared\n");
	}
	}

else if(utstrcmp(peeknext(evaluatefun,funpos),"SYMBOL")){
	String token(whatsnext(evaluatefun,funpos));
	token = functoSubString(token,evaluatefun,funpos);
	int value =StackString(token);
	//whitespacepos =0;
LinkedHashEntry Entry(variable, value);
if(!Map2.put(Entry)){
	printf("WARNING. Variable has already been declared\n");
}

}
else if(utstrcmp(peeknext(evaluatefun,funpos),"NAME")){
	int value = funcJumpto(evaluatefun,funpos);
	LinkedHashEntry Entry(variable, value);
	if(!Map2.put(Entry)){
			printf("WARNING. Variable has already been declared\n");
		}
}
else{
		printf("Variable cannot be evaluated\n");

}
}
/*******Function: funcPrintString******
 * PrintNum for a loop
 */
void funcPrintString(Vector* evaluatefun, uint32_t* funpos){
	*funpos = *funpos+2;
	char* temp = whatsnext(evaluatefun,funpos);
	    while (true) {
	        if ( utstrcmp(temp, "return")) {
	            *funpos = *funpos - 2;
	            break;
	        }

	        printf("%s", temp);
	        if(utstrcmp(peeknext(evaluatefun,funpos),"NAME")){
	        	printf(" ");
	        	      	        }
	        if(utstrcmp(peeknext(evaluatefun,funpos),"KEYWORD")){
	      	        	*funpos=*funpos-2;
	      	        	break;
	      	        }
	        temp = whatsnext(evaluatefun,funpos);
	    };
	    *funpos = *funpos -1;
}

void funcSetVariable(Vector* evaluatefun, uint32_t* funpos){
	*funpos = *funpos +2;
	String variable(whatsnext(evaluatefun,funpos));

		if(utstrcmp(peeknext(evaluatefun,funpos),"NUMBER")){
		LinkedHashEntry Entry(variable, token_number_value);
		 if(!Map2.reassign(Entry)){printf("variable %s not declared\n",variable.c_str());}
		}
		else if(utstrcmp(peeknext(evaluatefun,funpos),"SYMBOL")){
			String evaluate(whatsnext(evaluatefun,funpos));
			evaluate = functoSubString(evaluate, evaluatefun, funpos);
			int value= StackString(evaluate);
			//whitespacepos =0;

		LinkedHashEntry Entry(variable, value);
		if(!Map2.reassign(Entry)){if(!Map.reassign(Entry)){printf("variable %s not declared\n",variable.c_str());}}
		}
		else{
				printf("Variable cannot be evaluated\n");

		}
		*funpos = *funpos -1;
}


/*******Function: functionParser******
 * Turn entire expression into a String
 */
String functionParser(String evaluate){
	String returnstmt("return");
	int flag =0;
	do{
			read_next_token();

			String symbol(next_token());
			if(symbol == returnstmt){
				flag = 1;
			}
			evaluate.append(next_token());


			String next(peek_next_token());
			if(next == "nufed"){
				evaluate.append(next_token());
				break;
			}
		}while(true) ;
if(flag == 0){
	evaluate.append("return");
	evaluate. append("0");
}
return  evaluate;
}

/*******Function: functionCall******
 * put the function in a HashTable
 */

void functionCall(void){
	read_next_token();
	String functionname(next_token());
	read_next_token();
	String expression(next_token());
	expression = functionParser(expression);
	HashFunction Entry(functionname,expression);
	Func.put(Entry);
}

void FunctionTable(){

}
int executeFunction(Vector* evaluatefun){
	uint32_t funpos = 0;

		while (!utstrcmp((*evaluatefun)[funpos],"return")){
			char* keywordtype = (*evaluatefun)[funpos];

				if (utstrcmp(keywordtype, "output")) {
					funcPrintNum(evaluatefun,&funpos);
				} else if (utstrcmp(keywordtype, "text")) {
					funcPrintString(evaluatefun,&funpos);
				} else if (utstrcmp(keywordtype, "var")) {
					funcDeclareVariable(evaluatefun,&funpos);
				} else if (utstrcmp(keywordtype, "set")) {
					funcSetVariable(evaluatefun,&funpos);
				} else if (utstrcmp(keywordtype, "//")) {
					skip_line();
				} else if (utstrcmp(keywordtype, "do")){
					doKeyword();
				} else if(utstrcmp(keywordtype,"params")){
					int i =0;
					funpos = funpos + 2;
					char* params = whatsnext(evaluatefun, &funpos);
					if(next_token_type == NAME){
						while(!utstrcmp(params, "smarap")){
							String currentparameter(params);
							LinkedHashEntry PutIn(currentparameter,array[i]);
							Map2.put(PutIn);
							i++;

							params = (*evaluatefun)[funpos];
							funpos = funpos + 2;
						}
						funpos = funpos -2;
					}
				}
				else{

				}
				if(utstrcmp((*evaluatefun)[funpos],"return")){
					funpos = funpos +2;
					char* token = whatsnext(evaluatefun,&funpos);
					if(next_token_type == NUMBER){
						return token_number_value;}

				else if(next_token_type == NAME){
					String tokentype (token);
					int x = Map2.get(tokentype);
					if(x == -1){
						x = Map.get(tokentype);
					}
					return x;
				}
				else if(next_token_type == SYMBOL){
					String tokentype(token);
					tokentype = functoSubString(token, evaluatefun, &funpos);
					int evaluated = StackString(tokentype);
					return evaluated;
				}



		}
				funpos +=1;

}
		if(utstrcmp((*evaluatefun)[funpos],"return")){
							funpos = funpos+ 2;
							char* token = whatsnext(evaluatefun,&funpos);
							if(next_token_type == NUMBER){
								return token_number_value;}

						else if(next_token_type == NAME){
							String tokentype (token);
							int x = Map2.get(tokentype);
							if(x == -1){
								x = Map.get(tokentype);
							}
							return x;
						}
						else if(next_token_type == SYMBOL){
							String tokentype(token);
							tokentype = functoSubString(token, evaluatefun, &funpos);
							int evaluated = StackString(tokentype);
							return evaluated;
						}
}
		return 0;
}
int evaluateFunction(String evaluate){
	Vector* evaluatefun= new Vector();
	char token[10] = {0,0,0,0,0,0,0,0,0,0};
	int i =0;
	int j =0;
	int breakflag =0;
	while(evaluate[i] != 0){
		while(evaluate[i] != ' '){
			if(evaluate[i] == 0){breakflag =1;break;}
			token[j++] = evaluate[i++];
		}
			String* temp = new String((char*) token);
		        evaluatefun->push_back((char*)temp->c_str());
		        for(int k =0; k<10; k ++){
		        	token[k] =0;
		        }
		        j=0;
		if(evaluate[i] == ' '){
			evaluatefun->push_back(" ");
		}
		if(breakflag==1){break;}
		i++;

	}
int returnvalue = executeFunction(evaluatefun);
return returnvalue;
}



int funcJumpto(Vector* evaluatefun, uint32_t* funpos){


char* nextstmt = whatsnext(evaluatefun,funpos);
String functionname(nextstmt);
String expression(Func.get(functionname));
*funpos = *funpos + 2;
while(!utstrcmp(next_token(),"sgra")){
*funpos = *funpos + 2;
//arguments -> push_back((char*)(*evaluatefun)[*funpos] );
}
int evaluated = evaluateFunction(expression);
return evaluated;
}

int loopfuncJumpto(Vector* evaluatefun, uint32_t* funpos){


char* nextstmt = statement();
String functionname(nextstmt);
String expression(Func.get(functionname));
//blockpos+=1;
int i =0;
while(!utstrcmp(statement(),"sgra")){

	//blockpos = blockpos + 2;
	if(utstrcmp((char*) (*block)[blockpos],"sgra")){break;}
	if(next_token_type == NAME){
	String variable((char*) (*block)[blockpos]);
	int value = Map.get(variable);
	array[i++] = value;
	}
	else if(next_token_type == NUMBER){
		array[i++] = token_number_value;
	}
	else if(next_token_type == SYMBOL){
		String evaluate((char*) (*block)[blockpos]);
		evaluate = looptoSubString(evaluate);
		int numbereval = StackString(evaluate);
		array[i++] = numbereval;
	}

}
int evaluated = evaluateFunction(expression);
return evaluated;
}

/*******Function: loopSetVariable******
 * SetVariable for a loop
 */
void loopSetVariable(void){
	blockpos = blockpos +1;
	String variable(statement());
	char* deb = peek();
	//statement();
	//blockpos = blockpos-2;
	if(utstrcmp(peek(),"NUMBER")){
	LinkedHashEntry Entry(variable, token_number_value);
	 if(!Map.reassign(Entry)){printf("variable %s not declared\n",variable.c_str());}
	}
	else if(utstrcmp(peek(),"SYMBOL")){
		String evaluate(statement());
		evaluate = looptoSubString(evaluate);
		int value =StackString(evaluate);
		//whitespacepos =0;

	LinkedHashEntry Entry(variable, value);
	if(!Map.reassign(Entry)){printf("variable %s not declared\n",variable.c_str());}
	}
	else{
			printf("Variable cannot be evaluated\n");

	}

}
/*******Function: loopdoKeyword******
 * Basic While Loop
 */
void loopdoKeyword(){
	statement();
	if(next_token_type == SYMBOL){
		//String evaluate(next_token());
		String evaluate("");
		 evaluate = toSubStringCopy(evaluate);//saved as String
		saveBlock(); //saves the loop inside
		String debug1;
		int debug2;
		while(StackString(returnwithHash(evaluate.c_str()))){
			executeBlock();
			debug1= returnwithHash(evaluate.c_str());
			debug2= StackString(returnwithHash(evaluate.c_str()));
			stack.reset();


		}
	}
}


String looptoSubString(String evaluate){

	do{

			//blockpos = blockpos -1;
			char* symbol = statement();

			 if ( utstrcmp(symbol, "od")) {
				            blockpos = blockpos - 2;
				            break;
				        }
				        if(utstrcmp(peek(),"KEYWORD")){
				        	blockpos=blockpos-2;
				        	break;
				        }
			//blockpos = blockpos -1;
			if(next_token_type == SYMBOL){
			evaluate.append(symbol);

			}
			else if(next_token_type == NAME){
				String key(symbol);
				int x = Map.get(key);

				char* y = itoa (x,10);
				evaluate.append(y);
			}
			else if(next_token_type == NUMBER){
				evaluate.append(symbol);

			}

			//flag++;
			//String next(statement());

		}while(true) ;

return  evaluate;
}


String functoSubString(String evaluate,Vector* evaluatefun, uint32_t* funpos){

	do{

			//blockpos = blockpos -1;
			char* symbol = whatsnext(evaluatefun,funpos);

			 if (IS_KEYWORD(symbol)) {
				            *funpos = *funpos - 2;
				            break;
				        }


			//blockpos = blockpos -1;
			if(next_token_type == SYMBOL){
			evaluate.append(symbol);

			}
			else if(next_token_type == NAME){
				String key(symbol);
				int x = Map2.get(key);
				if(x==-1){x = Map.get(key);}
				char* y = itoa (x,10);
				evaluate.append(y);
			}
			else if(next_token_type == NUMBER){
				evaluate.append(symbol);

			}

			//flag++;
			//String next(statement());

		}while(true) ;

return  evaluate;
}

char* peeknext(Vector* evaluatefun,uint32_t* funpos){
	int peeknumber = *funpos;
	//peeknumber += 1;
	char* syntax = (*evaluatefun)[peeknumber];
	if (IS_NUMBER(syntax[0])) {
		 token_number_value = atoi(syntax);
	        return "NUMBER";

	    } else if (utstrcmp(syntax, "//")){
	        return "COMMENT";
	    } else if (! IS_LETTER(syntax[0])) {
	        return "SYMBOL";
	    } else if (IS_KEYWORD(syntax)) {
	        return "KEYWORD";
	    }
	    else if (IS_LETTER(syntax[0])){
	        	return "NAME";
	        }
return "";
}

char* whatsnext(Vector* evaluatefun, uint32_t* funpos){
    char* syntax = (*evaluatefun)[*funpos];
    *funpos = *funpos + 2;
    if (IS_NUMBER(syntax[0])) {
    	token_number_value = atoi(syntax);
        next_token_type = NUMBER;

    } else if (utstrcmp(syntax, "//")){
        next_token_type = COMMENT;
    } else if (! IS_LETTER(syntax[0])) {
        next_token_type = SYMBOL;
    } else if (IS_KEYWORD(syntax)) {
        next_token_type = KEYWORD;
    }
    else if (IS_LETTER(syntax[0])){
    	next_token_type = NAME;
    }
    return syntax;
}
