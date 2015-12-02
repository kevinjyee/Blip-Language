/*
 * LinkedStack.h
 *
 *  Created on: Nov 16, 2015
 *      Author: kevin
 */

#ifndef LINKEDSTACK_H_
#define LINKEDSTACK_H_

struct node
{
 public:
    int data;
    node* next;
};

struct StackusingList
{
public:

StackusingList(int max)
{
    top = nullptr;
    maxnum = max;
    count=0;
}

void push(int element)
{
//    if(count == maxnum)
//            return;
//    else
//    {
        node *newTop = new node;
        if(top == nullptr)
        {
        	count++;
            newTop->data = element;
            newTop->next = nullptr;
            top = newTop;

        }
        else
        {
            newTop->data = element;
            newTop->next = top;
            top = newTop;
            count++;
        }
//    }
}

void pop()
{
    if(top == nullptr)
            return;
    else
    {
        node * old = top;
        top = top->next;
        count--;
        delete(old);
    }
}

int topofstack()
{
	if(top != nullptr){
    return top->data;
	}
}

void reset()
{
    node* current = top;

    while (current != nullptr)
    {
        node* next = current->next;
        delete current;
        current = next;
    }

    top = nullptr;
}


private:
    node *top;
    int count; //head
    int maxnum;

};

extern StackusingList stack;

#endif /* LINKEDSTACK_H_ */
