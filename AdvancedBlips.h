/*
 * AdvancedBlips.h
 *
 *  Created on: Nov 29, 2015
 *      Author: kevin
 */
#include "Vector.h"

#ifndef ADVANCEDBLIPS_H_
#define ADVANCEDBLIPS_H_
void loopPrintString(Vector*, uint32_t*);
void loopPrintNum(Vector*, uint32_t*);
void loopifKeyword(Vector*, uint32_t*);
void loopDeclareVariable(Vector*,uint32_t*);

void funcloopdoKeyword(Vector*,uint32_t*);
Vector*  funcloopsaveBlock(Vector*,uint32_t*);
void funcPrintNum(Vector* , uint32_t* );
void funcPrintString(Vector*, uint32_t* );
void funcSetVariable(Vector*, uint32_t*);
void funcifKeyword(Vector*,uint32_t*);
String functoSubString(String,Vector* , uint32_t*);
String functionParser(String);
void functionCall(void);
int loopJumpto(Vector*, uint32_t*);
int executeFunction(Vector*);
int evaluateFunction(String);
int funcJumpto(Vector*, uint32_t*);
void loopSetVariable(Vector* , uint32_t*);
void loopdoKeyword(Vector* , uint32_t*);
int loopfuncJumpto(Vector*, uint32_t*);
String looptoSubString(String ,Vector* , uint32_t*);
char* peeknext(Vector*,uint32_t*);
char* whatsnext(Vector*, uint32_t*);

void loopfunctionCall(Vector*, uint32_t*,int);
String loopfunctionParser(String,Vector*, uint32_t*);
extern int countdo;



#endif /* ADVANCEDBLIPS_H_ */



