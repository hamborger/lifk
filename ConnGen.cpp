/*
To generate the ssets.conf and nsets.conf files
for synfire chain.
ssets.conf format: dxdt:3,g1:0,g2:0,last_spike:0,gsyn:0.1,tau1:10,tau2:100,esyn:20,pre:0,post:2
nsets.conf format: dxdt:4,v:20,m:0,n:0,h:0,iext:10
*/

#include<cmath>
#include<random>
#include<vector>
#include<iostream>
#include<fstream>
#include<string>

using namespace std;

// Get a random number from the range (inclusive)
double normal(double mean, double var) 
{
  random_device rd;
  mt19937 gen(rd());
  normal_distribution<> dist(mean, var);

  return dist(gen);
}


void conn_Syn(int G, int N)
{
    int i = 0;
    int j = 0;
    int k = 0;
    ofstream s_sets;
    s_sets.open("ssets.conf");
    for(i=0;i<(G-1)*N;i=i+N)
        for(j=i;j<i+N;j++)
            for(k=i+N;k<i+N+N;k++)
            {    
                s_sets<<"dxdt:2,g1:0,g2:0,gsyn:1.9,delay:0,esyn:0,tau_psp:1.7,pre:";
                s_sets<<j<<",post:"<<k<<";"<<"\n";
            }
    s_sets.close();
}

void conn_Neu(int G, int N)
{
    ofstream n_sets;
    n_sets.open("nsets.conf");
    for(int i=0;i<N*G;i++)
        if(i<N)	
        {
            n_sets<<"dxdt:2,v:"<<normal(-63,5)<<",gk:0,v_reset:-70,v_rest:-70,tau_ref:1,tau_rel:15,syn_weight:1,noise_weight:12";
            n_sets<<",gbar_k:8,e_k:-65,v_th:"<<-55<<",t_rest:"<<0<<",spike:0,iext:"<<140;
            n_sets<<",tau_m:"<<10;
            n_sets<<",pulsewidth:"<<20<<";"<<"\n";   
        }
        else
        {
            n_sets<<"dxdt:2,v:"<<normal(-63,5)<<",gk:0,v_reset:-70,v_rest:-70,tau_ref:1,tau_rel:15,syn_weight:1,noise_weight:12";
            n_sets<<",gbar_k:8,e_k:-65,v_th:"<<-55<<",t_rest:"<<0<<",spike:0,iext:"<< 0;
            n_sets<<",tau_m:"<<10;
            n_sets<<",pulsewidth:"<<225<<";"<<"\n";   
        } 
    n_sets.close();
}    

int main()
{
    int G=10;
    int N=100;
    conn_Syn(G,N);
    conn_Neu(G,N);
    return 0;
}
