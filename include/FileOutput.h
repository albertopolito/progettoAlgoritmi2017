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
        const bool apriFileOutput(const string nome_file);
        void chiudiFileOutput();
        virtual void scriviFileOutput();
    protected:
        ofstream _file_output;
    private:
        string _nome_file;
};

#endif // FILEOUTPUT_H
