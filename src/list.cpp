#include "../include/list.h"

List::List()
{
    this->first = NULL;
    this->last = NULL;
    this->length = 0;
}

void List::add(char symbol)
{
    Node *node = this->get_node(symbol);

    if (node != NULL)
    {
        node->set_frequency(node->get_frequency() + 1);
        this->sort(node);
    }
    else
    {
        node = new Node(symbol, 1);
        this->add(node);
    }
}

void List::add(Node *node)
{
    if (this->is_empty())
    {
        this->first = node;
        this->last = node;
        this->length = 1;
    }
    else
    {
        node->set_next_node(this->first);
        this->first->set_previous_node(node);
        this->first = node;
        this->length++;
        this->sort(node);
    }
}

void List::remove(Node *node)
{
    if (this->get_length() == 0)
    {
        return;
    }

    for (Node *aux = this->first; aux != NULL; aux = aux->get_next_node())
    {
        if (node == aux)
        {
            // Remove o único.
            if (this->get_length() == 1)
            {
                this->first = NULL;
                this->last = NULL;
                this->length--;
                node = NULL;
                break;
            }

            // Remove primeiro.
            if (node == this->first)
            {
                this->first = this->first->get_next_node();
                this->first->set_previous_node(NULL);
                node = NULL;
                this->length--;
                break;
            }

            // Remove último.
            if (node == this->last)
            {
                this->last = this->last->get_previus_node();
                this->last->set_next_node(NULL);
                node = NULL;
                this->length--;
                break;
            }

            // Remove no meio
            node->get_previus_node()->set_next_node(node->get_next_node());
            node->get_next_node()->set_previous_node(node->get_previus_node());
            node = NULL;
            this->length--;
            break;
        }
    }
}

Node *List::get_last()
{
    return this->last;
}

Node *List::get_first()
{
    return this->first;
}

int List::get_length()
{
    return this->length;
}

bool List::is_empty()
{
    return this->first == NULL && this->last == NULL;
}

Node *List::get_node(char symbol)
{
    for (Node *aux = this->first; aux != NULL; aux = aux->get_next_node())
    {
        if (aux->get_symbol() == symbol)
        {

            return aux;
        }
    }

    return NULL;
}

void List::shift(Node *node, Node *other)
{
    Node *beforeNode = NULL;
    Node *afterNode = NULL;
    Node *beforeOther = NULL;
    Node *afterOther = NULL;

    if (this->first == node)
    {
        this->first = other;
    }

    if (this->last == other)
    {
        this->last = node;
    }

    if (other->get_previus_node() != NULL)
    {
        beforeOther = other->get_previus_node();
    }

    if (other->get_next_node() != NULL)
    {
        afterOther = other->get_next_node();
    }

    if (node->get_previus_node() != NULL)
    {
        beforeNode = node->get_previus_node();
    }

    if (node->get_next_node() != NULL)
    {
        afterNode = node->get_next_node();
    }

    node->set_next_node(NULL);
    node->set_previous_node(NULL);
    other->set_next_node(NULL);
    other->set_previous_node(NULL);

    if (beforeOther != NULL)
    {
        if (beforeOther != node)
        {
            node->set_previous_node(beforeOther);
            beforeOther->set_next_node(node);
        }
        else
        {
            node->set_previous_node(other);
            other->set_next_node(node);
        }
    }

    if (afterOther != NULL)
    {
        node->set_next_node(afterOther);
        afterOther->set_previous_node(node);
    }

    if (beforeNode != NULL)
    {
        other->set_previous_node(beforeNode);
        beforeNode->set_next_node(other);
    }

    if (afterNode != NULL)
    {
        if (afterNode != other)
        {
            other->set_next_node(afterNode);
            afterNode->set_previous_node(other);
        }
        else
        {
            other->set_next_node(node);
            node->set_previous_node(other);
        }
    }
}

void List::print()
{
    for (Node *aux = this->get_first(); aux != NULL; aux = aux->get_next_node())
    {
        aux->print_node();

        if (aux->get_previus_node() != NULL)
        {
            std::cout << "\t\tleft: " << *aux->get_previus_node();
        }
        else
        {
            std::cout << "\t\t\t\t";
        }

        if (aux->get_next_node() != NULL)
        {
            std::cout << "\t\tright: " << *aux->get_next_node();
        }
        else
        {
            std::cout << "\t\t\t\t";
        }

        std::cout << "\n";
    }
}

void List::sort(Node *node)
{
    bool needShift = false;
    Node *aux = node;

    if (aux->get_next_node() != NULL)
    {
        while (node->get_frequency() > aux->get_next_node()->get_frequency())
        {
            needShift = true;

            aux = aux->get_next_node();

            if (aux->get_next_node() == NULL)
            {
                break;
            }
        }

        if (needShift)
        {
            this->shift(node, aux);
        }
    }
}