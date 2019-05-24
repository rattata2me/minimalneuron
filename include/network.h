#ifndef MINIMAL_NEURON_H
#define MINIMAL_NEURON_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct{
	
	size_t weight_len;
	double * weights;
	double * biases;

} Minimal_Layer;

typedef struct{

	size_t config_size;
	size_t * config;
	Minimal_Layer * layers;

} Minimal_Network;

double random_value();

Minimal_Network * create_minimal_neuron(size_t * config, size_t config_size);

double * feedforward(double * input, Minimal_Network * network);

void destroy_minimal_neuron();

double sigmoid(double value);

#endif
