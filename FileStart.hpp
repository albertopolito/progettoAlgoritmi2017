#ifndef FILESTART_HPP_INCLUDED
#define FILESTART_HPP_INCLUDED
#include <string>
#include<vector>
#include<algorithm>
#include "FileInput.h"
using namespace std;
template<class T>
///classe per il file contenente la sequenza iniziale di ID
class FileStart : public FileInput
{
    public:
        FileStart();
        virtual ~FileStart();
        FileStart(const FileStart& to_copy);
        ///ritorna l'ID della prossima domanda da sottoporre
        const T getDomandaObbligatoria();
        ///controlla se ci sono altre domande da sottoporre
        const bool finitoDomandeObbligatorie();
        ///ritorna all'inizio del vettore di domande
        void resettaDomandeObbligatorie();
        ///legge da file le domande da sottoporre e le inserisce nel vettore
        const bool leggiFile(const string& nome_file);
    protected:

    private:
        ///vettore di domande e iteratore associato
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
FileStart<T>::FileStart(const FileStart& to_copy)
{
    this->_domande_obbligatorie=to_copy._domande_obbligatorie;
    this->_it_domande_obbligatorie=to_copy._it_domande_obbligatorie;
}

template<class T>
const bool FileStart<T>::leggiFile(const string& nome_file)
{
    T id_domanda;
    //controllo che il file sia leggibile e non vuoto
    if(apriFileInput(nome_file.c_str())){
        return 1;
    } else if(_file_input.eof()){
        chiudiFileInput();
        return 1;
    } else {
        //leggo tutte le domande da file e le inserisco nel vettore
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
    //ottengo la prossima domanda da porre e vado alla domanda successiva
    if(!finitoDomandeObbligatorie())
    {
        T domanda_di_appoggio=*_it_domande_obbligatorie;
        _it_domande_obbligatorie++;
        return domanda_di_appoggio;
    }else{
        return T();
    }
}

template<class T>
const bool FileStart<T>::finitoDomandeObbligatorie()
{
    //controllo se ci sono ancora domande da porre
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

#endif // FILESTART_HPP_INCLUDED
