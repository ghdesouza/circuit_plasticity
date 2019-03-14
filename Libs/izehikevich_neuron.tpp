#ifndef IZHIKEVICH_NEURON_TPP
#define IZHIKEVICH_NEURON_TPP

#include "neurons.tpp"

template<typename T = float>
class Izhikevich_Neuron : public Neurons<T>{
	
	public:
		Izhikevich_Neuron(){
			this->i_inj = 0;
			this->transmissor = 1;
			this->variables = new T[6]; // {voltage, u, a, b, c, d}
			this->variables[0] = -70.0;
			this->variables[2] = 0.02;
			this->variables[3] = 0.2;
			this->variables[4] = -65.0;
			this->variables[5] = 8.0;
			this->variables[1] = this->variables[3]*this->variables[0];
		}
		bool step(T dt){
			
			bool fired = false;
			
			if(this->variables[0] == 30.0){
				this->variables[0] = this->variables[4];
				this->variables[1] += this->variables[5];
			}

			this->variables[0] += dt*(0.04*this->variables[0]*this->variables[0] + 5*this->variables[0] + 140 - this->variables[1] + this->i_inj);
			this->variables[1] += dt*(this->variables[2]*(this->variables[3]*this->variables[0]-this->variables[1]));
			
			if(this->variables[0] >= 30.0){
				this->variables[0] = 30.0;
				this->variables[1] += dt*(this->variables[2]*(this->variables[3]*this->variables[0]-this->variables[1])); // tem que ter essa linha ??
				fired = true;
			}
			this->i_inj = 0;

			return fired;
		}
	
};

#endif // IZHIKEVICH_NEURON_TPP

