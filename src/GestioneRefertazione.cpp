#include "GestioneRefertazione.h"
#include"FileRisposte.h"
#include"FileDomande.h"
#include"FileStart.h"
#include"FileTest.h"
#include"FileLog.h"
using namespace std;

template<class T, class R>
GestioneRefertazione<T,R>::GestioneRefertazione(string nome_file_risposte, string nome_file_domande, string nome_file_start, string nome_file_test)
{
    _risposte(nome_file_risposte);
    _domande(nome_file_domande);
    _start(nome_file_start);
    _test(nome_file_test);
    _iteratore_delle_domande_da_porre=_domande_da_porre.begin();
}

template<class T, class R>
GestioneRefertazione<T,R>::GestioneRefertazione(const GestioneRefertazione& to_copy)
{

}

template<class T, class R>
GestioneRefertazione<T,R>::~GestioneRefertazione()
{
    //dtor
}

template<class T, class R>
const vector<bool> GestioneRefertazione<T,R>:: analisiSintattica()
{

}

template<class T, class R>
const bool GestioneRefertazione<T,R>:: analisiSemantica()
{

}

template<class T, class R>
void GestioneRefertazione<T,R>:: daFileDiTestAFileDiLog(const string nome_file_log)
{

}

/*template<class T, class R>
const struct domanda_risposte GestioneRefertazione<T,R>:: prossimaDomanda()
{

}*/

template<class T, class R>
void GestioneRefertazione<T,R>:: setRisposta(string risposta)
{

}

template<class T, class R>
const bool GestioneRefertazione<T,R>:: fineDomande()
{
    if(_iteratore_delle_domande_da_porre=_domande_da_porre.end()&&_start.domandeFinite())
    {
        return 1;
    }else{
        return 0;
    }
}
