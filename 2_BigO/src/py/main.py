from lc389 import *
from lc771 import *

def main():
    # Problem 389 test cases.
    print('Problem 389 test cases.')
    print(findTheDifference('abcd', 'abcde'))
    print(findTheDifference('', 'y'))
    print(findTheDifference('a', 'aa'))
    print(findTheDifference('ae', 'aea'))
    print()

    # Problem 771 test cases.
    print('Problem 771 test cases.')
    print(numJewelsInStones('aA', 'aAAbbbb'))
    print(numJewelsInStones('z', 'ZZ'))

if __name__ == '__main__':
    main()