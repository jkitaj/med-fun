//
// Created by Jakub Kitaj.
//
#include "fileUtils.h"

void create_modified_file(string filename, int decision_column, int decision_type)
{
}

int read_from_modified_file(string filename, vector<Candidate *> &C1, int number_of_transactions)
{
    ifstream infile(filename.c_str());
    ofstream outfile("output.txt");
    vector <vector <dictionary> > dict;
    string s;
    int id_row=0;//ktory wiersz(transakcja) w pliku
    if (getline( infile, s )){
        istringstream ss( s );//ss cały wiersz pliku
        istringstream tmp (s);//to samo
        //policz ile kolumn potem przeczytaj
        int column_number_total=0;
        while (ss)



        {
            string s;
            if (!getline( ss, s, ',' )) break;//wez do przecinka z ss
            column_number_total++;

        }
        cout<<column_number_total<<endl;
        dict.resize(column_number_total);

        for (int z=0;z<column_number_total; z++){
            C1.push_back(new Candidate);
            C1.at(z)->Cand_id.push_back(z);
        }
        int column_number=0;
        while (tmp)
        {
            string s;
            if (!getline( tmp, s, ',' )) break;
            dict.at(column_number).push_back(dictionary(s,0));
            C1.at(column_number)->groups.push_back(new vector <int*> ());
            //int *id =new int(id_row);
            //id=id_row;
            C1.at(column_number)->groups.at(0)->push_back(new int(id_row));
            outfile<<"0 ";
            //int *a=C1.at(column_number)->groups.at(0)->at(0);
            //cout<<*a<<"\t"<<a<<endl;
            column_number++;
        }
        outfile<<"\n";
    }
    /*for(unsigned int z=0;z<dict.size(); z++){
        for(unsigned int a=0;a<dict.at(z).size(); a++){
            cout<<z<<"\t"<<dict.at(z).size()<<"\t"<<dict.at(z).at(a).word<<"\t";

        }
        cout<<endl;
    }*/


    int transaction_counter=2;
    while (infile && transaction_counter<=number_of_transactions)
    {
        id_row++;
        string s;
        if (!getline( infile, s )) break;
        istringstream ss( s );
        int column_number=0;
        while (ss)
        {
            string s;
            if (!getline( ss, s, ',' )) break;
            bool is_in_dict=false;
            for(unsigned int z=0;z<dict.at(column_number).size();z++){
                if(s==dict.at(column_number).at(z).word){//jezeli jest juz w slowniku, to dodaj do grupy o id ze slownika element(id_wiersza)
                    is_in_dict=true;
                    C1.at(column_number)->groups.at(dict.at(column_number).at(z).id)->push_back(new int (id_row));
                    outfile<<dict.at(column_number).at(z).id<<" ";
                    break;
                }

            }
            if(!is_in_dict){//dodaj do slownika, dodaj nowa grupe i jej element(id wiersza)
                int dict_id = dict.at(column_number).size();
                dict.at(column_number).push_back(dictionary(s,dict_id));
                C1.at(column_number)->groups.push_back(new vector <int*> ());
                C1.at(column_number)->groups.at(dict.at(column_number).at(dict_id).id)->push_back(new int (id_row));
                outfile<<dict.at(column_number).at(dict_id).id<<" ";
            }


            column_number++;
        }
        outfile<<"\n";
        transaction_counter++;


    }
    outfile.close();
    infile.close();
    /*for(unsigned int z=0;z<dict.size(); z++){
        for(unsigned int a=0;a<dict.at(z).size(); a++){
            cout<<dict.at(z).at(a).word<<"\t"<<dict.at(z).at(a).id<<"\t";

        }
        cout<<endl;
    }*/

    /*for(unsigned int z=0;z<C1.at(6)->groups.size(); z++){//atrybut 0 wszystkie grupy
        //cout<<z<<endl;
        for(unsigned int a=0;a<C1.at(6)->groups.at(z)->size(); a++){//wszystkie elementy z grupy
            //int *b=C1.at(5)->groups.at(z)->at(a);
            //cout<<*b<<"\t";
            cout<<*(C1.at(6)->groups.at(z)->at(a))<<"\t";

        }
        cout<<endl;
    }*/
    return id_row;//number of transactions
}

void save_to_outputfile(vector <Candidate*> Rk,int a_type, int number_of_transactions, double dif1, double dif2,string input_file)
{
    string filename="results";
    string a_name;
    ostringstream temp_records;
    temp_records<<number_of_transactions;
    string records=temp_records.str();
    for(unsigned int i=0;i<input_file.size();i++){
        if(input_file[i]=='.'){
            filename.append("_");
            filename.append(input_file.begin(),input_file.begin()+i);
            filename.append("_");
        }
    }
    filename.append(records);
    filename.append("_");
    switch(a_type)
    {

        case 3:
            a_name="SuperFun";
            break;//tu bedzie super_fun

        case 2:
            a_name="Stripped";
            break;
        case 1:
            a_name="Basic";
            break;
        default:
            a_name="Error";;
            break;
    }
    filename.append(a_name);
    filename.append(".txt");
    ofstream output(filename.c_str());
    output<<"Liczba minimalnych zaleznosci funkcyjnych "<<Rk.size()<<endl;
    output<<"Identyfikatory minimalnych zaleznosci funkcyjnych "<<endl;
    for(unsigned int i=0;i<Rk.size();i++){
        for(unsigned int j=0;j<Rk.at(i)->Cand_id.size();j++){
            output<<Rk.at(i)->Cand_id.at(j)<<" ";
        }
        output<<"\t";
    }
    output<<endl;
    output<<"Czas przetwarzania pliku: "<<dif1<<endl;
    output<<"Czas wykonywania algorytmu: "<<dif2<<endl;
    output.close();
}

void prepare_output_file(ofstream *outputFile){

}

void write_time_to_file(ofstream *outputFile, string str, double time){

}