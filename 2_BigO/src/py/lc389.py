# 389: Find the Difference
#
# Find the difference bewteen some string and its shuffled and added one more character one.
#
# https://leetcode.com/problems/find-the-difference/

# Status: Accepted
# Runtime: 40 ms (35.49 %)
# Memory Useage: 14.3 MB (64.20 %)
# https://leetcode.com/submissions/detail/552197100/

def findTheDifference(s: str, t: str) -> str:
    # 소문자 알파벳이 등장한 횟수를 기록할 두 개의 배열 선언.
    s_char: list = [0 for _ in range(26)]
    t_char: list = [0 for _ in range(26)]

    # s와 t중 s의 길이만큼 반복하여 NullPointerExceptio을 방지.
    for i in range(len(s)):
        s_char[ord(s[i]) - ord('a')] += 1
        t_char[ord(t[i]) - ord('a')] += 1
    t_char[ord(t[len(t) - 1]) - ord('a')] += 1      # t의 마지막 원소에 대한 처리를 수행.

    # 알파벳 등장 횟수를 비교하여 횟수가 다른 알파벳을 반환.
    for i in range(26):
        if s_char[i] != t_char[i]:
            return chr(i + ord('a'))

    # 함수 반환형 오류 방지.
    return '\0'

#
# 입력되는 문자열 s의 길이를 n이라 두자.
#
# 최초 s, t 탐색 시 O(n) + O(1) -> O(n)
# 알바벳 등장 횟수 비교 시 O(26) -> O(1)
# 
# 따라서, 해당 알고리즘의 빅 오는 O(n) + O(1) -> O(n)
#