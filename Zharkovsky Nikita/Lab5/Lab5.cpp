#include<iostream>
#include<fstream>
using namespace std;

char* CountSum(char *);
void SimpleMergingSort(char *);
char *Build(char *, char *);

int main()
{
    //input file name
    char *inputFileName = "input.txt";
    //Create temp file with structure: index of matrix, sum of side diagonal of the matrix
    char *tempSumFile = CountSum(inputFileName);
    //Sorting temp file by sum of side diagonal
    SimpleMergingSort(tempSumFile);
    //Build output file using temp sorted file
    char *output = Build(inputFileName, tempSumFile);
    remove(tempSumFile);
    cout << "Complete. Output file name = '" << output << "'\n";
}

char* CountSum(char *inputFileName)
{
    char *tempSumFile = "tempSumAndIndex.txt";
    ifstream fin(inputFileName);
    ofstream fout("tempSumAndIndex.txt");
    int m;
    fin >> m;
    for (int k = 0; k < m; k++)
    {
        int n;
        fin >> n;
        int sum = 0;
        for (int  i = 0, x; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                fin >> x;
                if (i == n - 1 - j)
                    sum += x;
            }
        }
        fout << k << " " <<  sum << "\n";
    }
    fout.close();
    fin.close();
    return tempSumFile;
}

void SimpleMergingSort (char *name)
{
    int i1, i2, a1, a2, k, i, j, kol, tmp;
    FILE *f, *f1, *f2;
    kol = 0;
    if ( (f = fopen(name,"r")) == NULL )
        printf("\nÈñõîäíûé ôàéë íå ìîæåò áûòü ïðî÷èòàí...");
    else
    {
        while ( !feof(f) )
        {
            fscanf(f,"%d",&i1);
            fscanf(f,"%d",&a1);
            kol++;
        }
        fclose(f);
    }
    k = 1;
    while ( k < kol )
    {
        f = fopen(name,"r");
        f1 = fopen("smsort_1","w");
        f2 = fopen("smsort_2","w");
        if ( !feof(f) )
        {
            fscanf(f,"%d",&i1);
            fscanf(f,"%d",&a1);
        }
        while ( !feof(f) )
        {
            for ( i = 0; i < k && !feof(f) ; i++ )
            {
                fprintf(f1,"%d ",i1);
                fscanf(f,"%d",&i1);
                fprintf(f1,"%d ",a1);
                fscanf(f,"%d",&a1);
            }
            for ( j = 0; j < k && !feof(f) ; j++ )
            {
                fprintf(f2,"%d ",i1);
                fscanf(f,"%d",&i1);
                fprintf(f2,"%d ",a1);
                fscanf(f,"%d",&a1);
            }
        }
        fclose(f2);
        fclose(f1);
        fclose(f);

        f = fopen(name,"w");
        f1 = fopen("smsort_1","r");
        f2 = fopen("smsort_2","r");
        if ( !feof(f1) )
        {
            fscanf(f1,"%d",&i1);
            fscanf(f1,"%d",&a1);
        }
        if ( !feof(f2) )
        {
            fscanf(f2,"%d",&i2);
            fscanf(f2,"%d",&a2);
        }
        while ( !feof(f1) && !feof(f2) )
        {
            i = 0;
            j = 0;
            while ( i < k && j < k && !feof(f1) && !feof(f2) )
            {
                if ( a1 < a2 )
                {
                    fprintf(f,"%d ",i1);
                    fscanf(f1,"%d",&i1);
                    fprintf(f,"%d ",a1);
                    fscanf(f1,"%d",&a1);
                    i++;
                }
                else
                {
                    fprintf(f,"%d ",i2);
                    fscanf(f2,"%d",&i2);
                    fprintf(f,"%d ",a2);
                    fscanf(f2,"%d",&a2);
                    j++;
                }
            }
            while ( i < k && !feof(f1) )
            {
                fprintf(f,"%d ",i1);
                fscanf(f1,"%d",&i1);
                fprintf(f,"%d ",a1);
                fscanf(f1,"%d",&a1);
                i++;
            }
            while ( j < k && !feof(f2) )
            {
                fprintf(f,"%d ",i2);
                fscanf(f2,"%d",&i2);
                fprintf(f,"%d ",a2);
                fscanf(f2,"%d",&a2);
                j++;
            }
        }
        while ( !feof(f1) )
        {
            fprintf(f,"%d ",i1);
            fscanf(f1,"%d",&i1);
            fprintf(f,"%d ",a1);
            fscanf(f1,"%d",&a1);
        }
        while ( !feof(f2) )
        {
            fprintf(f,"%d ",i2);
            fscanf(f2,"%d",&i2);
            fprintf(f,"%d ",a2);
            fscanf(f2,"%d",&a2);
        }
        fclose(f2);
        fclose(f1);
        fclose(f);
        k *= 2;
    }
    remove("smsort_1");
    remove("smsort_2");
}

char *Build(char *inputFileName, char *tempSumFile)
{
    char *output = "output.txt";
    ifstream temp(tempSumFile);
    ofstream fout(output);

    ifstream fin(inputFileName);
    int m;
    fin >> m;
    fin.close();

    for (int k = 0, index, sum, tempM, n; k < m; k++)
    {
        temp >> index >> sum;

        ifstream fin(inputFileName);

        fin >> tempM;
        for(int p = 0, n; p < index; p++)
        {
            fin >> n;
            for(int i = 0, x; i < n; i++)
                for(int j = 0; j < n; j++)
                    fin >> x;
        }

        fin >> n;
        for(int i = 0, x; i < n; i++)
        {
            for(int j = 0; j < n; j++)
            {
                fin >> x;
                fout<< x << " ";
            }
            fout << "\n";
        }

        fout << "\n";

        fin.close();
    }

    temp.close();
    fout.close();

    return output;
}
