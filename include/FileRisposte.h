#ifndef FILERISPOSTE_H
#define FILERISPOSTE_H
#include"FileInput.h"
#include"VocabolarioId.h"
#include <string>
#include<vector>
#include<algorithm>
#include<iostream>
#include<sstream>
using namespace std;
template<class R>
class FileRisposte : public FileInput
{
    public:
        FileRisposte(const string nome_file);
        virtual ~FileRisposte();
        FileRisposte(const FileRisposte& other);
        bool leggiFile();
        string getRispostaDaId(const R id);
    protected:

    private:
        VocabolarioId<R> _vocabolario_risposte;
};

template<class R>
FileRisposte<R>::FileRisposte(const string nome_file): FileInput(nome_file)
{
    //ctor
    apriFileInput();
}

template<class R>
FileRisposte<R>::~FileRisposte()
{
    //dtor
}

template<class R>
FileRisposte<R>::FileRisposte(const FileRisposte& other): FileInput(other)
{
    //copy ctor
}

template<class R>
bool FileRisposte<R>::leggiFile()
{
    R id_risposta;
    string testo_risposta;

    if(!_file_input.is_open()){
        cerr << "Error " << _nome_file << " : file not open" << endl;
        return 1;
    }else if(_file_input.eof()){
        chiudiFileInput();
        return 1;
    }else{
        while(!_file_input.eof()){
            testo_risposta.clear();
            if(_file_input>>id_risposta && (getline(_file_input, testo_risposta))!= NULL){
                _vocabolario_risposte.setNuovoElemento(id_risposta, testo_risposta);
            } else {
                chiudiFileInput();
                return 1;
            }
        }
    }
    chiudiFileInput();
    return 0;
}

template<class R>
string FileRisposte<R>::getRispostaDaId(const R id)
{
    return _vocabolario_risposte.getIdDaStriga(id);
}


#endif // FILERISPOSTE_H
