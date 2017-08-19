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
    //dtor
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

/*template<class T,class R>
vector<adiacenza> Nodo<T,R>:: getAdiacenze()
{
    return _adiacenze;
}*/

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
    //da implementare
}

template<class T,class R>
const Nodo<T,R> Nodo<T,R>:: findArcoPerTipologia(const short int tipologia_ricerca)
{
    //da implementare
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
const vector<Nodo<T,R> > Nodo<T,R>:: getNodiAdiacentiDaPesoArco(R peso_arco)
{

}
