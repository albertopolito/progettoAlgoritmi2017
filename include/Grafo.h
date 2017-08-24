#ifndef GRAFO_H
#define GRAFO_H
#include"Nodo.h"
#include <string>
#include<vector>
#include<algorithm>
#define NEUTRO 0
#define TREE 1
#define BACKWARD 2
#define FORWARD 3
#define CROSS 4
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
        const Nodo<T,R>* immettiNellaListaUnNuovoNodo(const T contenuto);
        const Nodo<T,R>* ricercaNodoPerContenuto(const T contenuto);
        int _tempo_totale;
};

#endif // GRAFO_H
