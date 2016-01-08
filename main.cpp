
#include <iostream>
#include "functions.h"

using namespace std;
int main(int argc, char *argv[])
{

    ProductStorer v1,v2,v3;
    int tmp[]= {0,0,1,1,1,0,0,0,0,0};
    v1.T= std::vector<int>(tmp,tmp+10);
    //v1.T={0,0,1,1,1,0,0,0,0,0};
    v1.GroupNo=2;
    int tmp2[]= {0,1,1,1,1,0,0,0,0,0};
    v2.T= std::vector<int>(tmp2,tmp2+10);
    //v2.T={0,1,1,1,1,0,0,0,0,0};
    v2.GroupNo=2;
    Product(v1,v2,v3);
    for(unsigned int z=0;z<v3.T.size(); z++){
        cout<<v3.T.at(z)<<"\t";
    }
    return 0;
}
