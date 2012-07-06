#include <iostream>
#include <cstdlib>
#include <list>
#include <vector>
#include <assert.h>

#define NOT_FOUND -1

using namespace std;

bool search(int a, int b, vector< list<int> > adj);
int find(string a, vector<string> list);
void printList(list<int> list);

int main() {
	vector<string> cities;
	vector<int> cityIndex;
	vector< list<int> > adjList;
	int cityTargetNum = 0, tripNum = 0, cityTotal = 0;
	
	while (cin >> cityTargetNum && cityTargetNum != 0) {
		for (int i = 0; i < cityTargetNum; i++) {
			string city;
			cin >> city;
			cities.push_back(city);
			cityIndex.push_back(i);
			list<int> newCity;
			adjList.push_back(newCity);
		}
		
		cityTotal = cityTargetNum;
		cin >> tripNum;
		
		for (int i = 0; i < tripNum; i++) {
			string first, second;
			cin >> first; //from this city
			cin >> second; //to this city
			
			/*	If the city/s in the path aren't know yet
				a list entry is created for them	*/
			int firstIndex = find(first,cities);
			int secondIndex = find(second,cities);
			
			if (firstIndex == NOT_FOUND) { 
				cities.push_back(first);
				cityIndex.push_back(cityTotal);
				list<int> newList;
				adjList.push_back(newList);
				firstIndex = cityTotal;
				cityTotal++;
			}	

			if(find(second,cities) == NOT_FOUND) {
				cities.push_back(second);
				cityIndex.push_back(cityTotal);
				list<int> newList;
				adjList.push_back(newList);
				secondIndex = cityTotal;
				cityTotal++;
			}
			assert(firstIndex != -1);
			assert(secondIndex != -1);
			adjList[firstIndex].push_back(secondIndex);
		}
		// for (int i = 0; i < cityTotal; i++) {
			// printList(adjList[i]);
		// }
		bool prevSearch = true;
		int i = 0;
		while (prevSearch && i != cityTargetNum-1) {
			//cout << i << " to " << i+1 << " is ";
			prevSearch = prevSearch && search(i, i+1, adjList);
			//cout << prevSearch << endl;
			i++;
		}
		if(prevSearch) {
			cout << "The tour can be planned." << endl;
		} else {
			cout << "The tour cannot be planned with the given flight segments." << endl;
		}
		
		adjList.clear();
		cities.clear();
		cityIndex.clear();
		tripNum = 0;
		cityTotal = 0;
	}
	return 0;
}

int find(string a, vector<string> list) {
	// cout << "target: " << a << endl;
	// for (int i = 0; i < list.size(); i++) {
		// cout << list[i] << endl;
	// }
	for (int i = 0; i < list.size(); i++) {
		if (!a.compare(list[i])) return i; //compare() returning 0 on match is weird imo
	}
	return -1;
}
void printList(list<int> l) {
	list<int>::iterator i;
	for (i = l.begin(); i!= l.end(); ++i) {
		cout << *i << " ";
	}
	cout << endl;
}
bool search(int a, int b, vector< list<int> > adj) {
	bool visited[adj.size()];
	for (int i = 0; i < adj.size(); i++) {
		visited[i] = false;
	}
	visited[a] = true;
	
	list<int> frontier;
	frontier.push_back(a);
	while(!frontier.empty()) {
		list<int> curList = adj[frontier.front()];
		frontier.pop_front();
		list<int>::iterator i;
		if (!curList.empty()) {
			for(i = curList.begin(); i!= curList.end(); ++i) {
				if (*i == b) return true;
				if (visited[*i] == false) {
					frontier.push_back(*i);
					visited[*i] = true;
				}
			}
		}
	}
	return false;
}