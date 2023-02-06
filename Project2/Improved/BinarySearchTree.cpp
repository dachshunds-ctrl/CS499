#include <iostream>
#include <memory>

using namespace std;

// define a structure to hold bid information
struct Bid {
    string bidId; // unique identifier
    string title;
    string fund;
    double amount;
    Bid() {
        amount = 0.0;
    }
};

// structure for tree node
struct Node {
    Bid bid; 
    unique_ptr<Node> left; // left child
    unique_ptr<Node> right; // right child
};

// Binary Search Tree class
class BinarySearchTree {
private:
    unique_ptr<Node> root;

    void addNode(unique_ptr<Node>& node, Bid bid);
    unique_ptr<Node> removeNode(unique_ptr<Node>& node, string bidId);
    void inOrder(const unique_ptr<Node>& node);
    unique_ptr<Node>& searchNode(unique_ptr<Node>& node, string bidId);

public:
    BinarySearchTree();
    ~BinarySearchTree() = default;
    void Insert(Bid bid);
    void Remove(string bidId);
    Bid Search(string bidId);
    void InOrder();
};

BinarySearchTree::BinarySearchTree() : root(nullptr) {}

void BinarySearchTree::Insert(Bid bid) {
    if (!root) {
        root = make_unique<Node>();
        root->bid = bid;
    }
    else {
        addNode(root, bid);
    }
}

void BinarySearchTree::addNode(unique_ptr<Node>& node, Bid bid) {
    if (bid.bidId < node->bid.bidId) {
        if (!node->left) {
            node->left = make_unique<Node>();
            node->left->bid = bid;
        }
        else {
            addNode(node->left, bid);
        }
    }
    else if (bid.bidId > node->bid.bidId) {
        if (!node->right) {
            node->right = make_unique<Node>();
            node->right->bid = bid;
        }
        else {
            addNode(node->right, bid);
        }
    }
}

void BinarySearchTree::Remove(string bidId) {
    if (!root) {
        return;
    }

    unique_ptr<Node>& node = searchNode(root, bidId);
    if (node) {
        node = removeNode(node, bidId);
    }
}

unique_ptr<Node> BinarySearchTree::removeNode(unique_ptr<Node>& node, string bidId) {
    if (!node) {
        return nullptr;
    }

    if (bidId < node->bid.bidId) {
        node->left = removeNode(node->left, bidId);
    }
    else if (bidId > node->bid.bidId) {
        node->right = removeNode(node->right, bidId);
    }
   
