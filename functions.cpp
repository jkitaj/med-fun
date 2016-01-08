#include <functions.h>
#include <iostream>
/*int StrippedProduct(StrippedProductStorer A, StrippedProductStorer B, std::vector<int> C)
{
    std::list<std::list<int> > S; //lista list, kontener S
    //std::vector<int> S;
    int AGrId=0;
    int GroupNo=B.GroupNo;
    std::vector<int> T=A.array;
    int oid=0;
    int j;
    for (int oid=0;oid<B.size();oid++){
        j=T[oid];
        if(j==nullptr)
            GroupNo++;
        else
        {
            S[j]=oid;
            if(j>AGrId)
            AGrId++;
        }
    }
    for(j=1;j<=AGrId;j++){
        if(S[j]>1)//tablica list


    }

}*/

void Product(ProductStorer A, ProductStorer B, ProductStorer &C)
{
    //std::list<std::list<int> > S; //lista list, kontener S
    //std::multimap<int,int>S;
    std::vector<std::vector<int> > S;
    S.resize(A.GroupNo);
    //S.resize(N);
    C.T.clear();
    C.T.resize(A.T.size());
    int GroupsNo=0;
    std::vector<std::vector<int> > GroupsB;
    std::vector<int> T=A.T;
    //int BGroupNo=0;
    GroupsB.resize(B.GroupNo);
    //GroupsB.push_back(std::vector<int>());
    //stworzenie grup B
    for(unsigned int i=0;i<B.T.size();i++){
        /*if(B[i]>BGroupNo){
            BGroupNo++;
            GroupsB.push_back(std::vector<int>());//vector na nowe grupy
            }*/
        GroupsB.at(B.T.at(i)).push_back(i);
    }
    std::set<int> AGroupIds;//set, bo groupsID moze sie powtarzac, a my nie chcemy
    std::cout<<"krok1"<<std::endl;
    for(unsigned int i=0;i<GroupsB.size();i++){//petla obslugujaca kazda grupe B
        AGroupIds.clear();
        int j;
        for(unsigned int k=0;k<GroupsB.at(i).size();k++){//petla obslugujaca kazdy element z grupy z B
            j=T.at(GroupsB.at(i).at(k)); // GroupsB.at(i).at(k) - oid
            S.at(j).push_back(GroupsB.at(i).at(k)); //S[j]
            AGroupIds.insert(j);
        }
        std::cout<<"krok2"<<std::endl;
        std::cout<<GroupsB.size()<<std::endl;
        //for(unsigned int z=0;z<AGroupIds.size(); z++){
        std::set<int>::iterator it;
        for (it=AGroupIds.begin(); it!=AGroupIds.end(); ++it){
            std::cout<<"krok3 S.at(z)="<<S.at(*it).at(0)<<std::endl;
            for(unsigned int x=0;x<S.at(*it).size(); x++){//insertowanie S[j] do C
                //std::cout<<"krok4a"<<std::endl;
                C.T.at(S.at(*it).at(x))=GroupsNo;
                std::cout<<"krok4b"<<std::endl;
            }
            std::cout<<"krok5"<<std::endl;
            GroupsNo++;



        }
        std::cout<<"krok6"<<std::endl;
        S.clear();
        S.resize(N);
    }
    std::cout<<"krok7"<<std::endl;
    C.GroupNo=GroupsNo;
    return;
}




