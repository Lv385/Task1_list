// Task_1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "StringList.h"


int main()
{
	char *list;
	StringListInit(&list);
	std::cout << "Press\n"
		"1 to list your array\n"
		"2 to enter and add string to an array\n"
		"3 to enter and remove string from array\n"
		"4 to get the numbers of strings in array\n"
		"5 to enter a string and find index of it in array\n"
		"6 to sort list\n"
		"7 to remove duplicates\n"
		"8 to enter \"before\" and \"after\" string, and replace all \"before\" by \"after\"\n"
		"q to quit\n";
	char choice = '0';
	char* temp_str = (char*)malloc(sizeof(char) * 50);
	char* after_str = (char*)malloc(sizeof(char) * 50);
	

	while ((choice = getchar()) != 'q')
	{
		if (choice == '\n')
			continue;

		switch (choice)
		{
		case '1':
			Display(list);
			break;
		case '2':
			std::cout << "Enter a string to be added:\n";
			std::cin >> temp_str;
			StringListAdd(&list, temp_str);
			break;
		case '3':
			std::cout << "Enter a string to remove:\n";
			std::cin >> temp_str;
			StringListRemove(&list, temp_str);
			break;
		case '4':
			std::cout << "Number of strings in list:\n";
			printf("%d", get_StringListSize(&list));
			break;
		case '5':
			std::cout << "Enter a string: ";
			std::cin >> temp_str;
			printf("%d",StringListIndexOf(&list, temp_str));
			break;
		case '6':
			std::cout << "Sorted";
			StringListSort(&list);
			break;
		case '7':
			StringListRemoveDuplicates(&list);
			break;
		case '8':
			std::cout << "Enter a string before:\n";
			std::cin >> temp_str;
			std::cout << "Enter a string after:\n";
			std::cin >> after_str;
			StringListReplaceInStrings(&list, temp_str, after_str);
			break;
		default:
			std::cout << "Invalid input";
			break;
		}
	}
	StringListDestroy(&list);
	free(temp_str);
	free(after_str);
		system("pause");
    return 0;
}

