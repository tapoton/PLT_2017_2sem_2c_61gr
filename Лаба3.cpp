#include <iostream>

using namespace std;
 
const int n = 7;
bool existence[n];
int x[n][n]= {
  {0,1,0,0,1,0,0},
  {1,0,1,0,1,0,0},
  {0,1,0,1,1,0,0},
  {0,0,1,0,1,0,0},
  {1,1,1,1,0,0,0},
  {0,0,0,0,0,0,1},
  {0,0,0,0,0,1,0}
 };
 
void printf()
{
	cout << "Adjacency matrix: "<< endl;
	cout <<"    v1 v2 v3 v4 v5 v6 v7 "<< endl;
	for (int i = 0; i< n; i++)
		{
			cout << "v"<< (i+1) << ": ";
			for (int j = 0; j < n; j++)
				cout << x[i][j] << "  ";
			cout << endl;
		}
	cout << endl;
}

bool neorgraf() 
{
	for (int i = 0; i < n; i++)
   		for(int j = 0; j < n; j++)
    		if (x[i][j] != x[j][i]) 
     			return 0;
	return 1;
}

void init_ex() 
{
	for (int i = 0; i < n; i++)
  		existence[i]=0;
}

void back(int i)
{  
	existence[i] = 1;  
  	for(int j = 0; j < n; j++)
   		if(i != j && x[i][j] == 1 && existence[j] == 0) 
    			back(j);
  	
}

bool proverka()
{
	for(int j = 0; j < n; j++)
     		if(existence[j]==0)	
     			return 1;
    return 0;
} 
 
int main()
{
  	init_ex();
  	int beg;
  	printf();
  	
  	while(1)
  	{
  		cout << "Enter the top from 1 to " << n << " : ";
  		cin >> beg;
  		if (beg >= 1 && beg <= n)
  			break;
  		else
  			cout << "Invalid input. Try again." << endl;
  	}
  	
  	beg--;
  	
  	if (neorgraf())
  	{
  		back(beg);
  		if (proverka())
			{
				cout << "Unattainable top:" << endl;
				for(int j = 0; j < n; j++)
     				if(existence[j]==0)
	 					cout << (j+1)<< ' ';	
			}
		else
			cout << "There are no such vertices" << endl;			
 	}
  	else 
   		cout<<"The graph is not undirected" << endl;
   		
 	return 0;	
 } 
