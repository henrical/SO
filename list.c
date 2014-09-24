/*
 * list.c - implementation of the integer list functions 
 */


#include <stdlib.h>
#include <stdio.h>
#include "list.h"



list_t* lst_new()
{
   list_t *list;
   list = (list_t*) malloc(sizeof(list_t));
   list->first = NULL;
   return list;
	printf("new list created");
}


void lst_destroy(list_t *list)
{
   printf("lst_destroy\n");
}


void lst_insert(list_t *list, int value)
{
	lst_iitem_t *current, *previous;
	current = list->first;
	previous = NULL;
	
	lst_iitem_t *item;
	item = (lst_iitem_t*) malloc(sizeof(lst_iitem_t));
	item->value = value;
	item->next = NULL;

	if(list->first == NULL)
		{
		list->first = item;
		}
	else
		{
		while(current!=NULL)
			previous = current;
			current = current->next;
			printf("test");
		}

	if(previous!=NULL)
		previous->next = item;
			
		
	printf("lst_insert: value=%d\n", value);	
		
}


void lst_remove(list_t *list, int value)
{
   printf("lst_remove: value=%d\n", value);
}


void lst_print(list_t *list)
{
   printf("lst_print\n");
}
