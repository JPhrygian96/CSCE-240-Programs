/****************************************************************
 * Header file for the application class for the edit distance
 * program.
 *
 * Author/copyright:  Duncan Buell
 * Edited by: Jordan Leach
 * Date: 20 October 2016
 *
**/

#ifndef EDITDISTANCE_H
#define EDITDISTANCE_H

#include <iostream>
#include <vector>
using namespace std;

#include "../../Utilities/scanner.h"
#include "../../Utilities/scanline.h"

class EditDistance {
public:
 EditDistance();
 virtual ~EditDistance();

 int GetMinimum(vector<int> vect); 
 void ComputeDistances();
 void Initialize(Scanner& scanner);
 string ToString();

private:
 const int kCostDeletion = 1;
 const int kCostInsertion = 1;
 const int kCostSubstitution = 2;
 const int kDummyDistance = -1;
 const string kDummyString = "XX";

 // we will pad the shorter string to get a common 'length_'
 int length_;

 // note the space in '> >' because the compiler needs it
 vector<vector<int> > dist_;

 vector<string> sentence1_;
 vector<string> sentence2_;
};

#endif
