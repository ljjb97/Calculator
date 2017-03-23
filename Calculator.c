#include "Calculator.h"

/*Finds what the inputed variable is equal to given a
pointer to a function*/
listnode_t* find_variable_value(listnode_t *function, char variable)
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
	
	listnode_t* head = create_listnode_link(NULL, 2.0, 0, 0);
	char input[1], input_c[1], input_f[1];
	double input_d[1];
	for(;input[0] != '/';) {
		input[0] = 0;
		printf("input a type\n");
		scanf(" %c",&input[0]);
		input_c[0] = 0;
		input_f[0] = 0;
		input_d[0] = 0;
		if(input[0] == 'd') {
			printf("input a number\n");
			scanf(" %lf",&input_d[0]);
			head = create_listnode_link(head, input_d[0], 0, 0);
		} else if(input[0] == 'c') {
			printf("input a variable\n");
			scanf(" %c",&input_c[0]);
			head = create_listnode_link(head, 0, input_c[0], 0);
		} else if(input[0] == 'f') {
			printf("input a function\n");
			scanf(" %c",&input_f[0]);
			head = create_listnode_link(head, 0, 0, input_f[0]);
		}
	}
	printf("input a variable to solve for\n");
	scanf(" %c",&input[0]);
	find_variable_value(head, input[0]);
}
