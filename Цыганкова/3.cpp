/*
Tsygankova Elizaveta 2 c 61 g 
Lab ¹3: Find a city in a system of two-way roads, 
which has the minimum sum of distances to other cities.
*/
#include <cstdlib>
#include <iostream>
#include <stdio.h>

using namespace std;

int InitMatr ( int n, int **a )
{   
  int sum=0;  
  int weight;
  for (int i=0; i<n; i++) 
  {
    a[i][i]=0;                  //No loops in graph
    for (int j=i+1; j<n; j++) 
    {
      cout<<"Enter the distanse "<<(i+1)<<" - "<<(j+1)<<": ";  
      cin>>weight;
      sum+=weight;
      a[i][j] = weight;
      a[j][i] = weight;
    }
  } 
  return sum;                  //Future unattainble big label
}


void PrintMatr( int n, int **a )
{
  for (int i=0; i<n; i++) 
  {
    for (int j=0; j<n; j++)
      cout<< a[i][j]<<"     ";
    cout<<endl;
  }    
}


void InitVS(int n, int *d, bool *v, int max, int k)
/*
 * Init of vertex labels and flags
*/
 {
  for (int i = 0; i<n; i++) 
  {
    d[i] = max;
    v[i] = 0;
  }
  d[k] = 0;          //k - index of vertex from wich we start our pathes
}



void Deikstra(int n, int max, bool *v, int *d, int **a, int k, int &s, int smin)
/*
 *Recursive Deikstra algorithm. In s stores the sum of min pathes for 
 *current city, in smin stores min among all cities
*/
{  
    int minind = n+1;
    int min1 = max;
    int weight;
    int i=k;
    do                   //Search for unvisited vertex with min label
    {
      if (!v[i] && d[i]<min1)                                     
      {                            
        min1 = d[i];
        minind = i;
      }
      i++;
      if(i >= n)
        i=0;
    }while(i!=k);
    
    if (minind != n+1)    //If we found it
    {
      int i=k;
      do                  //Look through all neighbors of this vertex and
      {                   //if we find smaller path - re-label them
        if (a[minind][i] > 0)                      
        {
          weight = min1 + a[minind][i];         
          if (weight < d[i])                    
            d[i] = weight;
        }  
        i++;
        if(i >= n)
          i=0;      
      }while(i!=k);
      v[minind] = 1;      //Mark the vertex as visited one
      s=s+d[minind];      //Add const label of the vertex(min path to this vertex from vertex with index k) to general sum 
      if(s > smin)        //If this sum become bigger than current min sum - interrupt the algorithm. 
        return ;
      else               
        Deikstra(n, max, v, d, a, k, s, smin);  
    }
    else
      return ;   
}



int main()
{
  setlocale(LC_ALL,"Russian"); 
  
  int n;
  cout<<"Enter the number of cities: ";
  cin>>n;
     
  int **a;                //Distance matrix
  a=new int*[n];
  for (int i =0; i<n; i++)
    a[i]=new int[n];
    
  
  int max;
  max = InitMatr(n,a)*n;  //max - unattainble big distance 

  PrintMatr(n,a);         

  int d[n];               //Min distances 
  bool v[n];              //Flags of visited vertexes
  int smin = max;
  int minind;
  
  for(int ind=0; ind<n; ind++)
  {  
    InitVS(n,d,v,max,ind);      
    int sum=0;
    Deikstra(n,max,v,d,a,ind,sum,smin);
    if(sum<smin)
    {
      smin=sum;
      minind = ind;
    }
  }
  
  cout<<"City "<<minind+1<<" has the smalest sum distanse = "<<smin<<endl;
  
    system("PAUSE");
    return EXIT_SUCCESS;
}

