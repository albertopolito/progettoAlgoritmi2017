#ifndef FILETEST_H
#define FILETEST_H
#include <string>
#include<vector>
#include<algorithm>
#include "FileOutput.h"
#include "FileInput.h"
///modalità apertura file
#define LETTURA 0
#define SCRITTURA 1
///modalità di lettura delle risposte
#define ANALISI 0
#define FUNZIONAMENTO 1
///modalità di immissione dei dati
#define DA_FUNZIONAMENTO 1
#define DA_FILE 0
using namespace std;

template<class T, class R>
class FileTest : public FileInput , FileOutput
{
    struct test {
        R id_risposta;
        T id_domanda;
        bool ho_risposto;
    };
    public:
        FileTest();
        virtual ~FileTest();
        //aggiungere copy ctr
        const bool apriInLetturaScrittura(const string nome_file, const bool modalita=LETTURA);
        const T leggiDomandaCorrente();//leggi la domanda puntata dall'iteratore
        void  prossimaDomanda();//aumenta l'iteratore di 1
        const R getRispostaDaDomanda(const T id_domanda,const bool modalita=ANALISI);
        const bool hoGiaRisposto(const T id_domanda);
        const bool hoFinitoLeDomande(const bool modalita=ANALISI);
        void resettaIlPuntoDiAnalisi();
        void immettiNuovoElemento(const T id_domanda,const R id_risposta, const bool modalita_scrittura_in_struttura_dati=DA_FILE);
        void scriviFileOutput();
    protected:

    private:
        vector<test> _domande_con_risposta;
        typename vector<test>::iterator _it_domande_con_risposta;
        const bool leggiFile();
};

template<class T, class R>
FileTest<T,R>::FileTest()
{
    resettaIlPuntoDiAnalisi();
}

template<class T, class R>
const bool  FileTest<T,R>:: apriInLetturaScrittura(const string nome_file, const bool modalita)
{
    if(modalita)
    {
        FileOutput(nome_file);
        return apriFileOutput();
    }else{
        FileInput(nome_file);
        return (apriFileInput()||leggiFile());
    }
}

template<class T, class R>
const T FileTest<T,R>:: leggiDomandaCorrente()
{
    if(*_it_domande_con_risposta!=_domande_con_risposta.end())
    {
        return test(*_it_domande_con_risposta).id_domanda;
    }else{
        return T();
    }
}

template<class T, class R>
void FileTest<T,R>:: prossimaDomanda()
{
    if(_it_domande_con_risposta!=_domande_con_risposta.end())
        _it_domande_con_risposta++;
}

template<class T, class R>
const R FileTest<T,R>::getRispostaDaDomanda(const T id_domanda, const bool modalita)
{

}

template<class T, class R>
const bool FileTest<T,R>::hoGiaRisposto(const T id_domanda)
{

}

template<class T, class R>
const bool FileTest<T,R>::hoFinitoLeDomande(const bool modalita)
{
    if(modalita==FUNZIONAMENTO)
    {
        typename vector<test>::iterator it_domande;
        for(it_domande=_domande_con_risposta.begin();it_domande!=_domande_con_risposta.end();it_domande++)
        {
            if(!test(*it_domande).ho_risposto)
            {
                return 0;
            }
        }
        return 1;
    }else if(modalita==ANALISI)
    {
        if(_it_domande_con_risposta==_domande_con_risposta.end())
        {
            return 1;
        }else{
            return 0;
        }
    }
    return 0;
}

template<class T, class R>
void FileTest<T,R>::resettaIlPuntoDiAnalisi()
{
   _it_domande_con_risposta=_domande_con_risposta.begin();
}

#endif // FILETEST_H
