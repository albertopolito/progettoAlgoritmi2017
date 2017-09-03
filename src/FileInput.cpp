#include "FileInput.h"
#include <string>
#include<vector>
#include<algorithm>
#include<fstream>
FileInput::FileInput(const string nome_file)
{
    _nome_file=nome_file;
}

FileInput::~FileInput()
{
    //dtor
}

FileInput::FileInput(const FileInput& to_copy)
{
    this->_nome_file=to_copy._nome_file;
}


//da guardare
bool FileInput::apriFileInput()
{

}

void FileInput::chiudiFileInput()
{

}
