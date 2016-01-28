#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#endif // FUNCTIONS_H
#include <vector>
#include <list>
#include <map>
#include <set>
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
//#include <utility>
//const int N=10;
//int T[N],S[N];
using namespace std;
struct dictionary{
    string word;
    int id;
    dictionary(string a, int b){
        word=a;
        id=b;
    }
};

//int StrippedProduct(std::vector<int> A, std::vector<int> B, int *C);
struct Candidate{//pi
    vector <vector <int*>* > groups;
    int GroupsNo;//ile roznych grup
    vector <int> Cand_id;//id kandydata, wektor z id atrybutow
};
void create_modified_file(string filename, int decision_column, int decision_type);
int read_from_modified_file(string filename, vector <Candidate*> &C1, int number_of_transactions);
void save_to_outputfile(vector <Candidate*> Rk,int a_type, int number_of_transactions, double dif1, double dif2, string input_file);
bool Holds(vector<int> T,vector <vector <int*>* > C);
bool StrippedHolds(vector<int> T,vector <vector <int*>* > C);
void StrippedPartitionArrayRepresentation(vector <vector <int*>* > A, vector <int> &T);
void PartitionArrayRepresentation(vector <vector <int*>* > A, vector <int> &T);
void Product(vector <vector <int*>* > A, vector <vector <int*>* > B,  vector <vector <int*>* > &C, int &GNo, vector <int> T,int N);
void StrippedProduct(vector <vector <int*>* > A, vector <vector <int*>* > B, int BGroupNo, vector <vector <int*>* > &C, int &GNo, vector <int> T,int N);
void StrippedFunGen(vector <Candidate*> Ck,int k, vector <Candidate*> &output, vector <int> T, int N);
void FunGen(vector <Candidate*> Ck,int k, vector <Candidate*> &output, vector <int> T, int N);
void SuperFunGen(vector<int> T, vector <Candidate*> Ck);
void InitializeParenthood(Candidate *A,Candidate *B);
void Basic_algorythm(vector <Candidate*> C1,int id_row, vector <Candidate*> &Rk, int d_column);
void Stripped_algorythm(vector <Candidate*> C1,int id_row, vector <Candidate*> &Rk,int d_column);
void Super_Fun_algorythm(vector <Candidate*> C1,int id_row, vector <Candidate*> &Rk,int d_column);
//void Product(ProductStorer A, ProductStorer B, ProductStorer &C);
/*struct ProductStorer{
    static int a[n];
    int GroupNo;
};*/
