#ifndef FILESTART_H
#define FILESTART_H
#include <string>
#include<vector>
#include<algorithm>
#include "FileInput.h"
using namespace std;
template<class T>

class FileStart : public FileInput
{
    public:
        FileStart(const string nome_file): FileInput(nome_file)
        {
            apriFileInput();
        };
        virtual ~FileStart();
        bool leggiFile();
        T getProssimaDomandaObbligatoria();
        bool domandeFinite();
    protected:

    private:
        vector<T> _domande_obbligatorie;
};

#endif // FILESTART_H
