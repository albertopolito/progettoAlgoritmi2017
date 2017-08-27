#ifndef GESTIONEREFERTAZIONE_H
#define GESTIONEREFERTAZIONE_H
#include"FileRisposte.h"
#include"FileDomande.h"
#include"FileStart.h"
#include"FileTest.h"
#include"FileLog.h"
using namespace std;

template<class T, class R>
class GestioneRefertazione
{
    struct domanda_rispote
    {
        string domanda;
        vector<string> risposte;
    };
    public:
        GestioneRefertazione(const string nome_file_risposte,const string nome_file_domande,const string nome_file_start,const string nome_file_test);
        GestioneRefertazione(const GestioneRefertazione& to_copy);
        virtual ~GestioneRefertazione();
        const vector<bool> analisiSintattica();
        const bool analisiSemantica();
        void daFileDiTestAFileDiLog(const string nome_file_log);
        const struct domanda_risposte prossimaDomanda();
        void setRisposta(string risposta);
        const bool fineDomande();
    protected:

    private:
        FileRisposte<R> _risposte;
        FileDomande<T,R> _domande;
        FileStart<T> _start;
        FileTest<T,R> _test;
        vector<domanda_rispote> _domande_da_porre;
        typename vector<domanda_rispote>:: iterator _iteratore_delle_domande_da_porre;
};

#endif // GESTIONEREFERTAZIONE_H
