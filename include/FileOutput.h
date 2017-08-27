#ifndef FILEOUTPUT_H
#define FILEOUTPUT_H
#include <string>
#include<fstream>
using namespace std;

class FileOutput
{
    public:
        FileOutput(const string nome_file);
        virtual ~FileOutput();
        FileOutput(const FileOutput& other);
        virtual void scriviFileOutput()=0;
    protected:
        ofstream _file_output;
        void apriFileOutput();
        void chiudiFileOutput();
    private:
        string _nome_file;
};

#endif // FILEOUTPUT_H
