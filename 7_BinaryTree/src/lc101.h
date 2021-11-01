// 101: Symmetric Tree
/*
 * Determine if the tree is symmetric or not.
 */
// https://leetcode.com/problems/symmetric-tree/

// Status: Accepted
// Runtime: 4 ms (78.82 %)
// Memory Usage: 20.1 MB (7.42 %)
// https://leetcode.com/submissions/detail/580630763/

// 2020136018 김성녕

#ifndef _LC_101_H
#define _LC_101_H

#include <list>

struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode() : val(0), left(nullptr), right(nullptr) { }
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) { }
	TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) { }
};

namespace Solution101 {
	void trackValsOnLeftSide(TreeNode* node, std::list<int>* lst) {
		if (node->left == nullptr || node->right == nullptr) {
			if (node->left == nullptr && node->right == nullptr) {
				lst->push_back(node->val);
				return;
			}

			if (node->left != nullptr)
				trackValsOnLeftSide(node->left, lst);
			else
				lst->push_back(-2800);

			if (node->right != nullptr)
				trackValsOnLeftSide(node->right, lst);
			else
				lst->push_back(-2800);

			lst->push_back(node->val);

			return;
		}

		trackValsOnLeftSide(node->left, lst);
		trackValsOnLeftSide(node->right, lst);

		lst->push_back(node->val);
	}

	void trackValsOnRightSide(TreeNode* node, std::list<int>* lst) {
		if (node->left == nullptr || node->right == nullptr) {
			if (node->left == nullptr && node->right == nullptr) {
				lst->push_back(node->val);
				return;
			}

			if (node->right != nullptr)
				trackValsOnRightSide(node->right, lst);
			else
				lst->push_back(-2800);

			if (node->left != nullptr)
				trackValsOnRightSide(node->left, lst);
			else
				lst->push_back(-2800);

			lst->push_back(node->val);

			return;
		}

		trackValsOnRightSide(node->right, lst);
		trackValsOnRightSide(node->left, lst);

		lst->push_back(node->val);
	}

	bool isSymmetric(TreeNode* root) {
		std::list<int> lhs;
		std::list<int> rhs;

		if (root->left != nullptr)
			trackValsOnLeftSide(root->left, &lhs);
		if (root->right != nullptr)
			trackValsOnRightSide(root->right, &rhs);

		return lhs == rhs;
	}
};

using namespace Solution101;

#endif
