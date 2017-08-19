#ifndef NODO_H
#define NODO_H
#include <string>
#include<vector>

using namespace std;
template<class T,class R>
class Nodo
{
//provare a condensare le 2 struct se possibile
    struct adiacenza
        {
            short int tipologia_arco;
            R peso_arco;
            Nodo* nodo_adiacente;
        };

//struttura "prototipo" che serve per ricercare un dato elemento del vettore in un singolo campo tramite la find_if dell'iteratore
    struct find_adiacenza
        {
            short int f_tipologia;
            bool ricerca_tipologia;
            R f_peso_arco;
            bool ricerca_peso_arco;
            Nodo* f_nodo_adiacente;
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
        void setAdiacenza(const R arco,const Nodo *nodo_adiacente);
        const T getContenuto();
        void setContenuto(const T nuovo_contenuto);
        void setNuovoColore(const short int nuovo_colore);
        const short int getColore();
        void setTipologiaArco(const short int nuova_tipologia,const Nodo *nodo_adiacente);
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

#endif // NODO_H
