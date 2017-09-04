#ifndef FILEINPUT_H
#define FILEINPUT_H
#include <string>
#include<fstream>
using namespace std;

class FileInput
{
    public:
        FileInput(const string nome_file);
        virtual ~FileInput(); //chiude il file se ancora aperto
        FileInput(const FileInput& to_copy);
        virtual const bool leggiFile()=0;
    protected:
        ifstream _file_input;
        bool apriFileInput();//se errore 1 altrimenti 0
        void chiudiFileInput();//chiude il file se ancora aperto
    private:
        string _nome_file;

};

#endif // FILEINPUT_H
