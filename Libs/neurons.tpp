#ifndef NEURONS_TPP
#define NEURONS_TPP

template<typename T = float>
class Neurons{
	
	protected:
		T* variables;
		T i_inj;
		T transmissor;
		
	public:
		virtual ~Neurons(){delete[] this->variables;}
		
		T get_transmissor(){return this->transmissor;}
		void set_transmissor(T transmissor){this->transmissor = transmissor;}
		T get_voltage(){return this->variables[0];}
		void set_voltage(T voltage){this->variables[0] = voltage;}
		T get_variable(int id_variable){return this->variables[id_variable];}
		void set_variable(int id_variable, T value){this->variables[id_variable] = value;}
		T get_I_inj(){return this->i_inj;}
		void set_I_inj(T i_inj){this->i_inj = i_inj;}
		
		virtual bool step(T dt) = 0;
};

#endif // NEURONS_TPP

