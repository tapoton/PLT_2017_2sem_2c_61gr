//Zaytsev Dmitri №10
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <algorithm>
using namespace std;

struct node
 {int len;
  bool end_word;
  node *prev;
  int ind;
  node *next[26];};
  
void insert(string word,node *begin)
 {node *now=begin;
  for(int i=0;i<word.length();++i)
   {int letter=(int)word[i]-(int)'a';
	if(now->next[letter]==NULL)
	 {now->next[letter]=new node();
	  now->next[letter]->prev=now;
      now->next[letter]->end_word=0;
      now->next[letter]->len=now->len+1;
      now->next[letter]->ind=letter;
      for(int i=0;i<26;++i)
       {now->next[letter]->next[i]=NULL;}}
	now=now->next[letter];}
  now->end_word=1;}

string reverse(string word)
 {int len=word.length();
  for(int i=0;i<len/2;++i)
   {char t=word[i];
    word[i]=word[len-i-1];
    word[len-i-1]=t;}
  return(word);}

void print(node *now)
 {bool trig=0;
  if(now!=NULL)
   {for(int i=25;i>=0;--i)
     {if(now->next[i]!=NULL)
	   {trig=1;
	    print(now->next[i]);}
	  else
	   {if((now->end_word==1)&&(i==0)&&(trig==0))
	     {for(int j=0;j<now->len;++j) 
	       {cout<<" ";}
          cout<<(char)(now->ind+int('a'))<<endl;}}}
	if(trig==1)
	 {if(now->prev!=NULL)
	   {for(int j=0;j<now->len;++j) 
	     {cout<<" ";}
          cout<<(char)(now->ind+int('a'))<<endl;}}}}
     
void r_build(node *now, string word,node *begin_r)
 {if(now!=NULL)
   {if(now->len!=0)
     {word=word+(char)(now->ind+(int)'a');}
    if(now->end_word)
     {insert(reverse(word),begin_r);}
    for(int i=25;i>=0;--i)
     {if(now->next[i])
	   {r_build(now->next[i],word,begin_r);}}}}
	   
void print_2(node *now, string word)
 {if(now!=NULL)
   {if(now->len!=0)
     {word=word+(char)(now->ind+(int)'a');}
    if(now->end_word)
     {cout<<endl<<word;}
    for(int i=25;i>=0;--i)
     {if(now->next[i])
	   {print_2(now->next[i],word);}}}}
   
int main()
 {setlocale(LC_ALL, "Russian");
  node *begin;
  node *begin_r;
  node *now;
  begin=new node();
  begin->prev=NULL;
  begin->end_word=0;
  begin->len=0;
  begin_r=new node();
  begin_r->prev=NULL;
  begin_r->end_word=0;
  begin_r->len = 0;
  for(int i=0;i<26;++i)
   {begin->next[i]=NULL;
    begin_r->next[i]=NULL;}
  string word;
  cout<<"Введите слова(Латиницей). В конце поставьте 0."<<endl;
  while(1)
   {cin>>word;
    if(word=="0")
	 {break;}
	else
	 {insert(word,begin);}}
  cout<<endl<<"________________Оригинальное дерево__________________"<<endl;
  print(begin);
  r_build(begin,"",begin_r);
  cout<<endl<<"________________Реверсированное дерево__________________"<<endl;
  print(begin_r); 
  cout<<endl<<"_______________Слова оригинального дерева___________________"<<endl;
  print_2(begin,"");
  cout<<endl<<"_________________Слова реверсированного дерева_________________"<<endl;
  print_2(begin_r,"");
  return 0;}
