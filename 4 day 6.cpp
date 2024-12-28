#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

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
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        // Create a map to store the indices of inorder elements
        unordered_map<int, int> inorderMap;
        for (int i = 0; i < inorder.size(); i++) {
            inorderMap[inorder[i]] = i;
        }

        // Helper function to build the tree recursively
        return build(inorder, 0, inorder.size() - 1,
                     postorder, 0, postorder.size() - 1,
                     inorderMap);
    }

private:
    TreeNode* build(vector<int>& inorder, int inStart, int inEnd,
                    vector<int>& postorder, int postStart, int postEnd,
                    unordered_map<int, int>& inorderMap) {
        if (inStart > inEnd || postStart > postEnd) return nullptr;

        // The last element in postorder is the root
        int rootVal = postorder[postEnd];
        TreeNode* root = new TreeNode(rootVal);

        // Find the index of the root in inorder
        int rootIndex = inorderMap[rootVal];
        int leftSubtreeSize = rootIndex - inStart;

        // Recursively build the left and right subtrees
        root->left = build(inorder, inStart, rootIndex - 1,
                           postorder, postStart, postStart + leftSubtreeSize - 1,
                           inorderMap);
        root->right = build(inorder, rootIndex + 1, inEnd,
                            postorder, postStart + leftSubtreeSize, postEnd - 1,
                            inorderMap);

        return root;
    }
};

// Function to print the tree in inorder for verification
void printInorder(TreeNode* root) {
    if (!root) return;
    printInorder(root->left);
    cout << root->val << " ";
    printInorder(root->right);
}

int main() {
    // Example input
    vector<int> inorder = {9, 3, 15, 20, 7};
    vector<int> postorder = {9, 15, 7, 20, 3};

    Solution solution;
    TreeNode* root = solution.buildTree(inorder, postorder);

    // Print the inorder traversal of the constructed tree
    cout << "Inorder Traversal of Constructed Tree: ";
    printInorder(root);
    cout << endl;

    return 0;
}
