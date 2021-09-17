// 2020136018 김성녕

#include <iostream>

#include "lc389.h"
#include "lc771.h"

using namespace std;

int main(void) {
    // Problem 389 test cases.
    cout << "Problem 389 test cases.\n";
    cout << findTheDifference("abcd", "abcde") << endl;
    cout << findTheDifference("", "y") << endl;
    cout << findTheDifference("a", "aa") << endl;
    cout << findTheDifference("ae", "aea") << endl;
    cout << endl;

    // Problem 771 test cases.
    cout << "Problem 771 test cases.\n";
    cout << numJewelsInStones("aA", "aAAbbbb") << endl;
    cout << numJewelsInStones("z", "ZZ") << endl;

    return 0;
}
