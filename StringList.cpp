#include "stdafx.h"
#include "StringList.h"

#define SIZE_OF_NODE (sizeof(char *) * 2)

void StringListInit(char** list)
{
	*list = NULL;
}

void StringListDestroy(char** list)
{
	int* prevString = NULL;
	int tmp = get_StringListSize(list);
	int count_strings = 0;
	while ((int*)*list != NULL)
	{
		int* next = (int*)*list;
		while ((int*)*next != NULL)
		{
			count_strings++;
			if (count_strings == tmp && tmp != 0)
			{
				prevString = next;
				tmp--;
			}
			next = (int*)*next;
		}
		
		count_strings = 0;
		free((void*)((int*)*(next + 1)));
		free((void*)next);
		*(int*)(list) = NULL;		
	}
}

void StringListAdd(char** list, char* str)
{
	if (*list)
	{
		int* next = (int*)*list;
		while (*next != NULL) next = (int*)*next;

		char* newNode = (char*)malloc(SIZE_OF_NODE);
		int* value = (int*)(newNode + sizeof(char*));
		*value = (int)malloc(strlen(str) + 1);
		strcpy((char *)*value, str);
		*next = (int)newNode;
		*((int*)newNode) = NULL;
	}
	else
	{
		char* newNode = (char*)malloc(SIZE_OF_NODE);
		int* value = (int*)(newNode + sizeof(char*));
		*value = (int)malloc(strlen(str) + 1);
		strcpy((char *)*value, str);
		*((int*)newNode) = NULL;
		*list = (char*)newNode;

	}
}

int get_StringListSize(char** list)
{
	int* next = (int*)(*list);
	int count = 0;
	while (next != NULL)
	{
		count++;
		next = (int*)*next;
	}
	return count;
}
int StringListIndexOf(char** list, char* str)
{
	int* next = (int*)*list;
	int count = 1;
	
	while (next != NULL)
	{
		if (!strcmp((char*)*(next + 1), str))
			break;
		else
			count++;
		
		next = (int*)*next;
	}
	return count;

}
void StringListRemove(char** list, char* str)
{
	int* next = (int*)*list;
	int* tmp = NULL;

	while (next != NULL)
	{
		if (!strcmp((char*)*(next + 1), str))
		{
			free((void*)*(next + 1));

			if (tmp)
				*tmp = *next;
			else
				*list = (char*)*next;	
			
			void* mem_to_del = (void*)next;
			next = (int*)*next;
			free(mem_to_del);

		}
		else
		{
			tmp = next;
			next = (int*)*next;
		}
	}
}

void StringListReplaceInStrings(char** list, char* before, char* after)
{
	int* next = (int*)*list;

	while (next != NULL)
	{
		if (!strcmp((char*)*(next + 1), before))
		{
			*(next + 1) = (int)realloc((void*)*(next + 1), strlen(after) + 1);
			strcpy((char*)*(next + 1), after);
		}
		next = (int*)*next;
	}
}

void StringListSort(char** list)
{
	int tmp = 0;
	for (int* next = (int*)*list; next != NULL; next = (int*)*next)
	{
		int* min_element = next;
		for (int* iter_node = (int*)*(next); iter_node != NULL; iter_node = (int*)*iter_node)
		{
			if (strcmp((char*)*(iter_node + 1), (char*)*(min_element + 1)) < 0)
				min_element = iter_node;
		}
		tmp = *(next + 1);
		*(next + 1) = *(min_element + 1);
		*(min_element + 1) = tmp;
	}
}

void StringListRemoveDuplicates(char** list)
{
	StringListSort(list);

	for (int* next = (int*)*list; *(next) != NULL;)
	{
		if (!strcmp((char*)*(next + 1), (char*)*(((int*)*next) + 1)))
		{
			free((void*)*(((int*)*next) + 1));

			void* node_to_free = (void*)*next;
			*next = *((int*)*next);
			free(node_to_free); 
		}
		else
		{
			next = (int*)*next;
		}
	}
}

void Display(char* list)
{
	char* next;
	char* tmp;
	if (list != nullptr)
	{
		printf("StringList\n----------\n");
		while (list != nullptr)
		{
			tmp = (char*)*((int*)(list + sizeof(char*)));
			printf("%s\n", tmp);
			list = (char*)*((int*)(list));
		}
	}
	else
		printf("List is empty\n");
}