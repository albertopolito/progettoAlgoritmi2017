#include "Nodo.h"
#include <string>
#include<vector>
#include<algorithm>
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
    //da implementare
}

template<class T,class R>
void Nodo<T,R>::setAdiacenza(const R arco,const Nodo *nodo_adiacente)
{
    adiacenza nuova_adiacenza;
    nuova_adiacenza._arco=arco;
    nuova_adiacenza._nodo_adiacente=nodo_adiacente;
}

template<class T,class R>
T Nodo<T,R>::getContenuto()
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
short int Nodo<T,R>:: getColore()
{
    return _colore_nodo;
}

template<class T,class R>
void Nodo<T,R>:: setTipologiaArco(const short int nuova_tipologia,const Nodo *nodo_adiacente)
{
    //da implementare
}

template<class T,class R>
Nodo<T,R> Nodo<T,R>:: findArcoPerTipologia(const short int tipologia_ricerca)
{
    //da implementare
}

template<class T,class R>
void Nodo<T,R>:: resettaTipologiaArchi()
{
    //da implementare
}

template<class T,class R>
vector<R> Nodo<T,R>:: getPesoArchi()
{
    //da implementare
}

template<class T,class R>
vector<Nodo<T,R> > Nodo<T,R>:: getNodiAdiacentiDaPesoArco(R peso_arco)
{
    //da implementare
}
