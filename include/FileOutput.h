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
        virtual ~FileOutput();
        virtual void scriviFileOutput();
    protected:
        ofstream _file_output;
        const bool apriFileOutput(const string nome_file);
        void chiudiFileOutput();
    private:
        string _nome_file;
};

#endif // FILEOUTPUT_H
