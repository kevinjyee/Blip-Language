/*
 * AdvancedBlips.h
 *
 *  Created on: Nov 29, 2015
 *      Author: kevin
 */

#ifndef ADVANCEDBLIPS_H_
#define ADVANCEDBLIPS_H_
void loopPrintString(void);
void loopPrintNum(void);
void loopifKeyword(void);
void funcPrintNum(Vector* , uint32_t* );
void funcPrintString(Vector*, uint32_t* );
void funcSetVariable(Vector*, uint32_t*);
String functoSubString(String,Vector* , uint32_t*);
String functionParser(String);
void functionCall(void);
int executeFunction(Vector*);
int evaluateFunction(String);
int funcJumpto(Vector*, uint32_t*);
void loopSetVariable(void);
void loopdoKeyword(void);
int loopfuncJumpto(Vector*, uint32_t*);
String looptoSubString(String);
char* peeknext(Vector*,uint32_t*);
char* whatsnext(Vector*, uint32_t*);




#endif /* ADVANCEDBLIPS_H_ */



