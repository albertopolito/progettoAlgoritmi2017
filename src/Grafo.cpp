#include "Grafo.h"
#include"Nodo.h"
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
template<class T,class R>
Grafo<T,R>::Grafo()
{
    dfs_o_bfs=NULL;
}

template<class T,class R>
Grafo<T,R>::~Grafo()
{
    //dtor
}

template<class T,class R>
Grafo<T,R>::Grafo(const Grafo& to_copy)
{
    this->_lista_nodi=to_copy._lista_nodi;
}

template<class T,class R>
void Grafo<T,R>:: setNuovoNodo(const T contenuto,const R arco,const T contenuto_nodo_adiacente=0)
{
    Nodo<T,R>* puntatore_nodo_a_cui_aggiungere_adiacenze=NULL;
    Nodo<T,R>* puntatore_nodo_adiacente=NULL;
    typename vector<Nodo<T,R>*>::iterator f_it_nodo_a_cui_aggiungere_adiacenze, f_it_nodo_adiacente;
    f_it_nodo_a_cui_aggiungere_adiacenze = _lista_nodi.begin();
    for(bool trovato=0;trovato!=0||f_it_nodo_a_cui_aggiungere_adiacenze!=_lista_nodi.end();f_it_nodo_a_cui_aggiungere_adiacenze++)
    {
        if(*f_it_nodo_a_cui_aggiungere_adiacenze->getContenuto==contenuto)
        {
            trovato=1;
        }
    }
    if(f_it_nodo_a_cui_aggiungere_adiacenze==_lista_nodi.end())
    {
        puntatore_nodo_a_cui_aggiungere_adiacenze=immettiNelVettoreUnNuovoNodo(contenuto);
    }else{
        puntatore_nodo_a_cui_aggiungere_adiacenze=*f_it_nodo_a_cui_aggiungere_adiacenze;
    }
    f_it_nodo_adiacente = _lista_nodi.begin();
    for(bool trovato=0;trovato!=0||f_it_nodo_adiacente!=_lista_nodi.end();f_it_nodo_adiacente++)
    {
        if(*f_it_nodo_adiacente->getContenuto==contenuto_nodo_adiacente)
        {
            trovato=1;
        }
    }
    if(f_it_nodo_adiacente==_lista_nodi.end())
    {
        puntatore_nodo_adiacente=immettiNelVettoreUnNuovoNodo(contenuto_nodo_adiacente);
    }else{
        puntatore_nodo_adiacente=*f_it_nodo_adiacente;
    }
    puntatore_nodo_a_cui_aggiungere_adiacenze->setAdiacenza(arco,puntatore_nodo_adiacente);
}

template<class T,class R>
vector<R> Grafo<T,R>:: daContenutoAnalisiInProfondita(const T contenuto)
{

}

template<class T,class R>
vector<T> Grafo<T,R>:: daArcoAnalisiInProfondita(const R arco)
{

}

template<class T,class R>
const bool Grafo<T,R>:: aciclico()
{

}

template<class T,class R>
void Grafo<T,R>:: analisiTotaleInProfondita()
{

}

template<class T,class R>
void Grafo<T,R>:: visitaNodoDfs(const Nodo<T,R>* nodo_da_visitare)
{

}

template<class T,class R>
const Nodo<T,R>* Grafo<T,R>:: immettiNelVettoreUnNuovoNodo(const T contenuto)
{
    Nodo<T,R>* nuovo_nodo=new Nodo<T,R>(contenuto);
    return nuovo_nodo;
}


