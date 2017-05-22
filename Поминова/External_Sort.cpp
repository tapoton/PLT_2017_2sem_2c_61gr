/* 
Pominova. Laba 5.
There are one letter of student`s last name and the number of points for attestation from 0 to 9 on each line in the file.
Sort the file in the order of nondecreasing scores.
*/

#include <iostream>
#include <fstream>

using namespace std;

void simpleMergingSort (char *name);

int main()
{
	simpleMergingSort("main_file.txt");
	
	return 0;
}

void simpleMergingSort (char *name)
{
  int a1, a2, k, i, j, kol, tmp;
  char cha1,cha2;
  fstream f;
  f.open("main_file.txt", ios::in);
  kol = 0;
  if ( !f.is_open() )
    cout << "\nCan`t read the file";
  else {
    while ( !f.eof() ) {
      f >> cha1;
      f >> a1;
      kol++;
    }
    f.close();
  }

  k = 1;
  while ( k < kol ){
    f.open(name, ios::in);
    fstream f1;
	f1.open("smsort_1.txt", ios::out);
  	fstream f2;
	f2.open("smsort_2.txt", ios::out);
    if ( !f.eof() ) {
		f >> cha1;
		f >> a1;	
    }
    while ( !f.eof() ){
      for ( i = 0; i < k && !f.eof() ; i++ ){
		f1 << cha1 << ' ';
        f1 << a1 << '\n';
		f >> cha1;
        f >> a1;
      }
      for ( j = 0; j < k && !f.eof() ; j++ ){
		f2 << cha1 << ' ';
        f2 << a1 << '\n';
		f >> cha1;
        f >> a1;
      }
    }
    
    f.close();
    f1.close();
    f2.close();
	
	f.open(name, ios::out);
    f1.open("smsort_1.txt", ios::in);
  	f2.open("smsort_2.txt", ios::in);
    if ( !f1.eof() )
	{
		f1 >> cha1;
		f1 >> a1;
	} 
    if ( !f2.eof() )
	{
		f2 >> cha2;	
		f2 >> a2;	
	} 
    while ( !f1.eof() && !f2.eof() ){ 			//merge
      i = 0;
      j = 0;
      while ( i < k && j < k && !f1.eof() && !f2.eof() ) {
        if ( a1 < a2 ) {
		  f << cha1 << ' ';
          f << a1 << '\n';
		  f1 >> cha1;
          f1 >> a1;
          i++;
        }
        else {
          f << cha2 << ' ';
          f << a2 << '\n';
          f2 >> cha2;
          f2 >> a2;;
          j++;
        }
      }
      while ( i < k && !f1.eof() ) {
      	f << cha1 << ' ';
        f << a1 << '\n';
        f1 >> cha1;
        f1 >> a1;
        i++;
      }
      while ( j < k && !f2.eof() ) {
      	f << cha2 << ' ';
        f << a2 << '\n';
        f2 >> cha2;
        f2 >> a2;
        j++;
      }
    }
    
    while ( !f1.eof() ) {
      f << cha1 << ' ';
      f << a1 << '\n';
      f1 >> cha1;
      f1 >> a1;
    }
    while ( !f2.eof() ) {
      f << cha2 << ' ';
      f << a2 << '\n';
      f2 >> cha2;
      f2 >> a2;
    }
    f.close();
    f1.close();
    f2.close();
    k *= 2;
  }
  remove("smsort_1.txt");
  remove("smsort_2.txt");
}
