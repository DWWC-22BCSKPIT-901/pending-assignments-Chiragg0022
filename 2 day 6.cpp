#include <iostream>
#include <cmath> // For pow()

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    int countNodes(TreeNode* root) {
        if (!root) return 0;
        // Compute the height of the leftmost and rightmost paths
        int leftHeight = getHeight(root->left);
        int rightHeight = getHeight(root->right);

        if (leftHeight == rightHeight) {
            // Left subtree is perfect
            return (1 << leftHeight) + countNodes(root->right); // 2^leftHeight + count of right subtree
        } else {
            // Right subtree is perfect
            return (1 << rightHeight) + countNodes(root->left); // 2^rightHeight + count of left subtree
        }
    }

private:
    // Helper function to compute the height of the tree
    int getHeight(TreeNode* node) {
        int height = 0;
        while (node) {
            height++;
            node = node->left; // Traverse down the leftmost path
        }
        return height;
    }
};

int main() {
    // Build a complete binary tree
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    root->right->left = new TreeNode(6);

    // Create solution object
    Solution solution;
    int nodeCount = solution.countNodes(root);

    // Output the result
    std::cout << "Number of nodes: " << nodeCount << std::endl; // Output: 6

    return 0;
}
