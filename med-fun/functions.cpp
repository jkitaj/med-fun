#include <functions.h>
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

int Product(ProductStorer A, ProductStorer B, std::vector<int> &C)
{
    //std::list<std::list<int> > S; //lista list, kontener S
    //std::multimap<int,int>S;
    std::vector<std::vector<int> > S;
    S.resize(A.GroupNo);
    C.clear();
    int GroupsNo=0;
    std::vector<std::vector<int> > GroupsB;
    std::vector<int> T=A.T;
    //int BGroupNo=0;
    GroupsB.resize(B.GroupNo);
    //GroupsB.push_back(std::vector<int>());
    //stworzenie grup B
    for(unsigned int i=0;i<B.size();i++){
        /*if(B[i]>BGroupNo){
            BGroupNo++;
            GroupsB.push_back(std::vector<int>());//vector na nowe grupy
            }*/
        GroupsB.at(B[i]).push_back(i);
    }
    std::list<int> AGroupIds;
    for(unsigned int i=0;i<GroupsB.size();i++){//petla obslugujaca kazda grupe B
        AGroupIds.clear();
        int j;
        for(unsigned int k=0;i<GroupsB.at(i).size();k++){//petla obslugujaca kazdy element z grupy z B
            j=T.at(GroupsB.at(i).at(k));
            //S.insert(std::pair<int,int>(j,GroupsB.at(i).at(k))); //S[j]
            S.at(j).push_back(GroupsB.at(i).at(k));
            AGroupIds.push_back(j);
        }
        for(std::list<int>::iterator it=AGroupIds.begin();it != AGroupIds.end(); it++){





        }
    }
}




