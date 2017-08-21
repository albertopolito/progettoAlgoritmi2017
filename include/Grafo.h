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
        vector<R> daContenutoAnalisiInProfondita(const T contenuto);
        vector<T> daArcoAnalisiInProfondita(const R arco);
        const bool aciclico();
    protected:

    private:
        bool dfs_o_bfs;
        vector<Nodo<T,R>*> _lista_nodi;
        //secondo vettore su quaderno
        void analisiTotaleInProfondita();
        void visitaNodoDfs(const Nodo<T,R>* nodo_da_visitare);
        const Nodo<T,R>* immettiNelVettoreUnNuovoNodo(const T contenuto);
};

#endif // GRAFO_H
