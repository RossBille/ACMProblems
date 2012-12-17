/* 	Written by Thomas Upfold
	Problem B of the 2012 South Pacific "Log Books"
	
	Summary:Given a sequence of times (sunrise, sunset, start, finish) calculate
			the duration of each driving session and if it meets certain conditions
			(<2 hours, night/day hours etc)
			 
	Link:	https://icpcarchive.ecs.baylor.edu/external/61/6162.pdf
	
	Knowledge Required: Good grasp on input methods and comparing time values
	
	Status: near submission (testing)
*/
#include <iostream>
#include <sstream>
#include <string>
#define DAY 1
#define NIGHT 0
//#define vDEBUG
//define lDEBUG
//#define sDEBUG
using namespace std;

struct timePair {
	int hour;
	int minute;
};
timePair init() {
	timePair t;
	t.hour = 0;
	t.minute = 0;
	return t;
}

timePair stringToTime(string t);
timePair timeLength(timePair start, timePair finish);
bool timeOfDay(timePair sunrise, timePair sunset, timePair start, timePair finish);
int tpToInt(timePair tp);

int main() {
	int logEntries;
	cin >> logEntries;
	while (logEntries != 0) {
		bool valid = true;
		timePair dayHours = init(), nightHours = init();
		for (int i = 0; i < logEntries; i++) {
			timePair timeArr[4];
			//{sunrise, sunset , start, finish}
			for (int j = 0; j < 4; j++) {
				string t;
				cin >> t;
				if (valid) timeArr[j] = stringToTime(t);
			}
			if (valid) {
				timePair sunrise = timeArr[0], sunset = timeArr[1];
				timePair start = timeArr[2], finish = timeArr[3];
				
				timePair length = timeLength(start, finish); 
				if (length.hour > 2 || (length.hour == 2 && length.minute != 0)) {
					valid = false;
					#ifdef vDEBUG
						cout << i+1 << " gap too big\n";
					#endif
				} else {
					timePair cur;
					if (timeOfDay(sunrise, sunset, start, finish) == DAY) {
						cur = dayHours;
					} else {
						cur = nightHours;
					}
					cur.hour += length.hour;
					int min = cur.minute + length.minute;
					if (min >= 60) {
						cur.hour++;
						cur.minute-=60;
					}
				}
			}
		}
		int total = dayHours.hour + nightHours.hour;
		if (dayHours.minute + nightHours.minute >= 60) total++;
		
		if (!valid || nightHours.hour <10 || total < 50) cout << "NON\n";
		else cout << "PASS\n";
		cin >> logEntries;
	}
}
bool timeOfDay(timePair sunrise, timePair sunset, timePair start, timePair finish) {
	int rise = tpToInt(sunrise), set = tpToInt(sunset); 
	int s = tpToInt(start), f = tpToInt(finish);
	if (f <= rise) return NIGHT;
	if (s >= set) return NIGHT;
	
	if (s <= rise && f >= rise) {
		if (rise - s >= f - rise) return NIGHT;
		else return DAY;
	}
	if (s <= set && f >= set) {
		if (set-s <= f-set) return NIGHT;
		else return DAY;
	}
	return DAY;
}
int tpToInt(timePair tp) {
	int i = 0;
	i+= tp.hour*100;
	i+= tp.minute;
	return i;
}
timePair stringToTime(string t) {
	int i = 0;
	timePair tp;
	#ifdef sDEBUG
		cout << "stringToTime start" << endl;
		cout << t << endl;
	#endif
	while (t[++i]!=':');
	string h = t.substr(0,i);
	string m = t.substr(i+1, 2);
	istringstream hours(h);
	hours >> tp.hour;
	istringstream minutes(m);
	minutes >> tp.minute;
	#ifdef sDEBUG
		cout << h << " " << m << " " << tp.hour << " " << tp.minute << endl;
		cout << "stringToTime end" << endl;
	#endif
	return tp;
}
timePair timeLength(timePair start, timePair finish) {
	timePair length;
	int startRoundUp = 0, finishRoundDown = 0;
	//Round times to a round hour point while saving times
	#ifdef lDEBUG
		cout << "length start" << endl;
		cout << start.hour << ":" << start.minute << " " << finish.hour << ":" << finish.minute << endl;
	#endif
	if (start.minute != 0) {
		startRoundUp = 60 - start.minute;
		start.hour++;
		start.minute = 0;
	}
	if (finish.minute != 0) {
		finishRoundDown = finish.minute;
		finish.minute = 0;
	}
	int hourDiff = finish.hour - start.hour, minuteDiff = startRoundUp + finishRoundDown;
	if (minuteDiff >= 60) {
		hourDiff++;
		minuteDiff -= 60;
	}
	length.hour = hourDiff;
	length.minute = minuteDiff;
	#ifdef lDEBUG
		cout << length.hour << ":" << length.minute << endl;
		cout << "length end" << endl;
	#endif
	return length;
}
			
				
				
			
