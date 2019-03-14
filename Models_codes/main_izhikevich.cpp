#include <stdio.h>
#include "../Libs/izehikevich_neuron.tpp"
#include <iostream>

using namespace std;

int main(){

	Neurons<>* iz = new Izhikevich_Neuron<>();
	string type = "rs";

	if(type == "ch"){
		iz->set_variable(2, 0.02);
		iz->set_variable(3, 0.2);
		iz->set_variable(4, -50.0);
		iz->set_variable(5, 2.0);
		iz->set_variable(0, -70);
	}else if(type == "ib"){
		iz->set_variable(2, 0.02);
		iz->set_variable(3, 0.2);
		iz->set_variable(4, -55.0);
		iz->set_variable(5, 4.0);
		iz->set_variable(0, -70.0);
	}else if(type == "fs"){
		iz->set_variable(2, 0.1);
		iz->set_variable(3, 0.2);
		iz->set_variable(4, -65.0);
		iz->set_variable(5, 2.0);
		iz->set_variable(0, -70.0);
	}else if(type == "tc"){
		iz->set_variable(2, 0.02);
		iz->set_variable(3, 0.25);
		iz->set_variable(4, -65.0);
		iz->set_variable(5, 0.05);
		iz->set_variable(0, -64.4139);
	}else if(type == "rz"){
		iz->set_variable(2, 0.1);
		iz->set_variable(3, 0.26);
		iz->set_variable(4, -65.0);
		iz->set_variable(5, 2.0);
		iz->set_variable(0, -62.5);
	}else if(type == "lts"){
		iz->set_variable(2, 0.02);
		iz->set_variable(3, 0.25);
		iz->set_variable(4, -65.0);
		iz->set_variable(5, 2.0);
		iz->set_variable(0, -64.41391);
	}else{ // regular spiking (rs)
		iz->set_variable(2, 0.02);
		iz->set_variable(3, 0.2);
		iz->set_variable(4, -65.0);
		iz->set_variable(5, 8.0);
		iz->set_variable(0, -70.0);
	}

	float dt = 0.1;
	float T = 300.0;

	FILE* arq = fopen("saida.txt", "w");
	for(int i = 0; i*dt <= T; i++){
		if(i*dt >= 20 && i*dt <=200){
			if(type == "tc") iz->set_I_inj(10.0/8);
			else if(type == "rz") iz->set_I_inj(10.0/64.0+2*(i*dt > 60 &&i*dt < 65));
			else iz->set_I_inj(10);
		}
		//fprintf(arq, "%f\t%f\n", i*dt, iz->get_voltage());
		if(i*dt >= 50 && i*dt <=150) fprintf(arq, "%f\t%f\n", iz->get_voltage(), iz->get_variable(1));
		iz->step(dt);
	}
	fclose(arq);

	//if(system("python3 graphic.py \"time \\ [ms]\" \"voltage \\ [mV]\""));
	if(system("python3 graphic.py \"voltage \\ [mV]\" \"u\" "));

	delete iz;
	return 0;

}
