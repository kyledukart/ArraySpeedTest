// array speed test

#include <iostream>
#include <iomanip>
#include <chrono>
#include <vector>
#include <random>
#include <valarray>

using namespace std;

typedef chrono::high_resolution_clock Clock;

int number_of_elements = 10000000;
int output_width = floor(log10(number_of_elements) + 1);


int* theArray;
vector<int> theVector;
valarray<int> theValarray;

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

void testValarrayInitialize() {
  theValarray.resize(number_of_elements);
  for (unsigned int i = 0; i < number_of_elements; ++i)
    theValarray[i] = i;
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

int testValarraySequentialAccess() {
  int sum = 0;
  for (unsigned int i = 0; i < number_of_elements; ++i)
    sum += theValarray[i];
  return sum;
}

int testArrayRandomAccess() {
  random_device rd;  // seeds the rng
  mt19937 gen(rd()); // mersenne twister seeded with rd()
  uniform_int_distribution<> distrib(0,(number_of_elements - 1));  // range of output
  int sum = 0;
  for (unsigned int i = 0; i < number_of_elements; ++i)
    sum += theArray[distrib(gen)];
  return sum;
}

int testVectorRandomAccess() {
  random_device rd;  // seeds the rng
  mt19937 gen(rd()); // mersenne twister seeded with rd()
  uniform_int_distribution<> distrib(0,(number_of_elements - 1));  // range of output
  int sum = 0;
  for (unsigned int i = 0; i < number_of_elements; ++i)
    sum += theVector.at(distrib(gen));
  return sum;
}

int testValarrayRandomAccess() {
  random_device rd;  // seeds the rng
  mt19937 gen(rd()); // mersenne twister seeded with rd()
  uniform_int_distribution<> distrib(0,(number_of_elements - 1));  // range of output
  int sum = 0;
  for (unsigned int i = 0; i < number_of_elements; ++i)
    sum += theValarray[distrib(gen)];
  return sum;
}

int main() {
  //output formatting
  cout << fixed << setprecision(output_width) << std::left;

  //initialize
  auto clockStart = Clock::now();
  testArrayInitialize();
  auto clockEnd = Clock::now();
  cout << "Array initialization took \t" << setw(output_width)
    << chrono::duration_cast<chrono::microseconds>(clockEnd - clockStart).count() << "µs" << endl;

  clockStart = Clock::now();
  testVectorInitialize();
  clockEnd = Clock::now();
  cout << "Vector initialization took \t" << setw(output_width)
    << chrono::duration_cast<chrono::microseconds>(clockEnd - clockStart).count() << "µs" << endl;

  clockStart = Clock::now();
  testValarrayInitialize();
  clockEnd = Clock::now();
  cout << "Valarray initialization took \t" << setw(output_width)
    << chrono::duration_cast<chrono::microseconds>(clockEnd - clockStart).count() << "µs" << endl;

  // access and sum
  clockStart = Clock::now();
  int arraySequentialOutput = testArraySequentialAccess();
  clockEnd = Clock::now();
  cout << "Array access and sum took \t" << setw(output_width)
    << chrono::duration_cast<chrono::microseconds>(clockEnd - clockStart).count() << "µs" << endl;

  clockStart = Clock::now();
  int vectorSequentialOutput = testVectorSequentialAccess();
  clockEnd = Clock::now();
  cout << "Vector access and sum took \t" << setw(output_width)
    << chrono::duration_cast<chrono::microseconds>(clockEnd - clockStart).count() << "µs" << endl;

  clockStart = Clock::now();
  int valarraySequentialOutput = testValarraySequentialAccess();
  clockEnd = Clock::now();
  cout << "Valarray access and sum took \t" << setw(output_width)
    << chrono::duration_cast<chrono::microseconds>(clockEnd - clockStart).count() << "µs" << endl;

  // random access and sum
  clockStart = Clock::now();
  int arrayRandomOutput = testArrayRandomAccess();
  clockEnd = Clock::now();
  cout << "Array random access and sum took \t" << setw(output_width)
    << chrono::duration_cast<chrono::microseconds>(clockEnd - clockStart).count() << "µs" << endl;

  clockStart = Clock::now();
  int vectorRandomOutput = testVectorRandomAccess();
  clockEnd = Clock::now();
  cout << "Vector random access and sum took \t" << setw(output_width)
    << chrono::duration_cast<chrono::microseconds>(clockEnd - clockStart).count() << "µs" << endl;

  clockStart = Clock::now();
  int valarrayRandomOutput = testValarrayRandomAccess();
  clockEnd = Clock::now();
  cout << "Valarray random access and sum took \t" << setw(output_width)
    << chrono::duration_cast<chrono::microseconds>(clockEnd - clockStart).count() << "µs" << endl;

  cout << "total sum: " << (arraySequentialOutput + vectorSequentialOutput + valarraySequentialOutput +
  arrayRandomOutput + vectorRandomOutput + valarrayRandomOutput);
}