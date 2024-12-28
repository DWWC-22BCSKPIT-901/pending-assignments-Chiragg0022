#include <iostream>
using namespace std;

// Definition for a Node.
struct Node {
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() : val(0), left(nullptr), right(nullptr), next(nullptr) {}
    Node(int _val) : val(_val), left(nullptr), right(nullptr), next(nullptr) {}
    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};

class Solution {
public:
    Node* connect(Node* root) {
        if (!root) return nullptr;

        Node* levelStart = root; // Start with the root node

        while (levelStart->left) { // While there are levels to process
            Node* current = levelStart;

            while (current) {
                // Connect left child to right child
                current->left->next = current->right;

                // Connect right child to the next node's left child (if exists)
                if (current->next) {
                    current->right->next = current->next->left;
                }

                // Move to the next node in the current level
                current = current->next;
            }

            // Move to the next level
            levelStart = levelStart->left;
        }

        return root;
    }
};

// Helper function to print the next pointers level by level
void printNextPointers(Node* root) {
    Node* levelStart = root;
    while (levelStart) {
        Node* current = levelStart;
        while (current) {
            cout << current->val << " -> ";
            if (current->next) {
                cout << current->next->val << " ";
            } else {
                cout << "NULL ";
            }
            current = current->next;
        }
        cout << endl;
        levelStart = levelStart->left;
    }
}

int main() {
    // Example tree
    Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->left->right = new Node(5);
    root->right->left = new Node(6);
    root->right->right = new Node(7);

    Solution solution;
    root = solution.connect(root);

    // Print the next pointers
    cout << "Next pointers by level:" << endl;
    printNextPointers(root);

    return 0;
}
