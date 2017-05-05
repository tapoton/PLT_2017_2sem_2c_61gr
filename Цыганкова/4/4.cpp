/*
Tsygankova Elizaveta 2 c 61 g 
Lab ¹4
*/
#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <fstream>

using namespace std;



struct Route
{
  int depart;         //Number of point of departure
  int tdepart;        //Time of departure
  int arrive;         //Number of destination point
  int tarrive;        //Time of destination
};



void InitVS(int N, int *ds, bool *vi, int max, int d)
/*
 * Init of village labels and flags
*/
 {
  for (int i = 0; i<N; i++) 
  {
    ds[i] = max;
    vi[i] = 0;
  }
  ds[d] = 0;          //d - index of village from which we start our pathes
}



void Deikstra(int N, int max, bool *vi, int *ds, int k, Route R[], int d, int v)
/*
 *Deikstra algorithm. k - number of routes, d - the number of village where we start, v - where we finish
*/
{  
  int minind = 0;         
  do
  {            
    minind = N+1;
    int min1 = max;
    int i=d;
    do                          //Search for unvisited vertex with min label 
    {
      if (!vi[i] && ds[i]<min1)                                     
      {                            
        min1 = ds[i];
        minind = i;
      }
      i++;
      if(i >= N)
        i=0;
    }while(i!=d);
    
    if (minind != N+1)           //If we found it
    {
      int i=d;
      do                  
      {                   
        for(int j=0; j<k; j++)                           //Look through all neighbors of this village and if we find smaller arrive time - re-label them
          if(R[j].depart == i+1 && R[j].depart >= min1 && R[j].tarrive < ds[R[j].arrive - 1])                    
            ds[R[j].arrive - 1] = R[j].tarrive;  
        i++;
        if(i >= N)
          i=0;      
      }while(i!= d);
      vi[minind] = 1;      //Mark the village as visited one 
      if (minind == v)
        return;
    }
  }while(minind < N+1);      
}



int main()
{
   setlocale(LC_ALL,"Russian");
   
   ifstream fin("f1.txt");
     
   int N;      //Number of villages
   fin>>N;     
   int d,v;    //d - the number of village where we start, v - where we finish
   fin>>d>>v;
   d = d-1;
   v = v-1;
   int k;      //Number of routes
   fin>>k;
   Route R[k];         
   for(int i=0; i<k; i++)      //Filling   
   {
     fin>>R[i].depart;
     fin>>R[i].tdepart;
     fin>>R[i].arrive;
     fin>>R[i].tarrive;
   }   
    
   fin.close(); 
   
   int ds[N];            //Min distances 
   bool vi[N];           //Flags of visited villages
   InitVS(N, ds, vi, 10000, d);
   
   Deikstra(N, 10000, vi, ds, k, R, d, v);
   
   cout<<"Result: ";
   if (ds[v] != 10000)
     cout<<ds[v]<<endl;
   else
     cout<<-1<<endl;      
   
    
    system("PAUSE");
    return EXIT_SUCCESS;
}
