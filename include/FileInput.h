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
        virtual const bool leggiFile(const string nome_file);
    protected:
        ifstream _file_input;
        const bool apriFileInput(const string nome_file);//se errore 1 altrimenti 0
        void chiudiFileInput();//chiude il file se ancora aperto
    private:
};

#endif // FILEINPUT_H
