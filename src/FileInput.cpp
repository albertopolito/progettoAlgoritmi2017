#include "FileInput.h"
#include <string>
#include<vector>
#include<algorithm>
#include<fstream>
using namespace std;

FileInput::FileInput()
{
}

FileInput::~FileInput()
{
    chiudiFileInput();
}

FileInput::FileInput(const FileInput& to_copy)
{
}

bool FileInput::apriFileInput(const string nome_file)
{
    _file_input.open(nome_file.c_str());
    return !_file_input.is_open();
}

void FileInput::chiudiFileInput()
{
    if(_file_input.is_open())
    {
        _file_input.close();
    }
}
