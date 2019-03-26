#ifndef SYNAPSES_TPP
#define SYNAPSES_TPP

#include <math.h>

template<typename T = float>
class Synapses{
	
	protected:
		T* variables;
		T presynaptic_voltage;
		T possynaptic_current;
		
	public:
		virtual ~Synapses(){delete[] this->variables;}
		
		T get_presynaptic_voltage(){return this->presynaptic_voltage;}
		void set_presynaptic_voltage(T voltage){this->presynaptic_voltage = voltage;}
		
		T get_possynaptic_current(){return this->possynaptic_current;}
		void set_possynaptic_current(T possynaptic_current){this->possynaptic_current = possynaptic_current;}
		
		T get_variable(int id_variable){return this->variables[id_variable];}
		void set_variable(int id_variable, T value){this->variables[id_variable] = value;}
		
		virtual void step(T dt, T v_pre, T v_pos, bool fired) = 0;
};

template<typename T = float>
class Basic_Synapse : public Synapses<T>{
	
	public:
	
		Basic_Synapse(){
			this->variables = new T[8]; // {intensity}
			this->variables[0] = 1;  // intensity - g_max
			this->variables[1] = 0;  // r
			this->variables[2] = 2;  // alpha
			this->variables[3] = 1;  // beta
			this->variables[4] = 0;  // E_syn
			this->variables[5] = 2;  // Vp
			this->variables[6] = 5;  // Kp
			this->variables[7] = this->variables[0];  // T_max
			this->presynaptic_voltage = 0;
			this->possynaptic_current = 0;
		}
		
		void step(T dt, T v_pre, T v_pos, bool fired){
			
			this->presynaptic_voltage = v_pre;
			T T_now = this->variables[7]/(1.0+exp((this->variables[5]-this->presynaptic_voltage)/this->variables[6]));
			
			this->variables[1] += dt*(T_now*this->variables[2]*(1-this->variables[1])-this->variables[3]*this->variables[1]);
			if(this->variables[1] < 0) printf("%f\n", this->variables[1]);
			
			this->possynaptic_current = this->variables[0]*this->variables[1]*(v_pos-this->variables[4]);
			if(this->possynaptic_current > 0) this->possynaptic_current = 0.0;
		}
	
		T get_T(){return this->variables[7]/(1.0+exp((this->variables[5]-this->presynaptic_voltage)/this->variables[6]));}
		T get_gsyn(){return this->variables[0]*this->variables[1];}
};


//template<typename T = float>
//class Basic_Synapse : public Synapses<T>{
	
	//public:
	
		//Basic_Synapse(){
			//this->variables = new T[1]; // {intensity}
			//this->variables[0] = 50;
			//this->presynaptic_voltage = 0;
			//this->possynaptic_current = 0;
		//}
		
		//void step(T dt, T v_pre, bool fired){
			
			//this->presynaptic_voltage = v_pre;
			
			//if(fired){
				//if(this->possynaptic_current < 50) this->possynaptic_current += this->variables[0];
			//}else{
				//// colocar caimento exponecial aqui
				//this->possynaptic_current /= 2;
			//}
		//}
	
//};


#endif // SYNAPSES_TPP

