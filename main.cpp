#include <stdio.h>
#include <string>
#include <stdio.h> // declarations of FILE and printf
#include <stdlib.h> // includes declaration of exit()
#include "String.h"
#include "MemHeap.h"
#include "Parse.h"
#include "Blip.h"
#include "AdvancedBlips.h"

struct CheckMemoryLeaks {
	~CheckMemoryLeaks(void) {
		if (! isSaneHeap()) {
			printf("oh goodness! you've corrupted the heap, naughty naughty\n");
			return;
		}
		if (! isEmptyHeap()) {
			printf("Uh Oh! you have a memory leak somewhere, better find it\n");
			return;
		}
		printf("The heap is all clean, good work!\n");
	}
} MemoryChecker;


String output = String("output");
String text = String("text");
String var = String("var");
String set = String("set");
String comment = String("//");
String doloop = String("do");
String ifstatement = String("if");
String function = String("defun");
String call = String("call");



int firstcode =0;
void run() {
	if(firstcode != 0 && next_token_type == END){read_next_token();}

	while (next_token_type != END){


		if(firstcode == 0){read_next_token();}
		String KEYWORD = (next_token());
		if (KEYWORD == output) {
			PrintNum();
		} else if (KEYWORD == text) {
			PrintString();
		} else if (KEYWORD == var) {
			DeclareVariable();
		} else if (KEYWORD == set) {
			SetVariable();
		} else if (KEYWORD == comment) {
			skip_line();
		} else if (KEYWORD == doloop){
			doKeyword();
		}
		else if (KEYWORD == ifstatement){
			ifKeyword();
		}
		else if (KEYWORD == function){
			functionCall();
		}
		else if (KEYWORD == call){
			Jumpto();
		}
		else if(KEYWORD == ""){

		}
		else {
//			printf("Encountered an error in input file\n");
//			printf("The offending line has been ignored\n");
		}
		if(firstcode != 0){read_next_token();}
	}

	firstcode ++;
	reset();


	//displayTailAndClose();
}


int main(void){



//	printf("Test2\n");
//		set_input("test2.blip");
//		run();
//
//		printf("Test3\n");
//				set_input("test3.blip");
//				run();
//
//			printf("Test4\n");
//								set_input("test4.blip");
//								run();
	printf("Test6\n");
			set_input("test6.blip");
			run();

//	printf("Test1\n");
//		set_input("/home/kevin/workspace/Final/More Test Cases/test1.blip");
//		run();
//
//
//		printf("Test2\n");
//			set_input("/home/kevin/workspace/Final/More Test Cases/test2.blip");
//			run();
//
//			printf("Test3\n");
//				set_input("/home/kevin/workspace/Final/More Test Cases/test3.blip");
//				run();

//			printf("Test7\n");
//				set_input("/home/kevin/workspace/Final/More Test Cases/test7.blip");
//				run();

//			printf("Test7\n");
//			set_input("testIrene.blip");
//			run();

}


