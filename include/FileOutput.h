#ifndef FILEOUTPUT_H
#define FILEOUTPUT_H
#include <string>
#include<vector>
#include<algorithm>
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
        fstream _file_output;
        void apriFileOutput();
    private:
        string _nome_file;
};

#endif // FILEOUTPUT_H
