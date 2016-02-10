#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <vector>
#include <list>
#include <map>
#include <set>
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>

using namespace std;
struct dictionary{
    string word;
    int id;
    dictionary(string a, int b){
        word=a;
        id=b;
    }
};

struct Candidate{//pi
    vector <vector <int*>* > groups;
    int GroupsNo;//ile roznych grup
    int RecordsNo;
    vector <int> Cand_id;//id kandydata, wektor z id atrybutow
};

bool Holds(vector<int> T,vector <vector <int*>* > C);
bool StrippedHolds(vector<int> T,vector <vector <int*>* > C);
bool SuperHolds(vector <vector <int*>* > C);
void StrippedPartitionArrayRepresentation(vector <vector <int*>* > A, vector <int> &T);
void PartitionArrayRepresentation(vector <vector <int*>* > A, vector <int> &T);
void Product(vector <vector <int*>* > A, vector <vector <int*>* > B,  vector <vector <int*>* > &C, int &GNo, vector <int> T,int N);
void StrippedProduct(vector <vector <int*>* > A, vector <vector <int*>* > B, int BGroupNo, vector <vector <int*>* > &C, int &GNo, vector <int> T,int N);
void StrippedFunGen(vector <Candidate*> Ck,int k, vector <Candidate*> &output, vector <int> T, int N);
void FunGen(vector <Candidate*> Ck,int k, vector <Candidate*> &output, vector <int> T, int N);
void SuperFunGen(vector <int> delta,vector <Candidate*> Ck,int k, vector <Candidate*> &output, vector <int> T, int N);
void InitializeParenthood(Candidate *A,Candidate *B, Candidate *&X, Candidate *&Y,int k);
void UpdateParenthood(Candidate *E, Candidate *&X, Candidate *&Y,int k);
void DecisionProduct(vector <int> delta,vector <vector <int*>* > A, vector <vector <int*>* > B, Candidate *&C,vector <int> T,int N);
bool IsGroupContainedInAnyDecisionClass(vector<int>  S, vector <int> delta);
void Basic_algorythm(vector <Candidate*> C1,int id_row, vector <Candidate*> &Rk, int d_column);
void Stripped_algorythm(vector <Candidate*> C1,int id_row, vector <Candidate*> &Rk,int d_column);
void Super_Fun_algorythmAB(vector <Candidate*> C1,int id_row, vector <Candidate*> &Rk,int d_column);
void Super_Fun_algorythmBA(vector <Candidate*> C1,int id_row, vector <Candidate*> &Rk,int d_column);
int CountRecords(Candidate *C);


#endif // FUNCTIONS_H