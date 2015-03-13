/*
 synapse/S_DefaultSynapse.hpp - Default non-specialized synapse with last spike logic

 Copyright (C) 2014 Pranav Kulkarni, Collins Assisi Lab, IISER, Pune <pranavcode@gmail.com>

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

#ifndef INCLUDED_S_LIFSYNAPSE_HPP
#define INCLUDED_S_LIFSYNAPSE_HPP

#include "core/engine.hpp"

namespace insilico {

class S_LIFsynapse {
 public:
  static void ode_set(const state_type& variables, state_type& dxdt, const double t, int index) {
    
    //cout<<"SYNAPSE CLASS:\n"; //debug
    
    int g1_index = engine::synapse_index(index, "g1");
    int g2_index = engine::synapse_index(index, "g2");

    double g1 = variables[g1_index];
    double g2 = variables[g2_index];
    
    // synapse logic for delay for recently spiked neuron
    double xt = 0.0;
    //double delay = engine::synapse_value(index, "delay");

    int neuron_index = engine::synapse_value(index, "pre");
    //double last_spike = engine::neuron_value(neuron_index, "last_spike");
    int spiked = engine::neuron_value(neuron_index, "spike");

    
    if ((spiked > 0.8)){ //(t - last_spike > delay) && 
      xt = 1.0;
    }
    else{
      xt = 0.0;
    }  
    
    /*if ((t - last_spiked > delay) && (spiked == 1)){           //if((t - last_spiked) <= delay){
      xt = 1.0;
    }
    else 
      xt = 0.0;
    */
    //cout<<"time:"<<t<<"\tindex:"<<index<<"\tneuron_index:"<<neuron_index<<"\tNumber of spikes:"<<spiked<<endl; //debug
    
    // constants from file
    double tau_psp = engine::synapse_value(index, "tau_psp");
    double gsyn = engine::synapse_value(index, "gsyn");

    // ODE set
    
    //cout<<"time:"<<t<<"\tg1:"<<g1<<"\tg2:"<<g2<<"\tf(g1,g2):"<<-(2*tau_psp*g2+g1-gsyn*xt)/(tau_psp*tau_psp)<<endl;  //debug
    //cout<<g1<<","<<g2<<","<<-(2*tau_psp*g2+g1-gsyn*xt)/(tau_psp*tau_psp)<<"\n";  //debug
    
    dxdt[g1_index] = g2;
    dxdt[g2_index] =-(2*tau_psp*g2+g1-gsyn*xt)/(tau_psp*tau_psp);
    
    /*if (xt==1){
       //cout<<"time:"<<t<<"\tindex:"<<index<<"\tneuron_index:"<<neuron_index<<"\tbow-wow (Activated):"<<xt<<endl;  //debug
    }
    else*/
       //cout<<"time:"<<t<<"\tindex:"<<index<<"\tneuron_index:"<<neuron_index<<"\tmeow (Not Activated):"<<xt<<endl;  //debug
       
  } // function ode_set
}; // class S_LIFsynapse

} // insilico

#endif

 
