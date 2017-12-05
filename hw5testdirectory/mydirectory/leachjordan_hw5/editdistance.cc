#include "editdistance.h"

/******************************************************************************
 *3456789 123456789 123456789 123456789 123456789 123456789 123456789 123456789
 * Class 'EditDistance' for the edit distance computation.
 *
 * Author: Duncan A. Buell
 * Edited by: Jordan Leach
 * Date last modified: 19 October 2016
**/

/******************************************************************************
 * Constructor
**/
EditDistance::EditDistance() {
}

/******************************************************************************
 * Destructor
**/
EditDistance::~EditDistance() {
}

/******************************************************************************
 * Accessors and Mutators
**/

/******************************************************************************
 * General functions.
**/
/******************************************************************************
 * Function 'GetMinimum'
 * This function establishes the minimum 
 * Here we take in a vector and compare a values current position to the
 * position at 'minimum'. If the value at 'i' is less than the value at
 * minimum then set to i. 
 * Returns:
 *  the integer value in the vector at the position at 'minimum'.
**/
int EditDistance::GetMinimum(vector<int> vect) {
  int minimum = 0;
  for (int i = 0; i < vect.size(); i++) {
    if (vect.at(i) < vect.at(minimum)) {
      minimum = i;
    }
  }
  return vect.at(minimum);
}

/******************************************************************************
 * Function 'ComputeDistances'.
 * This function computes the distances between the two sentences.
 * First a vector for the use of comparison is created. We push on the value
 * in front of, above, and up & to the left of our current position in the
 * matrix adding on the cost of insertion or substition. We then pass our 
 *comparision vector into GetMinimum. After the minimum is checked, clear the 
 * vector and run the loop again.  
**/
void EditDistance::ComputeDistances() {
  vector<int> compare_vector;
  // push on 3 values from the matrix
  for (int i = 1; i < length_; i++) {
    for (int j = 1; j < length_; j++) {
      compare_vector.push_back(dist_.at(i-1).at(j) + kCostInsertion);
      compare_vector.push_back(dist_.at(i).at(j-1) + kCostInsertion);
      if(sentence1_.at(j) == sentence2_.at(i)) {
        compare_vector.push_back(dist_.at(i-1).at(j-1));
      }
      else {
        compare_vector.push_back(dist_.at(i-1).at(j-1) + kCostSubstitution);
      }
    dist_.at(i).at(j) = GetMinimum(compare_vector);
    compare_vector.clear();
    }
  }
}

/******************************************************************************
 * Function 'Initialize'.
 * This function pushes a dummy strings onto each sentence vector. From there 
 * it pushes each word from an input file onto their respective sentences 
 * (sentence 1 or sentence 2). Once this is done there is a check to see if the
 * sentences are the same length. If they are not, the shorter sentence is
 * padded with dummy strings. Once they are equal, length_ is set to the size 
 * of the sentences. Then a vector of integers is created and we push on 
 * kDummyDistance. This vector is now pushed onto dist_, our vector of 
 * vectors to create the matrix. Then it initialize the distances of the first row
 * and column of the matrix. 
 * 
**/
void EditDistance::Initialize(Scanner& scanner) {
  // push on dummy strings
  
  sentence1_.push_back(kDummyString);
  sentence2_.push_back(kDummyString);

  ScanLine scanline;
  for (int i = 0; i < 2; i++) {
    scanline.OpenString(scanner.NextLine());
    if (i == 0) {
      while (scanline.HasNext()) {
        sentence1_.push_back(scanline.Next());
      }
    }
    if (i == 1) {
      while (scanline.HasNext()) {
        sentence2_.push_back(scanline.Next());
      }
    }
  }
  
  //make the sentence vectors the same size
  while (sentence1_.size() != sentence2_.size()) {
    if (sentence1_.size() > sentence2_.size()) {
      sentence2_.push_back(kDummyString);
    }
    else if (sentence2_.size() > sentence1_.size()) {
      sentence1_.push_back(kDummyString);
    }
  }
  
  // set length_ to the size of the sentences
  length_ = sentence1_.size();

  vector<int> the_vector;  
  for (int i = 0; i < length_; i++) { 
    the_vector.push_back(kDummyDistance);
    dist_.push_back(the_vector);
  }

  for(int i = 0; i < length_; i++) {
    for (int j = i; j < length_; j++) {
      dist_.at(i).push_back(kDummyDistance);
    }
  }
  // puts in the values for the first row and column
  if (sentence1_.at(0) == sentence2_.at(0)) {
    for (int i = 0; i < length_; i++) {
      for (int j = 0; j < length_; j++) {
        dist_.at(0).at(i) = i;
        dist_.at(i).at(0) = i;
      }
    }
  }
  else if (sentence1_.at(0) != sentence2_.at(0)){
    for (int i = 0; i < length_; i++) {
      for (int j =0 ; j < length_; j++) {
        dist_.at(0).at(i) = i + 2;
        dist_.at(i).at(0) = i + 2;
      }
    }  
  }
}

/******************************************************************************
 * Function 'ToString'.
 * Returns:
 *   a 'string' of the two sentences and the matrix with the edit distances
 * This method outputs the two sentences and then the formatted matrix.
**/
string EditDistance::ToString()
{
  string s = "";
  s += "Sentence 1"; 
  s +=  '\n';
  for (int i = 0; i < length_; i++) {
    s += sentence1_.at(i) + " " + "|";
  }
  s += '\n';
  s += "Sentence 2"; 
  s += '\n';
  for (int i = 0; i < length_; i++) {
    s += sentence2_.at(i)  + " " + "|";
  }

  s += '\n';
  s += '\n';

  s += "Distance Matrix: \n"; 
  s += Utils::Format(" ", 10, "right");
  for (int i = 0; i < length_; i++) {
    s += Utils::Format(sentence1_.at(i), 10, "right");
  }
  s += '\n';
  for (int i = 0; i < length_; i++) {
    s += Utils::Format(sentence2_.at(i), 10, "right");
    for (int j = 0; j < length_; j++) {
      s += Utils::Format(dist_.at(i).at(j), 10);
    }
    s += '\n';
  }
  
  
  return s;
}
