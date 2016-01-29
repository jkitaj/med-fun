//#include <QCoreApplication>
#include <iostream>
#include <ctime>
#include "functions.h"
#include "menu.h"
#include "fileUtils.h"

using namespace std;

int main(int argc, char *argv[]) {

    //QCoreApplication a(argc, argv);
    clock_t startAll, endAll;
    clock_t startFilePrepare, endFilePrepare;
    clock_t startAlg, endAlg;

    startAll = clock();
    int d_column = 1;   //number of column where decision is
    int d_type;         // id of decision type
    int a_type = 3;// id of algorythm type
    int number_of_transactions = 10;

    ifstream inputFile;
    ofstream outputFile;
    prepare_output_file(&outputFile);

    if (!Menu(&d_column, &d_type, &a_type, &inputFile))
        return endProgram();





    startFilePrepare = clock();
    //create_modified_file(input_file, decision_column, decision_type);
    endFilePrepare = clock();
    double diff = (endFilePrepare - startFilePrepare) / (double) (CLOCKS_PER_SEC / 1000);
    cout << "Koniec przetwarzania pliku - czas trwania operacji: " << diff << endl;
    write_time_to_file(&outputFile, "Time of preparing data: ", diff);


    vector<Candidate *> C1;//wektor do trzymania kandydatów o dlugosci 1
    int id_row = 3;//read_from_modified_file(input_file, C1, number_of_transactions);
    cout << "Liczba rekordów: " << id_row + 1 << endl;
    vector<Candidate *> Rk;


    switch (a_type) {
        case 1:
            startAlg = clock();
            Basic_algorythm(C1, id_row + 1, Rk, d_column);
            endAlg = clock();
            break;
        case 2:
            startAlg = clock();
            Stripped_algorythm(C1, id_row + 1, Rk, d_column);
            endAlg = clock();
            break;
        case 3:
            startAlg = clock();
            Basic_algorythm(C1, id_row + 1, Rk, d_column);
            endAlg = clock();
            break;//tu bedzie super_fun
        default:
            std::cerr << "Wrong algorythm number";
            endProgram();
            break;
    }

    diff = (endAlg - startAlg) / (double) (CLOCKS_PER_SEC / 1000);
    cout << "Czas trwania algorytmu: " << diff << endl;
    write_time_to_file(&outputFile, "Algorithm execution time", diff);


    //save_to_outputfile(Rk, a_type, number_of_transactions, dif1, dif2, input_file);


    endAll = clock();
    diff = (endAll - startAll) / (double) (CLOCKS_PER_SEC / 1000);
    cout << "Czas wykonania całego programu" << diff << endl;
    write_time_to_file(&outputFile, "Complet time of run program: ", diff);

    return endProgram();
    //return a.exec();
}
