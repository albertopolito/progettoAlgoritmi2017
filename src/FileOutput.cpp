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

FileOutput::~FileOutput()
{
    chiudiFileOutput();
}

FileOutput::FileOutput(const FileOutput& to_copy)
{

}

void FileOutput::scriviFileOutput()
{
    //copy ctor
}

const bool FileOutput::apriFileOutput(const string nome_file)
{
    _file_output.open(nome_file.c_str());
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
