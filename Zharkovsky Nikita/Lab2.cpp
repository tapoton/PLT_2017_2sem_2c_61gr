/*
    5. Set of entries of the following structure: phone number, name, address. 
	By phone number to find the owner's full name and address.
*/
#include<iostream>
#include<string>
#define HASHTAB_SIZE 101
using namespace std;

struct listnode {
    string phone_number;
    string fio;
    string adress;
    struct listnode *next;
};
struct listnode *hashtab[HASHTAB_SIZE];

unsigned int hashtab_hash(string phone_number)
{
    int sum=0,hash;
    for(int i=0;i<phone_number.size();i++)
        sum+=(int)phone_number[i]-(int)'0';
    hash=sum%HASHTAB_SIZE;
    return hash;
}

void hashtab_init(struct listnode **hashtab)
{
    for (int i = 0; i < HASHTAB_SIZE; i++)
        hashtab[i] = NULL;
}

void hashtab_add(struct listnode **hashtab, string phone_number, string fio, string adress)
{
    struct listnode *node = new listnode;
    int index = hashtab_hash(phone_number);
    // adding to the begin of list
    if (node != NULL) {
        node->phone_number = phone_number;
        node->fio = fio;
        node->adress = adress;
        node->next = hashtab[index];
        hashtab[index] = node;
    }
}

struct listnode *hashtab_lookup(struct listnode **hashtab, string phone_number)
{
    int index = hashtab_hash(phone_number);
    struct listnode *node;
    for (node = hashtab[index]; node != NULL; node = node->next) 
    {
        if (node->phone_number == phone_number)
            return node; 
    }
    return NULL;
}

int main()
{
	hashtab_init(hashtab);
	cout<<"Commands:"<<endl<<"1.Add name to the hash"<<endl<<"2.Lookup for number"<<endl<<"3.End the program";
	int command;
	while(1)
	{
		cout<<endl<<"Enter the command: ";
		cin>>command;
		switch(command)
		{
			case 1:{
    			cout<<"Enter the number of names: ";
    			int n,temp; cin>>n; temp=n;
    			cout<<"Enter phone number, name, adress (example: 88001232323 Alex Moscow):"<<endl;
    			while(n)
    			{
    				cout<<temp-n+1<<": ";
    				string phone_number,fio,adress;
    				cin>>phone_number>>fio>>adress;
    				if(hashtab_lookup(hashtab, phone_number)!=NULL)
    				{
    					cout<<"This phone number already exist"<<endl;
    					n++;
					}
    				else hashtab_add(hashtab, phone_number, fio, adress);
    				n--;
				}
				break;
			}
			case 2:{
				cout<<"Enter the phone number: ";
				string phone_number;
				cin>>phone_number;
		        struct listnode *node = hashtab_lookup(hashtab, phone_number);
		        if(node!=NULL) cout<<" Phone number: "<<node->phone_number<<endl
				                   <<" Name: "<<node->fio<<endl
								   <<" Adress: "<<node->adress<<endl;
				else cout<<" Not found";
				break;
			}
			case 3:{
				return 0;
				break;
			}
		}
	}
    return 0;
}
