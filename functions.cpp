#include "functions.h"
void PartitionArrayRepresentation(vector <vector <int*>* > A,vector <int> &T){

    for(unsigned int i=0;i<A.size();i++)
        for(unsigned int j=0;j<A.at(i)->size();j++)
            T.at(*(A.at(i)->at(j)))=i;


}
void Product(vector <vector <int*>* > A, vector <vector <int*>* > B, vector <vector <int*>* > &C, int &GNo,vector <int> T,int N)
{
    vector<vector<int> > S;
    C.clear();
    S.resize(N);
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
                C.back()->push_back(new int (S.at(*it).at(x)));
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
            for(int l=0;l<k;l++){
                if(l==k-1){
                    if(Ck.at(i)->Cand_id.at(l)==Ck.at(j)->Cand_id.at(l)){
                        ok_to_merge=false;
                    }


                }
                else if(Ck.at(i)->Cand_id.at(l)!=Ck.at(j)->Cand_id.at(l)){
                        ok_to_merge=false;
                        break;
                    }



            }
            if(ok_to_merge){
                output.push_back(new Candidate);
                output.back()->Cand_id=Ck.at(i)->Cand_id;//dodaj id atrybutów z pierwszego dziecka
                output.back()->Cand_id.push_back(Ck.at(j)->Cand_id.at(k-1));// i ostatni id z drugiego dziecka

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

void StrippedFunGen(vector <Candidate*> Ck,int k, vector <Candidate*> &output, vector <int> T, int N)
{
    for(unsigned int i=0;i<Ck.size();i++)
        for(unsigned int j=i+1;j<Ck.size();j++){
            bool ok_to_merge=true;
            for(int l=0;l<k;l++){
                if(l==k-1){
                    if(Ck.at(i)->Cand_id.at(l)==Ck.at(j)->Cand_id.at(l)){
                        ok_to_merge=false;
                    }


                }
                else if(Ck.at(i)->Cand_id.at(l)!=Ck.at(j)->Cand_id.at(l)){
                        ok_to_merge=false;
                        break;
                    }



            }
            if(ok_to_merge){
                output.push_back(new Candidate);
                output.back()->Cand_id=Ck.at(i)->Cand_id;//dodaj id atrybutów z pierwszego dziecka
                output.back()->Cand_id.push_back(Ck.at(j)->Cand_id.at(k-1));// i ostatni id z drugiego dziecka
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

}



void Basic_algorythm(vector <Candidate*> C1,int id_row, vector <Candidate*> &Rk, int d_column)
{
    vector <int> T;
    T.resize(id_row);
    vector <int> delta;
    delta.resize(id_row);
    cout<<C1.size()<<endl;
    for(unsigned int z=0;z<C1.size(); z++)//dodaj GroupsNo
        C1.at(z)->GroupsNo=C1.at(z)->groups.size();
    PartitionArrayRepresentation(C1.at(d_column-1)->groups,delta);
    for(unsigned int z=0;z<C1.at(d_column-1)->groups.size(); z++){//atrybut ostatni(decyzja) wszystkie grupy -usuwanie
        for(unsigned int a=0;a<C1.at(d_column-1)->groups.at(z)->size(); a++){//wszystkie elementy z grupy
            delete C1.at(d_column-1)->groups.at(z)->at(a);
        }
        delete C1.at(d_column-1)->groups.at(z);
    }
    delete C1.at(d_column-1);
    C1.erase(C1.begin()+d_column-1);
    vector <Candidate*> tmp;
    tmp=C1;
    for(int k=1;tmp.size()>0;k++){
        cout<<"Weryfikacja kandydatow o dlugosci: "<<k<<endl;
        for(int z=0;z<tmp.size();z++)
            if(Holds(delta,tmp.at(z)->groups)){
                Rk.push_back(tmp.at(z));
                tmp.erase(tmp.begin()+z);
                z--;
            }
        cout<<"Generowanie kandydatow o dlugosci: "<<k+1<<endl;
        vector <Candidate*> tmp2;
        FunGen(tmp,k,tmp2,T,id_row);
        tmp=tmp2;

    }

    cout<<"Liczba minimalnych zaleznosci funkcyjnych "<<Rk.size()<<endl;
    cout<<"Identyfikatory minimalnych zaleznosci funkcyjnych "<<endl;
    for(unsigned int i=0;i<Rk.size();i++){
        for(unsigned int j=0;j<Rk.at(i)->Cand_id.size();j++){
            cout<<Rk.at(i)->Cand_id.at(j)<<" ";
        }
        cout<<"\t";
    }
    cout<<endl<<"Koniec programu"<<endl;
}


void Stripped_algorythm(vector <Candidate*> C1,int id_row, vector <Candidate*> &Rk, int d_column)
{
    vector <int> T;
    T.resize(id_row);
    vector <int> delta;
    delta.resize(id_row);
    for(unsigned int z=0;z<C1.size(); z++)//dodaj GroupsNo
        C1.at(z)->GroupsNo=C1.at(z)->groups.size();
    for(unsigned int z=0;z<C1.size(); z++)//dla kazdego atrybutu
        for(int a=0;a<C1.at(z)->groups.size(); a++)//przystrzyz grupy
            if(C1.at(z)->groups.at(a)->size()==1)
            {
                delete C1.at(z)->groups.at(a)->at(0);
                delete C1.at(z)->groups.at(a);
                C1.at(z)->groups.erase(C1.at(z)->groups.begin()+a);
                a--;
            }

    StrippedPartitionArrayRepresentation(C1.at(d_column-1)->groups,delta);
    for(unsigned int z=0;z<C1.at(d_column-1)->groups.size(); z++){//atrybut ostatni(decyzja) wszystkie grupy -usuwanie
        for(unsigned int a=0;a<C1.at(d_column-1)->groups.at(z)->size(); a++){//wszystkie elementy z grupy
            delete C1.at(d_column-1)->groups.at(z)->at(a);
        }
        delete C1.at(d_column-1)->groups.at(z);
    }
    delete C1.at(d_column-1);
    C1.erase(C1.begin()+d_column-1);
    vector <Candidate*> tmp;
    tmp=C1;

    for(int k=1;tmp.size()>0;k++){
        cout<<"Weryfikacja kandydatow o dlugosci: "<<k<<endl;
        for(int z=0;z<tmp.size();z++)
            if(StrippedHolds(delta,tmp.at(z)->groups)){
                Rk.push_back(tmp.at(z));
                tmp.erase(tmp.begin()+z);
                z--;
            }
        cout<<"Generowanie kandydatow o dlugosci: "<<k+1<<endl;
        vector <Candidate*> tmp2;
        StrippedFunGen(tmp,k,tmp2,T,id_row);
        tmp=tmp2;

    }

    cout<<"Liczba minimalnych zaleznosci funkcyjnych "<<Rk.size()<<endl;
    cout<<"Identyfikatory minimalnych zaleznosci funkcyjnych "<<endl;
    for(unsigned int i=0;i<Rk.size();i++){
        for(unsigned int j=0;j<Rk.at(i)->Cand_id.size();j++){
            cout<<Rk.at(i)->Cand_id.at(j)<<" ";
        }
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
            if(S.at(*it).size()>1){//utworz grupy tylko niesingletonowe
                C.push_back(new vector <int*> ());
                for(unsigned int x=0;x<S.at(*it).size(); x++)//insertowanie S[j] do C
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


void SuperFunGen(vector <int> delta, vector <Candidate*> Ck,int k, vector <Candidate*> &output, vector <int> T, int N)
{
    for(unsigned int i=0;i<Ck.size();i++)
        for(unsigned int j=i+1;j<Ck.size();j++){
            bool ok_to_merge=true;
            for(int l=0;l<k;l++){
                if(l==k-1){
                    if(Ck.at(i)->Cand_id.at(l)==Ck.at(j)->Cand_id.at(l)){
                        ok_to_merge=false;
                    }


                }
                else if(Ck.at(i)->Cand_id.at(l)!=Ck.at(j)->Cand_id.at(l)){
                        ok_to_merge=false;
                        break;
                    }

            }
            if(ok_to_merge){
                vector <int> C=Ck.at(i)->Cand_id;
                C.push_back(Ck.at(j)->Cand_id.at(k-1));
                Candidate *X,*Y;
                InitializeParenthood(Ck.at(i),Ck.at(j),X,Y,k);

                bool cand_validate=true;
                vector <int> cand_validator;
                Candidate *E;
                for(unsigned int m=0;m<C.size();m++){//petla do sprawdzania kandydata
                    cand_validator.clear();
                    for(unsigned int n=0;n<C.size();n++){//petla do tworzenia sprawdzianow dla kandydata
                        if(n!=m)
                            cand_validator.push_back(C.at(n));//utworz id sprawdzianu
                    }
                    if((cand_validator==Ck.at(i)->Cand_id)||(cand_validator==Ck.at(j)->Cand_id))//jezeli jest równy ktoremus ojcu
                        continue;//to przejdz do nastepnego sprawdzianu, m++

                    for(unsigned int o=0;o<Ck.size();o++){//sprawdzenie czy sprawdzian spelnia warunki
                        cand_validate=false;
                        if(cand_validator==Ck.at(o)->Cand_id){//sprawdz czy istnieje podzbior
                            cand_validate=true;
                            E=Ck.at(o);
                            break;
                        }
                    }
                    if(cand_validate==false)
                        break;
                    else
                        UpdateParenthood(E,X,Y,k);
                }
                if(cand_validate){
                    Candidate *Cand=new Candidate;
                    DecisionProduct(delta,X->groups,Y->groups,Cand,T,N);
                    Cand->Cand_id=C;
                    if((Cand->RecordsNo!=X->RecordsNo)||(Cand->GroupsNo!=X->RecordsNo)){
                        output.push_back(Cand);
                    }
                    else
                        delete Cand;


                }



            }


        }

}


void InitializeParenthood(Candidate *A,Candidate *B,Candidate *&X, Candidate *&Y,int k)
{
    if(k==1){
        A->RecordsNo=CountRecords(A);
        B->RecordsNo=CountRecords(B);
    }
    if((A->RecordsNo<B->RecordsNo)||((A->RecordsNo==B->RecordsNo)&&(A->GroupsNo>B->GroupsNo))){
        X=A;
        Y=B;
    }
    else{
        X=B;
        Y=A;
    }
}

int CountRecords(Candidate *C)
{
    int records=0;
    for(unsigned int z=0;z<C->groups.size(); z++)//wszystkie grupy
        for(unsigned int a=0;a<C->groups.at(z)->size(); a++)//wszystkie elementy z grupy
            records++;
    return records;
}


void UpdateParenthood(Candidate *E, Candidate *&X, Candidate *&Y,int k)
{
    if(k==1)
        E->RecordsNo=CountRecords(E);
    if(X->RecordsNo<Y->RecordsNo){
        if(E->RecordsNo<X->RecordsNo){
            Y=X;
            X=E;
        }
        else if(E->RecordsNo==X->RecordsNo){
            if(E->GroupsNo>X->GroupsNo){
                Y=X;
                X=E;
            }
            else
                Y=E;
        }
        else if(E->RecordsNo<Y->RecordsNo)
            Y=E;
        else if(E->RecordsNo==Y->RecordsNo){
            if(E->GroupsNo>Y->GroupsNo){
                Y=E;
            }
        }

    }
    else if(E->RecordsNo<X->RecordsNo)
        X=E;
    else if(E->RecordsNo==X->RecordsNo){
        if(E->GroupsNo>X->GroupsNo){
            X=E;
        }
        else if(E->GroupsNo>Y->GroupsNo)
            Y=E;
    }


}


void DecisionProduct(vector <int> delta,vector <vector <int*>* > A, vector <vector <int*>* > B, Candidate *&C,vector <int> T,int N)
{
    vector<vector<int> > S;
    C->groups.clear();
    C->GroupsNo=0;
    C->RecordsNo;
    S.resize(N);
    StrippedPartitionArrayRepresentation(B,T);
    set<int> BGroupIds;//set, bo groupsID moze sie powtarzac, a my nie chcemy
    for(unsigned int i=0;i<A.size();i++){//petla obslugujaca kazda grupe A
        BGroupIds.clear();
        int j;
        for(unsigned int k=0;k<A.at(i)->size();k++){//petla obslugujaca kazdy element z grupy z A
            j=T.at(*(A.at(i)->at(k))); // A.at(i).at(k) - oid
            if(j!=-1){
                S.at(j).push_back(*(A.at(i)->at(k))); //S[j]
                BGroupIds.insert(j);
            }
        }
        set<int>::iterator it;
        for (it=BGroupIds.begin(); it!=BGroupIds.end(); ++it){
            if(IsGroupContainedInAnyDecisionClass(S.at(*it),delta)==false){
                C->groups.push_back(new vector <int*> ());
                for(unsigned int x=0;x<S.at(*it).size(); x++){//insertowanie S[j] do C
                    C->groups.back()->push_back(new int (S.at(*it).at(x)));
                    C->RecordsNo++;
                }
                C->GroupsNo++;
            }



        }
        S.clear();
        S.resize(N);
    }
}


void Super_Fun_algorythm(vector<Candidate *> C1, int id_row, vector<Candidate *> &Rk, int d_column)
{
    vector <int> T;
    T.resize(id_row);
    vector <int> delta;
    delta.resize(id_row);
    for(unsigned int z=0;z<C1.size(); z++)//dodaj GroupsNo
        C1.at(z)->GroupsNo=C1.at(z)->groups.size();
    for(unsigned int z=0;z<C1.size(); z++)//dla kazdego atrybutu
        for(int a=0;a<C1.at(z)->groups.size(); a++)//przystrzyz grupy
            if(C1.at(z)->groups.at(a)->size()==1)
            {
                delete C1.at(z)->groups.at(a)->at(0);
                delete C1.at(z)->groups.at(a);
                C1.at(z)->groups.erase(C1.at(z)->groups.begin()+a);
                a--;
            }

    StrippedPartitionArrayRepresentation(C1.at(d_column-1)->groups,delta);

    for(unsigned int z=0;z<C1.at(d_column-1)->groups.size(); z++){//atrybut ostatni(decyzja) wszystkie grupy -usuwanie
        for(unsigned int a=0;a<C1.at(d_column-1)->groups.at(z)->size(); a++){//wszystkie elementy z grupy
            delete C1.at(d_column-1)->groups.at(z)->at(a);
        }
        delete C1.at(d_column-1)->groups.at(z);
    }
    delete C1.at(d_column-1);
    C1.erase(C1.begin()+d_column-1);
    vector <Candidate*> tmp;
    tmp=C1;

    for(int k=1;tmp.size()>0;k++){
        cout<<"Weryfikacja kandydatow o dlugosci: "<<k<<endl;
        if(k==1){
            for(int z=0;z<tmp.size();z++)
                if(StrippedHolds(delta,tmp.at(z)->groups)){
                    Rk.push_back(tmp.at(z));
                    tmp.erase(tmp.begin()+z);
                    z--;
                }
        }
        else{
            for(int z=0;z<tmp.size();z++)
                if(SuperHolds(tmp.at(z)->groups)){
                    Rk.push_back(tmp.at(z));
                    tmp.erase(tmp.begin()+z);
                    z--;
                }
        }

        cout<<"Generowanie kandydatow o dlugosci: "<<k+1<<endl;
        vector <Candidate*> tmp2;
        SuperFunGen(delta,tmp,k,tmp2,T,id_row);
        tmp=tmp2;

    }

    cout<<"Liczba minimalnych zaleznosci funkcyjnych "<<Rk.size()<<endl;
    cout<<"Identyfikatory minimalnych zaleznosci funkcyjnych "<<endl;
    for(unsigned int i=0;i<Rk.size();i++){
        for(unsigned int j=0;j<Rk.at(i)->Cand_id.size();j++){
            cout<<Rk.at(i)->Cand_id.at(j)<<" ";
        }
        cout<<"\t";
    }
    cout<<endl<<"Koniec programu"<<endl;
}


bool IsGroupContainedInAnyDecisionClass(vector<int> S, vector<int> delta)
{
    if(S.size()>1){
        int oid=S.at(0);
        int firstGroup = delta.at(oid);
        if(firstGroup==-1)
            return false;
        for(unsigned int k=1;k<S.size();k++){//petla obslugujaca kazdy element z grupy z S
            oid=S.at(k);
            int nextGroup = delta.at(oid);
            if(firstGroup!=nextGroup)
                return false;
        }
    }

    return true;
}


bool SuperHolds(vector<vector<int *> *> C)
{
    if(C.size()==0)
        return true;
    return false;
}






