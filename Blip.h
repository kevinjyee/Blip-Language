/*
 * Blip.h
 *
 *  Created on: Nov 14, 2015
 *      Author: kevin
 */

#ifndef BLIP_H_
#define BLIP_H_

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



bool stopEval(String);
String toSubString(String, int);
String toSubStringCopy(String);
String returnwithHash(const char*);
void PrintString(void);
void PrintNum(void);
void DeclareVariable(void);
void SetVariable(void);
void executeBlock(Vector*);
int condition();
Vector* saveBlock();
void doKeyword();
void ifSymbol(int);
void ifKeyword(void);
void reset(void);
int Jumpto(void);
bool IS_KEYWORD(char*);
char* statement(Vector*,uint32_t*);
char* peek(Vector*,uint32_t*);








extern struct symbols m;
extern HashTable<LinkedHashEntry,String> Map;
extern HashTable<LinkedHashEntry,String> Map2;
extern Hashdefun<HashFunction,String> Func;
//extern Vector* block;
extern Vector* evaluatefun;
extern int HashTableFlag;
//extern uint32_t blockpos;
extern  uint32_t funpos;

extern Vector* arguments;
extern int array[10];

#endif /* BLIP_H_ */
