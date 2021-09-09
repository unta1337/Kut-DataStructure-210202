// 389: Find the Difference
/*
 * Find the difference bewteen some string and its shuffled and added one more character one.
 */
// https://leetcode.com/problems/find-the-difference/

// Status: Accepted
// Runtime: 3 ms (77.59 %)
// Memory Usage: 6.7 MB (66.79 %)
// https://leetcode.com/submissions/detail/551563014/

#ifndef _LC_389_H
#define _LC_389_H

namespace Solution389 {
    char findTheDifference(std::string s, std::string t) {
        // 소문자 알파벳이 등장한 횟수를 기록할 두 개의 배열 선언.
        short s_char[26] = { 0, };
        short t_char[26] = { 0, };
        
        // s와 t중 s의 길이만큼 반복하여 NullPointerExceptio을 방지.
        for (int i = 0; i < s.length(); i++) {
            s_char[s[i] - 'a']++;
            t_char[t[i] - 'a']++;
        } t_char[t[t.length() - 1] - 'a']++;    // t의 마지막 원소에 대한 처리를 수행.

        // 알파벳 등장 횟수를 비교하여 횟수가 다른 알파벳을 반환.
        for (int i = 0; i < 26; i++) {
            if (s_char[i] != t_char[i])
                return i + 'a';
        }
        
        // 함수 반환형 오류 방지.
        return '\0';
    }
};

/*
 * 입력되는 문자열 s의 길이를 n이라 두자.
 *
 * 최초 s, t 탐색 시 O(n) + O(1) -> O(n)
 * 알바벳 등장 횟수 비교 시 O(26) -> O(1)
 * 
 * 따라서, 해당 알고리즘의 빅 오는 O(n) + O(1) -> O(n)
 */

using namespace Solution389;

#endif