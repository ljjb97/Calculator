#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct listnode {
    double* double_value;
    char* char_value;
	char* funct;
    struct listnode* next;
	struct listnode* previous;
} listnode_t;

listnode_t *create_listnode_link(listnode_t* next_link,double double_value,
char char_value, char funct)
{
	listnode_t *ptr;
	ptr = malloc(sizeof(listnode_t));
	assert(ptr != NULL);
	if(double_value == 0 && char_value != 0) 
	{
		ptr->double_value = NULL;
		ptr->funct = NULL;
		ptr->char_value = malloc(sizeof(char));
		assert(ptr->char_value != NULL);
		ptr->char_value[0] = char_value;
		ptr->next = next_link;
		if(ptr->next != NULL) {
			ptr->next->previous = ptr;
		} ptr->previous = NULL;
	} 
	else if(double_value != 0 && char_value == 0) 
	{
		ptr->char_value = NULL;
		ptr->funct = NULL;
		ptr->double_value = malloc(sizeof(double));
		assert(ptr->double_value != NULL);
		ptr->double_value[0] = double_value;
		ptr->next = next_link;
		if(ptr->next != NULL) {
			ptr->next->previous = ptr;
		}ptr->previous = NULL;
	}
	else
	{
		ptr->double_value = NULL;
		ptr->char_value = NULL;
		ptr->funct = malloc(sizeof(char));
		assert(ptr->funct != NULL);
		ptr->funct[0] = funct;
		ptr->next = next_link;
		if(ptr->next != NULL) {
			ptr->next->previous = ptr;
		}ptr->previous = NULL;
	}
	return ptr;
	
}


listnode_t* move(listnode_t *function, listnode_t *origin, listnode_t *destination) /*moves a node from origin to after destination address*/
{
	listnode_t *before_origin = NULL, *start = function;
	for(;function->next != NULL;function = function->next) {
		if(function->next == origin) {
			before_origin = function;
		} 
	}
	if(before_origin != NULL){
		before_origin->next = origin->next;
	}
	origin->next = destination->next;
	destination->next = origin;
	return start;
}

listnode_t* traverse_until(listnode_t *list, char char_or_funct,
char value)
{
	if (char_or_funct == 'c'){
		for(;list != NULL;) {
			if(list->char_value != NULL) {
				if(list->char_value[0] == value) {
					return list;
				} else if(list->funct[0] != value) {
					list = list->next;
				}
			}else if(list->next == NULL){
				return NULL;
		  	} else {
				list = list->next;
			}
		}
		return NULL;
	} else if (char_or_funct == 'f'){
		for(;list != NULL;) {
			if(list->next == NULL) {
				return NULL;
			} else if(list->funct != NULL) { 
				if(list->funct[0] == value) {
					return list;
				} else if(list->funct[0] != value) {
					list = list->next;
				}

			} else {
				list = list->next;
			}

		}
		return NULL;
	}
	else return NULL;
}

listnode_t* order_of_ops(listnode_t* function)
{
	listnode_t* highest_order = NULL;
	for(;; function = function->next) {
		if(function->next == NULL) {
			return highest_order;
		} else if(function->funct == NULL) {
		} else if(function->funct[0] == '=') {
			return highest_order;
		} else if(function->funct[0] != '=') {
			if((function->funct[0] == '+' || function->funct[0] == '-') && highest_order == NULL) {
				highest_order = function;
			} else if(function->funct[0] == '*' || function->funct[0] == '/') {
				if(highest_order == NULL) {
					highest_order = function;
				} else if(highest_order->funct[0] == ('+' || '-')) {
					highest_order = function;	
				}
			} else if(function->funct[0] == '(' || function->funct[0] == ')') {
				if(function->funct[0] == '('){
					highest_order = function;
				}
			}
		}
	}
}

listnode_t* calculate(listnode_t* function)
{
	listnode_t* moving = function;
	for(;function->next != NULL;) {
		listnode_t* first = NULL;
		first = order_of_ops(function);
		if(moving->next == first) {
			if(first->funct[0] == '(') {
			}else if(first->funct[0] == '*') {
				moving->double_value[0] = moving->double_value[0] * first->next->double_value[0];
				moving->next = moving->next->next->next;
			} else if(first->funct[0] == '/') {
				moving->double_value[0] = moving->double_value[0] / first->next->double_value[0];
				moving->next = moving->next->next->next;
			} else if(first->funct[0] == '+') {
				moving->double_value[0] = moving->double_value[0] + first->next->double_value[0];
				moving->next = moving->next->next->next;			
			} else if(first->funct[0] == '-') {
				moving->double_value[0] = moving->double_value[0] - first->next->double_value[0];
				moving->next = moving->next->next->next;
			} else {
				return NULL;
			}
		} else if(moving->next == NULL) {
			moving = function; 
		} else if(first == NULL){
			return function;
		}else {
			moving = moving->next;
		}
	}
	return function;

}
