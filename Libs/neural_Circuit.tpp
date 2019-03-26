#ifndef CIRCUIT_TPP
#define CIRCUIT_TPP

#include "graph.tpp"
#include "synapses.tpp"

// include of neuron models
#include "izehikevich_neuron.tpp"
#include "hodgkin_huxley_neuron.tpp"

#include <iostream>

template<typename T = float>
class Neural_Circuit : public Graph<Neurons<T>*, Synapses<T>*>{
	
	protected:
	
		int add_node(Neurons<T>* node);
		void add_edge(Synapses<T>* edge, int id1, int id2);
		
		T life_time;
		T* last_fire;
		bool* firing;
		
		void neuron_reaction(T dt){
			T temp_current;
			for(int i = 0; i < this->amount_nodes; i++){
				temp_current = 0;
				for(int j = 0; j < this->amount_edges[i]; j++){
					temp_current += this->edges[i][j]->get_possynaptic_current();
				}
				this->nodes[i]->set_I_inj(this->nodes[i]->get_I_inj()-temp_current);
				
				if(this->nodes[i]->step(dt)) this->firing[i] = true;
				else this->firing[i] = false;
				if(this->firing[i]) this->last_fire[i] = this->life_time;
				
				this->nodes[i]->set_I_inj(0);
			}
		}
		void synapse_propagation(T dt){
			for(int i = 0; i < this->amount_nodes; i++){
				for(int j = 0; j < this->amount_edges[i]; j++){
					this->edges[i][j]->step(dt, this->get_node(this->edges_destiny[i][j])->get_voltage(), 
											this->get_node(i+1)->get_voltage(), this->firing[this->edges_destiny[i][j]]);
				}
			}
		}
	
	public:
	
		Neural_Circuit(){
			this->life_time = 0.0;
			this->last_fire = new T[this->amount_nodes];
			for(int i = 0; i < this->amount_nodes; i++) this->last_fire[i] = 0;
			this->firing = new bool[this->amount_nodes];
			for(int i = 0; i < this->amount_nodes; i++) this->firing[i] = false;
		}
	
		~Neural_Circuit(){
			for(int i = 0; i < this->amount_nodes; i++){
				delete this->nodes[i];
			}
			for(int i = 0; i < this->amount_nodes; i++){
				for(int j = 0; j < this->amount_edges[i]; j++)
					delete this->edges[i][j];
			}
			delete[] this->last_fire;
			delete[] this->firing;
		}
	
		T get_life_time(){ return this->life_time; }
		T get_last_fire(int id){ return this->last_fire[id]; }
		T get_firing(int id){ return this->firing[id]; }
	
		int add_neuron(std::string tipo, T variables[], T transmissor){
			if(tipo == "iz"){
				Neurons<T> *n = new Izhikevich_Neuron<T>();
				n->set_transmissor(transmissor);
				n->set_voltage(variables[0]);
				n->set_variable(1, variables[1]);
				n->set_variable(2, variables[2]);
				n->set_variable(3, variables[3]);
				n->set_variable(4, variables[4]);
				n->set_variable(5, variables[5]);
				return Graph<Neurons<T>*, Synapses<T>*>::add_node(n);
			}else if(tipo == "hh"){
				Neurons<T> *n = new Hodgking_Huxley_Neuron<T>();
				n->set_transmissor(transmissor);
				return Graph<Neurons<T>*, Synapses<T>*>::add_node(n);
			}
			
			return -1;
		}
		
		void add_synapse(std::string tipo, T variables[], int pre_neuron_id, int pos_neuron_id){ // edge a -> b is that neuron a receive neurotransmissor of b
			if(tipo == "basic"){
				Synapses<T> *s = new Basic_Synapse<T>();
				s->set_variable(0, variables[0]);
				Graph<Neurons<T>*, Synapses<T>*>::add_edge(s, pos_neuron_id, pre_neuron_id);
			}
		}
	
		void step(T dt){
			this->life_time += dt;
			this->neuron_reaction(dt);
			this->synapse_propagation(dt);
		}
		void add_current(int id_neuron);
		void set_I_inj(int id_neuron, T current){this->get_node(id_neuron)->set_I_inj(current);}
		Neurons<T>* get_neuron(int id_neuron){this->get_node(id_neuron);}
		T get_voltage(int id_neuron){return this->get_node(id_neuron)->get_voltage();}
		T get_ieeg(int id_neuron, int conection); // intracranial electroencephalography
		T get_energy(){
			T sum = 0;
			for(int i = 0; i < this->amount_nodes; i++) sum += this->nodes[i]->get_voltage();
		};
	
		void print_graph(){
			for(int i = 0; i < this->amount_nodes; i++){
				printf("ID node: %d (%2.4f)\n\tEdges: ", this->id_nodes[i], (double) this->nodes[i]->get_voltage());
				for(int j = 0; j < this->amount_edges[i]; j++){
					printf("(%d, %d, %.2e) ", this->id_nodes[i], this->edges_destiny[i][j], (double) this->edges[i][j]->get_variable(0));
				}
				printf("\n");
			}
		}

};

#endif // CIRCUIT_TPP

