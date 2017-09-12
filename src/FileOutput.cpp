#include "FileOutput.h"
#include <string>
#include<fstream>
using namespace std;

FileOutput::FileOutput()
{
    //ctor
}

FileOutput::~FileOutput()
{
    chiudiFileOutput();
}


void FileOutput::scriviFileOutput()
{
    //copy ctor
}

const bool FileOutput::apriFileOutput(const string nome_file)
{
    _file_output.open(nome_file.c_str());
    return (!_file_output.is_open()||!_file_output.good());
}

void FileOutput::chiudiFileOutput()
{
    if(_file_output.is_open())
    {
        _file_output.close();
    }
}
