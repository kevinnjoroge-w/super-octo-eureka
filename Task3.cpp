#include <iostream>
using namespace std;

// (i) Define Node class
class Node {
public:
    int Data;    // Integer data
    Node* Next;  // Pointer to next node
};

int main() {
    // (ii) Create node instance
    Node node1;
    
    // (iii) Declare and assign head pointer
    Node* head = &node1;
    
    // (iv) Assign integer value
    node1.Data = 42;  // Example value
    
    // Verify the implementation
    cout << "Node data: " << head->Data << endl;
    cout << "Next pointer: " << head->Next << endl;
    
    return 0;
}
