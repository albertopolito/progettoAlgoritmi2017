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
            if(!apriFileInput())
            {
                _errore_lettura_file=leggiFile();
            }else{
                _errore_lettura_file=1;
            }
        };
        virtual ~FileStart();
        ///ritorna il valore 1 se ho un errore in lettura del file altrimenti 0
        const bool getErroreInLettura();
        const T getDomandaObbligatoria();
        const bool finitoDomandeObbligatorie();
    protected:

    private:
        const vector<T> _domande_obbligatorie;
        const bool leggiFile();
        bool _errore_lettura_file;
};

#endif // FILESTART_H
