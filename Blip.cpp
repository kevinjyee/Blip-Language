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

struct symbols m;
HashTable<LinkedHashEntry,String> Map;
HashTable<LinkedHashEntry,String> Map2;
Hashdefun<HashFunction,String> Func;
Vector* block = new Vector();
Vector* arguments = new Vector();
int array[10]= {0,0,0,0,0,0,0,0,0,0};

int HashTableFlag =0;
uint32_t blockpos = 0;
//uint32_t funpos =0;

/*******Function: stopEval*********
 *
 */

bool stopEval(String next){
	if(next == m.output ||
	   next == m.text ||
	   next == m.var ||
	   next == m.set ||
	   next == m.comments ||
	   next == m.empty||
	   next == m.fi||
	   next==m.elsestmt ||
	   next == m.ifstmt||
	   next == m.dostmt||
	   next == m.od){
				return true;
				}
	return false;
}
/*******Function: toSubString*******
 * String Parser. Retruns an evaluated Parse String
 */
String toSubString(String evaluate, int flag =0){

	do{

			read_next_token();

			String symbol(next_token());
			if(next_token_type == SYMBOL){
			evaluate.append(next_token());

			}
			else if(next_token_type == NAME){
				String key(next_token());
				int x = Map.get(key);

				char* y = itoa (x,10);
				evaluate.append(y);
			}
			else if(next_token_type == NUMBER){
				evaluate.append(next_token());

			}
			flag++;
			String next(peek_next_token());
			if(stopEval(next)){
				break;
			}
		}while(true) ;

return  evaluate;
}

/*******Function: toSubStringCopy*******
 * String Parser. Returns an unevaluated Parsed String
 */
String toSubStringCopy(String evaluate){


	do{

		String next(peek_next_token());
					if(stopEval(next)){
						evaluate.append(" ");
									break;
								}
			read_next_token();

			String symbol(next_token());
			if(next_token_type == SYMBOL){
			evaluate.append(next_token());

			}
			else if(next_token_type == NAME){
				String key(next_token());
				int x = Map.get(key);

				char* y = itoa (x,10);
				evaluate.append(next_token());
			}
			else if(next_token_type == NUMBER){
				evaluate.append(next_token());

			}
			//flag++;

		}while(true) ;

return  evaluate;
}

/*******Function: returnwithHash*******
 * Used to evaluate "toSubStringCopy"
 */
String returnwithHash(const char* evaluate){
	String temp(evaluate);
	char hashed[100];
	for(int i =0; i <100; i++){
	 hashed[i] = 0;
	}
	char keyk[10] = {0,0,0,0,0,0,0,0,0,0};
	int i =0;
	int j =0;
	int k=0;
	while(evaluate[i] != 0){

		 if(IS_LETTER(evaluate[i])){
			 while(evaluate[i] != ' '){
				 keyk[k++] = evaluate[i++];

			 }
			String key = keyk;
			int x = Map.get(key);
			char* y = itoa(x,10);


			k=0;
			while(y[k] != 0){
				hashed[j++] = y[k++];
			}

		}
		 else{
				 hashed[j++] = evaluate[i++];
	}

}
	//hashed[j] = evaluate[--i];
	String evaluated(hashed);
	return evaluated;
}
/*******Function: looptoSubString*******
 * String Parser. Returns an evaluated Parse String in a do loop
 */



/*******Function: Print String*******
 * Basic String Print
 */
void PrintString(void){
read_next_token();
printf("%s",next_token());
}


/*******Function: Print String*******
 * Basic Number Print
 */
void PrintNum(void){
	read_next_token();
	if(next_token_type == NUMBER){
		printf("%d",token_number_value);
	}

	else if(next_token_type == NAME){
		String key(next_token());
		int value = Map.get(key);
		if(value == -1){printf("WARNING Variable is undeclared\n");}
		else{

		printf("%d",value);
		}
	}

	else if(next_token_type == SYMBOL){
		String evaluate(next_token());
		evaluate =toSubString(evaluate);
		int value= StackString(evaluate);
		//whitespacepos =0;
		printf("%d",value);
		//ParseTree eval;

}

}

/*******Function: Declare Variable*******
 * Basic Variable Declaration
 */
void DeclareVariable(void){
	HashTableFlag = 1;
read_next_token();
String variable(next_token());

read_next_token();

if(next_token_type == NUMBER){
	LinkedHashEntry Entry(variable, token_number_value);
	if(!Map.put(Entry)){
		printf("WARNING. Variable has already been declared\n");
	}
	}

else if(next_token_type == SYMBOL){
	String evaluate(next_token());
	evaluate = toSubString(evaluate);
	int value =StackString(evaluate);
	//whitespacepos =0;
LinkedHashEntry Entry(variable, value);
if(!Map.put(Entry)){
	printf("WARNING. Variable has already been declared\n");
}

}
else if(next_token_type == NAME){
	int value = Jumpto();
	LinkedHashEntry Entry(variable, value);
	if(!Map.put(Entry)){
			printf("WARNING. Variable has already been declared\n");
		}
}
else{
		printf("Variable cannot be evaluated\n");

}
}


/*******Function: Set Variable******
 * Basic Variable Reassign
 */
void SetVariable(void){
read_next_token();
String variable(next_token());
read_next_token();
if(next_token_type == NUMBER){
LinkedHashEntry Entry(variable, token_number_value);
 if(!Map.reassign(Entry)){printf("variable %s not declared\n",variable.c_str());}
}
else if(next_token_type == SYMBOL){
	String evaluate(next_token());
	evaluate = toSubString(evaluate);
	int value =StackString(evaluate);
	//whitespacepos =0;

LinkedHashEntry Entry(variable, value);
if(!Map.reassign(Entry)){printf("variable %s not declared\n",variable.c_str());}
}

else if(next_token_type == NAME){
	int value = Jumpto();
	LinkedHashEntry Entry(variable, value);
	if(!Map.reassign(Entry)){
			printf("variable %s not declared\n",variable.c_str());
		}
}

else{
		printf("Variable cannot be evaluated\n");

}
}


/*******Function:execute block******
 * Executes block in a loop
 */

void executeBlock(){
	blockpos = 0;

	while (!utstrcmp((*block)[blockpos],"od")){
		char* keywordtype = (*block)[blockpos];

			if (utstrcmp(keywordtype, "output")) {
				loopPrintNum();
			} else if (utstrcmp(keywordtype, "text")) {
				loopPrintString();
			} else if (utstrcmp(keywordtype, "var")) {
				DeclareVariable();
			} else if (utstrcmp(keywordtype, "set")) {
				loopSetVariable();
			} else if (utstrcmp(keywordtype, "//")) {
				skip_line();
			} else if (utstrcmp(keywordtype, "do")){
				doKeyword();
			} else if (utstrcmp(keywordtype, "if")){
				loopifKeyword();
			} else if (utstrcmp(keywordtype, "defun")){
				functionCall();
			} else if (utstrcmp(keywordtype, "call")){
				Jumpto();
			}
			else{

			}
			if(utstrcmp((*block)[blockpos],"od")){break;}
			blockpos +=1;

	}

}

/*******Function: condition******
 * Evaluates condition of an if statement
 */
int condition(){

	String evaluate(next_token());
	evaluate = toSubString(evaluate);
	int value =StackString(evaluate);
	return value;

}

/*******Function: saveBlock******
 * Puts the expressions into a vector
 */

void saveBlock(){
   // read_next_token();
    while (!utstrcmp((char*)next_token(),"od")) {
        String* temp = new String((char*) next_token());
        block->push_back((char*) temp->c_str());
        read_next_token();
        String next(peek_next_token());
        	if(stopEval(next)){
        		block->push_back(" ");
        		}

    }
    block->push_back("od");
}


/*******Function: doKeyword******
 * Basic While Loop
 */
void doKeyword(){
	peek_next_token();
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
	block->reset();
}

/*******Function: ifSymbol******
 * Evaluates the ifStatement
 */

void ifSymbol(int value){
	int nestedifflag = 0;
	if(value){
			while (!utstrcmp(next_token(),"fi")){
				if(utstrcmp(next_token(),"else")){
					while(!utstrcmp(next_token(),"fi")){
						read_next_token();
					}
					break;
				}
				read_next_token();
				String KEYWORD = (next_token());

					if (KEYWORD == m.output) {
							PrintNum();
						} else if (KEYWORD == m.text) {
							PrintString();
						} else if (KEYWORD == m.var) {
							DeclareVariable();
						} else if (KEYWORD == m.set) {
							SetVariable();
						} else if (KEYWORD == m.comments) {
							skip_line();
						} else if (KEYWORD == "do"){
							doKeyword();
						}
						else if (KEYWORD == "if"){
							ifKeyword();
							nestedifflag = 1;
						}
						else if(KEYWORD == ""){

						}
			}

			}
		else{
			while(!utstrcmp(next_token(),"else")){
				if(utstrcmp(next_token(),"fi")){
					return;
				}
				read_next_token();
			}
			//read_next_token();

			while (!utstrcmp((char*) next_token(),"fi")){
						read_next_token();
						String KEYWORD = (next_token());

							if (KEYWORD == m.output) {
									PrintNum();
								} else if (KEYWORD == m.text) {
									PrintString();
								} else if (KEYWORD == m.var) {
									DeclareVariable();
								} else if (KEYWORD == m.set) {
									SetVariable();
								} else if (KEYWORD == m.comments) {
									skip_line();
								} else if (KEYWORD == "do"){
									doKeyword();
								}
								else if (KEYWORD == "if"){
									ifKeyword();
									nestedifflag = 1;
								}
								else if(KEYWORD == ""){

								}
					}

					}
	//if(nestedifflag ==1){nestedifflag = 0; read_next_token();}
}


/*******Function: ifKeyword******
 * If Statement determining if an if statement needs to be evaluated
 */
void ifKeyword(void){
	read_next_token();
	int value;
	if(next_token_type == SYMBOL){
		value = condition();
		ifSymbol(value);
	}
	else if(next_token_type == NUMBER){
		value = token_number_value;
		//read_next_token();
		ifSymbol(value);
	}


	}


void reset(void){
	if(HashTableFlag!=0)Map.resetHashTable();
	stack.reset();
	HashTableFlag = 0;
}



int Jumpto(void){
int i = 0;
read_next_token();
String functionname(next_token());
String expression(Func.get(functionname));
read_next_token();

while(!utstrcmp(next_token(),"sgra")){
read_next_token();
if(utstrcmp(next_token(),"sgra")){break;}
if(next_token_type == NAME){
String variable((char*) next_token());
int value = Map.get(variable);
array[i++] = value;
}
else if(next_token_type == NUMBER){
	array[i++] = token_number_value;
}
else if(next_token_type == SYMBOL){
	String evaluate(next_token());
	evaluate = toSubString(evaluate);
	int numbereval = StackString(evaluate);
	array[i++] = numbereval;
}
}


int evaluated = evaluateFunction(expression);
return evaluated;
}




bool IS_KEYWORD(char* t) {

    if (utstrcmp(t, "var")) {
        //command = VAR;
        return true;
    } else if (utstrcmp(t, "set")) {
        //command = SET;
        return true;
    } else if (utstrcmp(t, "output")) {
        //command = OUTPUT;
        return true;
    } else if (utstrcmp(t, "text")) {
        //command = TEXT;
        return true;
    } else if (utstrcmp(t, "do")) {
        //command = DO;
        return true;
    } else if (utstrcmp(t, "if")) {
       // command = IF;
        return true;
    } else if (utstrcmp(t, "else")) {
        //command = ELSE;
        return true;
    }else if (utstrcmp(t, "return")) {
        //command = ELSE;
        return true;
    }else if(utstrcmp(t,"nufed")){
    	return true;
    }
    return false;
}

char* statement(){


    char* syntax = (*block)[blockpos];
    blockpos = blockpos + 1;
    if (IS_NUMBER(syntax[0])) {
        next_token_type = NUMBER;
        token_number_value = atoi(syntax);
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



char* peek(){
	int peeknumber = blockpos;
	//peeknumber += 1;
	char* syntax = (*block)[peeknumber];
	if (IS_NUMBER(syntax[0])) {
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



