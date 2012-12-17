#include <iostream>
#include <algorithm>
using namespace std;

int main() {
	
	int classNum;
	cin >> classNum;
	
	for (int i = 0; i < classNum; i++) {
		int studentNum;
		
		cin >> studentNum;
		int classArr[studentNum];
		
		for (int j = 0; j < studentNum; j++) {
			int currentMark;
			cin >> currentMark;
			classArr[j] = currentMark;
		}
		
		sort(classArr, classArr+studentNum);
		int gap = 0;
		
		for (int j = 0; j < studentNum -1; j++) {
			int cur = classArr[j+1] - classArr[j];
			if (cur > gap) gap = cur;
		}
		
		cout << "Class " << i+1 << endl;
		cout << "Max " << classArr[studentNum-1] << ", Min " << classArr[0] << ", Largest gap " << gap << endl;
	}
}
		