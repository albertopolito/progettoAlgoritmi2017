#ifndef GESTIONEREFERTAZIONE_HPP_INCLUDED
#define GESTIONEREFERTAZIONE_HPP_INCLUDED
#include"FileRisposte.hpp"
#include"FileDomande.hpp"
#include"FileStart.hpp"
#include"FileTest.hpp"
#include"FileLog.hpp"
///modalità di lettura o scrittura del file di test
#define LETTURA 0
#define SCRITTURA 1

using namespace std;

template<class T, class R>
class GestioneRefertazione
{
    public:
        GestioneRefertazione(const string& nome_file_risposte,const string& nome_file_domande,const string& nome_file_start);
        GestioneRefertazione(const GestioneRefertazione& to_copy);
        virtual ~GestioneRefertazione();
        ///setta se il file di test viene letto o deve essere scritto
        void setModalitaDiFunzionamentoFileTest(const bool& modalita);
        ///procede con le diverse analisi e se queste vanno a buon fine inizializza il vettore delle domande da porre con le domande obbligatorie inserite nel file di start
        const bool analisiSintatticaSemanticaEdInizializzazione();
        ///apre il file di test in lettura o in scrittura  a seconda della modalità e fa i dovuti controlli
        const bool apriLetturaScritturaFileTest(const string& nome_file_test);
        ///scrive il file di log a partire dal file di test
        const bool daFileDiTestAFileDiLog(const string& nome_file_log);
        ///dà in uscita la nuova domanda da porre all'utente
        const string getNuovaDomanda() ;
        ///dà in uscita la risposta scritta nel file di test dato in lettura
        const string getRisposta();
        ///dice se sono finite le domande da porre oppure no
        const bool fineDomande();
        ///per la scrittura del file di test:

            ///dà in uscita tutte le risposte possibili
            const vector<string> getRispostePossibili();
            ///registra la risposta data se è corretta, offrendo in uscita un flag per verificare il corretto funzionamento della procedura, inoltre fa anadare avanti le domande
            const bool setRisposta(const string& risposta);
            ///quando le domande sono concluse scrive il file di test e setta la sua uscita a 0 altrimenti la setta a 1
            const bool scriviFileTest();


    protected:

    private:
        ///i diversi file di ingresso implementati come strutture dati nelle loro classi
        FileRisposte<R> _risposte;
        FileDomande<T,R> _domande;
        FileStart<T> _start;
        FileTest<T,R> _test;
        ///vettore che contiene le domade da porre in ordine
        vector<T> _domande_da_porre;
        ///flag che indica in che modalità si trova il programma, cioè se devo leggere o scrivere il file di test
        bool _modalita_di_funzionamento_per_il_file_test;
        ///errori nell'apertura dei vari file
        bool _errore_risposte;
        bool _errore_domande;
        bool _errore_start;
};
template<class T, class R>
GestioneRefertazione<T,R>::GestioneRefertazione(const string& nome_file_risposte,const string& nome_file_domande,const string& nome_file_start)
{
    //inizializzazione delle 3 classi
    _errore_risposte=_risposte.leggiFile(nome_file_risposte);
    _errore_domande=_domande.leggiFile(nome_file_domande);
    _errore_start=_start.leggiFile(nome_file_start);
}

template<class T, class R>
GestioneRefertazione<T,R>::GestioneRefertazione(const GestioneRefertazione& to_copy)
{
    this->_domande=to_copy._domande;
    this->_domande_da_porre=to_copy._domande_da_porre;
    this->_iteratore_delle_domande_da_porre=to_copy._iteratore_delle_domande_da_porre;
    this->_risposte=to_copy._risposte;
    this->_start=to_copy._start;
    this->_test=to_copy._test;
}

template<class T, class R>
GestioneRefertazione<T,R>::~GestioneRefertazione()
{
    //dtor
}

template<class T, class R>
void GestioneRefertazione<T,R>::setModalitaDiFunzionamentoFileTest(const bool& modalita)
{
    _modalita_di_funzionamento_per_il_file_test=modalita;
}

template<class T, class R>
const bool GestioneRefertazione<T,R>:: analisiSintatticaSemanticaEdInizializzazione()
{
    if(_errore_risposte||_errore_domande||_errore_start)
    {
        return 1;   //se ho un errore nella lettura dei tre file non continuo l'analisi e dò un errore
    }else{
        typename vector<R>::iterator it_risposte;

        vector<R> risposte_possibili=_domande.getTutteLeRispostePossibili();
        //guardo che gli id delle risposte che ci sono nel file delle domande sono presenti anche nel file delle risposte
        for(it_risposte=risposte_possibili.begin();it_risposte!=risposte_possibili.end();it_risposte++)
        {
            if(_risposte.getRispostaDaId(*it_risposte)=="")
            {
                return 1;
            }
        }
        //guardo che gli id delle domande obbligatorie nel file di start esistano, cioè siano contenute nel file delle domande
        _start.resettaDomandeObbligatorie();
        vector<T> domande_iniziali;
        while(!_start.finitoDomandeObbligatorie())
        {
            domande_iniziali.push_back(_start.getDomandaObbligatoria());
            if(_domande.getDomandaDaId(domande_iniziali.back())=="")
            {
                return 1;
            }
        }
        if(_domande.controlloAccodamentoDomande(domande_iniziali))
        {
            return 1;
        }
    }
    _start.resettaDomandeObbligatorie();
    //i controlli sono andati a buon fine allore inizializzo il vettore delle domande da porre con la prima domanda obbligatoria
    _domande_da_porre.push_back(_start.getDomandaObbligatoria());
    return 0;
}

template<class T, class R>
const bool  GestioneRefertazione<T,R>:: apriLetturaScritturaFileTest(const string& nome_file_test)
{
    //apre il file di test in modo opportuno, in lettura o in scrittura
    if(_test.apriInLetturaScrittura(nome_file_test, _modalita_di_funzionamento_per_il_file_test))
    {
       return 1;    //se ho un errore nell'apertura allora ritorno un errore e non continuo
    }
    //se devo leggere il file
    if(_modalita_di_funzionamento_per_il_file_test==LETTURA)
    {
        _test.resettaIlPuntoDiAnalisi();
        //lo analizzo guardando grazie al grafo inserito nel file delle domande se le risposte sono valide, se non lo sono dò errore
        while(!_test.hoFinitoLeDomande(ANALISI))
        {
            if(_domande.getDomandaDaId(_test.leggiDomandaCorrente())!="")
            {
                vector<R> risposte_valide=_domande.getRispostaDataLaDomanda(_test.leggiDomandaCorrente());

                if(find(risposte_valide.begin(),risposte_valide.end(),_test.getRispostaDaDomanda(_test.leggiDomandaCorrente()))==risposte_valide.end())
                {
                    return 1;
                }
                _test.prossimaDomanda();
            }else{
                return 1;
            }
        }
        //finchè le domande da porre non sono finite le leggo tutte in modo corretto attraverso il file delle domande
        while(!fineDomande())
        {
            if(_domande_da_porre.empty())
            {
                _domande_da_porre.push_back(_start.getDomandaObbligatoria());
            }
            T domanda_corrente=_domande_da_porre.back();
            if(domanda_corrente!=T())
            {
                vector<T> domande;
                _domande_da_porre.pop_back();
                domande=_domande.getDomandaDataRisposta(domanda_corrente,_test.getRispostaDaDomanda(domanda_corrente,FUNZIONAMENTO));
                reverse(domande.begin(),domande.end());
                for(typename vector<T>::iterator it=domande.begin();it!=domande.end();it++)
                {
                    if((*it)!=T())
                    {
                        _domande_da_porre.push_back(*it);
                    }
                }
            }
        }
        _start.resettaDomandeObbligatorie();
        _domande_da_porre.push_back(_start.getDomandaObbligatoria());
        //ritorno il parametro che mi indica se ho preso o no in considerazione tutte le righe scritte sul file di test, se non è così do in uscita un errore
        return !_test.hoFinitoLeDomande(FUNZIONAMENTO);
    }
    return 0;
}

template<class T, class R>
const bool GestioneRefertazione<T,R>:: daFileDiTestAFileDiLog(const string& nome_file_log)
{
    //inizializzo la classe del file di log, se ho un problema in apertura allora esco dalla funzione e dò errore
    FileLog<T,R> log;
    if(log.apriFileLog(nome_file_log))
    {
        return 1;
    }else{
            //dò errore se non ho finito di sottoporre le domande all'utente
            if(!fineDomande())
            {
                return 1;
            }else{
                //resetto il punto di analisi delle domnde e risposte immesse nella struttura del file di test e pian piano le scrivo in ordine sul file di log
                _test.resettaIlPuntoDiAnalisi();
                while(!_test.hoFinitoLeDomande())
                {
                    log.scriviFileOutput(_test.getRispostaDaDomanda(_test.leggiDomandaCorrente()),_test.leggiDomandaCorrente(),_domande.getDomandaDaId(_test.leggiDomandaCorrente()),_risposte.getRispostaDaId(_test.getRispostaDaDomanda(_test.leggiDomandaCorrente())),_domande.getDomandaDataRisposta(_test.leggiDomandaCorrente(),_test.getRispostaDaDomanda(_test.leggiDomandaCorrente())));
                    _test.prossimaDomanda();
                }
            }
    }
    return 0;
}

template<class T, class R>
const string GestioneRefertazione<T,R>:: getNuovaDomanda()
{
    return _domande.getDomandaDaId(_domande_da_porre.back());
}

template<class T, class R>
const string GestioneRefertazione<T,R>:: getRisposta()
{
    string risposta=_risposte.getRispostaDaId(_test.getRispostaDaDomanda(_domande_da_porre.back(),ANALISI));
    setRisposta(risposta);
    return risposta;
}

template<class T, class R>
const vector<string> GestioneRefertazione<T,R>:: getRispostePossibili()
{
    vector<string> vettore_di_ritorno;
    vector<R> risposte=_domande.getRispostaDataLaDomanda(_domande_da_porre.back());
    for(typename vector<R>::iterator it_risposte=risposte.begin();it_risposte!=risposte.end();it_risposte++)
    {
        vettore_di_ritorno.push_back(_risposte.getRispostaDaId(*it_risposte));
    }
    return vettore_di_ritorno;
}

template<class T, class R>
const bool GestioneRefertazione<T,R>:: setRisposta(const string& risposta)
{
    //dò errore anche se ho finito le domande da porre
    if(!fineDomande())
    {
        T domanda_posta=_domande_da_porre.back();
        R id_risposta=_risposte.getIdDaRisposta(risposta);
        vector<R> risposte_valide=_domande.getRispostaDataLaDomanda(domanda_posta);
        if(find(risposte_valide.begin(),risposte_valide.end(),id_risposta)==risposte_valide.end())
        {
            //se la risposta data non è valida ritorno un errore
            return 1;
        }else{
            vector<T> domande;
            //immetto altre domande nel vettore finchè non le finisco
            if(_modalita_di_funzionamento_per_il_file_test==SCRITTURA)
            {
                _test.immettiNuovoElemento(_domande_da_porre.back(),id_risposta,DA_FUNZIONAMENTO);
            }
            _domande_da_porre.pop_back();
            domande=_domande.getDomandaDataRisposta(domanda_posta,id_risposta);
            reverse (domande.begin(),domande.end());
            for(typename vector<T>::iterator it=domande.begin();it!=domande.end();it++)
            {
               _domande_da_porre.push_back(*it);
            }
            if(!_domande_da_porre.empty())
            {
                while(!_domande_da_porre.empty()&&(_domande_da_porre.back()==T()))
                {
                        _domande_da_porre.pop_back();
                    if(!_start.finitoDomandeObbligatorie()&&_domande_da_porre.empty())
                    {
                        _domande_da_porre.push_back(_start.getDomandaObbligatoria());
                    }
                }
            }
            return 0;
        }
    }else{
        return 1;
    }
}

template<class T, class R>
const bool GestioneRefertazione<T,R>:: scriviFileTest()
{
    //se sono in modalità scrittura e ho finito le domande da porre allora posso scrivere il file di test
    if(_modalita_di_funzionamento_per_il_file_test==SCRITTURA&&fineDomande())
    {
        _test.scriviFileOutput();
        return 0;
    }else{
        return 1;
    }
}

template<class T, class R>
const bool GestioneRefertazione<T,R>:: fineDomande()
{

    if(_domande_da_porre.empty()&&_start.finitoDomandeObbligatorie())
    {
        return 1;
    }
    return 0;
}
#endif // GESTIONEREFERTAZIONE_HPP_INCLUDED
