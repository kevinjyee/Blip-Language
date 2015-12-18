/*
 * Operators.h
 *
 *  Created on: Nov 14, 2015
 *      Author: kevin
 */

#ifndef OPERATORS_H_
#define OPERATORS_H_
#include "String.h"

struct symbols{
	String plus = "+";
	String minus = "-";
	String divide = "/";
	String multiply = "*";
	String mod ="%";

	String and1 = "&&";
	String or1 = "||";


	String less = "<";
	String greater = ">";
	String equalto = "==";
	String notequal = "!=";
	String lessequal = "<=";
	String greatequal = ">=";


	String not1 = "!";
	String negative = "~";

	String output = "output";
	String text ="text";
	String var = "var";
	String set = "set";
	String comments = "//";
	String empty = "";
	String dostmt = "do";
	String od = "od";
	String fi = "fi";
	String call = "call";
	String args = "args";
	String sgra = "sgra";
	String ifstmt = "if";
	String elsestmt = "else";
	String returnstmt = "return";
	String defun ="defun";
	String nufed = "nufed";

};



#endif /* OPERATORS_H_ */
