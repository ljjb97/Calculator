#include "Calculator.h"

/*Finds what the inputed variable is equal to given a
pointer to a function*/
listnode_t* find_variable_value(listnode_t *function,const char variable)
{
	assert(function != NULL);
	listnode_t* right_side,* answer;
	right_side = traverse_until(function,'f','=');
	right_side = right_side->next;
	if(traverse_until(right_side, 'c', variable) != NULL) { /*determins which side the variable is on. more = 0 means left side*/
		answer = calculate(function);
		printf("%c equals %f\n", variable, answer->double_value[0]);
		return answer;
	} else {
		answer = calculate(right_side);
		printf("%c equals %f\n", variable, answer->double_value[0]);
		return answer;
	}
}

int main(void)
{
	listnode_t* head = NULL;
	listnode_t* end = NULL;
	char input[3];
	char *ptr;
	printf("input\n");
	for(double i, k;input[0] != '\\';) {
		input[0] = 0;
		scanf(" %s", input);
		i = strtod(input, &ptr);
		k = ptr[0];
		if(input[0] == '\\') {
		} else if(i != 0) {
			if(head == NULL) {
				head = create_listnode_link(NULL, i, 0, 0);
				end = head;
			} else {
				end = append(end, ptr[0], i);
			}
		} else if(k >= 65) {
			if(head == NULL) {
				head = create_listnode_link(NULL, 0, ptr[0], 0);
				end = head;
			} else {
				end = append(end, ptr[0], i);
			}
		} else if(k < 65) {
			if(head == NULL) {
				head = create_listnode_link(NULL, 0, 0, ptr[0]);
				end = head;
			} else {
				end = append(end, ptr[0], i);
			}
		}
		print_function(head);
	}
	printf("input a variable to solve for\n");
	input[0] = 0;
	scanf(" %s", input);
	find_variable_value(head, input[0]);
	main();
}
