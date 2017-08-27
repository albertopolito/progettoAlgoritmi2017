#ifndef FILEINPUT_H
#define FILEINPUT_H
#include <string>
#include<vector>
#include<algorithm>
#include<fstream>
using namespace std;

class FileInput
{
    public:
        FileInput(const string nome_file);
        virtual ~FileInput(); //chiude il file
        FileInput(const FileInput &other);

        bool leggiFile(); //la vorrei virtuale
    protected:
        fstream _file_input;
        bool apriFileInput();//se errore 1 altrimenti 0
    private:
        string _nome_file;
};

#endif // FILEINPUT_H
