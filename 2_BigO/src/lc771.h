// 771: Jewels and Stones
/*
 * Find the jewels in the stones, where the letters are representing the types of stones.
 */
// https://leetcode.com/problems/jewels-and-stones/

// Runtime: 0 ms (100.00 %)
// Memory Useage: 6.1 MB (96.70 %)
// https://leetcode.com/submissions/detail/551589720/

#ifndef _LC_771_H
#define _LC_771_H

namespace Solution771 {
    int numJewelsInStones(std::string jewels, std::string stones) {
        bool j[58] = { 0, };
        for (int i = 0; i < jewels.length(); i++)
            j[jewels[i] - 'A'] = true;
        
        int count = 0;
        for (int i = 0; i < stones.length(); i++)
            count += j[stones[i] - 'A'];
        
        return count;
    }
};

using namespace Solution771;

#endif