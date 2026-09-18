// Madison Nichols
// Program #1 - 1D Game of Life: Fun with Bits
// CMPS 2433 Discrete Structures and Analysis, Fall 2026
//
// Reads N and N short integers from an input file, then repeatedly
// computes new "generations" of the sequence using only bitwise
// operators, printing the array and its sum after every generation.

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

//name: openFiles
//purpose: reads and opens files
//receives: ifstream infile, and ofstream outfile
//returns: nothing, void
void openFiles(ifstream& in, ofstream& out);

//name: isEven
//purpose: takes value num and checks if value is even using bitwise
//         operators (checks whether bit 0 is 0)
//receives: an int, num, the value
//returns: bool, true if num is even
bool isEven(int num);

//name: isOdd
//purpose: takes value num and checks if value is odd using bitwise
//         operators (checks whether bit 0 is 1)
//receives: an int, num, the value
//returns: bool, true if num is odd
bool isOdd(int num);

//name: readData
//purpose: reads the count N and then N integers from infile into arr
//receives: ifstream infile, int array arr, int& n (filled in by this function)
//returns: nothing, void
void readData(ifstream& infile, int arr[], int& n);

//name: computeSum
//purpose: adds up all N elements currently stored in arr
//receives: int array arr, int n (number of elements)
//returns: int, the sum of the elements
int computeSum(const int arr[], int n);

//name: printHeader
//purpose: prints the student's name and the assignment label as the
//         first lines of the output
//receives: ostream& out, string name (the student's name)
//returns: nothing, void
void printHeader(ostream& out, const string& name);

//name: printGeneration
//purpose: prints "Generation <genNum>: " followed by the array
//         contents and the sum of the array
//receives: ostream& out, int array arr, int n, int genNum (which generation)
//returns: nothing, void
void printGeneration(ostream& out, const int arr[], int n, int genNum);

//name: computeNextGeneration
//purpose: builds the next generation of the array in place by
//         applying the bitwise rules:
//           - shift X0 right one bit
//           - for odd j (1 <= j <= n-1): Xj = Xj & Xj-1
//           - for even j (2 <= j <= n-2): Xj = Xj ^ Xj+1
//           - clear bit i of Xn-1, where i is the generation number
//receives: int array arr, int n, int genNum (the generation being produced)
//returns: nothing, void
void computeNextGeneration(int arr[], int n, int genNum);

//name: wantsAnotherGeneration
//purpose: asks the user whether another generation should be computed
//receives: nothing
//returns: bool, true if the user answered Y or y
bool wantsAnotherGeneration();

int main() {
	ifstream infile;
	ofstream outfile;
	int* arr = nullptr; //array holding the current generation's integers
	int n = 0;        //number of integers in use
	int generation = 0; //generation counter, starts at generation 0

	string studentName = "Madison Nichols";

	openFiles(infile, outfile);
	
	infile >> n;
	if (!infile) {
		cout << "Error: could not open input file." << endl;
		return 1;
	}

	arr = new int[n];
	readData(infile, arr, n);
	infile.close();

	printHeader(outfile, studentName);
	printGeneration(outfile, arr, n, generation);

	//also echo to the screen so the user can see progress interactively
	printHeader(cout, studentName);
	printGeneration(cout, arr, n, generation);

	while (wantsAnotherGeneration()) {
		generation++;
		computeNextGeneration(arr, n, generation);
		printGeneration(outfile, arr, n, generation);
		printGeneration(cout, arr, n, generation);
	}

	outfile << "Generations complete!" << endl;
	cout << "Generations complete!" << endl;

	delete[] arr;
	outfile.close();

	return 0;
}

void openFiles(ifstream& infile, ofstream& outfile) {
	char inFileName[40];
	char outFileName[40];

	cout << "Enter the input file name: ";
	cin >> inFileName;
	infile.open(inFileName); //open input file

	cout << "Enter the output file name: ";
	cin >> outFileName;
	outfile.open(outFileName); //open output file
}

bool isEven(int num) {
	return (num & 1) == 0; //bit 0 clear means even
}

bool isOdd(int num) {
	return (num & 1) == 1; //bit 0 set means odd
}

void readData(ifstream& infile, int arr[], int& n) {
	for (int i = 0; i < n; i++) {
		infile >> arr[i];
	}
}

int computeSum(const int arr[], int n) {
	int sum = 0;

	for (int i = 0; i < n; i++) {
		sum += arr[i];
	}

	return sum;
}

void printHeader(ostream& out, const string& name) {
	out << name << endl;
	out << "Program #1" << endl << endl;
}

void printGeneration(ostream& out, const int arr[], int n, int genNum) {
	out << "Generation " << genNum << ": ";

	for (int i = 0; i < n; i++) {
		out << arr[i] << " ";
	}

	out << "Sum : " << computeSum(arr, n) << endl;
}

void computeNextGeneration(int arr[], int n, int genNum) {
	//Shift X0 to the right one bit
	arr[0] = arr[0] >> 1;

	//Walk the rest of the array left to right, using each element's
	//already-updated neighbor where the rule calls for it
	for (int j = 1; j <= n - 1; j++) {
		if (isOdd(j)) {
			//Set Xj to Xj & Xj-1, for 1 <= j <= n-1 and j odd
			arr[j] = arr[j] & arr[j - 1];
		}
		else if (isEven(j) && j <= n - 2) {
			//Set Xj to Xj ^ Xj+1, for 2 <= j <= n-2 and j even
			arr[j] = arr[j] ^ arr[j + 1];
		}
	}

	//Set bit i (the generation number) of Xn-1 to 0
	int mask = 1 << genNum;
	arr[n - 1] = arr[n - 1] & ~mask;
}

bool wantsAnotherGeneration() {
	char ans;

	cout << "Do you want to compute another generation? (Y/N): ";
	cin >> ans;

	return (ans == 'Y' || ans == 'y');
}

