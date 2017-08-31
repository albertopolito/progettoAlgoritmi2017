#ifndef GESTIONEREFERTAZIONE_H
#define GESTIONEREFERTAZIONE_H
#include"FileRisposte.h"
#include"FileDomande.h"
#include"FileStart.h"
#include"FileTest.h"
#include"FileLog.h"
///modalità di lettura o scrittura del file di test
#define LETTURA 0
#define SCRITTURA 1
using namespace std;

template<class T, class R>
class GestioneRefertazione
{
    public:
        GestioneRefertazione(const string nome_file_risposte,const string nome_file_domande,const string nome_file_start);
        GestioneRefertazione(const GestioneRefertazione& to_copy);
        virtual ~GestioneRefertazione();
        void setModalitaDiFunzionamentoFileTest(const bool modalita);
        const bool analisiSintatticaSemanticaEdInizializzazione();
        const bool apriLeggiScriviFileTest(const string nome_file_test);
        const bool daFileDiTestAFileDiLog(const string nome_file_log);
        //const struct domanda_risposte prossimaDomanda();
        const bool setRisposta(const string risposta);
        const bool scriviFileTest();
        const bool fineDomande();
    protected:

    private:
        FileRisposte<R> _risposte;
        FileDomande<T,R> _domande;
        FileStart<T> _start;
        FileTest<T,R> _test;
        vector<T> _domande_da_porre;
        bool _modalita_di_funzionamento_per_il_file_test;
};

template<class T, class R>
GestioneRefertazione<T,R>::GestioneRefertazione(const string nome_file_risposte,const string nome_file_domande,const string nome_file_start)
{
    _risposte(nome_file_risposte);
    _domande(nome_file_domande);
    _start(nome_file_start);
}

template<class T, class R>
GestioneRefertazione<T,R>::GestioneRefertazione(const GestioneRefertazione& to_copy)
{
    this->_domande=to_copy._domande;
    this->_domande_da_porre=to_copy._domande_da_porre;
    this->_iteratore_delle_domande_da_porre=to_copy._iteratore_delle_domande_da_porre;
    this->_risposte=to_copy._risposte;
    this->_start=to_copy._start;
    this->_test=to_copy._start;
}

template<class T, class R>
GestioneRefertazione<T,R>::~GestioneRefertazione()
{
    //dtor
}

template<class T, class R>
void GestioneRefertazione<T,R>::setModalitaDiFunzionamentoFileTest(const bool modalita)
{
    _modalita_di_funzionamento_per_il_file_test=modalita;
}

template<class T, class R>
const bool GestioneRefertazione<T,R>:: analisiSintatticaSemanticaEdInizializzazione()
{
    if(_risposte.getErroreInLettura()&&_domande.getErroreInLettura()&&_start.getErroreInLettura())
    {
        return 1;
    }else{
        typename vector<R>::iterator it_risposte;
        for(it_risposte=_domande.getTutteLeRispostePossibili().begin();it_risposte!=_domande.getTutteLeRispostePossibili().end();it_risposte++)
        {
            if(_risposte.getRispostaDaId(*it_risposte)=="")
            {
                return 1;
            }
        }
        typename vector<T>::iterator it_domande_obbligatorie;
        for(it_domande_obbligatorie=_start.getDomandeObbligatorie().begin();it_domande_obbligatorie!=_start.getDomandeObbligatorie().end();it_domande_obbligatorie++)
        {
            if(_domande.getDomandaDaId(*it_domande_obbligatorie)=="")
            {
                return 1;
            }
        }
    }
    _domande_da_porre.push_back(_start.getDomandeObbligatorie());
    return 0;
}

template<class T, class R>
const bool  GestioneRefertazione<T,R>:: apriLeggiScriviFileTest(const string nome_file_test)
{
    if(_test.apriInLetturaScrittura(nome_file_test, _modalita_di_funzionamento_per_il_file_test))
    {
       return 1;
    }
    if(_modalita_di_funzionamento_per_il_file_test==LETTURA)
    {
        while(!_test.hoFinitoLeDomande())
        {
            vector<R> risposte_valide=_domande.getRispostaDataLaDomanda(_test.leggiDomandaCorrente());
            if(find(risposte_valide.begin(),risposte_valide.end(),_test.getRispostaDaDomanda(_test.leggiDomandaCorrente))==risposte_valide.end())
            {
                return 1;
            }
            _test.prossimaDomanda();
        }
    }
    return 0;
}

template<class T, class R>
const bool GestioneRefertazione<T,R>:: daFileDiTestAFileDiLog(const string nome_file_log)
{
    FileLog<T,R> log(nome_file_log);
    if(log.getErroreApertura())
    {
        return 1;
    }else{
        if(_modalita_di_funzionamento_per_il_file_test==SCRITTURA)
        {
            while(!_test.hoFinitoLeDomande)
            {
                _test.resettaIlPuntoDiAnalisi();
                log.scriviFileOutput(_test.getRispostaDaDomanda(_test.leggiDomandaCorrente()),_test.leggiDomandaCorrente(),_domande.getDomandaDaId(_test.leggiDomandaCorrente()),_risposte.getRispostaDaId(_test.getRispostaDaDomanda(_test.leggiDomandaCorrente())),_domande.getDomandaDataRisposta(_test.leggiDomandaCorrente(),_test.getRispostaDaDomanda(_test.leggiDomandaCorrente())));
                _test.prossimaDomanda();
            }
        }else if(_modalita_di_funzionamento_per_il_file_test==LETTURA)
        {
            while(!_domande_da_porre.empty())
            {
                T domanda_corrente=_domande_da_porre.back();
                if(domanda_corrente!=T())
                {
                    log.scriviFileOutput(_test.getRispostaDaDomanda(domanda_corrente,FUNZIONAMENTO),domanda_corrente,_domande.getDomandaDaId(domanda_corrente),_risposte.getRispostaDaId(_test.getRispostaDaDomanda(domanda_corrente,FUNZIONAMENTO)),_domande.getDomandaDataRisposta(domanda_corrente,_test.getRispostaDaDomanda(domanda_corrente,FUNZIONAMENTO)));
                    _domande_da_porre.pop_back();
                    _domande_da_porre.push_back(_domande.getDomandaDataRisposta(domanda_corrente,_test.getRispostaDaDomanda(domanda_corrente)));
                }
            }
            return !_test.hoFinitoLeDomande(FUNZIONAMENTO);
        }
        return 0;
    }
}

/*template<class T, class R>
const struct domanda_risposte GestioneRefertazione<T,R>:: prossimaDomanda()
{

}*/

template<class T, class R>
const bool GestioneRefertazione<T,R>:: setRisposta(const string risposta)
{
    if(_modalita_di_funzionamento_per_il_file_test==SCRITTURA)
    {
        T domanda_posta=_domande_da_porre.back();
        R id_risposta=_risposte.getIdDaRisposta(risposta);
        vector<R> risposte_valide=_domande.getRispostaDataLaDomanda(domanda_posta);
        if(find(risposte_valide.begin(),risposte_valide.end(),id_risposta)==risposte_valide.end())
        {
            return 1;
        }else{
            _test.immettiNuovoElemento(_domande_da_porre.back(),id_risposta);
            _domande_da_porre.pop_back();
            _domande_da_porre.push_back(_domande.getDomandaDataRisposta(domanda_posta,id_risposta));
            if(_domande_da_porre.back()==T())
            {
                _domande_da_porre.pop_back();
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
    if(_domande_da_porre.empty())
    {
        return 1;
    }else{
        return 0;
    }
}

#endif // GESTIONEREFERTAZIONE_H
