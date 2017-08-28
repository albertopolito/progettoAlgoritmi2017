#ifndef NODO_H
#define NODO_H
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
class Nodo
{
//provare a condensare le 2 struct se possibile
    struct adiacenza
        {
            short int tipologia_arco;
            R peso_arco;
            Nodo<T,R>* nodo_adiacente;
        };

//struttura "prototipo" che serve per ricercare un dato elemento del vettore in un singolo campo tramite la find_if dell'iteratore
    struct find_adiacenza
        {
            short int f_tipologia;
            bool ricerca_tipologia;
            R f_peso_arco;
            bool ricerca_peso_arco;
            Nodo<T,R>* f_nodo_adiacente;
            bool ricerca_nodo_adiacente;

            find_adiacenza(short int tipologia) : f_tipologia(tipologia)
            {
                ricerca_tipologia=1;
                ricerca_peso_arco=0;
                ricerca_nodo_adiacente=0;
            }
            find_adiacenza(R peso_arco) : f_peso_arco(peso_arco)
            {
                ricerca_tipologia=0;
                ricerca_peso_arco=1;
                ricerca_nodo_adiacente=0;
            }
            find_adiacenza(Nodo* nodo_adiacente) : f_nodo_adiacente(nodo_adiacente)
            {
                ricerca_tipologia=0;
                ricerca_peso_arco=0;
                ricerca_nodo_adiacente=1;
            }
            bool operator () ( const adiacenza& f_adiacenza ) const
            {
                return (ricerca_tipologia&&f_adiacenza.tipologia_arco==f_tipologia)||(ricerca_peso_arco&&f_adiacenza.peso_arco==f_peso_arco)||(ricerca_nodo_adiacente&&f_adiacenza.nodo_adiacente==f_nodo_adiacente);
            }
        };

    public:
        Nodo(T contenuto);
        virtual ~Nodo();
        Nodo(const Nodo& to_copy);
        void setAdiacenza(const R arco, Nodo *nodo_adiacente);
        const T getContenuto();
        void setContenuto(const T nuovo_contenuto);
        void setNuovoColore(const short int nuovo_colore);
        const short int getColore();
        void setTipologiaArco(const short int nuova_tipologia, Nodo *nodo_adiacente);
        const Nodo<T,R>* findArcoPerTipologia(const short int tipologia_ricerca);
        void resettaTipologiaArchi();
        const vector<R> getPesoArchi();
        const vector<Nodo<T,R>* > getNodiAdiacentiDaPesoArco(R peso_arco);
        const int getTempoInizioVisita();
        const int getTempoFineVisita();
        void setTempoInizioVisita(const int tempo_inizio_visita);
        void setTempoFineVisita(const int tempo_fine_visita);
    protected:

    private:

        vector<adiacenza> _adiacenze;
        T _contenuto;
        short int _colore_nodo;
        int _tempo_inizio_visita;
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
    if(f_it!=_adiacenze.end())
    {

        return adiacenza(*f_it).nodo_adiacente;
    }
    return NULL;

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
        peso_archi.push_back(adiacenza(*it).peso_arco);
    }
    return peso_archi;
}

template<class T,class R>
const vector<Nodo<T,R>* > Nodo<T,R>:: getNodiAdiacentiDaPesoArco(R peso_arco)
{
    vector<Nodo<T,R>* > nodi_adiacenti_da_peso_arco;
    typename vector<adiacenza>::iterator f_it=_adiacenze.begin();
    while(f_it!=_adiacenze.end()){
        f_it=find_if(f_it+1,_adiacenze.end(),find_adiacenza(peso_arco));
        if(f_it!=_adiacenze.end())
        {
            if(find(nodi_adiacenti_da_peso_arco.begin(),nodi_adiacenti_da_peso_arco.end(),adiacenza(*f_it).nodo_adiacente)==nodi_adiacenti_da_peso_arco.end())
            {
                nodi_adiacenti_da_peso_arco.push_back(adiacenza(*f_it).nodo_adiacente);
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

#endif // NODO_H
