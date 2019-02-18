// Task1_dynamic_lists_str.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include "LinkedList.h"
using namespace std;

#define PTR_SIZE sizeof(char *) 

enum node {VALUE, NEXT_PTR, NODE_SIZE};

void StringListInit(char*** list) {
	*list = NULL;
}
void StringListAdd(char*** list, string str) {
	if (*list) { 
		char** lastNode = *list;//get root node
		while (lastNode[NEXT_PTR] != NULL){ 
			lastNode = (char**)lastNode[NEXT_PTR]; //find last node
		}
		char** newNode = (char**)malloc(PTR_SIZE*NODE_SIZE);
		newNode[VALUE] = (char*)malloc(str.size() + 1);
		memcpy(*newNode, str.c_str(), str.size() + 1);
		newNode[NEXT_PTR] = NULL;
		lastNode[NEXT_PTR] = (char*)newNode;//last node will be actually char** 		
	
	}
	else {//first time adding		
		//any type cast can be used here(perfectly it should be void* but 
		//we lose ability to perform pointer arithmetic); char** is chosen for consistency and clarity
		char** rootNode = (char**)malloc(PTR_SIZE*NODE_SIZE);
		rootNode[VALUE] = (char*)malloc(str.size() + 1);//rootNode[VALUE] is equivaent to *rootNode
		memcpy(*rootNode, str.c_str(), str.size() + 1);
		rootNode[NEXT_PTR] = NULL;//rootNode[NEXT_PTR] is equivaent to *(rootNode+1)		 
		*list = rootNode;		
	}
	
}
//
//in a case of local variable char** list (defined in main()) - it’s address should be received, 
//so char*** MUST be used in this implementation 

void StringListRemove(char*** list, string str) {
	char** prev = NULL;
	char** temp = NULL;
	char** currentNode=*list;
	while (currentNode != NULL) {
		string toCompare = currentNode[VALUE];
		if (!str.compare(toCompare)) { //strings are equal;
			free(currentNode[VALUE]);
			if (prev == NULL) {//head of the list will be removed
				temp = currentNode;
				*list= (char**)currentNode[NEXT_PTR];
			}else{//inside or at the end of a list
				prev[NEXT_PTR] = currentNode[NEXT_PTR];
			}
			currentNode = (char**)currentNode[NEXT_PTR];
			free(temp);
		}else {
			prev = currentNode;
			currentNode = (char**)currentNode[NEXT_PTR];
		}

	}
}


int StringListIndexOf(char** list, const char* str) {//TODO::Remove const
	int index = 0;
	while (list != NULL) {
		if (!strcmp(list[VALUE], str)) {
			return index;
		}
		list = (char**)list[NEXT_PTR];	
		index++;
	}
	return -1;
}



int StringListSize(char** list) {
	int size = 0;	
	while (list != NULL) {
		list = (char**)list[NEXT_PTR];
		size++;
	}
	return size;
}

void StringListDestroy(char*** list) {
	char** lastNode = *list;
	while (lastNode != NULL) {	
		char** temp = lastNode;
		lastNode = (char**)lastNode[NEXT_PTR];
		free(temp[VALUE]);
		free(temp);		
	}
	*list = NULL;
}

void printList(char*** list) {
	char** lastNode = *list;
	cout << "---------------------------------------" << endl;
	while (lastNode!= NULL) {
		cout <<lastNode[VALUE] << endl;
		lastNode = (char**)lastNode[NEXT_PTR];
	}
	cout << "---------------------------------------" << endl;
}

void StringListSort(char** list) {//simple bubble sort
	for (char** i = list; i[NEXT_PTR] != NULL; i = (char**)i[NEXT_PTR]) {
		for (char** j = list; j != NULL; j = (char**)j[NEXT_PTR]) {
			if (strcmp(i[VALUE], j[VALUE]) > 0) {
				char* temp = i[VALUE];//swap
				i[VALUE] = j[VALUE];
				j[VALUE] = temp;
			}		
		} 
	}
}
void StringListReplaceInStrings(char** list,  char* before,   char* after) {
	while (list != NULL) {
		if (!strcmp(list[VALUE], before)) {
			list[VALUE] = after;
		}
		list = (char**)list[NEXT_PTR];
	}
}
void StringListRemoveDuplicates(char** list) {
	char** prev = NULL;
	for (char** i = list; i[NEXT_PTR] != NULL; i = (char**)i[NEXT_PTR]) {
		prev = i;//at the beginning of a second loop char** i is always previous value to char** j
		for (char** j = (char**)i[NEXT_PTR]; j != NULL; j = (char**)j[NEXT_PTR]) {
			if (!strcmp(i[VALUE], j[VALUE])) {
				free(j[VALUE]);				
				prev[NEXT_PTR] = j[NEXT_PTR];
				free(j);
				j = prev;				
			}else {
				prev = j;
			}
		}
	}

}

int main()
{
	
	char** list;	
	StringListInit(&list);
	StringListAdd(&list, "Hello");
	StringListAdd(&list, "From");
	StringListAdd(&list, "From");
	StringListAdd(&list, "From");
	StringListAdd(&list, "LinkedList");
	StringListAdd(&list, "test");
	StringListAdd(&list, "test_other");
	StringListAdd(&list, "test_other2");
	StringListAdd(&list, "aaa");
	StringListAdd(&list, "test");
	
	//initial list
	cout << "Inital list content" << endl;
	printList(&list);
	
	//remove string from the list
	StringListRemove(&list, "From" );
	cout << "After deleting all occurence of \"From\""<<endl;
	printList(&list);
	
	//index of
	cout << "First occurence of \"LinkedList\"" << StringListIndexOf(list, "LinkedList") << endl;

	//list size
	cout << "Size of a linkedList is " << StringListSize(list) << endl;	
	
	//remove duplicates
	StringListRemoveDuplicates(list);
	cout <<endl<< "List after removed duplicates" << endl;
	printList(&list);
	
	//replace string 
	string before = "Hello";
	string after = "Hi";
	StringListReplaceInStrings(list, _strdup(before.c_str()), _strdup(after.c_str()));
	cout << "List after string replacement"<<endl;
	printList(&list);
	
	//sort list
	StringListSort(list);
	cout << "List after sorting" << endl;
	printList(&list);
	
	//destroy list 
	StringListDestroy(&list);
	
}


