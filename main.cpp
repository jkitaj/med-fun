#include <QCoreApplication>
#include <iostream>
#include "functions.h"
#include <ctime>
using namespace std;



int main(int argc, char *argv[])
{

    QCoreApplication a(argc, argv);
    clock_t start,end;

    int d_column=1;//number of column where decision is
    int d_type;// id of decision type
    int a_type=3;// id of algorythm type
    int number_of_transactions=10;
    string input_file="letters.data";
    string output_file;




    //TODO
    //Menu do wprowadzania danych z konsoli, do dodania parametr number_of_transactions
    void Menu(int &d_column, int &d_type, int &a_type, string &input_file,string &output_file);
    //Menu(d_column, d_type, a_type, input_file, output_file);
    start=clock();
    //create_modified_file(input_file, decision_column, decision_type);
    end=clock();
    double dif1=(end - start) / (double)(CLOCKS_PER_SEC / 1000);
    cout<<"koniec przetwarzania pliku- czas: "<<dif1<<endl;




    vector <Candidate*> C1;//wektor do trzymania kandydatów o dlugosci 1
    start=clock();
    int id_row=read_from_modified_file(input_file,C1,number_of_transactions);
    cout<<"Liczba rekordów: "<<id_row+1<<endl;
    vector <Candidate*> Rk;
    switch(a_type)
                   {

                   case 3:
                        Super_Fun_algorythm(C1,id_row+1,Rk,d_column);
                        break;

                   case 2:
                        Stripped_algorythm(C1,id_row+1,Rk,d_column);
                        break;
                   case 1:
                        Basic_algorythm(C1,id_row+1,Rk,d_column);
                        break;
                   default:
                       std::cerr << "Wrong algorythm number";
                       break;
                   }





    end=clock();
    double dif2=(end - start) / (double)(CLOCKS_PER_SEC / 1000);
    save_to_outputfile(Rk,a_type,number_of_transactions,dif1,dif2,input_file);





    cout<<"Czas wykonania algorytmu "<<dif2<<endl;



    return a.exec();
}
