#include "../Libs/neural_Circuit.tpp"
#include <stdio.h>
#include <iostream>
#include <time.h>
#include <random>

using namespace std;

default_random_engine generator;
normal_distribution<double> distribution(0.0,1.0);

float dt = 0.5;
float last_time = 500;

int population_size[] = {10, 20, 50, 100};
int current_intensities[] = {1, 2, 5, 8, 10};
int densities_synapse[] = {10, 15, 20, 50, 60, 100, 150, 200};

string str_population_size[] = {"10", "20", "50", "100"};
string str_current_intensities[] = {"1", "2", "5", "8", "10"};
string str_densities_synapse[] = {"10", "15", "20", "50", "60", "100", "150", "200"};

int cnt_population_size = 0; // 0 to 3
int cnt_current_intensities = 0; // 0 to 4
int cnt_densities_synapse = 0; // 0 to 7

int current_intensity = current_intensities[cnt_current_intensities];
int density_synapse = densities_synapse[cnt_densities_synapse];
int amount_neurons = population_size[cnt_population_size];
float prob_excitatory = 0.8;

void create_random_circuit(Neural_Circuit<> *circuit);

int main(int argc, char** argv){

	printf("%d %d %d\n", atoi(argv[1]), atoi(argv[2]), atoi(argv[3]));

	int cnt_population_size = atoi(argv[1]);
	int cnt_current_intensities = atoi(argv[2]);
	int cnt_densities_synapse = atoi(argv[3]);
	current_intensity = current_intensities[cnt_current_intensities];
	density_synapse = densities_synapse[cnt_densities_synapse];
	amount_neurons = population_size[cnt_population_size];

	//srand(time(NULL));
	srand(2019);

	Neural_Circuit<> *circuit;

	FILE* arq;
	FILE* arq2;
	
	circuit = new Neural_Circuit<>();
	create_random_circuit(circuit);
	
	arq = fopen(("exit_files/saida_"+str_population_size[cnt_population_size]+
				 "_"+str_current_intensities[cnt_current_intensities]+
				 "_"+str_densities_synapse[cnt_densities_synapse]+
				 ".tmp").c_str(), "w");
	arq2 = fopen(("exit_files/fire_"+str_population_size[cnt_population_size]+
				 "_"+str_current_intensities[cnt_current_intensities]+
				 "_"+str_densities_synapse[cnt_densities_synapse]+
				 ".tmp").c_str(), "w");
	for(int i = 0; i < (int)(last_time/dt); i++){
		for(int j = 0; j < ((int)(1*amount_neurons)); j++){
			if(circuit->get_node(j+1)->get_transmissor() > 0) circuit->set_I_inj(j+1, 5*current_intensity*(distribution(generator)));
			else circuit->set_I_inj(j+1, 2*current_intensity*(distribution(generator)));
		}
		fprintf(arq, "%f\t%f\n", circuit->get_life_time(), circuit->get_energy());
		fprintf(arq2, "%.5f", circuit->get_life_time());
		for(int k = 0; k < circuit->get_amount_nodes(); k++){
			if(circuit->get_firing(k)) fprintf(arq2, "\t1");
			else fprintf(arq2, "\t0");
		}
		circuit->step(dt);
		fprintf(arq2, "\n");
	}
	fclose(arq);
	fclose(arq2);
	//system("python neuron_graphic.py");
    return 0;
}


void create_random_circuit(Neural_Circuit<> *circuit){

	float variables[6];
	float transmissor;

	float temp, type_neuron;
	int id_pos;

	circuit->extend_nodes(amount_neurons);

	// set neurons
	for(int i = 1; i <= amount_neurons; i++){
		temp = ((double)rand())/RAND_MAX;
		type_neuron = ((double)rand())/RAND_MAX;
		variables[0] = -65.0;
		if(type_neuron < prob_excitatory){
			variables[2] = (0.02);
			variables[3] = (0.2);
			variables[4] = (-65.0+15.0*temp*temp);
			variables[5] = (8.0-6.0*temp*temp);
			transmissor = 1;
		}else{
			variables[2] = (0.02+0.08*temp);
			variables[3] = (0.25-0.05*temp);
			variables[4] = (-65.0);
			variables[5] = (2.0);
			transmissor = -1;
		}
		variables[1] = variables[3]*variables[0];
		circuit->add_neuron("iz", variables, transmissor);
		//circuit->add_neuron("hh", variables, transmissor);
	}
	
	// set synapses
	for(int i = 1; i <= amount_neurons; i++){
		type_neuron = circuit->get_node(i)->get_transmissor();
		for(int j = 0; j < density_synapse; j++){
			if(type_neuron > 0)	variables[0] = 0.5*((float)rand())/RAND_MAX;
			else variables[0] = 1.0*((float)rand())/RAND_MAX;
			
			id_pos = 1+(rand()%amount_neurons);
			circuit->add_synapse("basic", variables, i, id_pos);
		}
	}
	
	/*
	// full conected
	for(int i = 1; i <= amount_neurons; i++){
		type_neuron = circuit->get_node(i)->get_transmissor();
		for(int j = 1; j <= amount_neurons; j++){
			variables[0] = 1+0*((float)rand())/RAND_MAX;
			circuit->add_synapse("basic", variables, i, j);
		}
	}
	*/
	
}

