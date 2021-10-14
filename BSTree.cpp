#include "BSTree.h" 
#include <iostream> 
#include <string> 
#include <queue> 
#include <math.h> 

using namespace std; 
/////////////////////////////////// 
// Already Implemented Functions // 
/////////////////////////////////// 
// These functions are already implemented for you. Scroll below to // see the functions that you have to implement  

BSTree::BSTree() : size(0), root(nullptr) {}

ostream& operator<<(ostream& out, BSTree& tree){
    tree.print_level_by_level(out);
    return out;
}

ostream& operator<<(ostream& out, Node& node){
    return out << node.value << "[" << node.search_time << "]";
}

istream& operator>>(istream& in, BSTree& tree){
    /*
      take input from the in stream, and build your tree
      input will look like
      4 
      2 
      6 
      1 
      3 
      5 
      7
    */
    int next;
    while(in >> next) {
        tree.insert(next);
    }
    return in;
}
// Example recursive function 
void BSTree::copy_helper(Node*& newNode, const Node* sourceNode) { //Don't copy if the node is nullptr 
if (sourceNode == nullptr) 
return; 
//Change the new node to a copy of sourceNode 
newNode = new Node(sourceNode->value); 
//Copy over the search cost 
newNode->search_time = sourceNode->search_time; 
//Copy left subtree 
if (sourceNode->left != nullptr) 
copy_helper(newNode->left, sourceNode->left); 
//Copy right subtree 
if (sourceNode->right != nullptr) 
copy_helper(newNode->right, sourceNode->right); 
} 

Node* BSTree::CopyTree(Node *& newNode, const Node * sourceNode) { 
  if (sourceNode == nullptr) 
    return nullptr; 
//Change the new node to a copy of sourceNode 
  newNode = new Node(sourceNode->value); 
//Copy over the search cost 
  newNode->search_time = sourceNode->search_time; 
//Copy left subtree 
  if (sourceNode->left != nullptr) 
    newNode->left = CopyTree(newNode->left, sourceNode->left); 
//Copy right subtree 
  if (sourceNode->right != nullptr) 
    newNode->right = CopyTree(newNode->right, sourceNode->right); 
  return newNode; 
} 

int BSTree::get_total_search_time(Node* node){
  if (node != nullptr) {
    return node->search_time + get_total_search_time(node->left) + get_total_search_time(node->right);
  }
  return 0;
}
// implemented 
float BSTree::get_average_search_time() { 
  int total_search_time = get_total_search_time(root); 
  if (total_search_time == 0) 
    return -1; 
  return ((float)total_search_time) / size; 
} 
/////////////////////////////////// 
// Functions to Implement // 
/////////////////////////////////// 
// These are the functions you should implement 
// Feel free to call the functions above or create new helper functions Node* BSTree::newNode(int data) 

//new helper function 
Node* BSTree::newNode(int data){ 
    Node* temp = new Node; 
    temp->value = data; 
    temp->left = nullptr; 
    temp->right = nullptr; 
    return temp; 
} 
// copy constructor 

BSTree::BSTree(const BSTree& other) { 
    size = other.get_size(); 
    if (other.get_root() == nullptr) 
    { 
      root = nullptr; 
    } 
    else 
    { 
      const Node* sourceNode = other.get_root(); 
      root = CopyTree(root, sourceNode); 
    } 
} 
// move constructor 
BSTree::BSTree(BSTree&& other){ 
    root = other.root; 
    size = other.get_size(); 
    other.root = nullptr; 
    other.size = 0; 
} 
//copy assignment 
BSTree& BSTree::operator=(const BSTree& other){ 
    size = other.get_size(); 
    if (this != &other) 
    { 
      if (root != nullptr) 
        { 
          RemoveSubtree(root); 
        } 
      if (other.get_root() == nullptr) 
      { 
        root = nullptr; 
      } 
      else 
    { 
        root = CopyTree(root, other.get_root()); 
    } 
  } 
  return *this; 
} 

// move assignment 
BSTree& BSTree::operator=(BSTree&& other){ 
    if (root != other.root) 
    { 
      RemoveSubtree(root); 
      root = other.root; 
      size = other.get_size(); 
      other.root = nullptr; 
      other.size = 0; 
    } 
    return *this; 
} 

void BSTree::RemoveSubtree(Node* ptr) 
{ 
    if (ptr != NULL) 
  { 
      if (ptr->left != NULL) 
  { 
        RemoveSubtree(ptr->left); 
  } 
      if (ptr->right != NULL) 
      { 
        RemoveSubtree(ptr->right); 
      } 
    delete ptr; 
  } 
} 
// destructor 
BSTree::~BSTree() { 
    RemoveSubtree(root); 
} 

Node* BSTree::insert(int obj){ 
    Node* curr; 
    Node* trailerC; 
    Node* new_node; 

    new_node = newNode(obj); 
    new_node->left = nullptr; 
    new_node->right = nullptr; 
    if (root == NULL) 
    { 
      root = new_node; 
      size++; 
    } 
    else 
    { 
      curr = root; 
    while (curr != nullptr) 
    { 
      trailerC = curr; 
      if (curr->value>obj) 
      { 
        curr = curr->left; 
      } 
      else 
      { 
        curr = curr->right; 
      } 
    } 
  if (trailerC->value > obj) 
    { 
      trailerC->left = new_node; 
      trailerC->left->search_time = trailerC->search_time + 1; 
    } 
  else 
  { 
      trailerC->right = new_node; 
      trailerC->right->search_time = trailerC->search_time + 1; 
  } 
  size++; 
  } 
return new_node; 
} 

Node* BSTree::search(int obj){ 
    Node* current; 
    if (root == NULL) 
    { 
      return 0; 
    } 
    else 
    { 
      current = root; 
    while (current != NULL) 
    { 
      if (current->value == obj) 
      { 
        break; 
      } 
      else 
      { 
      if (current->value > obj) 
      { 
        current = current->left; 
      } 
      else 
      { 
        current = current->right; 
      } 
  } 
}
}
return current; 
}


int maxD(Node* node){
    if (node == NULL) 
      return 0; 
    else 
    { 
      int lDepth = maxD(node->left); 
      int rDepth = maxD(node->right);  
    if (lDepth > rDepth) 
      return(lDepth + 1); 
    else 
      return(rDepth + 1); 
  } 
} 

void BSTree::update_search_times(){ 
    queue<Node*> q; 
    q.push(root);
    int currentL = 0; 
    int currentI = 0; 

    int height = maxD(root); 
    int currentTime = 1; 

    while (q.size() > 0) 
      { 
        if (currentL >= height)
         break; 
    Node* n = q.front(); 
    q.pop(); 
    if (n != nullptr) 
    { 
      n->search_time = currentTime; 
      q.push(n->left);
      q.push(n->right);
    } 
    else 
    { 
      q.push(nullptr); 
      q.push(nullptr); 
    } 
    currentI++; 
  if (currentI >= int(pow(float(2), float(currentL)))) 
  { 
    currentI = 0; 
    currentL++; 
    currentTime++; 
  } 
  } 
} 

string output(string orig, Node*& currentNode) { 
    if (currentNode->left != nullptr) 
    { 
      orig= output(orig, currentNode->left); } 
      orig += to_string(currentNode->value) + "[" + to_string(currentNode->search_time) + "] "; 
    if (currentNode->right != nullptr) 
    { 
      orig = output(orig, currentNode->right); 
    } 
  return orig; 
} 

void BSTree::inorder(ostream& out){ 
    if (!root) 
    { 
      return; 
    } 
    out << output("", root); 
} 

string printTree(string orig, Node*& root){ 
    queue<Node*> q; 
    q.push(root);

    int currentL = 0; 
    int currentI = 0; 
    int height = maxD(root); 

    while (q.size() > 0) 
    { 
      if (currentL >= height)
    break; 
    Node* n = q.front(); 
    q.pop(); 
    if (n != nullptr) 
    { 
      orig += to_string(n->value) + "[" + to_string(n->search_time) + "] "; 
      q.push(n->left);
      q.push(n->right);
    } 
    else 
    { 
      orig += "X "; 
      q.push(nullptr);
      q.push(nullptr);
    } 
  currentI++; 
    if (currentI >= int(pow(float(2), float(currentL)))) 
    { 
      orig+= "\n"; 
      currentI = 0; 
      currentL++; 
    } 
    } 
return orig; 
} 
void BSTree::print_level_by_level(ostream& out){ 
/* Print the tree using a BFS so that each level contains the values for a level of the tree. 
Use X to mark empty positions. 
 if our tree looks like this: 
 4 
 2 6 
1 5 7 
 9 
it should output: 

4[1] 
2[2] 6[2] 
1[3] X 5[3] 7[3] 
X X X X X X X 9[4] 
it might be helpful to do this part with the std::queue data structure. Hint: the Nth level contains 2^(N-1) nodes (with a value or with an X).  Watch out 
for nodes like the left child of 6 above, and print the descendents of an  empty 
node as also empty 
You can use the << operator to print nodes in the format shown */ 
    out << printTree("", root); 
} 
