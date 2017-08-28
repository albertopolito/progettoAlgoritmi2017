#ifndef FILEINPUT_H
#define FILEINPUT_H
#include <string>
#include<fstream>
using namespace std;

class FileInput
{
    public:
        FileInput(const string nome_file);
        virtual ~FileInput(); //chiude il file
        FileInput(const FileInput& other);

        virtual const bool leggiFile()=0; //la vorrei virtuale
    protected:
        ifstream _file_input;
        bool apriFileInput();//se errore 1 altrimenti 0
        void chiudiFileInput();
    private:
        string _nome_file;
};

#endif // FILEINPUT_H
