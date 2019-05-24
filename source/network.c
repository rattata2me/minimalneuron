#include "network.h"

#define NUMBER_E 2.718281828459045


double random_value(){
	return (((double)rand())/RAND_MAX);
}


double randn(double mu, double sigma){
	double U1, U2, W, mult;
	static double X1, X2;
	static int call = 0;
	if (call == 1){
		call = !call;
		return (mu + sigma * (double) X2);
	}do{
		U1 = -1 + ((double) rand () / RAND_MAX) * 2;
		U2 = -1 + ((double) rand () / RAND_MAX) * 2;
		W = pow (U1, 2) + pow (U2, 2);
	}while (W >= 1 || W == 0);

	mult = sqrt ((-2 * log (W)) / W);
	X1 = U1 * mult;
	X2 = U2 * mult;

	call = !call;

	return (mu + sigma * (double) X1);
}


Minimal_Network * create_minimal_neuron(size_t * config, size_t config_size){ 

	Minimal_Network * network = malloc(sizeof(Minimal_Network));
	
	network->config = config;
	network->config_size = config_size;

	// Allocate layers space
	network->layers = malloc(sizeof(Minimal_Layer)*(config_size-1));

	//TODO check if the given config is plausible
	size_t prev_size = config[0];
	for(size_t i = 1; i < config_size; i++){
		Minimal_Layer * layer = network->layers+i-1;
		layer->weight_len = prev_size;
		layer->biases = malloc(sizeof(double)*config[i]);
		layer->weights = malloc(sizeof(double)*config[i]*prev_size);

		for(size_t j = 0; j < config[i]; j++){
			layer->biases[j] = randn(0, 1);
			for(size_t k = 0; k < prev_size; k++){
				layer->weights[j*prev_size+k] = randn(0, 1);
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
		memset(current, 0, sizeof(double)*network->config[i]);
		for(size_t j = 0; j < network->config[i]; j++){
			current[j] += network->layers[i-1].biases[j];
			for(size_t k = 0; k < network->config[i-1]; k++){
				current[j] += input[k]*(network->layers[i-1].weights[j*network->config[i-1]+k]);
			}
			current[j] = sigmoid(current[j]);
		}
		free(input);
		input = current;
	}

	return input;
}


double sigmoid(double x){
	double expo = exp((double)-x);
	return (double)(1.0 / (1.0+expo));
}

double sigmoid_prime(double x){
	return (sigmoid(x)*(1.0-sigmoid(x)));
}


void destroy_minimal_neuron(){

}
