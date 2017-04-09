
#include <iostream>
using namespace std;
 
struct stack
{
 int datax;
 int datay;
 stack *next;
};
 
const int n = 6;
int i,j;
int matrix[n][n]= 
{
 {1,1,0,0,1,0},
 {1,1,1,0,1,0},
 {0,1,1,1,1,0},
 {0,0,1,1,1,1},
 {1,1,1,1,1,0},
 {0,0,0,1,0,1}
};
 
 
 
/*=====================PROTORYPE======================*/
void Push(stack *&top, int valuex, int valuey); //добавление в стек пути
stack *Delete(stack *&top); //удаление из стека
void Show(stack *top); //показать стек
stack *Search(stack *&top, int xf, int yf, int **&matrix, int **&visited, int n); //поиск пути
bool Elemente(stack *top, int i, int j); //проверка стека на наличие элемента
/*=====================BODY==========================*/
int main()
{
    setlocale (LC_ALL, "Rus");
    bool flag = false;
    int x, y;
 
    int **visited= new int *[n];
        for (i=0; i<n; i++)
            visited[i]=new int [n];
 
    for (i=0; i<n; i++)
        for (j=0; j<n; j++)
            visited[i][j]=0;
 
    int **matrfunc= new int *[n];
        for (i=0; i<n; i++)
            matrfunc[i]=new int [n];
 
    for (i=0; i<n; i++)
        for (j=0; j<n; j++)
            matrfunc[i][j]=matrix[i][j];
 
    for(i=0; i<n; i++)
    {
        cout<<"\n";
        for(j=0; j<n; j++)
        cout<<" "<<matrfunc[i][j]<<" ";
    }
 
 
    for(int k=0; k<3; k++)
    { 
    
    flag=false;
    
    while(!flag)
    {
    cout<<"\n enter the first coordinate path:";
    cin >> x;
    cout<<"\n enter the second coordinate path:";
    cin >> y;
    if ((x<0 || x>6) || (y<0 || y>6))
    {
        cout<<"\n The data is incorrect, please try again.";
        flag = false;
    }   
    else 
        {
        cout<< "\n The data is correct.";
        matrfunc[x][y]=0;
        matrfunc[y][x]=0;
        flag= true;
        }
        }
    }
    
    for(i=0; i<n; i++)
    {
        cout<<"\n";
        for(j=0; j<n; j++)
        cout<<" "<<matrfunc[i][j]<<" ";
    }
 
    int start,  finish, xs, ys, xf, yf;
    flag=false;
    do
    {
        cout <<"\n Enter begin path:";
        cin>>start;
        cout <<"\n Enter begin path:";
        cin>>finish;
 
        if (start<1 || start>6 || finish<1 || finish>6)
            {
            cout<<"\n The data is incorrect, please try again.";
            flag = false;
            }
        else
            {
                xs=start-1;
                ys=start-1;
                xf=finish-1;
                yf=finish-1;
                cout<<"\n The data is correct.";
                flag = true;
            }
    }
    while(!flag);
 
    stack * top=new stack;
    top->datax =xs;
    top->datay=ys;
    top->next=NULL;
 
    top = Search(top, xf, yf, matrfunc, visited, n);
 
    if(top!=NULL)
    Show(top);
    else 
    cout<<"\n no path";
 
    
 
    system("pause");
}
 
/*=====================FUNCTION======================*/
 
void push(stack *&top, int valuex, int valuey)
{
    stack* n = new stack;
    n -> datax = valuex;
    n -> datay = valuey;
    n -> next = top;
    top = n;
}
 
stack *Delete(stack *&top)
{
    stack *n = top->next;
    delete top;
    return n;
}
 
stack *Search(stack *&top, int xf, int yf, int **&matrix, int **&visited, int n)
{
    int i=0, j;
    bool flag=false;
    if(top->datax==xf && top->datay==yf)
        return top; 
    else 
    {
        j=top->datax;
        while(i<n || flag)
        {
 
            if(matrix[i][j]==1 && visited[i][j]==0 && Elemente(top,i,j)==false)
            {
                push(top, i, j);
                if(top->datax==xf && top->datay==yf)
                flag=true;
                else
                top=Search(top, xf,yf,matrix, visited, n);
            }
 
            else 
                i++;
        }
 
        if(flag==false)
        {
            visited[top->datax][top->datay]=1;
            top=Delete(top);
        }
        else 
            return top;
    }
 
}
 
void Show(stack *top)
{
    while(top!=NULL)
    {
        cout<<top->datax;
        cout<<" ,"<<top->datay<<"\n";
        top=top->next;
    }
}
 
bool Elemente(stack *top, int a, int b)
{
    bool flag=false;
    while(top!=NULL && !flag)
    {
        if(top->datax==a && top->datay==b)
        {
            flag = true;
        }
        top=top->next;
    }
        if (flag==true)
            return 1;
        else 
            return 0;   
}

