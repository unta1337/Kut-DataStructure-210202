// 112: Path Sum
/*
 * Find if the values root through leaf can sum up to target.
 */
// https://leetcode.com/problems/path-sum/

// Status: Accepted
// Runtime: 4 ms (98.58 %)
// Memory Usage: 21.4 MB (37.85 %)
// https://leetcode.com/submissions/detail/580639665/

// 2020136018 김성녕

#ifndef _LC_112_H
#define _LC_112_H

#include <list>

struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode() : val(0), left(nullptr), right(nullptr) { }
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) { }
	TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) { }
};

namespace Solution112 {
    bool hasPathSumRec(TreeNode* node, int targetSum, int currentSum) {        
		currentSum += node->val;

		if (node->left == nullptr && node->right == nullptr)
			return currentSum == targetSum;

		bool lhs = false;
		bool rhs = false;

		if (node->left != nullptr)
			lhs = hasPathSumRec(node->left, targetSum, currentSum);
		if (node->right != nullptr)
			rhs = hasPathSumRec(node->right, targetSum, currentSum);

		return lhs || rhs;
	}
    
    bool hasPathSum(TreeNode* node, int targetSum) {
        if (node == nullptr)
            return false;
        
        return hasPathSumRec(node, targetSum, 0);
    }
};

using namespace Solution112;

#endif
