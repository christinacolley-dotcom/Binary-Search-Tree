#ifndef BSTREE_H
#define BSTREE_H
#include <iostream>
struct Node {
          int value;
          Node* left;
          Node* right;
          int search_time; //see the problem description
          // Node constructor
          Node(int val = 0, Node* l = nullptr, Node* r = nullptr)
                : value(val), left(l), right(r), search_time(1) {}
};
    struct BSTree
    {
    public:
          BSTree();
          BSTree(const BSTree& other);
          // move constructor
          BSTree(BSTree&& other);
          // copy assignment
          BSTree& operator=(const BSTree& other);
          // move assignment
          BSTree& operator=(BSTree&& other);
          ~BSTree();
          const Node* get_root() const { return root; }
          const int get_size() const { return size; }
          Node* insert(int obj);
          Node* search(int obj);
          void update_search_times();
          float get_average_search_time();
          void inorder(std::ostream& out);
          void print_level_by_level(std::ostream& out);
          void RemoveSubtree(Node* Ptr);
          Node* newNode(int data);
    private:
          int size;
Node* root;
          int get_total_search_time(Node* node);
          void copy_helper(Node*& newNode, const Node* sourceNode);
          Node* CopyTree(Node*& newNode, const Node* sourceNode);
    };

    std::ostream& operator<<(std::ostream& out, Node node);

    std::ostream& operator<<(std::ostream& out, BSTree& tree);

    std::istream& operator>>(std::istream& in, BSTree& tree);
#endif