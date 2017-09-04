#ifndef FILEINPUT_H
#define FILEINPUT_H
#include <string>
#include<fstream>
using namespace std;

class FileInput
{
    public:
        FileInput();
        virtual ~FileInput(); //chiude il file se ancora aperto
        FileInput(const FileInput& to_copy);
        virtual const bool leggiFile();
    protected:
        ifstream _file_input;
        bool apriFileInput(const string nome_file);//se errore 1 altrimenti 0
        void chiudiFileInput();//chiude il file se ancora aperto
    private:
};

#endif // FILEINPUT_H
