// array speed test

#include <iostream>
#include <iomanip>
#include <chrono>
#include <vector>

using namespace std;

typedef chrono::high_resolution_clock Clock;

int number_of_elements = 10000000;



int* theArray;
vector<int> theVector;

int main() {
  //output formatting
  cout << fixed << setprecision(floor(log10(number_of_elements) + 1)) << std::left;

  //initialize
  auto clockStart = Clock::now();
  testArrayInitialize();
  auto clockEnd = Clock::now();
  cout << "Array initialization took "
    << chrono::duration_cast<chrono::microseconds>(clockEnd - clockStart).count() << "µs" << endl;

  clockStart = Clock::now();
  testVectorInitialize();
  clockEnd = Clock::now();
  cout << "Vector initialization took "
    << chrono::duration_cast<chrono::microseconds>(clockEnd - clockStart).count() << "µs" << endl;

  // access and sum
  auto clockStart = Clock::now();
  int arraySequentialOutput = testArraySequentialAccess();
  auto clockEnd = Clock::now();
  cout << "Array access and sum took "
    << chrono::duration_cast<chrono::microseconds>(clockEnd - clockStart).count() << "µs" << endl;

  auto clockStart = Clock::now();
  int vectorSequentialOutput = testVectorSequentialAccess();
  auto clockEnd = Clock::now();
  cout << "Vector access and sum took "
    << chrono::duration_cast<chrono::microseconds>(clockEnd - clockStart).count() << "µs" << endl;

}

void testArrayInitialize() {
  theArray = new int[number_of_elements];
  for (unsigned int i = 0; i < number_of_elements; ++i)
    theArray[i] = i;
}

void testVectorInitialize() {
  theVector.reserve(number_of_elements);
  for (unsigned int i = 0; i < number_of_elements; ++i)
    theVector.push_back(i);
}

int testArraySequentialAccess() {
  int sum = 0;
  for (unsigned int i = 0; i < number_of_elements; ++i)
    sum += theArray[i];
  return sum;
}

int testVectorSequentialAccess(){
  int sum = 0;
  for (unsigned int i = 0; i < number_of_elements; ++i)
    sum += theVector.at(i);
  return sum;
}
