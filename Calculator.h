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

typedef struct order_que {
	int order_number;
	listnode_t * ptr;
	struct order_que* next;
	struct order_que* previous;
} order_que_t;

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

listnode_t* append(listnode_t *end, int k, double i ) {
	listnode_t* new_link;
	if(i != 0) {
		new_link = create_listnode_link(NULL, i, 0, 0);
		new_link->previous = end;
		end->next = new_link;
		end = new_link;
	} else if(k >= 65) {
		new_link = create_listnode_link(NULL, 0, k, 0);
		new_link->previous = end;
		end->next = new_link;
		end = new_link;
	} else if(k < 65) {
		new_link = create_listnode_link(NULL, 0, 0, k);
		new_link->previous = end;
		end->next = new_link;
		end = new_link;
	}
	return end;
}

order_que_t* insert_que(order_que_t *start, listnode_t *link, int order)
{
	order_que_t *ptr, *temp = start;
	ptr = malloc(sizeof(order_que_t));
	for(;;){
		if(start == NULL) {
			ptr->next = NULL;
			ptr->previous = NULL;
			ptr->order_number = order;
			ptr->ptr = link;
			return ptr;
		} else if(start->order_number < order) {
			ptr->previous = start->previous;
			ptr->next = start;
			start->previous = ptr;
			ptr->ptr = link;
			ptr->order_number = order;
			return temp->previous;
 		} else if(start->next == NULL) {
			ptr->previous = start;
			start->next = ptr;
			ptr->next = NULL;
			ptr->ptr = link;
			ptr->order_number = order;
			return temp;
		} else if(start->order_number >= order) {
			start = start->next;
		}
	}
}

listnode_t *deque(order_que_t *start, order_que_t **startad) 
{
	listnode_t *temp1 = start->ptr;
	printf("8");
	order_que_t *temp2 = start->next;
	printf("9");
	if(temp2 != NULL) {
		temp2->previous = NULL;
	}
	*startad = temp2;
	free(start);
	printf("10");
	return temp1;
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

order_que_t* order_of_ops(listnode_t* function)
{
	int order = 0;
	order_que_t* que = NULL;
	for(;function->next != NULL; function = function->next) {
		order = order / 10 * 10;
		if(function->funct == NULL) {
		} else if(function->funct[0] == '=') {
			return que;
		} else if(function->funct[0] != '=') {
			if(function->funct[0] == '(' || function->funct[0] == ')') {
				if(function->funct[0] == '('){
					order += 10;
				} else if (function->funct[0] == ')') {
					order -= 10;
				}
			} else if(function->funct[0] == '+' || function->funct[0] == '-') {
				order += 1;
				que = insert_que(que, function, order);
			} else if(function->funct[0] == '*' || function->funct[0] == '/') {
				order += 2;
				que = insert_que(que, function, order);
			}
		}
	}
	return que;

}

listnode_t* calculate(listnode_t* function)
{
	listnode_t* moving = function;
	for(;function->next != NULL;) {
		order_que_t* que;
		que = order_of_ops(function);
		printf("2");
		if(que == NULL){
			printf("3");
			return function;
		} else  {
			if(que->ptr->funct[0] == '*') {
				printf("$$");
				moving = deque(que, &que);
				printf("@");
				moving->previous->double_value[0] = moving->previous->double_value[0] * moving->next->double_value[0];
				printf("#");
				moving->previous->next = moving->next->next;
				printf("%");
				if(moving->previous->next != NULL) {
					moving->previous->next->previous = moving->previous;
				}
			} else if(que->ptr->funct[0] == '/') {
				moving = deque(que, &que);
				moving->previous->double_value[0] = moving->previous->double_value[0] / moving->next->double_value[0];
				moving->previous->next = moving->next->next;
				if(moving->previous->next != NULL) {
					moving->previous->next->previous = moving->previous;
				}
			} else if(que->ptr->funct[0] == '+') {
				moving = deque(que, &que);
				moving->previous->double_value[0] = moving->previous->double_value[0] + moving->next->double_value[0];
				moving->previous->next = moving->next->next;
				if(moving->previous->next != NULL) {
					moving->previous->next->previous = moving->previous;
				}		
			} else if(que->ptr->funct[0] == '-') {
				moving = deque(que, &que);
				moving->previous->double_value[0] = moving->previous->double_value[0] - moving->next->double_value[0];
				moving->previous->next = moving->next->next;
				if(moving->previous->next != NULL) {
					moving->previous->next->previous = moving->previous;
				}
			} else {
				return NULL;
			}
		} 
	}
	return function;

}

int print_function(listnode_t *function)
{
	for(;function != NULL; function = function->next) {
		if(function->double_value != NULL) {
			printf("%lf",function->double_value[0]);
		}else if(function->char_value != NULL) {
			printf("%c",function->char_value[0]);
		}else if(function->funct != NULL) {
			printf("%c",function->funct[0]);
		}
	}
	printf("\n");
	return(0);
}
