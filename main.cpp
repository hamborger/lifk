/*
 main.cpp - Integrate and Fire neuron example's main()

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

#include "core/configuration.hpp"
#include "core/engine.hpp"

#include "neuron/N_LIF_S1967.hpp"
#include "synapse/S_LIFsynapse.hpp"

#include <boost/numeric/odeint.hpp>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

using namespace boost;
using namespace insilico;
using namespace std;

//std::default_random_engine generator;
//std::poisson_distribution<int> distribution(20000*(0.88*2 - 0.12*12.5)*0.14);


void engine::operator()(state_type &variables, state_type &dxdt,
                       const double time) {
  //N_LIF_S1967::ode_set(variables, dxdt, time, 0);
  int network_size = engine::neuron_count();
  int synapse_count = engine::synapse_count();

  for(int neuron_index = 0; neuron_index < network_size; ++neuron_index) {
    N_LIF_S1967::ode_set(variables, dxdt, time, neuron_index);
  }
  for(int synapse_index = 0; synapse_index < synapse_count; ++synapse_index) {
    S_LIFsynapse::ode_set(variables, dxdt, time, synapse_index);
  }
}

void configuration::observer::operator()(state_type &variables, const double t) {
  vector<int> indices = engine::get_indices("v");
  //vector<int> isyns = engine::get_indices("gk");     //print gk
  vector<double> isyns = engine::get_values("I_Syn");
  vector<double> spike = engine::get_values("spike");
  assert(observer::outfile.is_open());
  
  observer::outfile << setprecision(4) << fixed << t;
  for(int index : indices) {
    observer::outfile << ',' << setprecision(6) << fixed << variables[index];
  }
  for(double val : isyns) {
    observer::outfile << ',' << setprecision(6) << fixed << val;//variables[val];
  }
  for(double sp : spike) {
    observer::outfile << ',' << setprecision(1) << fixed << sp;//variables[val];
  }
  observer::outfile<<"\n";
};

int main(int argc, char** argv) {
       
     /*  for(int i=0;i<100000;i++){
       int val =  distribution(generator);
       if(val > 10) { cout<<val;
       cout<< endl;}
       }*/
       
  configuration::initialize(argc, argv);  
  
  state_type variables = engine::get_variables();
  
  using namespace boost::numeric::odeint;
  integrate_const(runge_kutta4<state_type>(), engine(), variables,
                  0.0, 70.0, 0.05, configuration::observer(configuration::outstream));

  configuration::finalize();
  return 0;
}
