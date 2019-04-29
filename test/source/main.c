#include <stdio.h>
#include "network.h"

int main(){
	size_t config[] = {3,2,3};
	Minimal_Network * network = create_minimal_neuron(&config[0], 3);
	double input[] = {1, 2, 3};
	double * input_p = malloc(sizeof(double)*3);
	for(size_t i = 0; i < 3; i++){
		input_p[i] = input[i];
	}
	double * r = feedforward(input_p, network);
	for(int i = 0; i < 3; i++){
		printf("[%f],", r[i]);
	}
	printf("\nThis looks fine!\n");
	return 0;
}
