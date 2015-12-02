/*
 * HashFunction.h
 *
 *  Created on: Nov 28, 2015
 *      Author: kevin
 */

#ifndef HASHFUNCTION_H_
#define HASHFUNCTION_H_
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Parse.h"
#include "String.h"

class HashFunction {
private:
      String variable;
      String value;
      HashFunction* next;
public:

      HashFunction(void) {
      this->variable = "";
      this->value = "";
      this->next = NULL;
      }

      HashFunction(String key, String value){
    	  this->variable = key;
    	  this->value=value;
    	  this->next = NULL;
      }

      String getKey(){
    	return variable;
    }

      String getValue() {
        return value;
     }


    void setKey(String key){
    	this->variable = key;
    }

    void setValue(String value){
    	this->value = value;
    }


    int getHash(int M){
    	uint32_t index =0;
    	for (int i=0; i<variable.size();i++){
    		index *= 33;
    		index += (int) variable[i];

    	}
    	index = index%M;
    	return index;
    }

    HashFunction* getNext(){
    	return next;
    }

    void setNext(HashFunction* next){
    	this->next = next;
    }

~HashFunction(void){
	this->variable = "";
	this->value = "";
}


};

const int FUNCTION_SIZE = 128;
template <typename T,typename K>
class Hashdefun{
private:
	HashFunction **table;
public:
	  Hashdefun(){
	  table = new HashFunction*[FUNCTION_SIZE];
	  for (int i = 0; i < FUNCTION_SIZE; i++)
	  table[i] = NULL;
	      }


	  bool put(T newRecord) {
		 int hash = (newRecord.getHash(FUNCTION_SIZE));//hash already accounts for table size

	           // while (table[hash] != NULL && table[hash]->getKey() != newRecord.getKey())//sure there can be two identical keys
	                  //hash = (hash + 1) % FUNCTION_SIZE;
	            //if (table[hash] != NULL){
	            	//return false;

            //else{

	            //table[hash] = new HashFunction(newRecord);
	           //return true;
		if(table[hash] == NULL || table[hash]->getKey() == ""){
			table[hash] = new HashFunction(newRecord.getKey(),newRecord.getValue()); //first value first
			return true;
		}
		else{
			HashFunction* entry = table[hash];// table[hash] is a linkedhash initself
			while(entry->getNext()!=NULL){//create the linked list chains
				entry = entry->getNext(); //

			if(entry->getKey() == newRecord.getKey()){
				//entry->setValue(newRecord.getValue());
				return false;
	            }
	        else{
	        	entry->setNext(new HashFunction(newRecord.getKey(),newRecord.getValue()));
	        	return true;
	        }
	      }
	  }
	  }




	  bool reassign(T newRecord){
		  int hash = (newRecord.getHash(FUNCTION_SIZE));
		  if(table[hash] == NULL){return false;}

		  	HashFunction* entry = table[hash];

		  while(entry->getNext()!=NULL && entry->getKey()!= newRecord.getKey())
			  entry = entry->getNext();
		  if(entry->getKey() == newRecord.getKey()){
			  entry->setValue(newRecord.getValue());
			  return true; //hash was found in linkedlist
		  }
		  else{
		  	  return false;
		  }

		  }



	  String get(K key) {
		  String fail("");
		  T tempRecord;
		  tempRecord.setKey(key);
	            int hash = (tempRecord.getHash(FUNCTION_SIZE));


	            if (table[hash] == NULL)
	                  return fail;
	            else{

	            	HashFunction *entry = table[hash];
	            	while(entry != NULL && entry->getKey() != key)
	            		entry = entry->getNext();
	            	if(entry == NULL)
	            		return fail;
	            	else
	                  	return entry->getValue();

	  }
	      }



	  void resetHashTable() {
		  for (int i = 0; i < FUNCTION_SIZE; i++){
		  			      if (table[i] != NULL){
		  			    	  table[i]->setKey("");//set all the values to "" as a temp reset
		  			      }

		  			      }


	  }


	  ~Hashdefun(){
	  	 for (int i = 0; i < FUNCTION_SIZE; i++)
                  if (table[i] != NULL) {
                        HashFunction *prevEntry = NULL; //temp variable
                        HashFunction *entry = table[i]; //current entry
                        while (entry != NULL) {
                             prevEntry = entry; //go into previous value and reset
                             entry = entry->getNext();
                             delete prevEntry;
                        }
                  }
            delete[] table;
      }

	  };












#endif /* HASHFUNCTION_H_ */
