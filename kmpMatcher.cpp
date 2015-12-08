#include "kmpMatcher.h"
#include <iostream>

/* Intitialise the parser. Saves the pattern to be matched.
 * Create the state machine and set current state to 0
 */
kmpMatcher::kmpMatcher (string p) {
	pattern = p;
	preProcessPattern();
	state  = 0;
}

/* Pre process the pattern to calulate the next state on fallure for each state.
 * nextStateOnFailure[0] = -1
 * nextStateOnFailure[j + 1] = i + 1 | if i is the largest integer such that i < j and
 *					pattern[j] = pattern[i]
 *					pattern[j - 1] = pattern[i - 1]
 *					. . .
 *					pattern[j - i] = pattern[0]
 *			    0	     | if no such i exist 
 */
void kmpMatcher::preProcessPattern() {
	int i, j;

	nextStateOnFailure.resize(pattern.length() + 1);
	nextStateOnFailure[0] = -1;
	
	for (i = -1, j = 0; j < pattern.length(); j++) {
		while(i >= 0 && pattern[i] != pattern[j])
			i = nextStateOnFailure[i];
		i++;
		nextStateOnFailure[j + 1] =  i;
	}
}

/* Print the pattern and state machine
 */
void kmpMatcher::printMachine() {
	cout<<"Pattern : "<<pattern<<endl;
	cout<<"Fn      : ";
	for (int i = 0; i < nextStateOnFailure.size(); i++)
		cout<<nextStateOnFailure[i]<<" ";
	cout<<endl;
}

/* Update the state of the machine based on current state and
 * check if it reaches the final state. Accept if it reach the
 * final state
 */
bool kmpMatcher::parseForPattern(char ch) {
	int m;
	m = pattern.length();
	while (state == m || (state >= 0 && pattern[state] != ch))
		state = nextStateOnFailure[state];
	state++;
	if (state == m)
		return true;
	return false;
}
