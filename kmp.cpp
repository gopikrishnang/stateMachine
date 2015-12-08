#include <iostream>
#include <stdio.h>
#include "kmpMatcher.h"

int main() {
	kmpMatcher m("hello");
	//m.printMachine();
	while (true) {
		char ch = getchar();
		bool patternFound = m.parseForPattern(ch);
		if (patternFound) {
			cout<<"Match"<<endl;
			break;
		}
	}
	return 0;
}
