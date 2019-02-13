#pragma once
#include <stdlib.h>
#include <string.h>
#include <stdio.h> 
#include <iostream> 


void StringListInit(char** list);

void StringListDestroy(char** list);

void Display (char* list);

void StringListAdd(char** list, char* str);

void StringListRemove(char** list, char* str);

int get_StringListSize(char** list);

int StringListIndexOf(char** list, char* str);

void StringListRemoveDuplicates(char** list);

void StringListSort(char** list);

void StringListReplaceInStrings(char** list, char* before, char* after);