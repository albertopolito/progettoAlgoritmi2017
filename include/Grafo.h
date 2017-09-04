#ifndef GRAFO_H
#define GRAFO_H
#include"Nodo.h"
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
///tipo di analisi
#define NESSUNA_ANALISI 0
#define PROFONDITA 1
#define AMPIEZZA 2


using namespace std;
template<class T,class R>
class Grafo
{
    public:
        Grafo();
        virtual ~Grafo();
        Grafo(const Grafo& to_copy);
        ///immette un nuovo nodo attraverso il contenuto del nodo, l'arco, e il contenuto del nodo adiacente
        void setNuovoNodo(const T contenuto,const R arco,const T contenuto_nodo_adiacente);
        ///immette un nuovo nodo senza archi
        void setNuovoNodo(const T contenuto);
        ///ritorna un vettore degli archi che partono dal nodo ricercato
        const vector<R> daContenutoAnalisi(const T contenuto);
        ///ritorna il contenuto dei nodi collegati al nodo ricercato attraverso un ben preciso peso degli archi
        const vector<T> daArcoAnalisi(const R arco, const T contenuto);
        ///ritorna 1 se � aciclico, o se ciclico
        const bool aciclico();
    protected:

    private:
        ///flag che dice se la tipologia degli archi � valida per l'analisi in ampiezza o in profondit� � 0=nullo, 1=profondit�, 2=ampiezza
        short int _dfs_o_bfs;
        ///lista dei nodi interni al grafo
        vector<Nodo<T,R>*> _lista_nodi;
        ///tempo totale della visita
        int _tempo_totale;
        ///implementa l'analisi in profondit� su tutto il grafo
        void analisiTotaleInProfondita();
        ///implementa l'analisi in profondit� per un singolo nodo
        void visitaNodoDfs( Nodo<T,R>* nodo_da_visitare);
        ///resetta i valori di analisi del grafo
        void resettaNodi();
        ///crea un nuovo nodo e lo immette nella lista; ritorna il puntatore al nodo creato
        Nodo<T,R>* immettiNellaListaUnNuovoNodo(const T contenuto);
        ///ritorna l'indirizzo del nodo ricercato per contenuto
        Nodo<T,R>* ricercaNodoPerContenuto(const T contenuto);
};


template<class T,class R>
Grafo<T,R>::Grafo()
{
    _dfs_o_bfs=NESSUNA_ANALISI;    //inizializzo il flag di analisi con un valore nullo
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
    //finch� la lista dei nodi da copiare non � vuota l'analizzo
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
    //il vettore della lista nodi rimane copiato ma al rovescio per� ci� non � importante, basta che le adiacenze siano giuste
}

template<class T,class R>
void Grafo<T,R>:: setNuovoNodo(const T contenuto,const R arco,const T contenuto_nodo_adiacente)
{
    Nodo<T,R>* puntatore_nodo_a_cui_aggiungere_adiacenze=NULL;
    Nodo<T,R>* puntatore_nodo_adiacente=NULL;
    //gurdo se i nodi richiesti sono gi� nella lista, se lo sono allora li uso altrimenti li creo
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
void Grafo<T,R>:: setNuovoNodo(const T contenuto)
{
    Nodo<T,R>* puntatore_nodo=NULL;
    //gurdo se il nod0 richiesto � gi� nella lista, se non lo � lo creo
    if((puntatore_nodo=ricercaNodoPerContenuto(contenuto))==NULL)
    {
        puntatore_nodo=immettiNellaListaUnNuovoNodo(contenuto);
    }
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
    while(!vettore_adiacenze.empty()) //svuoto pian piano il vettore dei nodi adiacenti e immetto passo passo il suo contenuto nel vettore da ritornare
    {
        vettore_contenuto_adiacenze.push_back(vettore_adiacenze.back()->getContenuto());
        vettore_adiacenze.pop_back();
    }
    return vettore_contenuto_adiacenze;
}

template<class T,class R>
const bool Grafo<T,R>:: aciclico()
{
    typename vector<Nodo<T,R>*>::iterator itr_lista_nodi;
    if(_dfs_o_bfs!=PROFONDITA)  //se non ho gi� fatto l'analisi in profondit� la faccio
    {
        analisiTotaleInProfondita();

    }
    //cerco in ogni nodo del grafo se gli archi ettichettati con backward, se ne esiste anche solo uno allora il grafo � ciclico, altrimenti � aciclico
    for(itr_lista_nodi=_lista_nodi.begin();itr_lista_nodi!=_lista_nodi.end();itr_lista_nodi++)
    {
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
    resettaNodi();              //resetto il colore e la tipologia degli archi per ogni nodo
    _dfs_o_bfs=PROFONDITA;      //setto che sto svolgendo l'analisi in profondit�
    _tempo_totale=0;            //setto a zero il tempo di visita totale
    for(itr_lista_nodi=_lista_nodi.begin();itr_lista_nodi!=_lista_nodi.end();itr_lista_nodi++)
    {

        Nodo<T,R>* nodo=*itr_lista_nodi;    //puntatore di appoggio
        if(nodo->getColore()==WHITE)        //per tutti i nodi bianchi implemento la visita in profondit�
        {
            visitaNodoDfs(*itr_lista_nodi);
        }
    }
}

template<class T,class R>
void Grafo<T,R>:: visitaNodoDfs( Nodo<T,R>* nodo_da_visitare)
{
    Nodo<T,R>* nodo_adiacente;
    nodo_da_visitare->setNuovoColore(GREY);
    _tempo_totale++;
    nodo_da_visitare->setTempoInizioVisita(_tempo_totale);


    //visito il nodo, ricerco le adiacenze ancora da analizzare tramite l'analisi della neutralit� degli archi che gli partono
    while((nodo_adiacente=nodo_da_visitare->findArcoPerTipologia(NEUTRO))!=NULL)
    {
        switch(nodo_adiacente->getColore())
        {
            case WHITE: nodo_da_visitare->setTipologiaArco(TREE,nodo_adiacente);    //se il nodo adiacente � bianco allora la tipologia dell'arco � TREE
                        visitaNodoDfs(nodo_adiacente);                              //e richiamo ricorsivamente se stessa per continuare l'analisi
                        break;
            case GREY:  nodo_da_visitare->setTipologiaArco(BACKWARD,nodo_adiacente);//se il nodo � grigio allora l'arco � backward e non lo analizzo
                        break;
            case BLACK:if(nodo_adiacente->getTempoInizioVisita()>nodo_da_visitare->getTempoInizioVisita())
                        {
                            //se il nodo � nero e si verifica la condizione sopracitata allora l'arco � forward e non lo analizzo
                            nodo_da_visitare->setTipologiaArco(FORWARD,nodo_adiacente);
                        }else{
                            //altrimenti � di cross

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
Nodo<T,R>* Grafo<T,R>:: immettiNellaListaUnNuovoNodo(const T contenuto)
{
    //creo dinamicamente un nuovo nodo e lo aggiungo ai nodi del grafo
    Nodo<T,R>* nuovo_nodo=new Nodo<T,R>(contenuto);
    _lista_nodi.push_back(nuovo_nodo);
    return nuovo_nodo;
}

template<class T,class R>
void Grafo<T,R>::resettaNodi()
{
    //resetto l'analisi e tutti i nodi, perci� le tipologie degli archi e il colore dei nodi
    _dfs_o_bfs=NESSUNA_ANALISI;
    typename vector<Nodo<T,R>*>::iterator itr_lista_nodi;
    for(itr_lista_nodi=_lista_nodi.begin();itr_lista_nodi!=_lista_nodi.end();itr_lista_nodi++)
    {
        Nodo<T,R>* nodo=*itr_lista_nodi;
        nodo->setNuovoColore(WHITE);
        nodo->resettaTipologiaArchi();
    }
}

template<class T,class R>
Nodo<T,R>* Grafo<T,R>::ricercaNodoPerContenuto(const T contenuto)
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

#endif // GRAFO_H
