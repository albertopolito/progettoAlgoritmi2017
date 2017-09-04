#include "FileOutput.h"
#include <string>
#include<vector>
#include<algorithm>
#include<fstream>
using namespace std;

FileOutput::FileOutput()
{
    //ctor
}
FileOutput::FileOutput(const string nome_file)
{
    _nome_file=nome_file;
}

FileOutput::~FileOutput()
{
    chiudiFileOutput();
}

FileOutput::FileOutput(const FileOutput& to_copy)
{
    this->_nome_file=to_copy._nome_file;
    if(!to_copy._file_output.is_open())
    {
        this->_file_output.open(this->_nome_file.c_str());
    }
}

void FileOutput::scriviFileOutput()
{
    //copy ctor
}

const bool FileOutput::apriFileOutput()
{
    _file_output.open(_nome_file.c_str());
    if(_file_output.is_open())
    {
        return 0;
    }else{
        return 1;
    }
}

void FileOutput::chiudiFileOutput()
{
    if(_file_output.is_open())
    {
        _file_output.close();
    }
}
