// 771: Jewels and Stones
/*
 * Find the jewels in the stones, where the letters are representing the types of stones.
 */
// https://leetcode.com/problems/jewels-and-stones/

// Status: Accepted
// Runtime: 0 ms (100.00 %)
// Memory Useage: 6.1 MB (96.70 %)
// https://leetcode.com/submissions/detail/551589720/

#ifndef _LC_771_H
#define _LC_771_H

namespace Solution771 {
    int numJewelsInStones(std::string jewels, std::string stones) {
        // 알바벳 대문자와 소문자의 등장 횟수를 기록할 배열 선언 및 등장 횟수 계산.
        bool j[58] = { 0, };
        for (int i = 0; i < jewels.length(); i++)
            j[jewels[i] - 'A'] = true;
        
        // 입력으로 들어온 stone을 탐색하면서 해당 알파벳이 jewels에 있으면 카운트 증가.
        int count = 0;
        for (int i = 0; i < stones.length(); i++)
            count += j[stones[i] - 'A'];
        
        return count;
    }
};

/*
 * jewels의 길이를 n, stone의 길이를 m이라 두자.
 *
 * 최초 jewels 탐색 시 O(n)
 * 이후 알바벳 유무 탐색 시 O(m)
 * 
 * 따라서, 해당 알고리즘의 빅 오는 O(n) + O(m) -> O(n + m)
 * 또는, 입력되는 문자열의 총 길이를 n으로 하여: O(n)
 */

using namespace Solution771;

#endif