#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <cstdio>
#define HASHTABLE_size 52

using namespace std;

struct Node
{
	string value;
	int count;
	Node *next;
}**hashtable;

void Create_TAB()
{
	hashtable = new Node * [HASHTABLE_size];
	for (int i = 0; i < HASHTABLE_size; i++)	
			hashtable[i] = NULL;	
}

void Remove_TAB()
{
	for(int i = 0;i < HASHTABLE_size; i++)
		if(hashtable[i] != NULL) 
		{
			Node *q;
			while(hashtable[i] != NULL)
      		{
       			q = hashtable[i];
       			hashtable[i] = hashtable[i]->next;
       			delete q;
       			q = NULL; 
      		}
    	}
   	delete [] hashtable;		
 }
 
unsigned int hash_index (string value)
 {
	int sum = 0;
	for(int i=0 ;i <value.length(); i++)
		sum +=value[i]-'0';
  	return (sum % HASHTABLE_size);
 }

 Node *Search_TAB (string value) 
 {
 	Node *p;
   	p = hashtable[hash_index(value)];
   	while (p && p->value != value) 
  		 p = p ->next;
  	if( !p ) 
   		return NULL;
   	return p;
 }
  
 void Insert_TAB (string value)
 {
     Node *cur = new Node;
     Node *search = Search_TAB(value);
     int index = hash_index(value);
     if (search == NULL)
     {
     	if (cur != NULL) 
	 	{	
		 	cur->value = value;
		 	cur->count = 1;
         	cur->next = hashtable[index];
         	hashtable[index] = cur;
     	}
 	}
 	else
 			search->count++;
 }
 

 void Printf_TAB()
 {
 	cout << "The resulting hash function:" << endl;
	int sum = 0;
 	for (int i = 0; i < HASHTABLE_size; i++)
		if(hashtable[i] != NULL)
		{
     		Node *q;
     		
     	 	while(hashtable[i]!=NULL)
      		{   
       			q = hashtable[i];
       			sum += q->count;
       			cout << q-> value << " = " << q->count << endl;
       			hashtable[i]= hashtable[i]->next;
      		}
    	}
    	cout << "The total amount: " << sum << endl;
 }
 
 
 int main()
 {	
 	bool t = false;
 	int n = 127, m = 18, i;
 	char text[n];
 	Create_TAB();
 	char signs[] = ",.:;-()=+/*'><{}[]";
 	
	ifstream fin ("input.txt");
  	if (!fin)
	{
		cerr << "Error opening file" << endl;
	}
	
  	while (fin >> text)
  	{	
	  	if ((text[0] >= 'a'&& text[0] <= 'z') || (text[0] >= 'A' && text[0] <= 'Z'))
		 {
	 		for( int i = 0; i < n; i++)
  				for( int j = 0; j < m ; j++)
  			if (text[i]!=signs[j]) 
  					t = true;
  		 }
  		else 
  			t = false;
  		for (i=0; text[i]!='\0'; i++);
  		if (text[i-1 ] == ';' || text[i-1 ] == '.' || text[i-1 ] == ':')
  			text[i-1]='\0';
  		if (t)
  			Insert_TAB(text);
  	}
  	
  	Printf_TAB();
  	Remove_TAB();
 	return 0;
 }
 
