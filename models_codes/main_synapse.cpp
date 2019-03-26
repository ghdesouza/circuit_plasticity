#include <stdio.h>
#include "../Libs/izehikevich_neuron.tpp"
#include "../Libs/hodgkin_huxley_neuron.tpp"
#include "../Libs/synapses.tpp"
#include <iostream>

using namespace std;

int main(){

	Neurons<>* iz  = new Izhikevich_Neuron<>();
	Neurons<>* izpos =  new Izhikevich_Neuron<>();
	Basic_Synapse<>* syn = new Basic_Synapse<>();
	Basic_Synapse<>* synback = new Basic_Synapse<>();
	
	float dt = 0.01;
	float T = 300.0;

	FILE* arq = fopen("saida.txt", "w");
	for(int i = 0; i*dt <= T; i++){
		
		syn->step(dt, iz->get_voltage(), izpos->get_voltage(), (iz->get_voltage() > 0));
		izpos->set_I_inj(-syn->get_possynaptic_current());
		synback->step(dt, izpos->get_voltage(), iz->get_voltage(), (iz->get_voltage() > 0));
		if(i*dt >= 0 && i*dt <= 30
		   //|| i*dt >= 35 && i*dt <= 50
		   //||i*dt >= 65 && i*dt <= 80
		   ) iz->set_I_inj(50-synback->get_possynaptic_current());
		else iz->set_I_inj(-synback->get_possynaptic_current());
		
		iz->step(dt);
		izpos->step(dt);
		
		//if(i*dt >= 9 && i*dt <= 30) fprintf(arq, "%f\t%f\n", i*dt, syn->get_possynaptic_current());
		//if(i*dt >= 0 && i*dt <= 50) fprintf(arq, "%f\t%f\n", i*dt, izpos->get_voltage());
		if(i*dt >= 0 && i*dt <= 30) fprintf(arq, "%f\t%f\t%f\t%f\t%f\t%f\t%f\n", i*dt, 
											iz->get_voltage(), syn->get_T(), syn->get_variable(1),
											izpos->get_voltage(), synback->get_T(), synback->get_variable(1));
	}
	fclose(arq);

	if(system("python3 results/syn/graphic.py \"voltage \\ [mV]\" \"u\" "));
	//if(system("xdg-open figura.eps"))

	delete iz;
	delete izpos;
	delete syn;
	return 0;

}
