#include "../include/main.h"

int main(int argc, char *argv[])
{

    Huff *huff = new Huff();

    char command = argv[CLI_COMMAND_POSITION][0];
    switch (command)
    {
    case CLI_COMMAND_TO_COMPRESS:
        cout << "COMPRESS" << endl;
        huff->compress(argv[CLI_INPUT_FILE_POSITION], argv[CLI_OUTPUT_FILE_POSITION]);
        break;
    case CLI_COMMAND_TO_DECOMPRESS:
        cout << "DECOMPRESS" << endl;
        huff->decompress(argv[CLI_INPUT_FILE_POSITION], argv[CLI_OUTPUT_FILE_POSITION]);
        break;
    default:
        cout << "Comando inválido!" << endl;
        exit(EXIT_FAILURE);
        break;
    }
}