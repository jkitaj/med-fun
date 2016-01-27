#include <QCoreApplication>
#include <iostream>
#include "functions.h"
#include <time.h>
using namespace std;



int main(int argc, char *argv[])
{

    QCoreApplication a(argc, argv);
    time_t start,end;

    int d_column;//number of column where decision is
    int d_type;// id of decision type
    int a_type=1;// id of algorythm type
    string input_file;
    string output_file;




    //TODO
    //Menu do wprowadzania danych z konsoli
    void Menu(int &d_column, int &d_type, int &a_type, string &input_file,string &output_file);
    //Menu(d_column, d_type, a_type, input_file, output_file);
    time (&start);
    //create_modified_file(input_file, decision_column, decision_type);
    time (&end);
    double dif = difftime(end,start);
    cout<<"koniec przetwarzania pliku- czas: "<<dif<<endl;




    vector <Candidate*> C1;//wektor do trzymania kandydatów o dlugosci 1
    time (&start);
    int id_row=read_from_modified_file("car.data",C1);
    vector <Candidate*> Rk;
    switch(a_type)
                   {

                   case 3:
                        Basic_algorythm(C1,id_row,Rk);
                        break;//tu bedzie super_fun

                   case 2:
                        Stripped_algorythm(C1,id_row,Rk);
                        break;
                   case 1:
                        Basic_algorythm(C1,id_row,Rk);
                        break;
                   default:
                       std::cerr << "Wrong algorythm number";
                       break;
                   }




    //TODO
    save_to_outputfile(Rk);



    time(&end);
    dif=difftime(end,start);
    cout<<"Czas wykonania algorytmu "<<dif<<endl;



    return a.exec();
}
