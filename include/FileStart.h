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
        FileStart();
        virtual ~FileStart();
        ///ritorna il valore 1 se ho un errore in lettura del file altrimenti 0
        const T getDomandaObbligatoria();
        const bool finitoDomandeObbligatorie();
        void resettaDomandeObbligatorie();
        const bool leggiFile(const string nome_file);
    protected:

    private:
        vector<T> _domande_obbligatorie;
        typename vector<T>::iterator _it_domande_obbligatorie;
};


template<class T>
FileStart<T>::FileStart()
{
    resettaDomandeObbligatorie();
}

template<class T>
FileStart<T>::~FileStart()
{
}


template<class T>
const bool FileStart<T>::leggiFile(const string nome_file)
{
    T id_domanda;
    if(apriFileInput(nome_file.c_str())){
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
    T domanda_di_appoggio=*_it_domande_obbligatorie;
    _it_domande_obbligatorie++;
    return domanda_di_appoggio;
}

template<class T>
const bool FileStart<T>::finitoDomandeObbligatorie()
{
    if(_it_domande_obbligatorie==_domande_obbligatorie.end()){
        return 1;
    } else {
        return 0;
    }
}

template<class T>
void FileStart<T>::resettaDomandeObbligatorie()
{
    _it_domande_obbligatorie=_domande_obbligatorie.begin();
}
#endif // FILESTART_H
