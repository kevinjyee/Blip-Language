/*
 * StringEvaluate.h
 *
 *  Created on: Nov 15, 2015
 *      Author: kevin
 */
#include "String.h"
#ifndef STRINGEVALUATE_H_
#define STRINGEVALUATE_H_


char* itoa(int, int);
int ParseSubString(String);
int StackString(String);
int operation(String*, int, int);
constexpr unsigned int str2int(const char*, int h);
int32_t utstrcmp(const char*, const char*);
bool IS_NUMBER(char c);

bool IS_LETTER(char c);

bool IS_SPACE(char c);
extern int whitespacepos;

#endif /* STRINGEVALUATE_H_ */
