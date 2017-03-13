#include <cstdlib>
#include <iostream>
#include <fstream>
#include <ctime>
#include <cmath>


using namespace std;

struct LIST                                      
{                          
  float info; 
  LIST *next;
} ;


int Index(float el,float min)                    
{
  return (int)floor((el-min)/10);
}

  
void InsertWithSort(LIST *&head, int el)        
{
  LIST *tmp = new LIST;
  tmp->info= el;
  if (head == NULL)                         
  {
    tmp->next = NULL;
    head = tmp;
  }
  else
  {
    LIST *prew = head;
    if (prew->info >= tmp->info)               
    {
      tmp->next = prew;
      head = tmp;
    }
    else                                      
    {
      LIST *cur = prew->next;
      while (cur!=NULL)
      {
        if (prew->info < tmp->info && tmp->info <= cur->info)
        {
          prew->next = tmp;
          tmp->next = cur;
          return;
        }
        prew = cur;
        cur = cur->next;
      }
      prew->next = tmp;
      tmp->next = NULL;
    }
  }      
}



void BucketSort (float *mas,int m,int pks,float g1,float g2)
{
  LIST **buckets = new LIST*[m];
  for(int i=0; i<pks; i++) 
    buckets[i] = NULL;

  for(int i=0; i<m; i++)
  {      
    int j= (int)Index(mas[i],g1);
    InsertWithSort(buckets[j], mas[i]);
  }      
  int l=0;
  for(int i=0; i<pks; i++) 
    while(buckets[i]!=NULL) 
     {
       mas[l] = buckets[i]->info;
       buckets[i] = buckets[i]->next;
       l++;
     }
}


int main()
{
   setlocale(LC_ALL,"Russian");    
    
    int otv1;    
     cout<< "1) generacia random "<< endl<< "2) iz faila"<< endl;
     cin>> otv1;
     switch(otv1)
     {
       case 1:
       {       
         int n;
         float c,b;
         float p;
         cout<<"kolichestvo elementov v massive: ";
         cin>>n;
         float a[n];
         
         cout<<"granicy massiva: "<<endl;
         cin>>c>>b;
         srand ( time(NULL) );                     
         for(int i=0; i<n; i++)
         {
           a[i] =(int)c + rand() % ((int)b-(int)c+1);
           cout<<a[i]<< " ";
         }
         cout<< endl; 
         
         p=ceil((b-c)/10)+1;
         cout<<endl<<endl;
    
         unsigned int start_time = clock();                                             
         
         BucketSort (a,n,(int)p,c,b);
         
         unsigned int search_time = clock() - start_time;                              
         cout<< "otsortirovanniy massiv: "<<endl; 
         for(int i=0; i<n; i++)
           cout<<a[i]<< " ";
           
                    cout<< endl << endl << "vremya raboty: "<<search_time<<" ìëñ"<<endl<<endl;

         break;
       }  
       
       case 2:
       {
         int n;
         float f,c,b;
         cout<<"kolichestvo elementov: ";
         cin>>n;
         float a[n];
         cout<<"granicy massiva: "<<endl;
         cin>>c>>b;
            
         ofstream fout("f1.txt");
	     for(int i=0; i<n; i++)
         {
           a[i] = (int)c + rand() % ((int)b-(int)c+1);
           fout<< a[i]<< " ";
         }
         fout.close();  
          
         int k=0;                                      
         ifstream fin("f1.txt");                                            
         cout<<"v faile f1: "<<endl;
         while (fin>>a[k])
         {              
          cout  <<a[k]<<"  "; 
           k++;
         }
         cout<<endl<<endl;
         fin.close();
                                                                 
         f=ceil((b-c)/10)+1;
         
         srand(time(NULL));
         unsigned int start_time = clock();                                            
         
         BucketSort (a,n,f,c,b);
                                          
         unsigned int search_time = clock() - start_time;                             
         cout<< "vremya raboty: "<<search_time<<" ìëñ"<<endl<<endl;
                                        
         break;
      } 
   }
    
    system("PAUSE");
    return EXIT_SUCCESS;
}
