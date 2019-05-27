#include <stdio.h>
#include "network.h"
#include <stdlib.h>


#define D_SIZE 50000

int * load_mnist_index(){

	FILE * file = fopen("index.bin", "r");
	
	int * data = malloc(sizeof(int)*D_SIZE);
	fread(data, sizeof(int), D_SIZE, file);

	fclose(file);

	return data;
}

double * load_mnist_data(){

	FILE * file = fopen("images.bin", "r");

	double * data = malloc(sizeof(double)*28*28*D_SIZE);
	fread(data, sizeof(double), 28*28*D_SIZE, file);

	fclose(file);
	
	return data;
}

Minimal_Network * load_from_file(){
	
	FILE * file = fopen("weights.txt", "r");
	if(file == NULL) printf("Something is bad with the file\n");

	int net_size = 0;
	fscanf(file, "%i", &net_size);
	size_t * config = malloc(sizeof(size_t)*net_size);

	for(size_t i = 0; i < net_size; i++){
		fscanf(file, "%zu", config+i);
	}
	
	Minimal_Network * network = create_minimal_neuron(config, net_size);

	// Weigths
	
	for(int i = 1; i < net_size; i++){
		for(int j = 0; j < config[i]; j++){
			for(int k = 0; k < config[i-1]; k++){
				fscanf(file, "%lf", (network->layers[i-1].weights+(config[i-1]*j+k)));
			}
		}
	}

	fclose(file);

	// Biases
	
	FILE * fileb = fopen("biases.txt", "r");
	if(fileb == NULL) printf("Something is bad with the file\n");
	
	for(int i = 1; i < net_size; i++){
		for(int j = 0; j < config[i]; j++){
			fscanf(fileb, "%lf", (network->layers[i-1].biases+j));
		}
	}

	fclose(fileb);


	return network;
}

double * input(){

	double * list = malloc(sizeof(double)*28*28);

	FILE * f = fopen("image.txt", "r");

	if(f == NULL) printf("Something is bad with the file\n");

	for(int i = 0; i < 28*28; i++){
		fscanf(f, "%lf", (list+i));
	}

	fclose(f);
	
	return list; 
}

int main(){

	//size_t config[] = {28*28,100,10};
	//Minimal_Network * network = create_minimal_neuron(&config[0], 3);
	//double * input_p = malloc(sizeof(double)*config[0]);
	
	//feedforward(input_p, network);
	Minimal_Network * network = load_from_file();
	double * input_p = input();
	double * r = feedforward(input_p, network);
	double max = 0.0f;
	int indexmax = 0;
	for(int i = 0; i < 10; i++){
		printf("[%f],", r[i]);
		if(r[i] > max){
			max = r[i];
			indexmax = i;
		}
	}
	printf("\nEl numero es el %i!\n", indexmax);
	
	double * data = load_mnist_data();
	int * index = load_mnist_index();

	free(data);
	free(index);

	return 0;
}
