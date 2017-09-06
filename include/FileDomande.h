#ifndef FILEDOMANDE_H
#define FILEDOMANDE_H
#include"FileInput.h"
#include"VocabolarioId.h"
#include"Grafo.h"
#include<sstream>
using namespace std;

template<class T, class R>
///file delle domande, derivato dal file di input
class FileDomande : public FileInput
{
    public:
        ///costruttore, apre il file di input e, leggendolo verifica la sintassi, e l'aciclicità del grafo
        FileDomande();
        virtual ~FileDomande();
        FileDomande(const FileDomande& to_copy);
        ///ritorna un vettore con le risposte possibili per quella domanda
        const vector<R> getRispostaDataLaDomanda(const T id_domanda);
        ///ritorna un vettore con le domande successive data la risposta alla domanda precedente
        const vector<T> getDomandaDataRisposta(const T id_domanda, const R id_risposta);
        ///ritorna l'id data la stringa della domanda
        const string getDomandaDaId(const T id_domanda);
        ///ritorna tutte le risposte possibili
        const vector<R> getTutteLeRispostePossibili();
        ///implementazione della funzione virtuale della classe FileInput
        const bool leggiFile(const string nome_file);
    protected:

    private:
        ///ha all'interno tutte le domande correlate con il loro id
        VocabolarioId<T> _vocabolario_domande;
        ///struttura dati che mantiene le domande e le risposte relative
        Grafo<T,R> _grafo_domande_da_sottoporre;
};

template<class T, class R>
FileDomande<T,R>::FileDomande()
{
    //ctor
}

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
const vector<R> FileDomande<T,R>:: getRispostaDataLaDomanda(const T id_domanda)
{
    vector<R> vettore_senza_ripetizioni=_grafo_domande_da_sottoporre.daContenutoAnalisi(id_domanda);
    typename vector<R>::iterator itr_inizio_analisi=vettore_senza_ripetizioni.begin();
    typename vector<R>::iterator itr_fine_vettore_senza_ripetizioni=vettore_senza_ripetizioni.end();
    //cerco le ripetizioni degli archi e le rimuovo
    while(itr_inizio_analisi!=itr_fine_vettore_senza_ripetizioni)
    {
        R valore_di_cui_cercare_la_copia=*itr_inizio_analisi;
        itr_inizio_analisi++;
        if(itr_inizio_analisi!=itr_fine_vettore_senza_ripetizioni)
        {
            itr_fine_vettore_senza_ripetizioni=remove(itr_inizio_analisi,itr_fine_vettore_senza_ripetizioni,valore_di_cui_cercare_la_copia);
        }
    }
    //compatto il vettore lasciando solo i dati utili
    vettore_senza_ripetizioni.erase(itr_fine_vettore_senza_ripetizioni,vettore_senza_ripetizioni.end());
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
    typename vector<string>::iterator it_domande;
    typename vector<R>::iterator it_risposte;
    //analizzo tutte le risposte e, prima di inserirle nel vettore elimino le ripetizioni
    for(it_domande=tutte_le_domande.begin();it_domande!=tutte_le_domande.end();it_domande++)
    {
        vector<R> risposte=getRispostaDataLaDomanda(*it_domande);
        for(it_risposte=risposte.begin();it_risposte!=risposte.end();it_risposte++)
        {
            if(find(tutte_le_risposte.begin(),tutte_le_risposte.end(),*it_risposte)!=tutte_le_risposte.end())
            {
                tutte_le_risposte.push_back(*it_risposte);
            }
        }
    }
    return tutte_le_risposte;
}

template<class T, class R>
const bool FileDomande<T,R>:: leggiFile(const string nome_file)
{
    T domanda_corrente;
    T domanda_adiacente;
    R risposta;
    string striga_di_appoggio;
    stringstream stream_riga;
    string domanda;
    short int numero_risposte=0;
    //faccio i controlli di apertura del file e guardo se il file è vuoto, se ciò succede dò errore
    if(apriFileInput(nome_file.c_str()))
    {
        return 1;
    }else if(_file_input.eof()){
        return 1;
    }else{
        //leggo il file riga per riga tramite la stringa di appoggio e lo stream
        while(!_file_input.eof()){
            stream_riga.clear();
            striga_di_appoggio.clear();
            getline(_file_input,striga_di_appoggio);
            stream_riga.str(striga_di_appoggio);
            striga_di_appoggio.clear();
            stream_riga>>striga_di_appoggio;

            //leggi domanda con relativi controlli e immissioni nelle strutture dati previste
            if(((striga_di_appoggio=="[Q]")&&(numero_risposte==0))&&(stream_riga>>domanda_corrente>>numero_risposte))
            {
                    while(!stream_riga.eof())
                    {
                        striga_di_appoggio.clear();
                        stream_riga>>striga_di_appoggio;
                        domanda+=striga_di_appoggio;
                        domanda+=" ";
                    }
                    _vocabolario_domande.setNuovoElemento(domanda_corrente,domanda);
                    domanda.clear();
            }
            //leggi risposta con relativi controlli e immissioni nelle strutture dati previste
            else if(((striga_di_appoggio=="[A]")&&(numero_risposte>0))&&(stream_riga>>risposta))
            {

                    numero_risposte--;
                    if(stream_riga.eof())
                    {
                        //immetto un nodo fittizio con come contenuto un valore nullo (T()) come adiacenza così posso usare sempre lostesso formato per le risposte
                        _grafo_domande_da_sottoporre.setNuovoNodo(domanda_corrente,risposta,T());
                    }else {
                        while(!stream_riga.eof())
                        {
                            if(stream_riga>>domanda_adiacente)
                            {
                                _grafo_domande_da_sottoporre.setNuovoNodo(domanda_corrente,risposta,domanda_adiacente);
                            }else{
                                chiudiFileInput();
                                return 1;
                            }
                        }
                    }
            //errore di lettura
            }else {

                chiudiFileInput();
                return 1;
            }
        }

    }

    chiudiFileInput();
    //ritorno ancora l'ultimo controllo sull'aciclicità del grafo di modo che le domande passate non si ripetano all'infinito
    return (!_grafo_domande_da_sottoporre.aciclico()||_vocabolario_domande.controlloSintattico());
}

#endif // FILEDOMANDE_H
