#include "FileDomande.h"
#include"FileInput.h"
#include"VocabolarioId.h"
#include <string>
#include<vector>
#include<algorithm>

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

}

template<class T, class R>
const bool FileDomande<T,R>:: leggiFile()
{

}
