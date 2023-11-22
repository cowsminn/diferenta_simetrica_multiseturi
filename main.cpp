#include <iostream>
#include <set>
#include <algorithm>

struct Node {
    int data;
    Node* left;
    Node* right;

    explicit Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

class MultisetBST {
private:
    Node* root;

    Node* insert(Node* node, int val) {
        if (node == nullptr) {
            return new Node(val);
        }
        if (val < node->data)
            node->left = insert(node->left, val);
        else
            node->right = insert(node->right, val);
        /// in caz ca elementele sunt egale in multiset nu mai pun conditia
        /// pentru > ca sa se duca automat in dreapta
        return node;
    }

    void inorderTraversal(Node* node, std::multiset<int>& result) {
        if (node != nullptr) {
            inorderTraversal(node->left, result);
            result.insert(node->data);
            inorderTraversal(node->right, result);
        }
    }

    void destroyTree(Node* node) {
        if (node != nullptr) {
            destroyTree(node->left);
            destroyTree(node->right);
            delete node;
        }
    }

    void customSymmetricDifference(const std::multiset<int>& set1, const std::multiset<int>& set2, std::multiset<int>& result) {
        auto it1 = set1.begin();
        auto it2 = set2.begin();

        while (it1 != set1.end() && it2 != set2.end()) {
            if (*it1 < *it2) {
                result.insert(*it1);
                ++it1;
            } else if (*it2 < *it1) {
                result.insert(*it2);
                ++it2;
            } else {
                ++it1;
                ++it2;
            }
        }

        std::copy(it1, set1.end(), std::inserter(result, result.end()));
        std::copy(it2, set2.end(), std::inserter(result, result.end()));
    }

public:
    MultisetBST() : root(nullptr) {}

    void insert(int val) {
        root = insert(root, val);
    }

    std::multiset<int> symmetricDifference(MultisetBST& other) {
        std::multiset<int> result;

        std::multiset<int> thisSet;
        inorderTraversal(root, thisSet);

        std::multiset<int> otherSet;
        other.inorderTraversal(other.root, otherSet);

        customSymmetricDifference(thisSet, otherSet, result);

        return result;
    }

    ~MultisetBST() {
        destroyTree(root);
    }
};

int main() {
    MultisetBST set1, set2;

    set1.insert(1);
    set1.insert(2);
    set1.insert(2);

    set2.insert(2);
    set2.insert(3);

    std::multiset<int> result = set1.symmetricDifference(set2);

    for (auto value : result)
        std::cout << value << " ";

    return 0;
}
