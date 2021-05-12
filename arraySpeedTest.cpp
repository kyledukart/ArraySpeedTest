// array speed test

#include <iostream>
#include <chrono>
#include <vector>

using namespace std;

typedef chrono::high_resolution_clock Clock;

int number_of_elements = 100000;

int* theArray;
vector<int> theVector;

int main() {

  //initialize
  auto arrayStart = Clock::now();
  testArrayInitialize();
  auto arrayEnd = Clock::now();
  cout << "Array initialization took "
    << chrono::duration_cast<std::chrono::microseconds>(arrayEnd - arrayStart).count() << "µs";

  auto vectorStart = Clock::now();
  testVectorInitialize();
  auto vectorEnd = Clock::now();
  cout << "Array initialization took "
    << chrono::duration_cast<std::chrono::microseconds>(arrayEnd - arrayStart).count() << "µs";

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

