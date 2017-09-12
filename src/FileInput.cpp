#include "FileInput.h"
#include <string>
#include<fstream>
using namespace std;

FileInput::FileInput()
{
}

FileInput::~FileInput()
{
    chiudiFileInput();
}


const bool FileInput::apriFileInput(const string nome_file)
{
    _file_input.open(nome_file.c_str());
    return (!_file_input.is_open()||!_file_input.good());
}

const bool FileInput:: leggiFile(const string nome_file)
{
    return 0;
}

void FileInput::chiudiFileInput()
{
    if(_file_input.is_open())
    {
        _file_input.close();
    }
}
