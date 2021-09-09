// 389: Find the Difference
/*
 * Find the difference bewteen some string and its shuffled and added one more character one.
 */
// https://leetcode.com/problems/find-the-difference/

// Runtime: 3 ms (77.59 %)
// Memory Usage: 6.7 MB (66.79 %)
// https://leetcode.com/submissions/detail/551563014/

#ifndef _LC_389_H
#define _LC_389_H

namespace Solution389 {
    char findTheDifference(std::string s, std::string t) {
        short s_char[26] = { 0, };
        short t_char[26] = { 0, };
        
        for (int i = 0; i < s.length(); i++) {
            s_char[s[i] - 'a']++;
            t_char[t[i] - 'a']++;
        } t_char[t[t.length() - 1] - 'a']++;

        for (int i = 0; i < 26; i++) {
            if (s_char[i] != t_char[i])
                return i + 'a';
        }
        
        return '\0';
    }
};

using namespace Solution389;

#endif