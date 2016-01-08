#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#endif // FUNCTIONS_H
#include <vector>
#include <list>
#include <map>
#include <set>
//#include <utility>
const int N=10;
//int T[N],S[N];

int StrippedProduct(std::vector<int> A, std::vector<int> B, int *C);

struct ProductStorer{
    std::vector<int> T;
    int GroupNo;
};
void Product(ProductStorer A, ProductStorer B, ProductStorer &C);
/*struct ProductStorer{
    static int a[n];
    int GroupNo;
};*/
