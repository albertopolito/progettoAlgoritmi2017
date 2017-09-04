#ifndef NODO_H
#define NODO_H
#include <string>
#include<vector>
#include<algorithm>
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
class Nodo
{
//provare a condensare le 2 struct se possibile
    ///struttura dell'adiacenza (identificata dalla tipologia dell'arco da seguire, dal peso dell'arco, e dal puntatore al nodo adiacente
    struct adiacenza
        {
            short int tipologia_arco;
            R peso_arco;
            Nodo<T,R>* nodo_adiacente;
        };

///struttura "prototipo" che serve per ricercare un dato elemento del vettore (adiacenza) per un singolo campo tramite la find_if dell'iteratore
    struct find_adiacenza
        {
            short int f_tipologia;          //per tipologia arco
            bool ricerca_tipologia;         //indica che sto ricercando per la tipologia dell'arco
            R f_peso_arco;                  //per peso arco
            bool ricerca_peso_arco;         //indica che sto ricercando per il peso dell'arco
            Nodo<T,R>* f_nodo_adiacente;    //per indirizzo dell'adiacenza
            bool ricerca_nodo_adiacente;    //indica che sto ricercando per indirizzo dell'adiacenza

            find_adiacenza(const short int tipologia,const bool diverso_da_template) : f_tipologia(tipologia)    //costruttore della struct per la ricerca per tipologia
            {
                ricerca_tipologia=1;        //setto il flag per capire che sto ricercando per tipologia, ed annullo gli altri
                ricerca_peso_arco=0;
                ricerca_nodo_adiacente=0;
            }
            find_adiacenza(const R peso_arco) : f_peso_arco(peso_arco)            //costruttore della struct per la ricerca per peso dell'arco
            {
                ricerca_tipologia=0;        //setto il flag per capire che sto ricercando per peso dell'arco, ed annullo gli altri
                ricerca_peso_arco=1;
                ricerca_nodo_adiacente=0;
            }
            find_adiacenza(Nodo* nodo_adiacente) : f_nodo_adiacente(nodo_adiacente) //costruttore della struct per la ricerca per indirizzo del nodo adiacente
            {
                ricerca_tipologia=0;        //setto il flag per capire che sto ricercando per peso dell'arco, ed annullo gli altri
                ricerca_peso_arco=0;
                ricerca_nodo_adiacente=1;
            }
            //override dell'operatore () che mi restituisce 1 quando è stato trovato un elemento con il campo richiesto
            bool operator () ( const adiacenza& f_adiacenza ) const
            {
                return (ricerca_tipologia&&f_adiacenza.tipologia_arco==f_tipologia)||(ricerca_peso_arco&&f_adiacenza.peso_arco==f_peso_arco)||(ricerca_nodo_adiacente&&f_adiacenza.nodo_adiacente==f_nodo_adiacente);
            }
        };

    public:
        Nodo(T contenuto);
        virtual ~Nodo();
        Nodo(const Nodo& to_copy);
        ///immette una nuova adiacenza al vettore delle adiacenze del nodo
        void setAdiacenza(const R arco, Nodo *nodo_adiacente);
        ///ritorna il contenuto del nodo
        const T getContenuto();
        ///setta un nuovo contenuto al nodo
        void setContenuto(const T nuovo_contenuto);
        ///setta un nuovo colore al nodo
        void setNuovoColore(const short int nuovo_colore);
        ///ritorna il colore del nodo
        const short int getColore();
        ///setta la tipologia dell'arco
        void setTipologiaArco(const short int nuova_tipologia, Nodo *nodo_adiacente);
        ///ritorna l'indirizzo del primo nodo che trova collegato col nodo corrente attraverso un arco con la tipologia ricercata
        Nodo<T,R>* findArcoPerTipologia(const short int tipologia_ricerca);
        ///resetta la tipologia di tutti gli archi rendendoli uguali a NEUTRO
        void resettaTipologiaArchi();
        ///ritorna un vettore con il peso di tutti gli archi collegati al nodo corrente
        const vector<R> getPesoArchi();
        ///ritorna un vettore con gli indirizzi di tutti i nodi adiacenti collegati al nodo corrente attraverso archi con il peso ricercato
        const vector<Nodo<T,R>* > getNodiAdiacentiDaPesoArco(R peso_arco);
        ///per le visite in ampiezza e in profondità, ritorna il tempo in cui è iniziata la visita
        const int getTempoInizioVisita();
        ///per le visite in ampiezza e in profondità, ritorna il tempo in cui è finita la visita
        const int getTempoFineVisita();
        ///per le visite in ampiezza e in profondità, setta il tempo in cui è iniziata la visita
        void setTempoInizioVisita(const int tempo_inizio_visita);
        ///per le visite in ampiezza e in profondità, setta il tempo in cui è finita la visita
        void setTempoFineVisita(const int tempo_fine_visita);
    protected:

    private:
        ///vettore delle adiacenze del nodo corrente
        vector<adiacenza> _adiacenze;
        ///contenuto nodo corrente
        T _contenuto;
        ///colore del nodo corrente
        short int _colore_nodo;
        ///tempo inizio visita nodo corrente
        int _tempo_inizio_visita;
        ///tempo fine visita nodo corrente
        int _tempo_fine_visita;
};


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
void Nodo<T,R>::setAdiacenza(const R arco, Nodo *nodo_adiacente)
{
    //setto prima tutto nella struttura delle adiacenze e poi la metto nel vettore delle adiacenze
    adiacenza nuova_adiacenza;
    nuova_adiacenza.peso_arco=arco;
    nuova_adiacenza.nodo_adiacente=nodo_adiacente;
    _adiacenze.push_back(nuova_adiacenza);
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
void Nodo<T,R>:: setTipologiaArco(const short int nuova_tipologia, Nodo *nodo_adiacente)
{
    //la nuova tipologia deve essere diversa da NEUTRO, a questa tipologia si può arrivare solo resettando tutti gli archi
    if(nuova_tipologia!=NEUTRO)
    {
        bool trovato_arco_neutro=0; //flag che mi indica se ho tovato un arco neutro in cui posso settare una nuova tipologia
        typename vector<adiacenza>::iterator f_it=_adiacenze.begin();
        //finchè non ho trovato un arco neutro che è collegato al nodo di cui ho passato l'indirizzo alla funzione

        while((!trovato_arco_neutro)&&((f_it=find_if(f_it,_adiacenze.end(),find_adiacenza(nodo_adiacente)))!=_adiacenze.end())){

                if(adiacenza(*f_it).tipologia_arco==NEUTRO)
                {   //se ho trovato un arco ancora neutro collegato all'adiacenza allora faccio terminare il ciclo e scrivo la nuova tipologia
                    trovato_arco_neutro=1;
                    adiacenza temp;
                    temp=*f_it;
                    temp.tipologia_arco=nuova_tipologia;
                    *f_it=temp;
                }
                f_it++;
        }

    }
}

template<class T,class R>
Nodo<T,R>* Nodo<T,R>:: findArcoPerTipologia(const short int tipologia_ricerca)
{

    typename vector<adiacenza>::iterator f_it;
    if(!_adiacenze.empty())
    {
        f_it=find_if(_adiacenze.begin(),_adiacenze.end(),find_adiacenza(tipologia_ricerca,0));
        if(f_it!=_adiacenze.end())  //se ho trovato un arco con la tipologia ricercata allora lo ritorno alla funzione  attraverso il suo indirizzo
        {
            return adiacenza(*f_it).nodo_adiacente;
        }
        //altrimenti gli ritorno un indirizzo nullo
        return NULL;
    }

    return NULL;
}

template<class T,class R>
void Nodo<T,R>:: resettaTipologiaArchi()
{
    //mi scansiono tutto il vettore delle adiacenze e impongo la tipologia degli archi nulla tramite NEUTRO
    typename vector<adiacenza>::iterator it;
    for(it=_adiacenze.begin(); it!=_adiacenze.end(); it++)
    {
        adiacenza temp;
        temp=adiacenza(*it);
        temp.tipologia_arco=NEUTRO;
        *it=temp;
    }
}

template<class T,class R>
const vector<R> Nodo<T,R>:: getPesoArchi()
{
    //riempio il vettore con il peso degli archi e lo ritorno
    vector<R> peso_archi;
    typename vector<adiacenza>::iterator it;
    for(it=_adiacenze.begin(); it!=_adiacenze.end(); it++)
    {
        peso_archi.push_back(adiacenza(*it).peso_arco);
    }
    return peso_archi;
}

template<class T,class R>
const vector<Nodo<T,R>* > Nodo<T,R>:: getNodiAdiacentiDaPesoArco(R peso_arco)
{
    //vettore perchè più archi con lo stesso peso possono collegarsi a nodi differenti
    vector<Nodo<T,R>* > nodi_adiacenti_da_peso_arco;
    typename vector<adiacenza>::iterator f_it=_adiacenze.begin();
    while(f_it!=_adiacenze.end()){
        typename vector<adiacenza>::iterator f_it_temp=find_if(f_it,_adiacenze.end(),find_adiacenza(peso_arco));
        if(f_it_temp!=_adiacenze.end()) //se l'iteratore della ricerca è valido allora metto nel vettore l'adiacenza puntata dall'iteratore
        {
            nodi_adiacenti_da_peso_arco.push_back(adiacenza(*f_it_temp).nodo_adiacente);
            f_it=f_it_temp+1;   //setto un nuovo punto da cui iniziare la ricerca
        }else{
            f_it=_adiacenze.end();  //finisco il ciclo
        }
    }
    return nodi_adiacenti_da_peso_arco; //ritorno il vettore dei nodi ora completo
}
//metodi per settare o leggere i tempi di visita
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

#endif // NODO_H
