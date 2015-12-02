/*
 * HashMap.h
 *
 *  Created on: Nov 14, 2015
 *      Author: kevin
 */

#ifndef HASHMAP_H_
#define HASHMAP_H_
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Parse.h"
#include "String.h"

class LinkedHashEntry {
private:
      String variable;
      int value;
      LinkedHashEntry* next;
public:

      LinkedHashEntry(void) {
      this->variable = "";
      this->value = 0;
      this->next = NULL;
      }

      LinkedHashEntry(String key, int value){
    	  this->variable = key;
    	  this->value=value;
    	  this->next = NULL;
      }

      String getKey(){
    	return variable;
    }

      int getValue() {
        return value;
     }


    void setKey(String key){
    	this->variable = key;
    }

    void setValue(int value){
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

    LinkedHashEntry* getNext(){
    	return next;
    }

    void setNext(LinkedHashEntry* next){
    	this->next = next;
    }

~LinkedHashEntry(void){
	this->variable = "";
	this->value = 0;
}


};

const int TABLE_SIZE = 128;
template <typename T,typename K>
class HashTable{
private:
	LinkedHashEntry **table;
public:
	  HashTable(){
	  table = new LinkedHashEntry*[TABLE_SIZE];
	  for (int i = 0; i < TABLE_SIZE; i++)
	  table[i] = NULL;
	      }


	  bool put(T newRecord) {
		 int hash = (newRecord.getHash(TABLE_SIZE));//hash already accounts for table size

	           // while (table[hash] != NULL && table[hash]->getKey() != newRecord.getKey())//sure there can be two identical keys
	                  //hash = (hash + 1) % TABLE_SIZE;
	            //if (table[hash] != NULL){
	            	//return false; 

            //else{

	            //table[hash] = new LinkedHashEntry(newRecord);
	           //return true;
		if(table[hash] == NULL || table[hash]->getKey() == ""){
			table[hash] = new LinkedHashEntry(newRecord.getKey(),newRecord.getValue()); //first value first
			return true;
		}
		else{
			LinkedHashEntry* entry = table[hash];// table[hash] is a linkedhash initself
			while(entry->getNext()!=NULL){//create the linked list chains
				entry = entry->getNext(); //

			if(entry->getKey() == newRecord.getKey()){
				//entry->setValue(newRecord.getValue());
				return false;
	            }
	        else{
	        	entry->setNext(new LinkedHashEntry(newRecord.getKey(),newRecord.getValue()));
	        	return true;
	        }
	      }
	  }
	  }




	  bool reassign(T newRecord){
		  int hash = (newRecord.getHash(TABLE_SIZE));
		  if(table[hash] == NULL){return false;}

		  	LinkedHashEntry* entry = table[hash];

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
		
	  

	  int get(K key) {
		  T tempRecord;
		  tempRecord.setKey(key);
	            int hash = (tempRecord.getHash(TABLE_SIZE));

	            
	            if (table[hash] == NULL)
	                  return -1;
	            else{

	            	LinkedHashEntry *entry = table[hash];
	            	while(entry != NULL && entry->getKey() != key)
	            		entry = entry->getNext();
	            	if(entry == NULL)
	            		return -1;
	            	else
	                  	return entry->getValue();

	  }
	      }
	      


	  void resetHashTable() {
		  for (int i = 0; i < TABLE_SIZE; i++){
		  			      if (table[i] != NULL){
		  			    	  table[i]->setKey("");//set all the values to "" as a temp reset
		  			      }

		  			      }


	  }


	  ~HashTable(){
	  	 for (int i = 0; i < TABLE_SIZE; i++)
                  if (table[i] != NULL) {
                        LinkedHashEntry *prevEntry = NULL; //temp variable
                        LinkedHashEntry *entry = table[i]; //current entry
                        while (entry != NULL) {
                             prevEntry = entry; //go into previous value and reset
                             entry = entry->getNext();
                             delete prevEntry; 
                        }
                  }
            delete[] table;
      }

	  };







#endif /* HASHMAP_H_ */
