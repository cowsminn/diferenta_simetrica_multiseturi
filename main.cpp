#include <iostream>
#include <set>
#include <algorithm>

struct Node {
    int data;
    Node* left;
    Node* right;

    explicit Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

class Multiset {
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

    void parcurgere(Node* node, std::multiset<int>& result) {
        if (node != nullptr) {
            parcurgere(node->left, result);
            result.insert(node->data);
            parcurgere(node->right, result);
        }
    }

    void destrc(Node* node) {
        if (node != nullptr) {
            destrc(node->left);
            destrc(node->right);
            delete node;
        }
    }

    void diferenta(const std::multiset<int>& set1, const std::multiset<int>& set2, std::multiset<int>& result) {
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
    Multiset() : root(nullptr) {}

    void insert(int val) {
        root = insert(root, val);
    }

    std::multiset<int> diferenta_simetrica(Multiset& other) {
        std::multiset<int> result;

        std::multiset<int> thisSet;
        parcurgere(root, thisSet);

        std::multiset<int> otherSet;
        other.parcurgere(other.root, otherSet);

        diferenta(thisSet, otherSet, result);

        return result;
    }

    ~Multiset() {
        destrc(root);
    }
};

int main() {
    Multiset set1, set2;

    set1.insert(1);
    set1.insert(2);
    set1.insert(2);
    set1.insert(3);

    set2.insert(2);
    set2.insert(3);

    std::multiset<int> result = set1.diferenta_simetrica(set2);

    for (auto value : result)
        std::cout << value << " ";

    return 0;
}
