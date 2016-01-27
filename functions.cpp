#include "functions.h"
void PartitionArrayRepresentation(vector <vector <int*>* > A,vector <int> &T){

    for(unsigned int i=0;i<A.size();i++)
        for(unsigned int j=0;j<A.at(i)->size();j++)
            T.at(*(A.at(i)->at(j)))=i;


}
void Product(vector <vector <int*>* > A, vector <vector <int*>* > B, vector <vector <int*>* > &C, int &GNo,vector <int> T,int N)
{
    //std::list<std::list<int> > S; //lista list, kontener S
    //std::multimap<int,int>S;
    vector<vector<int> > S;
    C.clear();
    //S.resize(A.GroupNo);
    S.resize(N);
   // C.T.clear();
   // C.T.resize(A.T.size());
    int GroupsNo=0;
    PartitionArrayRepresentation(A,T);

    set<int> AGroupIds;//set, bo groupsID moze sie powtarzac, a my nie chcemy
    for(unsigned int i=0;i<B.size();i++){//petla obslugujaca kazda grupe B
        AGroupIds.clear();
        int j;
        for(unsigned int k=0;k<B.at(i)->size();k++){//petla obslugujaca kazdy element z grupy z B
            j=T.at(*(B.at(i)->at(k))); // B.at(i).at(k) - oid
            S.at(j).push_back(*(B.at(i)->at(k))); //S[j]
            AGroupIds.insert(j);
        }
        set<int>::iterator it;
        for (it=AGroupIds.begin(); it!=AGroupIds.end(); ++it){
            C.push_back(new vector <int*> ());
            for(unsigned int x=0;x<S.at(*it).size(); x++){//insertowanie S[j] do C
                //std::cout<<"krok4a"<<std::endl;
                //C.T.at(S.at(*it).at(x))=GroupsNo;
                C.back()->push_back(new int (S.at(*it).at(x)));
                //cout<<"krok4b"<<endl;
            }
            GroupsNo++;



        }
        S.clear();
        S.resize(N);
    }
    GNo=GroupsNo;
}


bool Holds(vector<int> T,vector <vector <int*>* > C)
{
    for(unsigned int i=0;i<C.size();i++){//petla obslugujaca kazda grupe z C
        int oid=*(C.at(i)->at(0));
        int firstGroup = T.at(oid);
        for(unsigned int k=1;k<C.at(i)->size();k++){//petla obslugujaca kazdy element z grupy z C
            oid=*(C.at(i)->at(k));
            int nextGroup = T.at(oid);
            if(firstGroup!=nextGroup)
            return false;
        }
    }
    return true;
}


void FunGen(vector <Candidate*> Ck,int k, vector <Candidate*> &output, vector <int> T, int N)
{
    for(unsigned int i=0;i<Ck.size();i++)
        for(unsigned int j=i+1;j<Ck.size();j++){
            bool ok_to_merge=true;
            //cout<<"Probuje laczyc "<<i<<" z "<<j<<endl;
            for(int l=0;l<k;l++){
                if(l==k-1){
                    if(Ck.at(i)->Cand_id.at(l)==Ck.at(j)->Cand_id.at(l)){
                        ok_to_merge=false;
                        //cout<<"takie same "<<Ck.at(i)->Cand_id.at(l)<<"\t"<<Ck.at(j)->Cand_id.at(l)<<endl;
                    }


                }
                else if(Ck.at(i)->Cand_id.at(l)!=Ck.at(j)->Cand_id.at(l)){
                        ok_to_merge=false;
                        //cout<<"inne"<<Ck.at(i)->Cand_id.at(l)<<"\t"<<Ck.at(j)->Cand_id.at(l)<<endl;
                        break;
                    }

                    /*if(Ck.at(i)->Cand_id.at(l)!=Ck.at(j)->Cand_id.at(l))
                        ok_to_merge=true;
                    else
                        ok_to_merge=false;
                }
                else{
                    if(Ck.at(i)->Cand_id.at(l)==Ck.at(j)->Cand_id.at(l))
                        ok_to_merge=true;
                    else{
                        ok_to_merge=false;
                        break;
                    }
                }*/

            }
            if(ok_to_merge){
                output.push_back(new Candidate);
                output.back()->Cand_id=Ck.at(i)->Cand_id;//dodaj id atrybutów z pierwszego dziecka
                output.back()->Cand_id.push_back(Ck.at(j)->Cand_id.at(k-1));// i ostatni id z drugiego dziecka
                    //for(unsigned int h=0;h<output.back()->Cand_id.size();h++)
                      //  cout<<output.back()->Cand_id.at(h);
                    //cout<<"\t";

                Product(Ck.at(i)->groups,Ck.at(j)->groups, output.back()->groups, output.back()->GroupsNo,T,N);
                bool cand_validate=false;
                vector <int> cand_validator;
                for(unsigned int m=0;m<output.back()->Cand_id.size();m++){//petla do sprawdzania kandydata
                    cand_validator.clear();
                    for(unsigned int n=0;n<output.back()->Cand_id.size();n++){//petla do tworzenia sprawdzianow dla kandydata
                        if(n!=m)
                            cand_validator.push_back(output.back()->Cand_id.at(n));
                    }
                    for(unsigned int o=0;o<Ck.size();o++){//sprawdzenie czy sprawdzian spelnia warunki
                        if(cand_validator==Ck.at(o)->Cand_id){//sprawdz czy istnieje podzbior
                            cand_validate=true;
                            if(output.back()->GroupsNo==Ck.at(o)->GroupsNo)//sprawdz czy podzbior ma tyle samo grup
                                cand_validate=false;
                            break;
                        }
                    }
                    if(cand_validate==false){//jezeli nie spelnia to nie sprawdzaj dalszych sprawdzianow i usun kandydata
                        for(unsigned int z=0;z<output.back()->groups.size(); z++){//wszystkie grupy
                            for(unsigned int a=0;a<output.back()->groups.at(z)->size(); a++){//usun wszystkie elementy z grupy
                                delete output.back()->groups.at(z)->at(a);
                            }
                            delete output.back()->groups.at(z);//usun wszystkie grupy
                        }
                        output.erase(output.end()-1);//usun kandydata
                        break;
                    }
                }


            }


        }

}

/*void StrippedFunGen(vector <Candidate*> Ck,int k, vector <Candidate*> &output, vector <int*> T, int N)
{
    for(unsigned int i=0;i<Ck.size();i++)
        for(unsigned int j=i+1;j<Ck.size();j++){
            bool ok_to_merge=true;
            //cout<<"Probuje laczyc "<<i<<" z "<<j<<endl;
            for(int l=0;l<k;l++){
                if(l==k-1){
                    if(Ck.at(i)->Cand_id.at(l)==Ck.at(j)->Cand_id.at(l)){
                        ok_to_merge=false;
                        //cout<<"takie same "<<Ck.at(i)->Cand_id.at(l)<<"\t"<<Ck.at(j)->Cand_id.at(l)<<endl;
                    }


                }
                else if(Ck.at(i)->Cand_id.at(l)!=Ck.at(j)->Cand_id.at(l)){
                        ok_to_merge=false;
                        //cout<<"inne"<<Ck.at(i)->Cand_id.at(l)<<"\t"<<Ck.at(j)->Cand_id.at(l)<<endl;
                        break;
                    }

                    /*if(Ck.at(i)->Cand_id.at(l)!=Ck.at(j)->Cand_id.at(l))
                        ok_to_merge=true;
                    else
                        ok_to_merge=false;
                }
                else{
                    if(Ck.at(i)->Cand_id.at(l)==Ck.at(j)->Cand_id.at(l))
                        ok_to_merge=true;
                    else{
                        ok_to_merge=false;
                        break;
                    }
                }

            }
            if(ok_to_merge){
                output.push_back(new Candidate);
                output.back()->Cand_id=Ck.at(i)->Cand_id;//dodaj id atrybutów z pierwszego dziecka
                output.back()->Cand_id.push_back(Ck.at(j)->Cand_id.at(k-1));// i ostatni id z drugiego dziecka
                    //for(unsigned int h=0;h<output.back()->Cand_id.size();h++)
                      //  cout<<output.back()->Cand_id.at(h);
                    //cout<<"\t";

                StrippedProduct(Ck.at(i)->groups,Ck.at(j)->groups,Ck.at(j)->GroupsNo, output.back()->groups, output.back()->GroupsNo,T,N);
                bool cand_validate=false;
                vector <int> cand_validator;
                for(unsigned int m=0;m<output.back()->Cand_id.size();m++){//petla do sprawdzania kandydata
                    cand_validator.clear();
                    for(unsigned int n=0;n<output.back()->Cand_id.size();n++){//petla do tworzenia sprawdzianow dla kandydata
                        if(n!=m)
                            cand_validator.push_back(output.back()->Cand_id.at(n));
                    }
                    for(unsigned int o=0;o<Ck.size();o++){//sprawdzenie czy sprawdzian spelnia warunki
                        if(cand_validator==Ck.at(o)->Cand_id){//sprawdz czy istnieje podzbior
                            cand_validate=true;
                            if(output.back()->GroupsNo==Ck.at(o)->GroupsNo)//sprawdz czy podzbior ma tyle samo grup
                                cand_validate=false;
                            break;
                        }
                    }
                    if(cand_validate==false){//jezeli nie spelnia to nie sprawdzaj dalszych sprawdzianow i usun kandydata
                        for(unsigned int z=0;z<output.back()->groups.size(); z++){//wszystkie grupy
                            for(unsigned int a=0;a<output.back()->groups.at(z)->size(); a++){//usun wszystkie elementy z grupy
                                delete output.back()->groups.at(z)->at(a);
                            }
                            delete output.back()->groups.at(z);//usun wszystkie grupy
                        }
                        output.erase(output.end()-1);//usun kandydata
                        break;
                    }
                }


            }


        }

}*/


void Basic_algorythm(vector <Candidate*> C1,int id_row, vector <Candidate*> &Rk)
{
    vector <int> T;
    T.resize(id_row);
    vector <int> delta;
    delta.resize(id_row);
    for(unsigned int z=0;z<C1.size(); z++)//dodaj GroupsNo
        C1.at(z)->GroupsNo=C1.at(z)->groups.size();
    PartitionArrayRepresentation(C1.back()->groups,delta);
    for(unsigned int z=0;z<C1.back()->groups.size(); z++){//atrybut ostatni(decyzja) wszystkie grupy -usuwanie
        for(unsigned int a=0;a<C1.back()->groups.at(z)->size(); a++){//wszystkie elementy z grupy
            delete C1.back()->groups.at(z)->at(a);
        }
        delete C1.back()->groups.at(z);
    }
    delete C1.back();
    C1.erase(C1.end()-1);
    vector <Candidate*> tmp;
    tmp=C1;

    for(int k=1;tmp.size()>0;k++){
        for(int z=0;z<tmp.size();z++)
            if(Holds(delta,tmp.at(z)->groups)){
                Rk.push_back(tmp.at(z));
                tmp.erase(tmp.begin()+z);
                z--;
            }
        vector <Candidate*> tmp2;
        FunGen(tmp,k,tmp2,T,id_row);
        tmp=tmp2;

    }


    cout<<"Liczba minimalnych zaleznosci funkcyjnych "<<Rk.size()<<endl;
    cout<<"Identyfikatory minimalnych zaleznosci funkcyjnych "<<endl;
    for(unsigned int i=0;i<Rk.size();i++){
        for(unsigned int j=0;j<Rk.at(i)->Cand_id.size();j++)
            cout<<Rk.at(i)->Cand_id.at(j);
        cout<<"\t";
    }
    cout<<endl<<"Koniec programu"<<endl;
}


void Stripped_algorythm(vector <Candidate*> C1,int id_row, vector <Candidate*> &Rk)
{
    vector <int> T;
    T.resize(id_row);
    vector <int> delta;
    delta.resize(id_row);
    for(unsigned int z=0;z<C1.size(); z++)//dodaj GroupsNo
        C1.at(z)->GroupsNo=C1.at(z)->groups.size();
    cout<<"bla"<<endl;
    for(unsigned int z=0;z<C1.size(); z++)//dla kazdego atrybutu
        for(unsigned int a=0;a<C1.at(z)->groups.size(); a++)//przystrzyz grupy
            if(C1.at(z)->groups.at(a)->size()==1)
            {
                delete C1.at(z)->groups.at(a)->at(0);
                delete C1.at(z)->groups.at(a);
                C1.at(z)->groups.erase(C1.at(z)->groups.begin()+a);
                a--;
            }

    cout<<"bla"<<endl;
    StrippedPartitionArrayRepresentation(C1.back()->groups,delta);
    if(StrippedHolds(delta,C1.back()->groups))
        cout<<"tak"<<endl;
    else
            cout<<"nie"<<endl;
    for(unsigned int z=0;z<C1.back()->groups.size(); z++){//atrybut ostatni(decyzja) wszystkie grupy -usuwanie
        for(unsigned int a=0;a<C1.back()->groups.at(z)->size(); a++){//wszystkie elementy z grupy
            delete C1.back()->groups.at(z)->at(a);
        }
        delete C1.back()->groups.at(z);
    }
    delete C1.back();
    if(StrippedHolds(delta,C1.at(5)->groups))
        cout<<"tak"<<endl;
    else
            cout<<"nie"<<endl;
    C1.erase(C1.end()-1);
    vector <Candidate*> tmp;
    tmp=C1;

    for(int k=1;tmp.size()>0;k++){
        for(int z=0;z<tmp.size();z++)
            if(StrippedHolds(delta,tmp.at(z)->groups)){
                Rk.push_back(tmp.at(z));
                tmp.erase(tmp.begin()+z);
                z--;
            }

        vector <Candidate*> tmp2;
        FunGen(tmp,k,tmp2,T,id_row);
        tmp=tmp2;

    }


    cout<<"Liczba minimalnych zaleznosci funkcyjnych "<<Rk.size()<<endl;
    cout<<"Identyfikatory minimalnych zaleznosci funkcyjnych "<<endl;
    for(unsigned int i=0;i<Rk.size();i++){
        for(unsigned int j=0;j<Rk.at(i)->Cand_id.size();j++)
            cout<<Rk.at(i)->Cand_id.at(j);
        cout<<"\t";
    }
    cout<<endl<<"Koniec programu"<<endl;
}


bool StrippedHolds(vector<int> T, vector<vector<int *> *> C)
{
    for(unsigned int i=0;i<C.size();i++){//petla obslugujaca kazda grupe z C
        int oid=*(C.at(i)->at(0));
        int firstGroup = T.at(oid);
        if(firstGroup==-1)
            return false;
        for(unsigned int k=1;k<C.at(i)->size();k++){//petla obslugujaca kazdy element z grupy z C
            oid=*(C.at(i)->at(k));
            int nextGroup = T.at(oid);
            if(firstGroup!=nextGroup)
            return false;
        }
    }
    return true;
}


void StrippedPartitionArrayRepresentation(vector<vector<int *> *> A, vector<int > &T)
{
    for(unsigned int i=0;i<T.size();i++)
        T.at(i)=-1;
    for(unsigned int i=0;i<A.size();i++)
        for(unsigned int j=0;j<A.at(i)->size();j++)
            T.at(*(A.at(i)->at(j)))=i;
}


void StrippedProduct(vector<vector<int *> *> A, vector<vector<int *> *> B, int BGroupNo, vector<vector<int *> *> &C, int &GNo, vector<int > T, int N)
{
    vector<vector<int> > S;
    C.clear();
    S.resize(N);
    int GroupsNo=BGroupNo;
    StrippedPartitionArrayRepresentation(A,T);
    set<int> AGroupIds;//set, bo groupsID moze sie powtarzac, a my nie chcemy
    for(unsigned int i=0;i<B.size();i++){//petla obslugujaca kazda grupe B
        AGroupIds.clear();
        int j;
        for(unsigned int k=0;k<B.at(i)->size();k++){//petla obslugujaca kazdy element z grupy z B
            j=T.at(*(B.at(i)->at(k))); // B.at(i).at(k) - oid
            if (j==-1)
                GroupsNo++;
            else{
                S.at(j).push_back(*(B.at(i)->at(k))); //S[j]
                AGroupIds.insert(j);
            }


        }
        set<int>::iterator it;
        for (it=AGroupIds.begin(); it!=AGroupIds.end(); ++it){
            C.push_back(new vector <int*> ());
            for(unsigned int x=0;x<S.at(*it).size(); x++){//insertowanie S[j] do C
                if(S.at(*it).size()>1)
                C.back()->push_back(new int (S.at(*it).at(x)));
            }
            GroupsNo++;



        }
        S.clear();
        S.resize(N);
        GroupsNo--;
    }
    GNo=GroupsNo;
}


/*void SuperFunGen(vector<int> T, vector<Candidate *> Ck)
{
    for(unsigned int i=0;i<Ck.size();i++)
        for(unsigned int j=i+1;j<Ck.size();j++){
            bool ok_to_merge=true;
            //cout<<"Probuje laczyc "<<i<<" z "<<j<<endl;
            for(int l=0;l<k;l++){
                if(l==k-1){
                    if(Ck.at(i)->Cand_id.at(l)==Ck.at(j)->Cand_id.at(l)){
                        ok_to_merge=false;
                        //cout<<"takie same "<<Ck.at(i)->Cand_id.at(l)<<"\t"<<Ck.at(j)->Cand_id.at(l)<<endl;
                    }


                }
                else if(Ck.at(i)->Cand_id.at(l)!=Ck.at(j)->Cand_id.at(l)){
                        ok_to_merge=false;
                        //cout<<"inne"<<Ck.at(i)->Cand_id.at(l)<<"\t"<<Ck.at(j)->Cand_id.at(l)<<endl;
                        break;
                    }

            }
            if(ok_to_merge){
                output.push_back(new Candidate);
                output.back()->Cand_id=Ck.at(i)->Cand_id;//dodaj id atrybutów z pierwszego dziecka
                output.back()->Cand_id.push_back(Ck.at(j)->Cand_id.at(k-1));// i ostatni id z drugiego dziecka
                    //for(unsigned int h=0;h<output.back()->Cand_id.size();h++)
                      //  cout<<output.back()->Cand_id.at(h);
                    //cout<<"\t";
                InitializeParenthood(Ck.at(i),Ck.at(j));
                Product(Ck.at(i)->groups,Ck.at(j)->groups, output.back()->groups, output.back()->GroupsNo,T,N);
                bool cand_validate=true;
                vector <int> cand_validator;
                for(unsigned int m=0;m<output.back()->Cand_id.size();m++){//petla do sprawdzania kandydata
                    cand_validator.clear();
                    for(unsigned int n=0;n<output.back()->Cand_id.size();n++){//petla do tworzenia sprawdzianow dla kandydata
                        if(n!=m)
                            cand_validator.push_back(output.back()->Cand_id.at(n));
                    }
                    for(unsigned int o=0;o<Ck.size();o++){//sprawdzenie czy sprawdzian spelnia warunki
                        if(cand_validator==Ck.at(o)->Cand_id){//sprawdz czy istnieje podzbior
                            cand_validate=true;
                            if(output.back()->GroupsNo==Ck.at(o)->GroupsNo)//sprawdz czy podzbior ma tyle samo grup
                                cand_validate=false;
                            break;
                        }
                    }
                    if(cand_validate==false){//jezeli nie spelnia to nie sprawdzaj dalszych sprawdzianow i usun kandydata
                        for(unsigned int z=0;z<output.back()->groups.size(); z++){//wszystkie grupy
                            for(unsigned int a=0;a<output.back()->groups.at(z)->size(); a++){//usun wszystkie elementy z grupy
                                delete output.back()->groups.at(z)->at(a);
                            }
                            delete output.back()->groups.at(z);//usun wszystkie grupy
                        }
                        output.erase(output.end()-1);//usun kandydata
                        break;
                    }
                }


            }


        }

}*/


void InitializeParenthood(Candidate *A,Candidate *B)
{

}


int read_from_modified_file(string filename, vector<Candidate *> &C1)
{
    ifstream infile(filename.c_str());
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
            //int *a=C1.at(column_number)->groups.at(0)->at(0);
            //cout<<*a<<"\t"<<a<<endl;
            column_number++;
          }
      }
      /*for(unsigned int z=0;z<dict.size(); z++){
          for(unsigned int a=0;a<dict.at(z).size(); a++){
              cout<<z<<"\t"<<dict.at(z).size()<<"\t"<<dict.at(z).at(a).word<<"\t";

          }
          cout<<endl;
      }*/



      while (infile)
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
                break;
            }

        }
        if(!is_in_dict){//dodaj do slownika, dodaj nowa grupe i jej element(id wiersza)
            int dict_id = dict.at(column_number).size();
            dict.at(column_number).push_back(dictionary(s,dict_id));
            C1.at(column_number)->groups.push_back(new vector <int*> ());
            C1.at(column_number)->groups.at(dict.at(column_number).at(dict_id).id)->push_back(new int (id_row));
        }


        column_number++;
      }


    }
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


void create_modified_file(string filename, int decision_column, int decision_type)
{
}


void save_to_outputfile(vector<Candidate *> Rk)
{
}
