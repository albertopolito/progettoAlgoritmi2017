#ifndef GRAFO_HPP_INCLUDED
#define GRAFO_HPP_INCLUDED
#include"Nodo.hpp"
///tipologie degli archi
#define NEUTRO 0
#define TREE 1
#define BACKWARD 2
#define FORWARD 3
#define CROSS 4
///colori dei nodi
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
        ///immette un nuovo nodo attraverso il contenuto del nodo, l'arco, e il contenuto del nodo adiacente
        void setNuovoNodo(const T& contenuto,const R& arco,const T& contenuto_nodo_adiacente);
        ///immette un nuovo nodo senza archi
        void setNuovoNodo(const T& contenuto);
        ///ritorna un vettore degli archi che partono dal nodo ricercato
        const vector<R> daContenutoAnalisi(const T& contenuto);
        ///ritorna il contenuto dei nodi collegati al nodo ricercato attraverso un ben preciso peso degli archi
        const vector<T> daArcoAnalisi(const R& arco, const T& contenuto);
        ///ritorna 1 se gli alberi con quelle radici sono ciclici, o esistono archi di cross, 0 altrimenti
        const bool aciclicoOppureArchiDiCross( vector<T> contenuto_radici, const short int& tipologia_arco_da_ricercare);
        ///ritorna un vettore con i contenuti di tutti i nodi
        vector<T> getTuttiIcontenuti();
    protected:

    private:
        ///lista dei nodi interni al grafo
        vector<Nodo<T,R>*> _lista_nodi;
        ///tempo totale della visita
        int _tempo_totale;
        ///implementa l'analisi in profondità su tutto il grafo
        void analisiTotaleInProfondita( vector<Nodo<T,R>*> nodi_da_visitare);
        ///implementa l'analisi in profondità per un singolo nodo
        void visitaNodoDfs( Nodo<T,R>* nodo_da_visitare, const T & contenuto_radice);
        ///resetta i valori di analisi del grafo
        void resettaNodi();
        ///crea un nuovo nodo e lo immette nella lista; ritorna il puntatore al nodo creato
        Nodo<T,R>* immettiNellaListaUnNuovoNodo(const T& contenuto);
        ///ritorna l'indirizzo del nodo ricercato per contenuto
        Nodo<T,R>* ricercaNodoPerContenuto(const T& contenuto);
};


template<class T,class R>
Grafo<T,R>::Grafo()
{

}

template<class T,class R>
Grafo<T,R>::~Grafo()
{
    //elimino tutti i nodi creati precedentemente
    while(!_lista_nodi.empty())
    {
        delete _lista_nodi.back();
        _lista_nodi.pop_back();
    }
}

template<class T,class R>
Grafo<T,R>::Grafo(const Grafo& to_copy)
{
    //finchè la lista dei nodi da copiare non è vuota l'analizzo
    while(!to_copy._lista_nodi.empty())
    {
        //analizzo il peso degli archi e le adiacenze a cui sono collegati e scrivo un grafo con all'interno nodi con indirizzi diversi ma stesso contenuto
        Nodo<T,R>* nodo=to_copy._lista_nodi.back();
        typename vector<R>::iterator it_archi;
        for(it_archi=nodo->getPesoArchi().begin();it_archi!=nodo->getPesoArchi().end();it_archi++)
        {
            typename vector<Nodo<T,R>*>::iterator it_nodi_adiacenti;
            for(it_nodi_adiacenti=nodo->getNodiAdiacentiDaPesoArco(*it_archi).begin();it_nodi_adiacenti!=nodo->getNodiAdiacentiDaPesoArco(*it_archi).end();it_nodi_adiacenti++)
            {
                Nodo<T,R>* nodo_adiacente=*it_nodi_adiacenti;
                this->setNuovoNodo(nodo->getContenuto(),*it_archi,nodo_adiacente->getContenuto());
            }
        }
        //elimino l'ultimo nodo dalla lista di nodi da copiare e ricomincio
        to_copy._lista_nodi.pop_back();
    }
    //il vettore della lista nodi rimane copiato ma al rovescio però ciò non è importante, basta che le adiacenze siano giuste
}

template<class T,class R>
void Grafo<T,R>:: setNuovoNodo(const T& contenuto,const R& arco,const T& contenuto_nodo_adiacente)
{
    Nodo<T,R>* puntatore_nodo_a_cui_aggiungere_adiacenze=NULL;
    Nodo<T,R>* puntatore_nodo_adiacente=NULL;
    //gurdo se i nodi richiesti sono già nella lista, se lo sono allora li uso altrimenti li creo
    if((puntatore_nodo_a_cui_aggiungere_adiacenze=ricercaNodoPerContenuto(contenuto))==NULL)
    {
        puntatore_nodo_a_cui_aggiungere_adiacenze=immettiNellaListaUnNuovoNodo(contenuto);
    }

    if((puntatore_nodo_adiacente=ricercaNodoPerContenuto(contenuto_nodo_adiacente))==NULL)
    {
        puntatore_nodo_adiacente=immettiNellaListaUnNuovoNodo(contenuto_nodo_adiacente);
    }
    //immetto una nuova adiacenza al nodo
    puntatore_nodo_a_cui_aggiungere_adiacenze->setAdiacenza(arco,puntatore_nodo_adiacente);
}

template<class T,class R>
void Grafo<T,R>:: setNuovoNodo(const T& contenuto)
{
    Nodo<T,R>* puntatore_nodo=NULL;
    //guardo se il nodo richiesto è già nella lista, se non lo è lo creo
    if((puntatore_nodo=ricercaNodoPerContenuto(contenuto))==NULL)
    {
        puntatore_nodo=immettiNellaListaUnNuovoNodo(contenuto);
    }
}

template<class T,class R>
const vector<R> Grafo<T,R>:: daContenutoAnalisi(const T& contenuto)
{
    return ricercaNodoPerContenuto(contenuto)->getPesoArchi();
}

template<class T,class R>
const vector<T> Grafo<T,R>:: daArcoAnalisi(const R& arco, const T& contenuto)
{
    vector<T> vettore_contenuto_adiacenze;
    vector<Nodo<T,R>*> vettore_adiacenze=ricercaNodoPerContenuto(contenuto)->getNodiAdiacentiDaPesoArco(arco);
    while(!vettore_adiacenze.empty()) //svuoto pian piano il vettore dei nodi adiacenti e immetto passo passo il suo contenuto nel vettore da ritornare
    {
        vettore_contenuto_adiacenze.push_back(vettore_adiacenze.back()->getContenuto());
        vettore_adiacenze.pop_back();
    }
    reverse(vettore_contenuto_adiacenze.begin(),vettore_contenuto_adiacenze.end());
    return vettore_contenuto_adiacenze;
}

template<class T,class R>
const bool Grafo<T,R>:: aciclicoOppureArchiDiCross(vector<T> contenuto_radici, const short int& tipologia_arco_da_ricercare)
{
    typename vector<Nodo<T,R>*>::iterator itr_lista_nodi;
    vector<Nodo<T,R>*> nodi_da_analizzare;
    for(itr_lista_nodi=_lista_nodi.begin();itr_lista_nodi!=_lista_nodi.end();itr_lista_nodi++)
    {
        Nodo<T,R>* nodo=*itr_lista_nodi;
        for(typename vector<T>::iterator it=contenuto_radici.begin();it!=contenuto_radici.end();it++)
        {
            if(nodo->getContenuto()==*it)
            {
                nodi_da_analizzare.push_back(nodo);
            }
        }
    }
    resettaNodi();
    analisiTotaleInProfondita(nodi_da_analizzare);
    //cerco nei nodi radici passati alla funzione se gli archi sono ettichettati con cross, se ne esiste anche solo uno allora il grafo è ciclico, altrimenti è aciclico
    //preparo i nodi da analizzare
    for(itr_lista_nodi=_lista_nodi.begin();itr_lista_nodi!=_lista_nodi.end();itr_lista_nodi++)
    {
        Nodo<T,R>* nodo=*itr_lista_nodi;
        for(typename vector<T>::iterator it=contenuto_radici.begin();it!=contenuto_radici.end();it++)
        {
            if(tipologia_arco_da_ricercare==CROSS)
            {
                if(nodo->getRadici().size()>1)
                {
                    if(nodo->getContenuto()!=T())
                    {
                        return 1;
                    }
                }
                if(nodo->findArcoPerTipologia(CROSS)!=NULL)
                {
                    nodo=nodo->findArcoPerTipologia(CROSS);
                    if(nodo->getContenuto()!=T())
                    {
                        return 1;
                    }
                }

            }else{
                if(nodo->findArcoPerTipologia(tipologia_arco_da_ricercare)!=NULL)
                {
                    return 1;
                }
            }
        }
    }
    return 0;
}

template<class T,class R>
void Grafo<T,R>:: analisiTotaleInProfondita(vector<Nodo<T,R>*> nodi_da_visitare)
{
    typename vector<Nodo<T,R>*>::iterator itr_lista_nodi;
    resettaNodi();              //resetto il colore e la tipologia degli archi per ogni nodo
    _tempo_totale=0;            //setto a zero il tempo di visita totale
    for(itr_lista_nodi=nodi_da_visitare.begin();itr_lista_nodi!=nodi_da_visitare.end();itr_lista_nodi++)
    {
        Nodo<T,R>* nodo=*itr_lista_nodi;    //puntatore di appoggio
        nodo->setNuovaRadice(nodo->getContenuto());
        if(nodo->getColore()==WHITE)        //per tutti i nodi bianchi implemento la visita in profondità
        {
            visitaNodoDfs(*itr_lista_nodi,nodo->getContenuto());
        }
    }
}

template<class T,class R>
void Grafo<T,R>:: visitaNodoDfs( Nodo<T,R>* nodo_da_visitare, const T& contenuto_radice)
{
    Nodo<T,R>* nodo_adiacente=NULL;
    nodo_da_visitare->setNuovoColore(GREY);
    _tempo_totale++;
    nodo_da_visitare->setTempoInizioVisita(_tempo_totale);


    //visito il nodo, ricerco le adiacenze ancora da analizzare tramite l'analisi della neutralità degli archi che gli partono
    while((nodo_adiacente=nodo_da_visitare->findArcoPerTipologia(NEUTRO))!=NULL)
    {
        nodo_adiacente->setNuovaRadice(contenuto_radice);
        switch(nodo_adiacente->getColore())
        {
            case WHITE: nodo_da_visitare->setTipologiaArco(TREE,nodo_adiacente);    //se il nodo adiacente è bianco allora la tipologia dell'arco è TREE
                        visitaNodoDfs(nodo_adiacente,contenuto_radice);                              //e richiamo ricorsivamente se stessa per continuare l'analisi
                        break;
            case GREY:  nodo_da_visitare->setTipologiaArco(BACKWARD,nodo_adiacente);//se il nodo è grigio allora l'arco è backward e non lo analizzo
                        break;
            case BLACK:if(nodo_adiacente->getTempoInizioVisita()>nodo_da_visitare->getTempoInizioVisita())
                        {
                            //se il nodo è nero e si verifica la condizione sopracitata allora l'arco è forward e non lo analizzo
                            nodo_da_visitare->setTipologiaArco(FORWARD,nodo_adiacente);
                        }else{
                            //altrimenti è di cross

                            nodo_da_visitare->setTipologiaArco(CROSS,nodo_adiacente);
                        }
                        break;
        }
    }
    //a fine visita setto il colore del nodo come nero e setto il tempo di fine visita, incrementando il tempo totale delle visite
    nodo_da_visitare->setNuovoColore(BLACK);
    _tempo_totale++;
    nodo_da_visitare->setTempoFineVisita(_tempo_totale);
}

template<class T,class R>
Nodo<T,R>* Grafo<T,R>:: immettiNellaListaUnNuovoNodo(const T& contenuto)
{
    //creo dinamicamente un nuovo nodo e lo aggiungo ai nodi del grafo
    Nodo<T,R>* nuovo_nodo=new Nodo<T,R>(contenuto);
    _lista_nodi.push_back(nuovo_nodo);
    return nuovo_nodo;
}

template<class T,class R>
void Grafo<T,R>::resettaNodi()
{
    //resetto l'analisi e tutti i nodi, perciò le tipologie degli archi e il colore dei nodi
    typename vector<Nodo<T,R>*>::iterator itr_lista_nodi;
    for(itr_lista_nodi=_lista_nodi.begin();itr_lista_nodi!=_lista_nodi.end();itr_lista_nodi++)
    {
        Nodo<T,R>* nodo=*itr_lista_nodi;
        nodo->setNuovoColore(WHITE);
        nodo->resettaTipologiaArchi();
    }
}

template<class T,class R>
Nodo<T,R>* Grafo<T,R>::ricercaNodoPerContenuto(const T& contenuto)
{
    //tramite gli iteratori e tramite la funzione getContenuto() della classe Nodo ricerco l'indirizzo del nodo sapendone il contenuto
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

template<class T,class R>
vector<T> Grafo<T,R>:: getTuttiIcontenuti()
{
    vector<T> vettore_di_ritorno;
    typename vector<Nodo<T,R>*>::iterator f_it_nodo;
    for(f_it_nodo= _lista_nodi.begin();f_it_nodo!=_lista_nodi.end();f_it_nodo++)
    {
        Nodo<T,R>* nodo=*f_it_nodo;
        if(nodo->getContenuto()!=T())
        {
            vettore_di_ritorno.push_back(nodo->getContenuto());
        }
    }
    return vettore_di_ritorno;
}
#endif // GRAFO_HPP_INCLUDED
