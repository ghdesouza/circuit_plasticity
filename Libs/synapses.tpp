#ifndef SYNAPSES_TPP
#define SYNAPSES_TPP

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
		
		virtual void step(T dt, T v_pre, bool fired) = 0;
};

template<typename T = float>
class Basic_Synapse : public Synapses<T>{
	
	public:
	
		Basic_Synapse(){
			this->variables = new T[1]; // {intensity}
			this->variables[0] = 0;
			this->presynaptic_voltage = 0;
			this->possynaptic_current = 0;
		}
		
		void step(T dt, T v_pre, bool fired){
			
			this->presynaptic_voltage = v_pre;
			
			if(fired){
				if(this->possynaptic_current < 50) this->possynaptic_current += this->variables[0];
			}else{
				// colocar caimento exponecial aqui
				this->possynaptic_current /= 2;
			}
		}
	
};

#endif // SYNAPSES_TPP

