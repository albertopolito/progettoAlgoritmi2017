#ifndef FILETEST_H
#define FILETEST_H
#include <string>
#include<vector>
#include<algorithm>
#include "FileOutput.h"
#include "FileInput.h"
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
        FileTest(const string nome_file):FileInput(nome_file),FileOutput(nome_file)
        {
            _iteratore_delle_risposte=_domande_con_risposta.begin();
        };
        virtual ~FileTest();
        //aggiungere copy ctr
        T leggiDomandaCorrente();//leggi la domanda puntata dall'iteratore
        void leggiProssimaDomanda();//aumenta l'iteratore di 1
        R getRispostaDaDomanda(const T id_domanda);
        bool hoFinitoLeDomande();
        void immettiNuovoElemento(const T id_domanda,const R id_risposta);//quando scrivi i dati scrivili in ordine di arrivo così le domande e le risposte sono già ordinate
        void scriviFileOutput();
        bool leggiFile();
    protected:

    private:
        vector<test> _domande_con_risposta;
        typename vector<test> :: iterator _iteratore_delle_risposte;

};

#endif // FILETEST_H
