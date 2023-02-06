#include <iostream>
#include <memory>

using namespace std;

// define a structure to hold bid information
struct Bid {
    string bidId; // unique identifier
    string title;
    string fund;
    double amount;
    Bid() : amount(0.0) {}
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
    unique_ptr<Node> root = nullptr;

    void addNode(unique_ptr<Node>& node, Bid bid);
    unique_ptr<Node> removeNode(unique_ptr<Node>& node, string bidId);
    void inOrder(const unique_ptr<Node>& node) const;
    unique_ptr<Node>& searchNode(const unique_ptr<Node>& node, string bidId) const;

public:
    BinarySearchTree() = default;
    ~BinarySearchTree() = default;
    void Insert(Bid bid);
    void Remove(string bidId);
    Bid Search(string bidId);
    void InOrder() const;
};

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
            addNode(node->
