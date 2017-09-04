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
        FileOutput();
        FileOutput(const string nome_file);
        virtual ~FileOutput();
        FileOutput(const FileOutput& to_copy);
        const bool apriFileOutput();
        void chiudiFileOutput();
        virtual void scriviFileOutput();
    protected:
        ofstream _file_output;

    private:
        string _nome_file;
};

#endif // FILEOUTPUT_H
