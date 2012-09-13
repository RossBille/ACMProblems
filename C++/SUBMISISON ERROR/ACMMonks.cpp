#include <iostream>
#include <map>
#include <list>
using namespace std;
struct triplet {
	int a;
	int b;
	int c;
	int swapCount;
};
triplet initTrip(int x, int y, int z) {
	triplet init;
	init.a = x;
	init.b = y;
	init.c = z;
	return init;
}
triplet initTrip(int x, int y, int z, int swaps) {
	triplet init;
	init.a = x;
	init.b = y;
	init.c = z;
	init.swapCount = swaps;
	return init;
}
void swap(int *a, int *b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}
void sortTriplet(triplet *t) {
	if (t->a < t->b) swap(&t->a, &t->b);
	if (t->a < t->c) swap(&t->a, &t->c);
	if (t->b < t->c) swap(&t->b, &t->c);
}
int BFS(triplet init);
int getKey(triplet t);
int main() {
	int a,b,c;
	while (cin >> a) {
		cin >> b;
		cin >> c;
		//checks for 0,0,0 input or x, y, 0 input
		if (!(a || b || c)) break;
		if (!(a && b && c)) {
			cout << a << " " << b << " " << c << " 0\n";
		} else {
			triplet input = initTrip(a,b,c);
			triplet parameter = initTrip(a,b,c,0);
			sortTriplet(&parameter);
			int minSwaps = BFS(parameter);
			cout << input.a << " " << input.b << " " << input.c << " " << minSwaps << endl;
		}
	}
	return 0;
}
int getKey(triplet t) {
	return t.a*100 + t.b*10 + t.c;
}
int BFS(triplet init) {
	map<int,bool> check;
	list<triplet> queue;
	queue.push_back(init);
	//int count = 0;
	while(true) {
		triplet cur = queue.front();
		//cout << "Test " << cur.swapCount << " : " << cur.a << " " << cur.b << " " << cur.c << endl;
		queue.pop_front();
		int a = cur.a, b = cur.b, c = cur.c;
		if(a == b || a == c || b == c) {
			//cout << "count: " << count << endl;
			return cur.swapCount+1;
		} else {
			triplet arr[3];
			arr[0] = initTrip(a-b,b*2,c,cur.swapCount+1);
			arr[1] = initTrip(a-c,b,c*2,cur.swapCount+1);
			arr[2] = initTrip(a,b-c,c*2,cur.swapCount+1);
			for (int i = 0; i < 3; i++) {
				sortTriplet(&arr[i]);
				if (check.count(getKey(arr[i])) == 0) {
					check[getKey(arr[i])] = true;
					queue.push_back(arr[i]);
				}
			}
		}
		//count++;
	}
			
}
