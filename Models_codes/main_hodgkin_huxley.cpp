#include <stdio.h>
#include "../Libs/hodgkin_huxley_neuron.tpp"
#include <iostream>

using namespace std;

int main(){

	Hodgking_Huxley_Neuron<>* hh = new Hodgking_Huxley_Neuron<>();

	float dt = 0.01;
	float T = 300.0;

	FILE* arq = fopen("saida.txt", "w");
	for(int i = -50; i*dt <= T; i++){
		if(i*dt >= 20 && i*dt <=200){
			hh->set_I_inj(10);
		}
		//if(i >= 0) fprintf(arq, "%f\t%f\n", i*dt, hh->get_voltage());
		if(i >= 0) fprintf(arq, "%f\t%f\n", pow(hh->get_variable(10), 3)*hh->get_variable(11), pow(hh->get_variable(9), 4));
		hh->step(dt);
	}
	fclose(arq);

	if(system("python3 graphic.py \"percent \\ of \\ Na \\ channels \\ open \\ [1]\" \"percent \\ of \\ K \\ channels \\ open \\ [1]\""));

	delete hh;
	return 0;

}
