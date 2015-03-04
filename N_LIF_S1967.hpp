/*
 neuron/N_LIF_S1967.hpp - Leaky Integrate and Fire with k conductance (Stein, 1967)

 Copyright (C) 2015 Pranav Kulkarni, Collins Assisi Lab, IISER, Pune <pranavcode@gmail.com>
 Copyright (C) 2015 Himanshu Rajmane, Suhita Nadkarni Lab, IISER, Pune <himanshu14121992@gmail.com>

 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef INCLUDED_N_LIF_S1967_HPP
#define INCLUDED_N_LIF_S1967_HPP

#include "core/engine.hpp"
#include <cmath>
#include "core/random.hpp"

namespace insilico {

class N_LIF_S1967 {
 public:
  static void ode_set(state_type& variables, state_type& dxdt, const double t,
               int index) {
    //cout<<"NEURON CLASS:\n";         //debug    
    int v_index = engine::neuron_index(index, "v");
    int gk_index = engine::neuron_index(index, "gk");

    double v = variables[v_index];
    double gk = variables[gk_index];
    
    // parameters
    double v_th = engine::neuron_value(index, "v_th");
    double tau_m = engine::neuron_value(index, "tau_m");
    double t_rest = engine::neuron_value(index, "t_rest");
    double tau_ref = engine::neuron_value(index, "tau_ref");    
    double tau_rel = engine::neuron_value(index, "tau_rel");        
    double gbar_k = engine::neuron_value(index, "gbar_k");
    double e_k = engine::neuron_value(index, "e_k");    
    double pulsewidth = engine::neuron_value(index, "pulsewidth");    
    double v_rest = engine::neuron_value(index, "v_rest");
    double noise_weight = engine::neuron_value(index, "noise_weight");
    double syn_weight = engine::neuron_value(index, "syn_weight");
    double v_reset = engine::neuron_value(index, "v_reset");
    
    vector<int> g1_indices = engine::get_pre_neuron_indices(index, "g1");       
    vector<double> esyn_values = engine::get_pre_neuron_values(index, "esyn");
      
    

    
    // incoming synaptic currents
    double I_Syn = 0.0;
    for(vector<int>::size_type iterator = 0; iterator < g1_indices.size(); ++iterator) {
      I_Syn = I_Syn + syn_weight*variables[g1_indices[iterator]] * (v - esyn_values[iterator]);// + distribution(generator);
      //cout<<"time:"<<t<<"\tsyn_weight:"<<syn_weight<<"\tg1_values[iterator]:"<<g1_values[iterator]<<"\tv:"<<v<<"\tesyn_values[iterator]:"<<esyn_values[iterator]<<endl;     //debug
    }
    //cout<<"time:"<<t<<"\tindex:"<<index<<"\tisyn:"<<I_Syn<<"\tg1_values.size():"<<g1_values.size()<<endl; //debug
    //cout<<I_Syn<<endl;
    I_Syn = I_Syn - random::rand(1e-3*20000*(0.88*2 - 0.12*12.5)*0.14,sqrt(1e-3*20000*(0.88*2 + 0.12*12.5)*0.14))*noise_weight;  // in mseconds
    
    double I_Ext = engine::neuron_value(index, "iext");    
    double spike = engine::neuron_value(index, "spike");
    
    // ODE set & LIF-K neuron model equations
    if(t > t_rest) {
    	if(t>pulsewidth){        
            I_Ext = 0;
        }
       dxdt[v_index] = (-(v - v_rest) - gk*(v - e_k) + I_Ext - I_Syn ) / tau_m ;       // ode for V
    	dxdt[gk_index] = -gk/tau_rel;                                                          // ode for gK 
    	if(v >= v_th){
    	     spike = 1;   
            engine::neuron_value(index, "t_rest", t+tau_ref);
            // Note the last spike time and number of times spiked
            engine::neuron_value(index, "last_spike", t);
            engine::neuron_value(index, "spike", spike);
        }
    }
    else {
       variables[v_index] = v_reset;
	variables[gk_index] = gbar_k;
	//engine::neuron_value(index, "spike", 0);
    }  
    
    // Push I_Syn to engine for the output
    engine::neuron_value(index, "I_Syn", I_Syn);
    
  } // function ode_set
}; // class N_LIF_S1967

} // namespace insilico

#endif
