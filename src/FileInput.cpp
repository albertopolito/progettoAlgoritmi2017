#include "FileInput.h"
#include <string>
#include<vector>
#include<algorithm>
#include<fstream>
FileInput::FileInput(const string nome_file)
{
    //ctor
    _nome_file = nome_file;
}

FileInput::~FileInput()
{
    //dtor
    _file_input.close();
}

FileInput::FileInput(const FileInput &other)
{
    //copy ctor
    _nome_file = other._nome_file;
}

//da guardare
bool FileInput::apriFileInput()
{
    _file_input.open(_nome_file.c_str(), std::fstream::in);
    return 0;
}
