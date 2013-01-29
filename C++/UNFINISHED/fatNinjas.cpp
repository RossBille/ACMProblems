/*   Written by Thomas Upfold
	Problem H of the 2012 South Pacific "Fat Ninjas"
	
	Summary: Given the length of a square room and the position of n roof mounted vertical lasers. Find the maximum
			width of the 'fat ninja' that can walk from one side of the room to the other
			 
	Link:	https://icpcarchive.ecs.baylor.edu/external/61/6168.pdf
	
	Knowledge Required: Dijkstra's algorithm, recognising that you can search the dual graph of the room layout and good design.
	
	Status: in progress
*/
#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <list>

#define NOPATH -1

using namespace std;

struct laserPair {
	float x;
	float y;
};
struct line {
	float len;
	laserPair a;
	laserPair b;
};
struct node {
	float best, leftWeight, upWeight, downWeight, rightWeight;
	struct node  *left, *up, *down, *right;
	int x, y;
	bool visited;
};
void leftConnect(node *n, node *l, float lw) {
	n->left = l;
	n->leftWeight = lw;
}
void rightConnect(node *n, node *r, float rw) {
	n->right = r;
	n->rightWeight = rw;
}
void upConnect(node *n, node *u, float uw) {
	n->up = u;
	n->upWeight = uw;
}
void downConnect(node *n, node *d, float dw) {
	n->down = d;
	n->downWeight = dw;
}
line init(float l, laserPair x, laserPair y) {
	line n;
	n.len = l;
	n.a = x;
	n.b = y;
	return n;
}
bool laserSorter(laserPair const& lhs, laserPair const& rhs) {
	if (lhs.x != rhs.x) {
		return lhs.x < rhs.x;
	} else {
		return lhs.y < rhs.y;
	}
};
bool nodeSorter(node const* lhs, node const* rhs) {
	return lhs->best > rhs->best;
}
bool operator==(laserPair const& lhs, laserPair const& rhs) {
	return (lhs.x == rhs.x) && (lhs.y == rhs.y);
}
float distPair(laserPair p1, laserPair p2) {
	return sqrt(pow((p2.x - p1.x),2.0) + pow((p2.y - p1.y),2.0));
};
void printNode(node *n) {
	cout << "u,d,l,r : ";
	cout << n->upWeight << " " << n->downWeight << " "
		 << n->leftWeight << " " << n->rightWeight << " ("
		 << n->x << "," << n->y << ")" << endl;
}
 int main() {
	static laserPair wall;
	int roomSize, laserNum;
	
	cin >> roomSize;
	cin >> laserNum;
	
	while (roomSize || laserNum) {
		laserPair lasers[laserNum];
		int colNum = 0, maxCol = 0;
		float lastX = -1.0;
		
		for (int i = 0; i < laserNum; i++) { //laser point input
			laserPair l;
			cin >> l.x;
			cin >> l.y;
			lasers[i] = l;
		}
		sort(lasers, lasers+laserNum, &laserSorter);
		
		for (int i = 0, count = 0; i < laserNum; i++) { //finds number of unique x values in test case
			if (lastX != lasers[i].x) {
				lastX = lasers[i].x;
				colNum++;
			}
		}
		
		vector<line> colDist[colNum]; //lines between each laser point on the same x col
		vector<laserPair> colPoint[colNum]; //laser co-ords for each laser point on the same x col
		float lastSeen = lasers[0].x;
		int colSplitLoc[colNum];
		line l = init(lasers[0].y, lasers[0], wall);
		colDist[0].push_back(l);
		colPoint[0].push_back(lasers[0]);

		/* splits points with the same x value into their own vectors and also does the column dist calculations */
		for (int i = 1, indexCount = 0; i < laserNum; i++) {
			if (lasers[i].x != lastSeen) {
				line l = init((roomSize - lasers[i-1].y), lasers[i-1], wall);
				colDist[indexCount].push_back(l);
				lastSeen = lasers[i].x;
				colSplitLoc[indexCount+1] = i;
				indexCount++;
				l = init(lasers[i].y, lasers[i], wall);
				colPoint[indexCount].push_back(lasers[i]);
				colDist[indexCount].push_back(l);
			} else {
				line l = init(lasers[i].y - lasers[i-1].y, lasers[i-1], lasers[i]);
				colDist[indexCount].push_back(l);
				colPoint[indexCount].push_back(lasers[i]);
			}
		}
		
		l = init((roomSize - lasers[laserNum-1].y), lasers[laserNum-1], wall);
		colDist[colNum-1].push_back(l);
		vector<line> betweenColDist[colNum+1];
		
		/* finds all the edges between the 'columns' which will contribute to the graph */
		for (int i = 1; i < colNum; i++) {
			vector<laserPair> v1 = colPoint[i-1], v2 = colPoint[i];
			if (v2.size() > v1.size()) {
				vector<laserPair> temp;
				temp = v1;
				v1 = v2;
				v2 = temp;
			}
			bool visited[v2.size()];
			
			for (int a = 0; a < v2.size(); a++) visited[a] = false;
			
			for (int lhp = 0; lhp < v1.size(); lhp++) {
				float minDist = 150.0; //just above max possible distance between two laser points
				laserPair bestL, bestR;
				for (int rhp = 0; rhp < v2.size(); rhp++) {
					float d = distPair(v1[lhp],v2[rhp]);
					if (d < minDist) {
						minDist = d;
						bestL = v1[lhp];
						bestR = v2[rhp];
						visited[rhp] = true;
					} else {
						break;
					}
				}
				line newLine = init(minDist, bestL, bestR);
				betweenColDist[i].push_back(newLine);
			}
			for (int j = 0; j < v2.size(); j++) {
				if (!visited[j]) {
					float minDist = 150.0; //just above max possible distance between two laser points
					laserPair bestL, bestR;
					for (int lhp = 0; lhp < v1.size(); lhp++) {
						float d = distPair(v1[lhp],v2[j]);
						if (d < minDist) {
							minDist = d;
							bestL = v1[lhp];
							bestR = v2[j];
							visited[j] = true;
						} else {
							break;
						}
					}
					line newLine = init(minDist, bestL, bestR);
					betweenColDist[i].push_back(newLine);
				}
			}
		}
		
		vector<node> graph[colNum+1];
		
		for (int i = 1; i < colNum+1; i++) { //inits graph
			for (int j = 0; j < betweenColDist[i].size()+1; j++) {
				node n;
				n.best = 0.0;
				n.visited = false;
				n.x = i;
				n.y = j;
				graph[i].push_back(n);
			}
		}
		/* creates graph connections */	
		node finish;
		finish.rightWeight = -2.0;
		finish.leftWeight = -2.0;
		finish.upWeight = -2.0;
		finish.downWeight = -2.0;
		finish.x = colNum;
		finish.y = 0;
		for (int i = 1; i < colNum; i++) { //ignores start and end index because they're the start and finish of the graph
			int leftIndex = 0, rightIndex = 0; //offset as initial start position is manually dealt with
			for (int j = 0; j < graph[i].size(); j++) {
			
				node *current = &graph[i][j], *lnode = NULL, *rnode = &finish;
				if (i-1 > 0) lnode = &graph[i-1][leftIndex];
				leftConnect(current, lnode, colDist[i-1][leftIndex].len);
				if (i+1 != colNum) rnode = &graph[i+1][rightIndex];
				rightConnect(current, rnode, colDist[i][rightIndex].len);
				if (j== 0 || j == betweenColDist[i].size()) {				
					
					if (j == 0) {
						upConnect(current, NULL, NOPATH);
						downConnect(current, &graph[i][j+1], betweenColDist[i][j].len);
						leftIndex++;
						rightIndex++;
					} else if (j == betweenColDist[i].size()) {
						downConnect(current, NULL, NOPATH);
						upConnect(current, &graph[i][j-1], betweenColDist[i][j-1].len);
						leftIndex = 0;
						rightIndex = 0;
					}
					//cout << i << " " << j << endl;
					//printNode(current);
					//cout << current->x << " " << current->y << endl;
				} else {
					line above = betweenColDist[i][j-1], below = betweenColDist[i][j];
					upConnect(current, &graph[i][j-1], above.len);
					downConnect(current, &graph[i][j+1], below.len);		
					
					if (above.a == below.a) { //no left entry
						leftConnect(current, NULL, NOPATH);
						rightIndex++;
					} else if (above.b == below.b) { //no right entry
						rightConnect(current, NULL, NOPATH);
						leftIndex++;
					} else {
						rightIndex++;
						leftIndex++;
					}
					//cout << i << " " << j << endl;
					//printNode(current);
					//cout << current->x << " " << current->y << endl;
				}
			}
		}
		list<node*> pq = list<node*>();
		float bestFoundLeft = graph[1][0].leftWeight; 
		int bestIndex = 0;
		for (int i = 0; i < graph[1].size(); i++) {
			node *cur = &graph[1][i];
			if (cur->leftWeight > bestFoundLeft) {
				bestIndex = i;
				bestFoundLeft = cur->leftWeight;
			}
		}
		graph[1][bestIndex].visited = true;
		graph[1][bestIndex].best = bestFoundLeft;
		pq.push_back(&graph[1][bestIndex]);
		float bestSize = 0.0;
		while (true) {
			pq.sort(&nodeSorter);
			node *cur = pq.front(), *right = cur->right, *up = cur->up, *down = cur->down;
			//cout << endl;
			pq.pop_front();
			//printNode(cur);

			cur->visited = true;
			float bestWidth = cur->best;
			if (cur->rightWeight == -2.0) {  //finish identifier
				cout << "asdf" << endl;
				bestSize = cur->best;
				break;
			}
			if (right != NULL && !(right->visited) && right->best < cur->rightWeight) {
				//cout << "right";
				if (cur->rightWeight >= bestWidth) {
					right->best = bestWidth;
				} else {
					right->best = cur->rightWeight;
				}
				pq.push_back(right);
			}
			if (up != NULL && !(up->visited) && up->best < cur->upWeight) {
				//cout << " up ";
				if (cur->upWeight >= bestWidth) {
					up->best = bestWidth;
				} else {
					up->best = cur->upWeight;
				}
				pq.push_back(up);
			}
			if (down != NULL && !(down->visited) && down->best < cur->downWeight) {
				//cout << " down ";
				if (cur->downWeight >= bestWidth) {
					down->best = bestWidth;
				} else {
					down->best = cur->downWeight;
				}
				pq.push_back(down);
			}
			//cout << endl;
		}
		cout << bestSize << endl;
		cin >> roomSize;
		cin >> laserNum;
	}
}
