#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>

using namespace std;

int series (char *begfile) // counting the number of series 
{	
	int kol = 1;
	string str1, str2;
    ifstream fin(begfile);
    fin >> str1;
    while (!fin.eof()) 
    {	 fin >> str2;
         if (str1.length() >= str2.length())
		 {
		 	if (str1.length()==str2.length())
			 {
			 	for (int i = str1.length() - 1; i >= 0; i--)
			 	{
			 		if (str1[i] < str2[i])
			 				break;
        			if (str1[i] > str2[i])
        			{
        				kol++;
        				break;
        			}
         		}
	   		}
	   	}
	   	else
	   		kol++;
	   	str1 = str2;
	}
    fin.close();
    return kol;
}

void Nature_Sort(char *name) // sorting naturally merge
{
    string str1, str2;
    int kol;
    bool t; // t = 1, if written to the first file - f1 ; t = 0, if written to the second file - f2
    fstream f,f1,f2;
	kol = series (name);
    while (kol != 1) //until the number of series in the file is 1
    {
       f.open(name,ios::in); // splitting file
       f1.open("file1_sort.txt",ios::out);
       f2.open("file2_sort.txt",ios::out);
       if (!f.eof())
        	f >> str1;
        f1 << str1 << endl;
        t = true; 
       while (!f.eof())
       {	
        	f >> str2;
        	 if (str1.length() > str2.length())
        	 	{
        	 		if (t)
        	 			f1 << str2 << endl;
        	 		else
        	 			f2 << str2 << endl;
        	 	}
        	else
        		if (str1.length() < str2.length())
        		{
        			if(t)
        			{
        				f2 << str2 << endl;
						t = false;	
        			}
        			else 
        			{
        				f1 << str2 << endl;
        				t = true;
        			}
        		}
        	else // if the lengths are equal
			 {
			 	for (int i = str1.length() - 1; i >= 0; i--)
			 	{
			 		if (str1[i] < str2[i]) // write to one file
			 		{
			 				if(t)
			 					f1 << str2 << endl;
			 				else
							 	f2 << str2 << endl;	
			 				break;
			 		}	
        			if (str1[i] > str2[i]) // write to different files
        			{	
        				if (t)
        				{
        					f2 << str2 << endl;
        					t = false;
        				}
        				else
        				{
        					f1 << str2 << endl;
        					t = true;
        				}
        				break;
        			}
         		}
        	}
        str1 = str2;
       }
       f.close();f1.close();f2.close();

       f.open(name,ios::out); // merge files
       f1.open("file1_sort.txt",ios::in);
       f2.open("file2_sort.txt",ios::in);
       if ( !f1.eof() )
        	f1 >> str1;
       if ( !f2.eof() )
        	f2 >> str2;
       while ( !f1.eof() && !f2.eof() )
       {
          while (!f1.eof() && !f2.eof() )
          {
            	if (str1.length() > str2.length())
		 			{
		 				f << str1 << endl;
                    	f1 >> str1;
                	}
		 		else 
			 		if (str1.length()==str2.length())
					 {
			 			for (int i = str1.length() - 1; i >= 0; i--)
			 			{
			 				if (str1[i] < str2[i])
			 					{
			 						f << str1 << endl;
                    				f1 >> str1;
			 						break;
								 }
        					if (str1[i] > str2[i])
        					{
        						f << str2 << endl;
	   							f2 >> str2;
        						break;
        					}
         				}	
	   				}
	   			else
	   				{
	   					f << str2 << endl;
	   					f2 >> str2;
					}
              
       		 }
        }
      while ( !f1.eof() )
      {
          f << str1 << endl;
          f1 >>str1;
      }
      while ( !f2.eof() )
      {
         f << str2 << endl;
         f2 >> str2;
      }
      f.close();f1.close();f2.close();
      kol = series(name);
   }
   remove("file1_sort.txt");
   remove("file2_sort.txt");
}

char* outputfile(char *begfile, char *endfile) 		// creation of the output file
{
 	ifstream fin (begfile);
 	ofstream fout (endfile);
 	string str;
 	if (!fin)
	{
		cerr << "Error opening file" << endl;
	}
	if (!fout)
	{
		cerr << "Error opening file" << endl;
	}
 	
	while(!fin.eof())
	{
		fin >> str;
		fout << str << endl;
	}
   
   	fin.close();   
	fout.close();
 	return endfile;
}

int main()
{
  	char *begfile = "f1.txt";
  	char *endfile = outputfile (begfile, "f2.txt"); // copying the contents of file f1.txt to f2.txt
  	Nature_Sort(endfile); 						// sorting the file f2.txt
  	cout << "Output file:" << endfile << endl;
  	system("pause");
  	return 0;
}
