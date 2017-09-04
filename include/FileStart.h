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
        bool leggiFile();
    protected:

    private:
        const vector<T> _domande_obbligatorie;
        bool _errore_lettura_file;
};


template<class T>
FileStart<T>::~FileStart()
{
    //dtor
}

template<class T>
bool FileStart<T>::leggiFile()
{
    T id_domanda;

    if(!_file_input.is_open()){
        return 1;
    } else if(_file_input.eof()){
        chiudiFileInput();
        return 1;
    } else {
        while(!_file_input.eof()){
            if(_file_input>>id_domanda){
                _domande_obbligatorie.push_back(id_domanda);
            } else {
                chiudiFileInput();
                return 1;
            }
        }
    }
    chiudiFileInput();
    return 0;
}

template<class T>
const T FileStart<T>::getDomandaObbligatoria()
{
    T domanda_di_appoggio;
    domanda_di_appoggio = _domande_obbligatorie.front();
    _domande_obbligatorie.pop_front();
    return domanda_di_appoggio;
}

template<class T>
const bool FileStart<T>::finitoDomandeObbligatorie()
{
    if(_domande_obbligatorie.empty()){
        return 0;
    } else {
        return 1;
    }
}

#endif // FILESTART_H
