#include "FileDomande.h"
#include"FileInput.h"
#include"VocabolarioId.h"
#include <sstream>

using namespace std;

template<class T, class R>
FileDomande<T,R>::~FileDomande()
{
    //dtor
}

template<class T, class R>
FileDomande<T,R>::FileDomande(const FileDomande& to_copy)
{
    this->_errore_lettura_file=to_copy._errore_lettura_file;
    this->_grafo_domande_da_sottoporre=to_copy._grafo_domande_da_sottoporre;
    this->_vocabolario_domande=to_copy._vocabolario_domande;
}

template<class T, class R>
const bool FileDomande<T,R>:: getErroreInLettura()
{
    return _errore_lettura_file;
}

template<class T, class R>
const vector<R> FileDomande<T,R>:: getRispostaDataLaDomanda(const T id_domanda)
{
    vector<R> vettore_senza_ripetizioni=_grafo_domande_da_sottoporre.daContenutoAnalisi(id_domanda);
    typename vector<R>::iterator itr_inizio_analisi=vettore_senza_ripetizioni.begin();
    typename vector<R>::iterator itr_fine_vettore_senza_ripetizioni=vettore_senza_ripetizioni.end();
    while(itr_inizio_analisi!=itr_fine_vettore_senza_ripetizioni)
    {
        R valore_di_cui_cercare_la_copia=*itr_inizio_analisi;
        itr_inizio_analisi++;
        itr_fine_vettore_senza_ripetizioni=remove(itr_inizio_analisi,itr_fine_vettore_senza_ripetizioni,valore_di_cui_cercare_la_copia);
    }
    vettore_senza_ripetizioni.resize(vettore_senza_ripetizioni.begin(),itr_fine_vettore_senza_ripetizioni);
    return vettore_senza_ripetizioni;
}

template<class T, class R>
const vector<T> FileDomande<T,R>:: getDomandaDataRisposta(const T id_domanda, const R id_risposta)
{
    return _grafo_domande_da_sottoporre.daArcoAnalisi(id_risposta,id_domanda);
}

template<class T, class R>
const string FileDomande<T,R>:: getDomandaDaId(const T id_domanda)
{
    return _vocabolario_domande.getStringaDaId(id_domanda);
}

template<class T, class R>
const vector<R> FileDomande<T,R>:: getTutteLeRispostePossibili()
{
    vector<R> tutte_le_risposte;
    vector<T> tutte_le_domande=_vocabolario_domande.getTuttiGliId();
    typename vector<T>::iterator it_domande;
    typename vector<R>::iterator it_risposte;
    for(it_domande=tutte_le_domande.begin();it_domande!=tutte_le_domande.end();it_domande++)
    {
        for(it_risposte=getRispostaDataLaDomanda(*it_domande).begin();it_risposte=getRispostaDataLaDomanda(*it_domande).end();it_risposte++)
        {
            if(find(tutte_le_risposte.begin(),tutte_le_risposte.end(),*it_risposte)==NULL)
            {
                tutte_le_risposte.push_back(*it_risposte);
            }
        }
    }
    return tutte_le_risposte;
}

template<class T, class R>
const bool FileDomande<T,R>:: leggiFile()
{
    T domanda_corrente;
    T domanda_adiacente;
    R risposta;
    string striga_di_appoggio;
    stringstream stream_riga;
    string domanda;
    short int numero_risposte=0;
    if(apriFileInput())
    {
        return 1;
    }else if(_file_input.end()){
        return 1;
    }else{
        while(!_file_input.end()){
            striga_di_appoggio.erase();
            getline(_file_input,striga_di_appoggio);
            stream_riga.str(striga_di_appoggio);
            stream_riga>>striga_di_appoggio;

            //leggi domanda
            if((striga_di_appoggio=="[Q]")&&(numero_risposte==0))
            {
                if(stream_riga>>domanda_corrente>>numero_risposte)
                {
                    while(!stream_riga.end())
                    {
                        striga_di_appoggio.erase();
                        stream_riga>>striga_di_appoggio;
                        domanda+=striga_di_appoggio;
                    }
                    _vocabolario_domande.setNuovoElemento(domanda_corrente,domanda);
                }else{
                    chiudiFileInput();
                    return 1;
                }
            }

            //leggi risposta
            else if((striga_di_appoggio=="[A]")&&(numero_risposte>0))
            {
                numero_risposte--;
                if(stream_riga>>risposta)
                {
                    if(stream_riga.end())
                    {
                        _grafo_domande_da_sottoporre.setNuovoNodo(domanda_corrente,risposta);
                    }
                    while(!stream_riga.end())
                    {
                        if(stream_riga>>domanda_adiacente)
                        {
                            _grafo_domande_da_sottoporre.setNuovoNodo(domanda_corrente,risposta,domanda_adiacente);
                        }else{
                            chiudiFileInput();
                            return 1;
                        }
                    }
                }else{
                    chiudiFileInput();
                    return 1;
                }

            //errore di lettura iniziale
            }else {
                chiudiFileInput();
                return 1;
            }
        }

    }
    chiudiFileInput();
    return !_grafo_domande_da_sottoporre.aciclico();
}
