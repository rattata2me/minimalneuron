#include "network.h"

double random_value(){
	return (((double)rand())/RAND_MAX);
}

Minimal_Network * create_minimal_neuron(size_t * config, size_t config_size){ 

	Minimal_Network * network = malloc(sizeof(Minimal_Network));
	
	network->config = config;
	network->config_size = config_size;

	// Allocate layers space
	network->layers = malloc(sizeof(Minimal_Layer)*(config_size-1));

	//TODO check if the given config is plausible
	size_t prev_size = *config;
	for(size_t i = 1; i < config_size; i++){
		Minimal_Layer * layer = network->layers+i-1;
		layer->weight_len = prev_size;
		layer->biases = malloc(sizeof(double)*config[i]);
		layer->weights = malloc(sizeof(double)*config[i]*prev_size);

		for(size_t j = 0; j < config[i]; j++){
			layer->biases[j] = random_value();
			for(size_t k = 0; k < prev_size; k++){
				layer->weights[j*prev_size+k] = random_value();
			}
		}
		prev_size = config[i];
	}

	return network;

}

// Feedforward method
double * feedforward(double * input, Minimal_Network * network){
	
	for(size_t i = 1; i < network->config_size; i++){
		double * current = malloc(sizeof(double)*network->config[i]);
		for(size_t j = 0; j < network->config[i]; j++){
			current[j] += network->layers[i-1].biases[j];
			for(size_t k = 0; k < network->config[i-1]; k++){
				current[j] += input[k]*network->layers[i-1].weights[j*network->config[i-1]+k];
			}
		}
		free(input);
		input = current;
	}

	return input;
}

void destroy_minimal_neuron(){

}
