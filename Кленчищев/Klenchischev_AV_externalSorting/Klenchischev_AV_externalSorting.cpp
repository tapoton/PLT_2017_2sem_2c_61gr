#include <iostream>
#include <fstream>

using namespace std;

char* multiplyMatrix(char *inputFileName) {
    char *tmpFileName = "tmpFile.txt";

    ifstream inputName(inputFileName);
    ofstream tmpFile(tmpFileName);
    int count;
    inputName >> count;
    for (int k = 0; k < count; k++) {
        int matrixCount;
        inputName >> matrixCount;
        int multiplication = 1;
        for (int  i = 0, value; i < matrixCount; i++) {
            for (int j = 0; j < matrixCount; j++) {
                inputName >> value;
                multiplication *= value;
            }
        }
        tmpFile << k << " " <<  multiplication << "\n";
    }

    tmpFile.close();
    inputName.close();
    return tmpFileName;
}

void sortTmpFile(char *tmpFileName) {
    int index1, index2;
    int mult1, mult2;
    int k, i, j, count = 0;

    FILE  *tmpFile, *tmpFile2, *tmpFile3;

    if ( (tmpFile = fopen(tmpFileName,"r")) == NULL )
        cout << "Can't open file" << endl;
    else {
        while (!feof(tmpFile)) {
            fscanf(tmpFile,"%d",&index1);
            fscanf(tmpFile,"%d",&mult1);
            count++;
        }
        fclose(tmpFile);
    }
    k = 1;
    while (k < count) {
        tmpFile = fopen(tmpFileName,"r");
        tmpFile2 = fopen("tmpFile2","w");
        tmpFile3 = fopen("tmpFile3","w");
        if (!feof(tmpFile)) {
            fscanf(tmpFile,"%d",&index1);
            fscanf(tmpFile,"%d",&mult1);
        }
        while (!feof(tmpFile)) {
            for (i = 0; i < k && !feof(tmpFile) ; i++) {
                fprintf(tmpFile2,"%d ",index1);
                fscanf(tmpFile,"%d",&index1);
                fprintf(tmpFile2,"%d ",mult1);
                fscanf(tmpFile,"%d",&mult1);
            }
            for (j = 0; j < k && !feof(tmpFile) ; j++)
            {
                fprintf(tmpFile3,"%d ",index1);
                fscanf(tmpFile,"%d",&index1);
                fprintf(tmpFile3,"%d ",mult1);
                fscanf(tmpFile,"%d",&mult1);
            }
        }
        fclose(tmpFile3);
        fclose(tmpFile2);
        fclose(tmpFile);

        tmpFile = fopen(tmpFileName,"w");
        tmpFile2 = fopen("tmpFile2","r");
        tmpFile3 = fopen("tmpFile3","r");
        if (!feof(tmpFile2)) {
            fscanf(tmpFile2,"%d",&index1);
            fscanf(tmpFile2,"%d",&mult1);
        }
        if (!feof(tmpFile3)) {
            fscanf(tmpFile3,"%d",&index2);
            fscanf(tmpFile3,"%d",&mult2);
        }
        while (!feof(tmpFile2) && !feof(tmpFile3)) {
            i = 0;
            j = 0;
            while (i < k && j < k && !feof(tmpFile2) && !feof(tmpFile3)) {
                if (mult1 < mult2) {
                    fprintf(tmpFile,"%d ",index1);
                    fscanf(tmpFile2,"%d",&index1);
                    fprintf(tmpFile,"%d ",mult1);
                    fscanf(tmpFile2,"%d",&mult1);
                    i++;
                }
                else {
                    fprintf(tmpFile,"%d ",index2);
                    fscanf(tmpFile3,"%d",&index2);
                    fprintf(tmpFile,"%d ",mult2);
                    fscanf(tmpFile3,"%d",&mult2);
                    j++;
                }
            }
            while (i < k && !feof(tmpFile2)) {
                fprintf(tmpFile,"%d ",index1);
                fscanf(tmpFile2,"%d",&index1);
                fprintf(tmpFile,"%d ",mult1);
                fscanf(tmpFile2,"%d",&mult1);
                i++;
            }
            while (j < k && !feof(tmpFile3)) {
                fprintf(tmpFile,"%d ",index2);
                fscanf(tmpFile3,"%d",&index2);
                fprintf(tmpFile,"%d ",mult2);
                fscanf(tmpFile3,"%d",&mult2);
                j++;
            }
        }
        while (!feof(tmpFile2)) {
            fprintf(tmpFile,"%d ",index1);
            fscanf(tmpFile2,"%d",&index1);
            fprintf(tmpFile,"%d ",mult1);
            fscanf(tmpFile2,"%d",&mult1);
        }
        while (!feof(tmpFile3)) {
            fprintf(tmpFile,"%d ",index2);
            fscanf(tmpFile3,"%d",&index2);
            fprintf(tmpFile,"%d ",mult2);
            fscanf(tmpFile3,"%d",&mult2);
        }

        fclose(tmpFile);
        fclose(tmpFile3);
        fclose(tmpFile2);

        k *= 2;
    }
    remove("tmpFile2");
    remove("tmpFile3");
}

void printSortedToFile(char *inputFileName, char *tmpFileName) {
    char *outputFileName = "output.txt";
    ifstream tmpFile(tmpFileName);
    ofstream outputFile(outputFileName);

    ifstream inputFile(inputFileName);
    int count;
    inputFile >> count;
    inputFile.close();

    int index, mult, tmpCount, matrixCount, value;
    for (int k = 0; k < count; k++) {
        tmpFile >> index >> mult;

        ifstream inputFile(inputFileName);

        inputFile >> tmpCount;
        for(int p = 0; p < index; p++) {
            inputFile >> matrixCount;
            for(int i = 0; i < matrixCount; i++)
                for(int j = 0; j < matrixCount; j++)
                    inputFile >> value;
        }

        inputFile >> matrixCount;
        for(int i = 0; i < matrixCount; i++) {
            for(int j = 0; j < matrixCount; j++) {
                inputFile >> value;
                outputFile << value << " ";
            }
            outputFile << "\n";
        }

        outputFile << "\n";

        inputFile.close();
    }

    tmpFile.close();
    outputFile.close();
}

int main() {
    char *inputFileName = "input.txt";
    char *tmpFileName = multiplyMatrix(inputFileName);

    sortTmpFile(tmpFileName);
    printSortedToFile(inputFileName, tmpFileName);
    remove(tmpFileName);

    cout << "Completed" << endl;

    return 0;
}
