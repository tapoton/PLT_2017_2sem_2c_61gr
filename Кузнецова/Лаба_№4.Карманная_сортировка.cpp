#include <cstdlib>
#include <iostream>
#include <fstream>
#include <ctime>
#include <cmath>


using namespace std;

struct LIST                                       //список
{                          
  float info; 
  LIST *next;
} ;


int Index(float el,float min)                    //вычисление номера кармана для элемента
{
  return (int)floor((el-min)/10);
}

  
void InsertWithSort(LIST *&head, int el)        //добавление элемента в карман + сортировка
{
  LIST *tmp = new LIST;
  tmp->info= el;
  if (head == NULL)                            //если карман был пуст
  {
    tmp->next = NULL;
    head = tmp;
  }
  else
  {
    LIST *prew = head;
    if (prew->info >= tmp->info)               //если добавляемый элемент меньше первого
    {
      tmp->next = prew;
      head = tmp;
    }
    else                                      //если добавляемый элемент больше первого
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
                                                        //склеиваие карманов
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
     cout<< "1) Числа из случайного массива "<< endl<< "2) Числа из файла"<< endl;
     cin>> otv1;
     switch(otv1)
     {
       case 1:
       {       
         int n;
         float c,b;
         float p;
         cout<<"Введите количество чисел: ";
         cin>>n;
         float a[n];
         
         cout<<"Введите диапозон: "<<endl;
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
    
         unsigned int start_time = clock();                                             // начальное время
         
         BucketSort (a,n,(int)p,c,b);
         
         unsigned int search_time = clock() - start_time;                              // конечное время
         cout<< "Элементы отсортированного массива: "<<endl; 
         for(int i=0; i<n; i++)
           cout<<a[i]<< " ";
           
                    cout<< endl << endl << "Время работы алгоритма: "<<search_time<<" млс"<<endl<<endl;

         break;
       }  
       
       case 2:
       {
         int n;
         float f,c,b;
         cout<<"Введите количество чисел: ";
         cin>>n;
         float a[n];
         cout<<"Введите диапозон: "<<endl;
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
         cout<<"В файле f1: "<<endl;
         while (fin>>a[k])
         {              
          cout  <<a[k]<<"  "; 
           k++;
         }
         cout<<endl<<endl;
         fin.close();
                                                                 
         f=ceil((b-c)/10)+1;
         
         srand(time(NULL));
         unsigned int start_time = clock();                                             // начальное время
         
         BucketSort (a,n,f,c,b);
                                          
         unsigned int search_time = clock() - start_time;                              // конечное время
         cout<< "Время работы алгоритма: "<<search_time<<" млс"<<endl<<endl;
                                        
         break;
      } 
   }
    
    system("PAUSE");
    return EXIT_SUCCESS;
}
