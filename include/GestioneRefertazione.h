#ifndef GESTIONEREFERTAZIONE_H
#define GESTIONEREFERTAZIONE_H
#include <string>
#include<vector>
#include<algorithm>
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
        GestioneRefertazione(string nome_file_risposte, string nome_file_domande, string nome_file_start, string nome_file_test);
        virtual ~GestioneRefertazione();
        vector<bool> analisiSintattica();
        bool analisiSemantica();
        void daFileDiTestAFileDiLog(string nome_file_log);
        struct domanda_risposte prossimaDomanda();
        void setRisposta(string risposta);
        bool fineDomande();
    protected:

    private:
        string _nome_file_risposte;
        string _nome_file_domande;//nome file
        string _nome_file_start;
        string _nome_file_test;
        FileRisposte<R> _risposte=_nome_file_risposte;
        FileDomande<T,R> _domande=_nome_file_domande;
        FileStart<T> _start=_nome_file_start;
        FileTest<T,R> _test=_nome_file_test;
        vector<domanda_rispote> _domande_da_porre;
};

#endif // GESTIONEREFERTAZIONE_H
