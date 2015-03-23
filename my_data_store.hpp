#ifndef INCLUDED_MDS_HPP
#define INCLUDED_MDS_HPP

#include <vector>

namespace insilico {

class data_store {
 public:
   static int group;
   static int npg;
     
   static std::vector< std::vector<double> > spike_time_list;
 };
 
 int data_store::group = 10;
 int data_store::npg = 100;
 
 std::vector<std::vector<double>> data_store::spike_time_list(data_store::group * data_store::npg); 
 
 }
 
 #endif
