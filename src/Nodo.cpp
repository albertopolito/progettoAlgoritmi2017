#include "Nodo.h"
#include <string>
#include<vector>
#include<algorithm>
//tipologie degli archi
#define NEUTRO 0
#define TREE 1
#define BACKWARD 2
#define FORWARD 3
#define CROSS 4
//colori dei nodi
#define WHITE 0
#define GREY 1
#define BLACK 2

using namespace std;

template<class T,class R>
Nodo<T,R>::Nodo(T contenuto)
{
    _contenuto=contenuto;
}

template<class T, class R>
Nodo<T,R>::~Nodo()
{

}

template<class T, class R>
Nodo<T,R>::Nodo(const Nodo& to_copy)
{
    this->_adiacenze=to_copy._adiacenze;
    this->_colore_nodo=to_copy._colore_nodo;
    this->_contenuto=to_copy._contenuto;
    this->_tempo_fine_visita=to_copy._tempo_fine_visita;
    this->_tempo_inizio_visita=to_copy._tempo_inizio_visita;
}

template<class T,class R>
void Nodo<T,R>::setAdiacenza(const R arco,const Nodo *nodo_adiacente)
{
    adiacenza nuova_adiacenza;
    nuova_adiacenza._arco=arco;
    nuova_adiacenza._nodo_adiacente=nodo_adiacente;
}

template<class T,class R>
const T Nodo<T,R>::getContenuto()
{
    return _contenuto;
}

template<class T,class R>
void Nodo<T,R>:: setContenuto(const T nuovo_contenuto)
{
    _contenuto=nuovo_contenuto;
}

template<class T,class R>
void Nodo<T,R>:: setNuovoColore(const short int nuovo_colore)
{
    _colore_nodo=nuovo_colore;
}

template<class T,class R>
const short int Nodo<T,R>:: getColore()
{
    return _colore_nodo;
}

template<class T,class R>
void Nodo<T,R>:: setTipologiaArco(const short int nuova_tipologia,const Nodo *nodo_adiacente)
{
    if(nuova_tipologia!=NEUTRO)
    {
        bool trovato_arco_neutro=0;
        typename vector<adiacenza>::iterator f_it=_adiacenze.begin();
        while(!trovato_arco_neutro){
            f_it=find_if(f_it+1,_adiacenze.end(),find_adiacenza(nodo_adiacente));
            if(f_it!=_adiacenze.end())
            {
                if(*f_it.tipologia_arco==NEUTRO)
                {
                    trovato_arco_neutro=1;
                    *f_it.tipologia_arco=nuova_tipologia;
                }
            }else{
                trovato_arco_neutro=1;
            }
        }
    }
}

template<class T,class R>
const Nodo<T,R>* Nodo<T,R>:: findArcoPerTipologia(const short int tipologia_ricerca)
{
    typename vector<adiacenza>::iterator f_it;
    f_it=find_if(_adiacenze.begin(),_adiacenze.end(),find_adiacenza(tipologia_ricerca));
    if(*f_it!=NULL)
    {
        return *f_it.nodo_adiacente;
    }else{
        return NULL;
    }
}

template<class T,class R>
void Nodo<T,R>:: resettaTipologiaArchi()
{
    typename vector<adiacenza>::iterator it;
    for(it=_adiacenze.begin(); it!=_adiacenze.end(); it++)
    {
        *it.tipologia_arco=NEUTRO;
    }
}

template<class T,class R>
const vector<R> Nodo<T,R>:: getPesoArchi()
{
    vector<R> peso_archi;
    typename vector<adiacenza>::iterator it;
    for(it=_adiacenze.begin(); it!=_adiacenze.end(); it++)
    {
        peso_archi.push_back(*it.peso_arco);
    }
    return peso_archi;
}

template<class T,class R>
const vector<Nodo<T,R>* > Nodo<T,R>:: getNodiAdiacentiDaPesoArco(R peso_arco)
{
    vector<Nodo<T,R>* > nodi_adiacenti_da_peso_arco;
    bool trovato_arco_neutro=0;
    typename vector<adiacenza>::iterator f_it=_adiacenze.begin();
    while(f_it!=_adiacenze.end()){
        f_it=find_if(f_it+1,_adiacenze.end(),find_adiacenza(peso_arco));
        if(f_it!=_adiacenze.end())
        {
            if(find_if(nodi_adiacenti_da_peso_arco.begin(),nodi_adiacenti_da_peso_arco.end(),nodi_adiacenti_da_peso_arco==*f_it.nodo_adiacenti)==NULL)
            {
                nodi_adiacenti_da_peso_arco.push_back(*f_it.nodo_adiacente);
            }
        }
    }
    return nodi_adiacenti_da_peso_arco;
}

template<class T,class R>
const int Nodo<T,R>::getTempoInizioVisita()
{
    return _tempo_inizio_visita;
}

template<class T,class R>
const int Nodo<T,R>::getTempoFineVisita()
{
    return _tempo_fine_visita;
}

template<class T,class R>
void Nodo<T,R>::setTempoInizioVisita(const int tempo_inizio_visita)
{
    _tempo_inizio_visita=tempo_inizio_visita;
}

template<class T,class R>
void Nodo<T,R>::setTempoFineVisita(const int tempo_fine_visita)
{
    _tempo_fine_visita=tempo_fine_visita;
}
