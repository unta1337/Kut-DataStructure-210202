# 771: Jewels and Stones
#
# Find the jewels in the stones, where the letters are representing the types of stones.
#
# https://leetcode.com/problems/jewels-and-stones/

# Status: Accepted
# Runtime: 32 ms (63.80 %)
# Memory Useage: 14.4 MB (13.44 %)
# https://leetcode.com/submissions/detail/552197646/

def numJewelsInStones(jewels: str, stones: str) -> int:
    # 알바벳 대문자와 소문자의 등장 횟수를 기록할 배열 선언 및 등장 횟수 계산.
    j: list = [False for _ in range(58)]
    for i in range(len(jewels)):
        j[ord(jewels[i]) - ord('A')] = True

    # 입력으로 들어온 stone을 탐색하면서 해당 알파벳이 jewels에 있으면 카운트 증가.
    count: int = 0
    for i in range(len(stones)):
        count += j[ord(stones[i]) - ord('A')]

    return count

#
# jewels의 길이를 n, stone의 길이를 m이라 두자.
#
# 최초 jewels 탐색 시 O(n)
# 이후 알바벳 유무 탐색 시 O(m)
# 
# 따라서, 해당 알고리즘의 빅 오는 O(n) + O(m) -> O(n + m)
# 또는, 입력되는 문자열의 총 길이를 n으로 하여: O(n)
#