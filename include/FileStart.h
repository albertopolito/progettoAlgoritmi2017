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
<<<<<<< HEAD
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
=======
        FileStart(const string nome_file);
        virtual ~FileStart();
        bool leggiFile();
        T getProssimaDomandaObbligatoria();         //NB elimina la domanda
        bool domandeFinite();                       //1 se le domande sono finite, 0 se non lo sono

        void testStampaListaDomande();
>>>>>>> umberto_toppino
    protected:

    private:
        const vector<T> _domande_obbligatorie;
        const bool leggiFile();
        bool _errore_lettura_file;
};

template<class T>
FileStart<T>::FileStart(const string nome_file): FileInput(nome_file)
{
    //ctor
    apriFileInput();
}


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
        cerr << "Errore " << _nome_file << " : file non aperto" << endl;
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
T FileStart<T>::getProssimaDomandaObbligatoria()
{
    T domanda_di_appoggio;
    domanda_di_appoggio = _domande_obbligatorie.front();
    _domande_obbligatorie.pop_front();
    return domanda_di_appoggio;
}

template<class T>
bool FileStart<T>::domandeFinite()
{
    if(_domande_obbligatorie.size()!= 0){
        return 0;
    } else {
        return 1;
    }
}

template<class T>
void FileStart<T>::testStampaListaDomande()
{
    int i;

    for(i=0; i<_domande_obbligatorie.size(); i++)
    {
        cout << _domande_obbligatorie[i] << endl;
    }
}
#endif // FILESTART_H
