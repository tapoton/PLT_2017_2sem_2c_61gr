#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>

using namespace std;

int main() 
{
	

	ofstream matr("matrix.dat"); //создать
	
	srand(time(0));
	
	int n;
	cout<<"Input the dimension of the matrix: "; cin>>n;
//	matr<<n<<" ";
	for (int i=0; i<n; i++)
		{
			for (int j=0; j<n; j++)
					matr<<rand()%10<<" ";
			matr<<'\n';	
		}
	matr.close();
	return 0;
}
