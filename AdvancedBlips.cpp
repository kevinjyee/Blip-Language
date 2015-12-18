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


int countdo =0;
String looptoSubStringCopy(String evaluate,Vector* block,uint32_t* blockpos){


	do{

		String next(peek(block,blockpos));
					if(utstrcmp(next.c_str(),"KEYWORD")){
						evaluate.append(" ");
									break;
								}


			String symbol((*block)[*blockpos]);
			if(next_token_type == SYMBOL){
			evaluate.append((*block)[*blockpos]);

			}
			else if(next_token_type == NAME){
				String key((*block)[*blockpos]);
				int x = Map.get(key);

				char* y = itoa (x,10);
				evaluate.append((*block)[*blockpos]);
			}
			else if(next_token_type == NUMBER){
				evaluate.append((*block)[*blockpos]);

			}
			statement(block,blockpos);
		}while(true) ;

return  evaluate;
}


/*******Function: loopPrintString******
 * PrintString for a loop
 */



void loopPrintString(Vector* block , uint32_t* blockpos){
	*blockpos = *blockpos+1;
	char* temp = statement(block,blockpos);
	    while (!utstrcmp(temp, " ")) {
	        if ( utstrcmp(temp, "od")) {
	            *blockpos = *blockpos - 2;
	            break;
	        }
	        if(utstrcmp(peek(block,blockpos),"KEYWORD")){
	        	*blockpos= *blockpos-2;
	        	break;
	        }
	        printf("%s", temp);
	        temp = statement(block,blockpos);
	    };
	    *blockpos = *blockpos -1;
}

/*******Function: loopPrintNumb******
 * PrintNum for a loop
 */
void loopPrintNum(Vector* block, uint32_t* blockpos){
	*blockpos = *blockpos+1;
		char* temp = statement(block,blockpos);
		String key (temp);
		if(next_token_type == NUMBER){
			printf("%d",token_number_value);
		}
		else if(utstrcmp(temp,"call")){
					int value = loopfuncJumpto(block, blockpos);
					printf("%d",value);
				}

		else if(next_token_type == NAME){
			//String key(next_token());
			int value = Map.get(temp);
			if(value == -1){printf("variable %s not declared\n",key.c_str());}
			else{

			printf("%d",value);
			}
		}

		else if(next_token_type == SYMBOL){
			String evaluate(temp);
			evaluate =looptoSubString(evaluate,block,blockpos);
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
			int value = funcJumpto(evaluatefun, funpos);
			if(value == -1){printf("variable %s not declared\n",temp);}
						else{

						printf("%d",value);
						}
		}

		else if(next_token_type == NAME){
			//String key(next_token());
			int value = Map2.get(temp);
			if(value == -1){printf("variable %s not declared\n",temp);}
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

void loopDeclareVariable(Vector* block, uint32_t* blockpos){
	HashTableFlag = 1;
	*blockpos = *blockpos +1;
		String variable(statement(block,blockpos));
		peek(block,blockpos);
if(utstrcmp(peek(block,blockpos),"NUMBER")){
	LinkedHashEntry Entry(variable, token_number_value);
	if(!Map.put(Entry)){
		printf("variable %s incorrectly re-initialized\n",variable.c_str());
	}
	}

else if(utstrcmp(peek(block,blockpos),"SYMBOL")){
	String evaluate(statement(block,blockpos));
	evaluate = looptoSubString(evaluate,block,blockpos);
	int value =StackString(evaluate);
	//whitespacepos =0;
LinkedHashEntry Entry(variable, value);
if(!Map.put(Entry)){
	printf("variable %s incorrectly re-initialized\n",variable.c_str());
}

}
else if(utstrcmp(peek(block,blockpos),"CALL")){
	int value = loopJumpto(block,blockpos);
	LinkedHashEntry Entry(variable, value);
	if(!Map.put(Entry)){
			printf("variable %s incorrectly re-initialized\n",variable.c_str());
		}
}
else{
		printf("variable %s incorrectly re-initialized\n",variable.c_str());

}

}

void funcDeclareVariable(Vector* evaluatefun, uint32_t* funpos){

*funpos = *funpos + 2;
String variable(whatsnext(evaluatefun,funpos));


if(utstrcmp(peeknext(evaluatefun,funpos),"NUMBER")){
	LinkedHashEntry Entry(variable, token_number_value);
	if(!Map2.put(Entry)){
		printf("variable %s incorrectly re-initialized\n",variable.c_str());
	}
	}

else if(utstrcmp(peeknext(evaluatefun,funpos),"SYMBOL")){
	String token(whatsnext(evaluatefun,funpos));
	token = functoSubString(token,evaluatefun,funpos);
	int value =StackString(token);
	//whitespacepos =0;
LinkedHashEntry Entry(variable, value);
if(!Map2.put(Entry)){
	printf("variable %s incorrectly re-initialized\n",variable.c_str());
}

}
else if(utstrcmp(peeknext(evaluatefun,funpos),"NAME")){
	whatsnext(evaluatefun,funpos);
	int value = funcJumpto(evaluatefun,funpos);
	LinkedHashEntry Entry(variable, value);
	if(!Map2.put(Entry)){
			printf("variable %s incorrectly re-initialized\n",variable.c_str());
		}
}
else{
		printf("variable %s incorrectly re-initialized\n",variable.c_str());

}
}
/*******Function: funcPrintString******
 * PrintNum for a loop
 */
void funcPrintString(Vector* evaluatefun, uint32_t* funpos){
	*funpos = *funpos+2;
	char* temp = (*evaluatefun)[*funpos];
	*funpos +=2;
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
	        temp = (*evaluatefun)[*funpos];
	        	*funpos +=2;
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
		else if(utstrcmp(peeknext(evaluatefun,funpos),"NAME")){
			whatsnext(evaluatefun,funpos);
			int value = funcJumpto(evaluatefun,funpos);
			LinkedHashEntry Entry(variable, value);
			if(!Map2.put(Entry)){
					printf("variable %s incorrectly re-initialized\n",variable.c_str());
				}
		}
		else{
				printf("Variable cannot be evaluated\n");

		}
		*funpos = *funpos -1;
}

String loopfunctionParser(String evaluate,Vector* block, uint32_t*blockpos){
	String returnstmt("return");
	int flag =0;
	do{
			statement(block,blockpos);

			String symbol((*block)[*blockpos]);
			if(symbol == returnstmt){
				flag = 1;
			}
			evaluate.append((*block)[*blockpos]);



			if(utstrcmp((*block)[*blockpos],"nufed")){
				//evaluate.append((*block)[*blockpos]);
				break;
			}
		}while(true) ;
if(flag == 0){
	evaluate.append("return");
	evaluate. append("0");
}
return  evaluate;
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

void loopfunctionCall(Vector* block, uint32_t* blockpos, int flag){
	char* word = statement(block,blockpos);
	if(flag ==1){*blockpos = *blockpos + 1;}
	//if(utstrcmp(word," ")){*blockpos = *blockpos + 1;}

	String functionname((*block)[*blockpos]);
	*blockpos = *blockpos + 1;
	if(utstrcmp((*block)[*blockpos]," ")){*blockpos+=1;}
	String expression((*block)[*blockpos]);
	expression = loopfunctionParser(expression,block,blockpos);
	HashFunction Entry(functionname,expression);
	Func.put(Entry);
}

void FunctionTable(){

}
int executeFunction(Vector* evaluatefun){read_next_token();
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
					funcloopdoKeyword(evaluatefun,&funpos);
				} else if (utstrcmp(keywordtype, "if")){
								funcifKeyword(evaluatefun,&funpos);
				} else if(utstrcmp(keywordtype,"defun")){
					loopfunctionCall(evaluatefun,&funpos,1);
				}
				else if(utstrcmp(keywordtype,"params")){
					int i =0;
					funpos = funpos + 2;
					char* params = peek(evaluatefun, &funpos);
					if(utstrcmp(params,"NAME")){
						while(!utstrcmp(params, "smarap")){
							String currentparameter(params);
							LinkedHashEntry PutIn(currentparameter,array[i]);
							if(!Map2.put(PutIn)){Map2.reassign(PutIn);}
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
					int lastflag = 0;
					if(next_token_type == END){
						lastflag = 1;
					}
					char* token = whatsnext(evaluatefun,&funpos);
					if(next_token_type == NUMBER){
						if(lastflag ==1){next_token_type = END;}
						return token_number_value;}
					else if(utstrcmp(token,"call")){
						int value = loopJumpto(evaluatefun, &funpos);
						if(lastflag ==1){next_token_type = END;}
						return value;
					}

				else if(next_token_type == NAME){
					String tokentype (token);
					int x = Map2.get(tokentype);
					if(x == -1){
						x = Map.get(tokentype);
					}
					if(lastflag ==1){next_token_type = END;}
					return x;
				}
				else if(next_token_type == SYMBOL){
					String tokentype(token);
					tokentype = functoSubString(token, evaluatefun, &funpos);
					int evaluated = StackString(tokentype);
					if(lastflag ==1){next_token_type = END;}
					return evaluated;
				}



		}
				funpos +=1;

}
		if(utstrcmp((*evaluatefun)[funpos],"return")){
			int lastflag =0;
			if(next_token_type == END){
									lastflag = 1;
								}
							funpos = funpos+ 2;
							char* token = whatsnext(evaluatefun,&funpos);
							if(next_token_type == NUMBER){
								if(lastflag ==1){next_token_type = END;}
								return token_number_value;}
							else if(utstrcmp(token,"call")){
							int value = loopJumpto(evaluatefun, &funpos);
							if(lastflag ==1){next_token_type = END;}
							return value;
										}

						else if(next_token_type == NAME){
							String tokentype (token);
							int x = Map2.get(tokentype);
							if(x == -1){
								x = Map.get(tokentype);
							}
							if(lastflag ==1){next_token_type = END;}
							return x;
						}
						else if(next_token_type == SYMBOL){
							String tokentype(token);
							tokentype = functoSubString(token, evaluatefun, &funpos);
							int evaluated = StackString(tokentype);
							if(lastflag ==1){next_token_type = END;}
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
while(!utstrcmp((*evaluatefun)[*funpos],"sgra")){
*funpos = *funpos + 2;
//arguments -> push_back((char*)(*evaluatefun)[*funpos] );
}
int evaluated = evaluateFunction(expression);
return evaluated;
}

int loopfuncJumpto(Vector* evaluatefun, uint32_t* funpos){


char* nextstmt = statement(evaluatefun,funpos);
String functionname(nextstmt);
String expression(Func.get(functionname));
//blockpos+=1;
int i =0;
while(!utstrcmp(statement(evaluatefun,funpos),"sgra")){

	//blockpos = blockpos + 2;
	if(utstrcmp((char*) (*evaluatefun)[*funpos],"sgra")){break;}
	if(next_token_type == NAME){
	String variable((char*) (*evaluatefun)[*funpos]);
	int value = Map.get(variable);
	array[i++] = value;
	}
	else if(next_token_type == NUMBER){
		array[i++] = token_number_value;
	}
	else if(next_token_type == SYMBOL){
		String evaluate((char*) (*evaluatefun)[*funpos]);
		evaluate = looptoSubString(evaluate,evaluatefun,funpos);
		int numbereval = StackString(evaluate);
		array[i++] = numbereval;
	}

}
int evaluated = evaluateFunction(expression);
return evaluated;
}

int loopJumpto(Vector* block, uint32_t* blockpos){

*blockpos =*blockpos +1;
char* nextstmt = statement(block,blockpos);
String functionname(nextstmt);
String expression(Func.get(functionname));
//blockpos+=1;
int i =0;
while(!utstrcmp(statement(block,blockpos),"sgra")){

	//blockpos = blockpos + 2;
	if(utstrcmp((char*) (*block)[*blockpos],"sgra")){break;}
	if(next_token_type == NAME){
	String variable((char*) (*block)[*blockpos]);
	int value = Map.get(variable);
	array[i++] = value;
	}
	else if(next_token_type == NUMBER){
		array[i++] = token_number_value;
	}
	else if(next_token_type == SYMBOL){
		String evaluate((char*) (*block)[*blockpos]);
		evaluate = looptoSubString(evaluate,block,blockpos);
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
void loopSetVariable(Vector* block, uint32_t* blockpos){
	*blockpos = *blockpos +1;
	String variable(statement(block,blockpos));
	char* deb = peek(block,blockpos);
	//statement();
	//blockpos = blockpos-2;
	if(utstrcmp(peek(block,blockpos),"NUMBER")){
	LinkedHashEntry Entry(variable, token_number_value);
	 if(!Map.reassign(Entry)){printf("variable %s not declared\n",variable.c_str());}
	}
	else if(utstrcmp(peek(block,blockpos),"SYMBOL")){
		String evaluate(statement(block,blockpos));
		evaluate = looptoSubString(evaluate,block,blockpos);
		int value =StackString(evaluate);
		//whitespacepos =0;

	LinkedHashEntry Entry(variable, value);
	if(!Map.reassign(Entry)){printf("variable %s not declared\n",variable.c_str());}
	}

	else if(utstrcmp(peek(block,blockpos),"NAME")){
		int value = loopJumpto(block,blockpos);
		LinkedHashEntry Entry(variable, value);
		if(!Map.reassign(Entry)){
				printf("variable %s not declared\n",variable.c_str());
			}
	}
	else{
			printf("Variable cannot be evaluated\n");

	}

}

Vector* loopsaveBlock(Vector* evaluatefun, uint32_t* funpos){
	Vector* block = new Vector();
   // read_next_token();
	int count =0;
    while (!utstrcmp((char*)(*evaluatefun)[*funpos],"od")) {
    	if(utstrcmp((char*)(*evaluatefun)[*funpos],"do")){
    	    		while (!utstrcmp((*evaluatefun)[*funpos],"od")){
    	    			String* temp = new String((char*) (*evaluatefun)[*funpos]);
    	    			        block->push_back((char*) temp->c_str());
    	    			        statement(evaluatefun,funpos);
    	    			        String next(peek(evaluatefun,funpos));
    	    			        	if(utstrcmp(next.c_str(),"KEYWORD")){
    	    			        		block->push_back(" ");
    	    			        		}
    	    		}
    	}
        String* temp = new String((char*) (*evaluatefun)[*funpos]);
        block->push_back((char*) temp->c_str());
        statement(evaluatefun,funpos);
        String next(peek(evaluatefun,funpos));
        	if(utstrcmp(next.c_str(),"KEYWORD")){
        		block->push_back(" ");
        		}

    }
    block->push_back("od");
    return block;
}
/*******Function: loopdoKeyword******
 * Basic While Loop
 */
void loopdoKeyword(Vector* block , uint32_t* blockpos){
	*blockpos+=1;
	String token = peek(block,blockpos);

	if(utstrcmp(token.c_str(),"SYMBOL")){
		//String evaluate(next_token());
		String evaluate(statement(block,blockpos));
		 evaluate = looptoSubStringCopy(evaluate,block,blockpos);//saved as String
		 Vector* block2 = loopsaveBlock(block,blockpos); //saves the loop inside
		String debug1;
		int debug2;
		while(StackString(returnwithHash(evaluate.c_str()))){
			executeBlock(block2);
			debug1= returnwithHash(evaluate.c_str());
			debug2= StackString(returnwithHash(evaluate.c_str()));
			stack.reset();

		}
	}
	else if(utstrcmp(token.c_str(),"NUMBER")){
			Vector* block2 = loopsaveBlock(block,blockpos);
			int x = token_number_value;
			while(x){
				executeBlock(block2);
			}
		}

		else if (utstrcmp(token.c_str(),"NAME")){
			String variable(statement(block,blockpos));
			Vector* block2 = loopsaveBlock(block,blockpos);
			while(Map.get(variable)){
				executeBlock(block2);
			}
		}

}

Vector* funcloopsaveBlock(Vector* evaluatefun, uint32_t* funpos){
	Vector* block = new Vector();
   // read_next_token();
	int count =0;
    while (!utstrcmp((char*)(*evaluatefun)[*funpos],"od")) {
    	if(utstrcmp((char*)(*evaluatefun)[*funpos],"do")){
    	    		while (!utstrcmp((*evaluatefun)[*funpos],"od")){
    	    			String* temp = new String((char*) (*evaluatefun)[*funpos]);
    	    			        block->push_back((char*) temp->c_str());
    	    			        whatsnext(evaluatefun,funpos);
    	    			        String next(peeknext(evaluatefun,funpos));
    	    			        	if(utstrcmp(next.c_str(),"KEYWORD")){
    	    			        		block->push_back(" ");
    	    			        		}
    	    		}
    	}
        String* temp = new String((char*) (*evaluatefun)[*funpos]);
        block->push_back((char*) temp->c_str());
        whatsnext(evaluatefun,funpos);
        String next(peeknext(evaluatefun,funpos));
        	if(utstrcmp(next.c_str(),"KEYWORD")){
        		block->push_back(" ");
        		}

    }
    block->push_back("od");
    return block;
}
/*******Function: loopdoKeyword******
 * Basic While Loop
 */
void funcloopdoKeyword(Vector* block , uint32_t* blockpos){
	*blockpos+=2;
	String token = peeknext(block,blockpos);

	if(utstrcmp(token.c_str(),"SYMBOL")){
		//String evaluate(next_token());
		String evaluate(whatsnext(block,blockpos));
		 evaluate = looptoSubStringCopy(evaluate,block,blockpos);//saved as String
		 Vector* block2 = funcloopsaveBlock(block,blockpos); //saves the loop inside
		String debug1;
		int debug2;
		while(StackString(returnwithHash(evaluate.c_str()))){
			executeBlock(block2);
			debug1= returnwithHash(evaluate.c_str());
			debug2= StackString(returnwithHash(evaluate.c_str()));
			stack.reset();

		}
	}
	else if(utstrcmp(token.c_str(),"NUMBER")){
			Vector* block2 = funcloopsaveBlock(block,blockpos);
			int x = token_number_value;
			while(x){
				executeBlock(block2);
			}
		}

		else if (utstrcmp(token.c_str(),"NAME")){
			String variable(whatsnext(block,blockpos));
			Vector* block2 = funcloopsaveBlock(block,blockpos);
			while(Map.get(variable)){
				executeBlock(block2);
			}
		}

}
int loopcondition(Vector* block, uint32_t* blockpos){

	String evaluate(statement(block,blockpos));
	evaluate = looptoSubString(evaluate,block,blockpos);
	int value =StackString(evaluate);
	return value;

}
void loopifSymbol(int value,Vector* block,uint32_t* blockpos){
	int nestedifflag = 0;
	int nestedelseflag=0;
	if(value){
			while (!utstrcmp((*block)[*blockpos],"fi")){
				if(utstrcmp((*block)[*blockpos],"else")){
					while(!utstrcmp((*block)[*blockpos],"fi")){
						statement(block, blockpos);
					}
					break;
				}
				statement(block,blockpos);
				String KEYWORD = (*block)[*blockpos];

					if (KEYWORD == m.output) {
							loopPrintNum(block,blockpos);
						} else if (KEYWORD == m.text) {
							loopPrintString(block,blockpos);
						} else if (KEYWORD == m.var) {
							loopDeclareVariable(block,blockpos);
						} else if (KEYWORD == m.set) {
							loopSetVariable(block,blockpos);
						} else if (KEYWORD == m.comments) {
							skip_line();
						} else if (KEYWORD == "do"){
							loopdoKeyword(block,blockpos);
						}
						else if (KEYWORD == "if"){
							loopifKeyword(block,blockpos);
							nestedifflag = 1;
							*blockpos+=1;
						}
						else if(KEYWORD == ""){

						}
			}

			}
		else{
			while(!utstrcmp((*block)[*blockpos],"else")){

				if(utstrcmp((*block)[*blockpos],"if")){
									while(!utstrcmp((*block)[*blockpos],"fi")){
										*blockpos +=1;
									}
									nestedelseflag = 1;
									*blockpos+=1;
								}

				if(utstrcmp((*block)[*blockpos],"fi")){
					return;
				}
				if (nestedelseflag ==0) {statement(block,blockpos);}
			}
			//read_next_token();

			while (!utstrcmp((*block)[*blockpos],"fi")){
						statement(block,blockpos);
						String KEYWORD = (*block)[*blockpos];

							if (KEYWORD == m.output) {
									loopPrintNum(block,blockpos);
								} else if (KEYWORD == m.text) {
									loopPrintString(block,blockpos);
								} else if (KEYWORD == m.var) {
									loopDeclareVariable(block,blockpos);
								} else if (KEYWORD == m.set) {
									loopSetVariable(block,blockpos);
								} else if (KEYWORD == m.comments) {
									skip_line();
								} else if (KEYWORD == "do"){
									loopdoKeyword(block,blockpos);
								}
								else if (KEYWORD == "if"){
									loopifKeyword(block,blockpos);
									nestedifflag = 1;
									*blockpos+=1;
								}
								else if(KEYWORD == ""){

								}
					}

					}
	//if(nestedifflag ==1){nestedifflag = 0; read_next_token();}
}
void loopifKeyword(Vector* block, uint32_t* blockpos){
	statement(block,blockpos);

	int value;
	if(utstrcmp(peek(block,blockpos),"SYMBOL")){
		value = loopcondition(block,blockpos);
		loopifSymbol(value,block,blockpos);
	}
	else if(utstrcmp(peek(block,blockpos),"NUMBER")){
		value = token_number_value;
		//read_next_token();
		loopifSymbol(value,block,blockpos);
	}
	else if(utstrcmp(peek(block,blockpos),"CALL")){
		value = loopJumpto(block,blockpos);
				loopifSymbol(value,block,blockpos);
		}
		else if(utstrcmp(peek(block,blockpos),"NAME")){
			String variable((*block)[*blockpos]);
			value = Map.get(variable);
			ifSymbol(value);
		}



	}



int funccondition(Vector* evaluatefun,uint32_t* funpos){

	String evaluate(whatsnext(evaluatefun,funpos));
	evaluate = functoSubString(evaluate,evaluatefun,funpos);
	int value =StackString(evaluate);
	return value;

}
void funcifSymbol(int value,Vector* evaluatefun,uint32_t* funpos){
	int nestedifflag = 0;
	if(value){
			while (!utstrcmp((*evaluatefun)[*funpos],"fi")){
				if(utstrcmp((*evaluatefun)[*funpos],"else")){
					while(!utstrcmp((*evaluatefun)[*funpos],"fi")){
						whatsnext(evaluatefun,funpos);
					}
					break;
				}
			//	whatsnext(evaluatefun,funpos);
				String tokentype = (*evaluatefun)[*funpos];

					if (tokentype == m.output) {
							funcPrintNum(evaluatefun,funpos);
						} else if (tokentype == m.text) {
							funcPrintString(evaluatefun,funpos);
						} else if (tokentype == m.var) {
							funcDeclareVariable(evaluatefun,funpos);
						} else if (tokentype == m.set) {
							funcSetVariable(evaluatefun,funpos);
						} else if (tokentype == m.comments) {
							skip_line();
						} else if (tokentype == "do"){
							funcloopdoKeyword(evaluatefun,funpos);
						}
						else if (tokentype == "if"){
							funcifKeyword(evaluatefun,funpos);
							nestedifflag = 1;
						}
						else if(tokentype == ""){

						}
					*funpos +=1;
			}

			}
		else{
			while(!utstrcmp((*evaluatefun)[*funpos],"else")){
				if(utstrcmp((*evaluatefun)[*funpos],"fi")){
					return;
				}
				whatsnext(evaluatefun,funpos);
			}
			//read_next_token();

			while (!utstrcmp((*evaluatefun)[*funpos],"fi")){

						String tokentype = (*evaluatefun)[*funpos];

							if (tokentype == m.output) {
									funcPrintNum(evaluatefun,funpos);
								} else if (tokentype == m.text) {
									funcPrintString(evaluatefun,funpos);
								} else if (tokentype == m.var) {
									funcDeclareVariable(evaluatefun,funpos);
								} else if (tokentype == m.set) {
									funcSetVariable(evaluatefun,funpos);
								} else if (tokentype == m.comments) {
									skip_line();
								} else if (tokentype == "do"){
									funcloopdoKeyword(evaluatefun,funpos);
								}
								else if (tokentype == "if"){
									funcifKeyword(evaluatefun,funpos);
									nestedifflag = 1;
								}
								else if(tokentype == ""){

								}
							*funpos +=1;
					}

					}
	//if(nestedifflag ==1){nestedifflag = 0; read_next_token();}
}
void funcifKeyword(Vector* evaluatefun,uint32_t* funpos){
	whatsnext(evaluatefun,funpos);

	int value;
	if(utstrcmp(peeknext(evaluatefun,funpos),"SYMBOL")){
		value = funccondition(evaluatefun,funpos);
		funcifSymbol(value,evaluatefun,funpos);
	}
	else if(utstrcmp(peeknext(evaluatefun,funpos),"NUMBER")){
		value = token_number_value;
		//read_next_token();
		funcifSymbol(value,evaluatefun,funpos);
	}
	else if(utstrcmp(peeknext(evaluatefun,funpos),"CALL")){
		value = funcJumpto(evaluatefun,funpos);
		funcifSymbol(value,evaluatefun,funpos);
	}
	else if(utstrcmp(peeknext(evaluatefun,funpos),"NAME")){
		String variable((*evaluatefun)[*funpos]);
		int value = Map.get(variable);
		funcifSymbol(value,evaluatefun,funpos);
	}


	}

String looptoSubString(String evaluate,Vector* block, uint32_t* blockpos){

	do{


			char* symbol = statement(block,blockpos);

			String next(peek(block,blockpos));
						if(utstrcmp(peek(block,blockpos),"KEYWORD")){
							*blockpos = *blockpos-2;
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
	    else if(utstrcmp(syntax,"call")){
	    	return "CALL";
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
