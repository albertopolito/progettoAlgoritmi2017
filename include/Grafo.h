#ifndef GRAFO_H
#define GRAFO_H
#include"Nodo.h"

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
class Grafo
{
    public:
        Grafo();
        virtual ~Grafo();
        Grafo(const Grafo& to_copy);
        void setNuovoNodo(const T contenuto,const R arco,const T contenuto_nodo_adiacente);
        const vector<R> daContenutoAnalisi(const T contenuto);
        const vector<T> daArcoAnalisi(const R arco, const T contenuto);
        const bool aciclico();
    protected:

    private:
        bool _dfs_o_bfs;
        vector<Nodo<T,R>*> _lista_nodi;
        void analisiTotaleInProfondita();
        void visitaNodoDfs(const Nodo<T,R>* nodo_da_visitare);
        void resettaNodi();
        Nodo<T,R>* immettiNellaListaUnNuovoNodo(const T contenuto);
        Nodo<T,R>* ricercaNodoPerContenuto(const T contenuto);
        int _tempo_totale;
};


template<class T,class R>
Grafo<T,R>::Grafo()
{
    _dfs_o_bfs=NULL;
}

template<class T,class R>
Grafo<T,R>::~Grafo()
{
    while(!_lista_nodi.empty())
    {
        delete _lista_nodi.back();
        _lista_nodi.pop_back();
    }
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

    if((puntatore_nodo_a_cui_aggiungere_adiacenze=ricercaNodoPerContenuto(contenuto))==NULL)
    {
        puntatore_nodo_a_cui_aggiungere_adiacenze=immettiNellaListaUnNuovoNodo(contenuto);
    }

    if((puntatore_nodo_adiacente=ricercaNodoPerContenuto(contenuto_nodo_adiacente))==NULL)
    {
        puntatore_nodo_adiacente=immettiNellaListaUnNuovoNodo(contenuto_nodo_adiacente);
    }
    puntatore_nodo_a_cui_aggiungere_adiacenze->setAdiacenza(arco,puntatore_nodo_adiacente);
}

template<class T,class R>
const vector<R> Grafo<T,R>:: daContenutoAnalisi(const T contenuto)
{
    return ricercaNodoPerContenuto(contenuto)->getPesoArchi();
}

template<class T,class R>
const vector<T> Grafo<T,R>:: daArcoAnalisi(const R arco, const T contenuto)
{
    vector<T> vettore_contenuto_adiacenze;
    vector<Nodo<T,R>*> vettore_adiacenze=ricercaNodoPerContenuto(contenuto)->getNodiAdiacentiDaPesoArco(arco);
    while(!vettore_adiacenze.empty())
    {
        vettore_contenuto_adiacenze.push_back(vettore_adiacenze.back()->getContenuto());
        vettore_adiacenze.pop_back();
    }
    return vettore_contenuto_adiacenze;
}

template<class T,class R>
const bool Grafo<T,R>:: aciclico()
{
    typename vector<Nodo<T,R>*>::iterator itr_lista_nodi=_lista_nodi.begin();
    while(itr_lista_nodi!=_lista_nodi.end())
    {
        itr_lista_nodi++;
        Nodo<T,R>* nodo=*itr_lista_nodi;
        if(nodo->findArcoPerTipologia(BACKWARD)!=NULL)
            return 0;
    }
    return 1;
}

template<class T,class R>
void Grafo<T,R>:: analisiTotaleInProfondita()
{
    typename vector<Nodo<T,R>*>::iterator itr_lista_nodi;
    resettaNodi();
    _dfs_o_bfs=0;
    _tempo_totale=0;
    for(itr_lista_nodi=_lista_nodi.begin();itr_lista_nodi!=_lista_nodi.end();itr_lista_nodi++)
    {
        if(*itr_lista_nodi->getColore()==WHITE)
        {
            visitaNodoDfs(*itr_lista_nodi);
        }
    }
}

template<class T,class R>
void Grafo<T,R>:: visitaNodoDfs(const Nodo<T,R>* nodo_da_visitare)
{
    Nodo<T,R>* nodo_adiacente;
    nodo_da_visitare->setNuovoColore(GREY);
    _tempo_totale++;
    nodo_da_visitare->setTempoInizioVisita(_tempo_totale);
    while((nodo_adiacente=nodo_da_visitare->findArcoPerTipologia(NEUTRO))!=NULL)
    {
        switch(nodo_adiacente->getColore())
        {
            case WHITE: nodo_da_visitare->setTipologiaArco(TREE,nodo_adiacente);
                        visitaNodoDfs(nodo_adiacente);
                        break;
            case GREY:  nodo_da_visitare->setTipologiaArco(BACKWARD,nodo_adiacente);
                        break;
            case BLACK: if(nodo_adiacente->getTempoInizioVisita()>nodo_da_visitare->getTempoInizioVisita())
                        {
                            nodo_da_visitare->setTipologiaArco(FORWARD,nodo_adiacente);
                        }else{
                            nodo_da_visitare->setTipologiaArco(CROSS,nodo_adiacente);
                        }
                        break;
        }
    }
    nodo_da_visitare->setNuovoColore(BLACK);
    _tempo_totale++;
    nodo_da_visitare->setTempoFineVisita(_tempo_totale);
}

template<class T,class R>
Nodo<T,R>* Grafo<T,R>:: immettiNellaListaUnNuovoNodo(const T contenuto)
{
    Nodo<T,R>* nuovo_nodo=new Nodo<T,R>(contenuto);
    _lista_nodi.push_back(nuovo_nodo);
    return nuovo_nodo;
}

template<class T,class R>
void Grafo<T,R>::resettaNodi()
{
    _dfs_o_bfs=NULL;
    typename vector<Nodo<T,R>*>::iterator itr_lista_nodi;
    for(itr_lista_nodi=_lista_nodi.begin();itr_lista_nodi!=_lista_nodi.end();itr_lista_nodi++)
    {
        *itr_lista_nodi->setNuovoColore(WHITE);
        *itr_lista_nodi->resettaTipologiaArchi();
    }
}

template<class T,class R>
Nodo<T,R>* Grafo<T,R>::ricercaNodoPerContenuto(const T contenuto)
{
    typename vector<Nodo<T,R>*>::iterator f_it_nodo;
    for(f_it_nodo= _lista_nodi.begin();f_it_nodo!=_lista_nodi.end();f_it_nodo++)
    {
        Nodo<T,R>* nodo=*f_it_nodo;
        if(nodo->getContenuto()==contenuto)
        {
            return *f_it_nodo;
        }
    }
    return NULL;
}

#endif // GRAFO_H
