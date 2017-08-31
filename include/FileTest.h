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

        const T leggiDomandaCorrente();//leggi la domanda puntata dall'iteratore
        void  prossimaDomanda();//aumenta l'iteratore di 1
        const R getRispostaDaDomanda(const T id_domanda);
        const bool hoFinitoLeDomande(const bool modalita=ANALISI);
        void resettaIlPuntoDiAnalisi();
        void immettiNuovoElemento(const T id_domanda,const R id_risposta);//quando scrivi i dati scrivili in ordine di arrivo così le domande e le risposte sono già ordinate
        const bool apriInLetturaScrittura(const string nome_file, const bool modalita=LETTURA);
    protected:

    private:
        vector<test> _domande_con_risposta;
        typename vector<test>::iterator it_domande_con_risposta;
        void scriviFileOutput();
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
#endif // FILETEST_H
