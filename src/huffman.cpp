#include "../include/huffman.h"

Huff::Huff()
{
    this->list = NULL;
}

void Huff::compress(string filename, std::string outfile)
{
    string text = this->read(filename);
    List *list = this->build_list(text);
    Node *node = this->build_trie(list);
    string *codes = this->build_code(node);
    string trie = this->transform(node);
    string bitflow = this->transform(text, codes);
    this->write(get_file_extension(filename, find(filename, '.')), trie, text.size(), bitflow, outfile);
}

void Huff::decompress(string filename, string outfile)
{
    string text = this->read(filename);
    string ext = this->read_file_extension(&text);
    Node *root = this->read_trie(&text);
    int size = this->read_size(&text);
    string bitflow = this->bytes_to_bit_flow(text);
    string translated = this->translate(bitflow, size, root);
    this->write(translated, outfile);
}

// Private.

/**
* Read the content of the file.
* 
* @param filename The filename.
* @return The content of the file.
*/
string Huff::read(string filename)
{
    ifstream source;
    source.open(filename.c_str());

    if (!source)
    {
        cout << "File not found!\n";
        exit(-1);
    }

    if (!source.is_open())
    {
        cout << "It was not possible open the file!\n";
        exit(-1);
    }

    stringstream buffer;
    buffer << source.rdbuf();

    source.close();

    return buffer.str();
}

/**
* Build a string list based on character occurrence.
* 
* @param text The source text.
* @return The list.
*/
List *Huff::build_list(string text)
{
    List *list = new List();

    for (int i = 0; i < text.size(); ++i)
    {
        list->add(text[i]);
    }

    return list;
}

string Huff::build_bytes(string bitflow)
{
    unsigned char byte = 0;
    unsigned int currbit = 0;
    std::string output = "";

    while (currbit < bitflow.size())
    {
        for (int i = 0; i < BYTE_SIZE;)
        {
            if (bitflow[currbit] == '1')
            {
                byte = byte << 1;
                byte = byte | 1;
            }
            else if (bitflow[currbit] == '0')
            {
                byte = byte << 1;
            }

            ++currbit;
            ++i;

            if (currbit >= bitflow.size())
            {
                int remaind = 8 - i;

                for (int j = 0; j < remaind; ++j)
                {
                    byte = byte << 1;
                }

                break;
            }
        }

        output += byte;
        byte = 0;
    }

    return output;
}

Node *Huff::build_trie(List *list)
{
    if (list == NULL)
    {
        throw "Argument is null!";
    }

    if (list->get_length() == 0)
    {
        throw "List is empty!";
    }

    while (list->get_length() > 1)
    {
        Node *first = list->get_first();
        Node *second = list->get_first()->get_next_node();

        int frequency = first->get_frequency() + second->get_frequency();

        Node *parent = new Node(frequency, first, second);

        list->remove(first);
        list->remove(second);
        list->add(parent);
    }

    return list->get_first();
}

string *Huff::build_code(Node *root)
{
    string *codes = new string[ASCII];
    this->build_code(codes, root, "");
    return codes;
}

void Huff::build_code(string *codes, Node *node, string code)
{
    if (node->is_leaf())
    {
        codes[node->get_symbol()] = code;
        return;
    }

    this->build_code(codes, node->get_left_node(), code + '0');
    this->build_code(codes, node->get_right_node(), code + '1');
}

void Huff::print_trie(Node *root)
{
    if (root->is_leaf())
    {
        root->print_node();
        return;
    }

    this->print_trie(root->get_left_node());
    this->print_trie(root->get_right_node());
}

void Huff::print_code(string *codes)
{
    cout << "Symbol  Bits\n";

    for (int i = 0; i < ASCII; ++i)
    {
        if (codes[i] != "")
        {
            char c = (char)i;
            cout << "    " << c << "  " << codes[i] << "\n";
        }
    }
}

void Huff::write(string text, string filename)
{
    ofstream target;
    target.open(filename.c_str());
    target << text;
    target.close();
}

void Huff::write(string fileext, string trie, int size, string bitflow, string filename)
{
    string output = fileext + ",";

    // Save file extension.
    output += trie;

    // Save size of original string.
    stringstream ss;
    ss << size;
    output += ss.str();

    // Save bitflow.
    output += build_bytes(bitflow);

    // Save on file.
    this->write(output, filename);
}

string Huff::transform(Node *node)
{
    return this->transform(node, "");
}

string Huff::transform(Node *node, string output)
{
    if (node->is_leaf())
    {
        output += '1';
        output += node->get_symbol();
        return output;
    }

    output += '0';
    output = transform(node->get_left_node(), output);
    output = transform(node->get_right_node(), output);
    return output;
}

string Huff::read_file_extension(string *text)
{
    string ext = "";

    int i;

    for (i = 0; (*text)[i] != ','; ++i)
    {
        ext += (*text)[i];
    }

    (*text).replace(0, i + 1, "");

    return ext;
}

Node *Huff::read_trie(string *text)
{
    int index = -1;
    Node *node = this->read_trie(*text, &index);
    index++;
    (*text).replace(0, index, "");
    return node;
}

Node *Huff::read_trie(string text, int *index)
{
    (*index)++;

    if (text[*index] == '1')
    {
        (*index)++;
        char symbol = text[*index];
        return new Node(symbol, 0, NULL, NULL, NULL, NULL);
    }

    return new Node('\0', 0, NULL, NULL, read_trie(text, index), read_trie(text, index));
}

int Huff::read_size(string *text)
{
    stringstream ss(*text);
    int size;

    ss >> size;
    ss.str("");
    ss.clear();

    ss << size;
    int index = ss.str().size();

    (*text) = (*text).replace(0, index, "");

    return size;
}

string Huff::transform(string text, string *table)
{
    string output = "";

    for (int i = 0; i < text.size(); ++i)
    {
        output += table[text[i]];
    }

    return output;
}

string Huff::bytes_to_bit_flow(string bytes)
{
    string bits = "";

    for (int i = 0; i < bytes.size(); ++i)
    {
        for (int j = 0; j < BYTE_SIZE; ++j)
        {
            if ((bytes[i] & 256) == 256) // compare "c" with 1000 0000
            {
                bits += '1';
            }
            else
            {
                bits += '0';
            }

            bytes[i] = bytes[i] << 1; // left shift
        }
    }

    return bits;
}

string Huff::translate(string bitflow, int size, Node *root)
{
    int bit = 0;
    string text = "";

    for (int i = 0; i < size; ++i)
    {
        Node *node = root;

        while (!node->is_leaf())
        {
            if (bitflow[bit] == '1')
            {
                node = node->get_right_node();
            }
            else
            {
                node = node->get_left_node();
            }

            ++bit;
        }

        text += node->get_symbol();
    }

    return text;
}

int Huff::find(string filename, char charact)
{
    int index = -1;

    for (int i = filename.size() - 1; i > 0; --i)
    {
        if (filename[i] == charact)
        {
            index = i;
            return index;
        }
    }

    return index;
}

string Huff::get_file_extension(string filename, int index)
{
    if (index != -1)
    {
        filename.replace(0, index + 1, "");
    }

    return filename;
}

string Huff::get_file_without_extension(string filename, int index)
{
    if (index != -1)
    {
        filename.replace(index, filename.size() - 1, "");
    }

    return filename;
}