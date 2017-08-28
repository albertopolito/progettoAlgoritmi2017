#include "FileInput.h"
#include <string>
#include<vector>
#include<algorithm>
#include<fstream>
#include<iostream>
FileInput::FileInput(const string nome_file)
{
    //ctor
    _nome_file = nome_file;
    cout << "call FileInput" << endl;
}

FileInput::~FileInput()
{
    //dtor
    _file_input.close();
    cout << "FileInput dtor" << endl;
}

FileInput::FileInput(const FileInput &other)
{
    //copy ctor
    _nome_file = other._nome_file;
}

bool FileInput::leggiFile()
{
    return 0;
}

bool FileInput::apriFileInput()
{
    _file_input.open(_nome_file.c_str(), std::fstream::in);
    if(!_file_input.is_open())
    {
        cerr << "Error: file " << _nome_file << endl;
        return 1;
    } else
    {
        return 0;
    }
}
