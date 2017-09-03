#include "FileInput.h"
#include <string>
#include<vector>
#include<algorithm>
#include<fstream>
using namespace std;

FileInput::FileInput(const string nome_file)
{
    _nome_file=nome_file;
}

FileInput::~FileInput()
{
    chiudiFileInput();
}

FileInput::FileInput(const FileInput& to_copy)
{
    this->_nome_file=to_copy._nome_file;
    if(!to_copy._file_input.is_open())
    {
        this->_file_input.open(this->_nome_file.c_str());
    }
}

bool FileInput::apriFileInput()
{
    _file_input.open(_nome_file.c_str());
    return !_file_input.is_open();
}

void FileInput::chiudiFileInput()
{
    if(_file_input.is_open())
    {
        _file_input.close();
    }
}
