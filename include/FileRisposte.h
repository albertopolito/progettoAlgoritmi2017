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
        ///ritorna il valore 1 se ho un errore in lettura del file altrimenti 0
        const bool getErroreInLettura();
        const string getRispostaDaId(const R id);
        const R getIdDaRisposta(const string risposta);
    protected:

    private:
        VocabolarioId<R> _vocabolario_risposte;
        ///variabile di errore
        bool _errore_lettura_file;
        const bool leggiFile();
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
const bool FileRisposte<R>::leggiFile()
{
    R id_risposta;
    string testo_risposta;

    if(apriFileInput()){
        _errore_lettura_file=1;
        return 1;
    }else if(_file_input.eof()){
        chiudiFileInput();
        _errore_lettura_file=1;
        return 1;
    }else{
        while(!_file_input.eof()){
            testo_risposta.clear();
            if(_file_input>>id_risposta && (getline(_file_input, testo_risposta))!= NULL){
                _vocabolario_risposte.setNuovoElemento(id_risposta, testo_risposta);
            } else {
                chiudiFileInput();
                _errore_lettura_file=1;
                return 1;
            }
        }
    }
    chiudiFileInput();
    _errore_lettura_file=_vocabolario_risposte.controlloSintattico();
    return _errore_lettura_file;
}

template<class R>
const string FileRisposte<R>::getRispostaDaId(const R id)
{
    return _vocabolario_risposte.getStringaDaId(id);
}

template<class R>
const R FileRisposte<R>:: getIdDaRisposta(const string risposta)
{
    return _vocabolario_risposte.getIdDaStriga(risposta);
}

template<class R>
const bool FileRisposte<R>:: getErroreInLettura()
{
    return _errore_lettura_file;
}
#endif // FILERISPOSTE_H
