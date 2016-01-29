//
// Created by Jakub Kitaj
//

#ifndef MED_PROJEKT_FILEUTILS_H
#define MED_PROJEKT_FILEUTILS_H

#include <vector>
#include <string>
#include "functions.h"

void create_modified_file(string filename, int decision_column, int decision_type);
int read_from_modified_file(string filename, vector <Candidate*> &C1, int number_of_transactions);
void save_to_outputfile(vector <Candidate*> Rk);
void prepare_output_file(ofstream *outputFile);
void write_time_to_file(ofstream *outputFile, string str, double time);

#endif //MED_PROJEKT_FILEUTILS_H
