#ifndef NODE
#define NODE
#include <iostream>
#include <sstream>

class Node
{
public:
    Node();
    Node(char symbol, int frequency);
    Node(char symbol, int frequency, Node *prev, Node *next);
    Node(int frequency, Node *left, Node *right);
    Node(char symbol, int frequency, Node *prev, Node *next, Node *left, Node *right);

    ~Node();

    void set_symbol(char symbol);
    char get_symbol();

    void set_frequency(int frequency);
    int get_frequency();

    void set_previous_node(Node *prev);
    Node *get_previus_node();

    void set_next_node(Node *next);
    Node *get_next_node();

    void set_left_node(Node *left);
    Node *get_left_node();

    void set_right_node(Node *right);
    Node *get_right_node();

    void print_node();
    bool is_leaf();

    friend std::ostream &operator<<(std::ostream &stream, Node &node);

private:
    char symbol;
    int frequency;
    Node *prev;
    Node *next;
    Node *left;
    Node *right;
};
#endif