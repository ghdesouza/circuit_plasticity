#ifndef HODGKIN_HUXLEY_TPP
#define HODGKIN_HUXLEY_TPP

#include <math.h>

#include "neurons.tpp"

template<typename T = float>
class Hodgking_Huxley_Neuron : public Neurons<T>{
	
	private:
		T get_an(){ return 0.01 * (10.0 - (this->variables[0] - this->variables[1])) / ( exp((10.0 - (this->variables[0] - this->variables[1]))/10.0) - 1.0 ); }
		T get_bn(){ return 0.125 * exp( (-(this->variables[0] - this->variables[1]))/80.0 ); }
		T get_am(){ return 0.10 * (25.0 - (this->variables[0] - this->variables[1])) / ( exp((25.0 - (this->variables[0] - this->variables[1]))/10.0) - 1.0 ); }
		T get_bm(){ return 4.00 * exp( (-(this->variables[0] - this->variables[1]))/18.0 ); }
		T get_ah(){ return 0.07 * exp( -(this->variables[0] - this->variables[1])/20.0 ); }
		T get_bh(){ return 1.0 / ( exp( (30.0 - (this->variables[0] - this->variables[1]))/10.0 ) + 1.0 ); }
	
	public:
		Hodgking_Huxley_Neuron(){
			this->i_inj = 0;
			this->transmissor = 1;
			this->variables = new T[12]; // {voltage, resting_potential, cm, gna_max, gk_max, gl_max, ena, ek, el, n, m, h}
			this->variables[0] = -60.0; // voltage
			this->variables[1] = -65.0; // resting potential
			this->variables[2] = 1.0; // cm
			this->variables[3] = 120.0; // gna_max;
			this->variables[4] = 36.0; // gk_max
			this->variables[5] = 0.3; // gl_max
			this->variables[6] = 50.0; // ena
			this->variables[7] = -77.0; // ek
			this->variables[8] = -54.387; // el
			this->variables[9] = 0.3177380; // n
			this->variables[10] = 0.0529571; // m
			this->variables[11] = 0.5960090; // h
			
			T temp;
			for(int i = 0; i < 9; i++){
				temp = (2.0*((T)rand())/RAND_MAX)-1.0;
				this->variables[i] += 0.1*temp*this->variables[i];
			}
		}
		bool step(T dt){

			T last_v = this->variables[0];

			T j_ion = this->variables[5]*(this->variables[0]-this->variables[8]); // gl*(vm-el)
			j_ion += this->variables[4]*(this->variables[0]-this->variables[7])*pow(this->variables[9], 4); // gk*(vm-ek)*n**4
			j_ion += this->variables[3]*(this->variables[0]-this->variables[6])*pow(this->variables[10], 3)*this->variables[11]; // gna*(vm-ena)*m**3*h

			this->variables[0]  += (dt/this->variables[2])*(this->i_inj-j_ion);
			this->variables[9]  += dt*(this->get_an()*(1.0-this->variables[9])-this->get_bn()*this->variables[9]);
			this->variables[10]  += dt*(this->get_am()*(1.0-this->variables[10])-this->get_bm()*this->variables[10]);
			this->variables[11] += dt*(this->get_ah()*(1.0-this->variables[11])-this->get_bh()*this->variables[11]);
			
			this->i_inj = 0;
			
			if(last_v < 0 && this->variables[0] > 0) return true;
			return false;

		}
	
		T get_Ina(){ return this->variables[3]*(this->variables[0]-this->variables[6])*pow(this->variables[10], 3)*this->variables[11]; }
		T get_Ik(){ return this->variables[4]*(this->variables[0]-this->variables[7])*pow(this->variables[9], 4); }
	
};

#endif // HODGKIN_HUXLEY_TPP

