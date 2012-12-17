/* 	Written by Thomas Upfold
	Problem A of the 2012 South Pacific "Making Decisions"
	
	Summary:Given a even string of 0's and 1's, find if the middle two
			characters differ.
			 
	Link:	https://icpcarchive.ecs.baylor.edu/external/61/6161.pdf
	
	Knowledge Required: Basic programming skills 
	
	Status: Accepted (0.013s)
*/
#include <iostream>
using namespace std;
int main() {
	string bitString;
	int caseNum;
	cin >> caseNum;
	for (int i = 0; i < caseNum; i++) {
		cin >> bitString;
		int len = bitString.length();
		if (bitString[len/2] == bitString[(len/2)-1]) cout << "Do-it\n";
		else cout << "Do-it-Not\n";
	}
}
			
			
	
	
