#include "network.h"

Minimal_Network * create_minimal_neuron(size_t * config, size_t config_size){
	
	size_t prev_length; 
	
	Minimal_Network * network = malloc(sizeof(Minimal_Network));
	
	network->config = config;

	// Allocate layers space
	network->layers = malloc(sizeof(Minimal_Layer)*config_size);

	//TODO check if the given config is plausible
	for(size_t i = 1; i < config_size; i++){	
		Minimal_Neuron neuron = malloc(sizeof(Minimal_Neuron));		
	}

}


