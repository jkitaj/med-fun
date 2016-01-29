//#include <QCoreApplication>
#include <iostream>
#include <ctime>
#include "functions.h"
#include "menu.h"
#include "fileUtils.h"

using namespace std;

int main(int argc, char *argv[]) {
    clock_t startAll, endAll;
    clock_t startFilePrepare, endFilePrepare;
    clock_t startAlg, endAlg;
    double diffAll, diffFilePrepare, diffAlg;

    startAll = clock();
    int d_column = 1;   //number of column where decision is
    int d_type;         // id of decision type
    int a_type = 3;// id of algorythm type
    int number_of_transactions = 0;

    string inputFileName;
    ifstream inputFile;

    if (!Menu(&d_column, &d_type, &a_type, &inputFile, inputFileName, &number_of_transactions))
        return endProgram();

    startFilePrepare = clock();
    string modifiedFile;
    create_modified_file(&inputFile, d_column, d_type, modifiedFile, 10);
    endFilePrepare = clock();
    diffFilePrepare = (endFilePrepare - startFilePrepare) / (double) (CLOCKS_PER_SEC / 1000);
    cout << "Koniec przetwarzania pliku - czas trwania operacji: " << diffFilePrepare << endl;

    vector<Candidate *> C1;//wektor do trzymania kandydatów o dlugosci 1
    int id_row = read_from_modified_file(modifiedFile, C1, number_of_transactions);
    cout << "Liczba rekordów: " << id_row + 1 << endl;
    vector<Candidate *> Rk;

    switch (a_type) {
        case 1:
            startAlg = clock();
            Basic_algorythm(C1, id_row + 1, Rk, d_column-1);
            endAlg = clock();
            break;
        case 2:
            startAlg = clock();
            Stripped_algorythm(C1, id_row + 1, Rk, d_column-1);
            endAlg = clock();
            break;
        case 3:
            startAlg = clock();
            Super_Fun_algorythm(C1, id_row + 1, Rk, d_column-1);
            endAlg = clock();
            break;
        default:
            std::cerr << "Wrong algorythm number";
            return endProgram();
    }

    diffAlg = (endAlg - startAlg) / (double) (CLOCKS_PER_SEC / 1000);
    cout << "Czas trwania algorytmu: " << diffAlg << endl;

    endAll = clock();
    diffAlg = (endAll - startAll) / (double) (CLOCKS_PER_SEC / 1000);
    cout << "Czas wykonania całego programu" << diffAlg << endl;

    save_to_outputfile(Rk, a_type, number_of_transactions, inputFileName, diffFilePrepare, diffAlg, diffAll);

    return endProgram();
}
