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
	char input = 'd';
	while(input != '/') {
		printf("input a type\n");
		fflush(stdout);
		scanf("%c",&input);
		char input_c = 0, input_f = 0;
		double input_d = 0;
		if(input == 'd') {
			printf("input a number\n");
			fflush(stdout);
			scanf("%lf",&input_d);
			head = create_listnode_link(head, 0, 0, input_d);
		} else if(input == 'c') {
			printf("input a variable\n");
			fflush(stdout);
			scanf("%c",&input_c);
			head = create_listnode_link(head, 0, input, 0);
		} else if(input == 'f') {
			printf("input a function\n");
			fflush(stdout);
			scanf("%c",&input_f);
			head = create_listnode_link(head, 0, 0, input_f);
		}
	}
	scanf("%c",&input);
	find_variable_value(head, input);
}
