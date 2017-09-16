#ifndef FILEINPUT_H
#define FILEINPUT_H
#include <string>
#include<fstream>
using namespace std;
///classe generale da cui si derivano quelle per i file input
class FileInput
{
    public:
        FileInput();
        virtual ~FileInput();
        virtual const bool leggiFile(const string& nome_file);
    protected:
        ifstream _file_input;
        const bool apriFileInput(const string& nome_file);
        void chiudiFileInput();
    private:
};

#endif // FILEINPUT_H
