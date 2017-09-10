#ifndef FILERISPOSTE_HPP_INCLUDED
#define FILERISPOSTE_HPP_INCLUDED
#include"FileInput.h"
#include"VocabolarioId.hpp"
#include<sstream>
using namespace std;
template<class R>
///file delle risposte
class FileRisposte : public FileInput
{
    public:
        FileRisposte();
        virtual ~FileRisposte();
        FileRisposte(const FileRisposte& other);
        ///ritorna una string contenente il testo della risposta associato al ID immesso
        const string getRispostaDaId(const R id);
        ///ritorna un ID di tipo R associato al testo della risposta immesso
        const R getIdDaRisposta(const string risposta);
        ///legge il file di risposte e crea il vocabolario di ID e testo delle risposte
        ///ritorna 1 in caso di errore di lettura del file
        const bool leggiFile(const string nome_file);
    protected:

    private:
        ///contiene tutti gli ID e it testo della risposta corrispondente
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
    //controllo che il file sia aperto correttamente e che non sia vuoto
    if(apriFileInput(nome_file.c_str())){
        return 1;
    }else if(_file_input.eof()){
        chiudiFileInput();
        return 1;
    }else{
        //leggo da file ogni ID e risposta e li aggiungo nel vocabolario
        while(!_file_input.eof()){
            testo_risposta.clear();
            if(_file_input>>id_risposta)
            {
                _file_input.ignore();
                if((getline(_file_input, testo_risposta))!= NULL)
                {
                    _vocabolario_risposte.setNuovoElemento(id_risposta, testo_risposta);
                }else{
                    chiudiFileInput();
                    return 1;
                }
            } else {

                chiudiFileInput();
                return 1;
            }
        }
    }
    chiudiFileInput();
    //controllo che il vocabolario sia corretto e ritorno il valore del controllo
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


#endif // FILERISPOSTE_HPP_INCLUDED
