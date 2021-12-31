#ifndef LIST
#define LIST
#include "./node.h"

class List
{
public:
    List();

    ~List();

    // Methods.
    void add(char symbol);
    void add(Node *node);
    void remove(Node *node);
    bool is_empty();
    void print();

    // Getters and Setters.
    Node *get_first();
    Node *get_last();
    Node *get_node(char symbol);
    int get_length();

private:
    // Attributes.
    Node *first;
    Node *last;
    int length;

    // Methods.
    void shift(Node *node, Node *other);
    void sort(Node *node);
};

#endif