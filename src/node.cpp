#include "../include/node.h"

std::ostream &operator<<(std::ostream &stream, Node &node)
{
    std::stringstream ss;
    ss << node.get_frequency();

    std::string text = "(";
    text += node.get_symbol();
    text += ",";
    text += ss.str();
    text += ")";

    return stream << text;
}

Node::Node()
{
    this->symbol = '\0';
    this->frequency = 0;
    this->left = NULL;
    this->right = NULL;
}

Node::Node(char symbol, int frequency)
{
    this->symbol = symbol;
    this->frequency = frequency;
    this->prev = NULL;
    this->next = NULL;
    this->left = NULL;
    this->right = NULL;
}

Node::Node(char symbol, int frequency, Node *prev, Node *next)
{
    this->symbol = symbol;
    this->frequency = frequency;
    this->prev = prev;
    this->next = next;
    this->left = NULL;
    this->right = NULL;
}

Node::Node(int frequency, Node *left, Node *right)
{
    this->symbol = '\0';
    this->frequency = frequency;
    this->prev = NULL;
    this->next = NULL;
    this->left = left;
    this->right = right;
}

Node::Node(char symbol, int frequency, Node *prev, Node *next, Node *left, Node *right)
{
    this->symbol = symbol;
    this->frequency = frequency;
    this->prev = prev;
    this->next = next;
    this->left = left;
    this->right = right;
}

// Methods.

void Node::set_symbol(char symbol)
{
    this->symbol = symbol;
}

char Node::get_symbol()
{
    return this->symbol;
}

void Node::set_frequency(int frequency)
{
    this->frequency = frequency;
}

int Node::get_frequency()
{
    return this->frequency;
}

void Node::set_left_node(Node *left)
{
    this->left = left;
}

Node *Node::get_left_node()
{
    return this->left;
}

void Node::set_right_node(Node *right)
{
    this->right = right;
}

Node *Node::get_right_node()
{
    return this->right;
}

void Node::set_previous_node(Node *prev)
{
    this->prev = prev;
}

Node *Node::get_previus_node()
{
    return this->prev;
}

void Node::set_next_node(Node *next)
{
    this->next = next;
}

Node *Node::get_next_node()
{
    return this->next;
}

void Node::print_node()
{
    std::cout << *this;
}

bool Node::is_leaf()
{
    return this->left == NULL && this->right == NULL;
}