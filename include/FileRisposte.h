#ifndef FILERISPOSTE_H
#define FILERISPOSTE_H
#include"FileInput.h"
#include"VocabolarioId.h"
#include <string>
#include<vector>
#include<algorithm>
//#include<iostream>
#include<sstream>
using namespace std;
template<class R>
class FileRisposte : public FileInput
{
    public:
        FileRisposte();
        virtual ~FileRisposte();
        FileRisposte(const FileRisposte& other);
        const string getRispostaDaId(const R id);
        const R getIdDaRisposta(const string risposta);
        const bool leggiFile(const string nome_file);
    protected:

    private:
        VocabolarioId<R> _vocabolario_risposte;
};

template<class R>
FileRisposte<R>::FileRisposte()
{

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
const bool FileRisposte<R>::leggiFile(const string nome_file)
{
    R id_risposta;
    string testo_risposta;
    if(apriFileInput(nome_file.c_str())){
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
    return _vocabolario_risposte.controlloSintattico();
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
#endif // FILERISPOSTE_H
