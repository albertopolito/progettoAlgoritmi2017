#ifndef FILETEST_H
#define FILETEST_H
#include <string>
#include<vector>
#include<algorithm>
#include "FileOutput.h"
#include "FileInput.h"
///modalità apertura file
#define LETTURA 0
#define SCRITTURA 1
///modalità di lettura delle risposte
#define ANALISI 0
#define FUNZIONAMENTO 1
///modalità di immissione dei dati
#define DA_FUNZIONAMENTO 1
#define DA_FILE 0
using namespace std;

template<class T, class R>
class FileTest : public FileInput , FileOutput
{
    struct test {
        R id_risposta;
        T id_domanda;
        bool ho_risposto;
/*        test()
        {

        }*/
        test(R n_id_risposta,T n_id_domanda,bool risposto)
        {
            id_domanda=n_id_domanda;
            id_risposta=n_id_risposta;
            ho_risposto=risposto;
        }
    };
    struct f_test{
        R f_id_risposta;
        T f_id_domanda;
        bool f_ho_risposto;
        short int f_ricerca_risposta_domanda;
        f_test(R id_risposta) : f_id_risposta(id_risposta)
        {
            f_ricerca_risposta_domanda=0;
        }

        f_test(T id_domanda, const bool domanda) : f_id_domanda(id_domanda)
        {
            f_ricerca_risposta_domanda=1;
        }

        f_test(T id_domanda, bool risposto, const bool domanda) : f_id_domanda(id_domanda),f_ho_risposto(risposto)
        {
            f_ricerca_risposta_domanda=2;
        }

        bool operator () ( const test& f_test ) const
        {
            return ((f_ricerca_risposta_domanda==0&&f_test.id_risposta==f_id_risposta)||(f_ricerca_risposta_domanda==1&&f_test.id_domanda==f_id_domanda)||(f_ricerca_risposta_domanda==2&&f_test.id_domanda==f_id_domanda&&f_test.ho_risposto==f_ho_risposto));
        }
    };
    public:
        FileTest();
        virtual ~FileTest();
        //aggiungere copy ctr
        const bool apriInLetturaScrittura(const string nome_file,const bool modalita=LETTURA );
        const T leggiDomandaCorrente();//leggi la domanda puntata dall'iteratore
        void  prossimaDomanda();//aumenta l'iteratore di 1
        const R getRispostaDaDomanda(const T id_domanda,const bool modalita=ANALISI);
        const bool hoGiaRisposto(const T id_domanda);
        const bool hoFinitoLeDomande(const bool modalita=ANALISI);
        void resettaIlPuntoDiAnalisi();
        void immettiNuovoElemento(const T id_domanda,const R id_risposta, const bool modalita_scrittura_in_struttura_dati=DA_FILE);
        void scriviFileOutput();
    protected:

    private:
        vector<test> _domande_con_risposta;
        typename vector<test>::iterator _it_domande_con_risposta;
        const bool leggiFile();
};

template<class T, class R>
FileTest<T,R>::FileTest()
{
    resettaIlPuntoDiAnalisi();
}

template<class T, class R>
FileTest<T,R>::~FileTest()
{

}

template<class T, class R>
const bool  FileTest<T,R>:: apriInLetturaScrittura(const string nome_file, const bool modalita)
{
    if(modalita)
    {
        return apriFileOutput(nome_file);
    }else{
        if(!apriFileInput(nome_file))
        {
            return (leggiFile());
        }else{
            return 1;
        }
    }
}

template<class T, class R>
const T FileTest<T,R>:: leggiDomandaCorrente()
{
    if(_it_domande_con_risposta!=_domande_con_risposta.end())
    {
        return test(*_it_domande_con_risposta).id_domanda;
    }
    return T();
}

template<class T, class R>
void FileTest<T,R>:: prossimaDomanda()
{
    _it_domande_con_risposta++;
}

template<class T, class R>
const R FileTest<T,R>::getRispostaDaDomanda(const T id_domanda, const bool modalita)
{
    typename vector<test>::iterator it_test=find_if(_domande_con_risposta.begin(),_domande_con_risposta.end(),f_test(id_domanda,0));
    if(it_test!=_domande_con_risposta.end())
    {

        R id_risposta=test(*it_test).id_risposta;
        if(modalita==FUNZIONAMENTO)
        {
            test temp(test(*it_test).id_risposta,test(*it_test).id_domanda,1);
            _domande_con_risposta.erase(it_test);
            _domande_con_risposta.push_back(temp);
        }
        return id_risposta;
    }else{
        return R();
    }
}

template<class T, class R>
const bool FileTest<T,R>::hoGiaRisposto(const T id_domanda)
{

    typename vector<test>::iterator it_test=find_if(_domande_con_risposta.begin(),_domande_con_risposta.end(),f_test(id_domanda,1,0));
    if(it_test==_domande_con_risposta.end())
    {
        return 0;
    }else{
        return 1;
    }
}

template<class T, class R>
const bool FileTest<T,R>::hoFinitoLeDomande(const bool modalita)
{
    if(modalita==FUNZIONAMENTO)
    {
        typename vector<test>::iterator it_domande;
        for(it_domande=_domande_con_risposta.begin();it_domande!=_domande_con_risposta.end();it_domande++)
        {
            if(!test(*it_domande).ho_risposto)
            {
                return 0;
            }
        }
        return 1;
    }else
    {
        if(_it_domande_con_risposta==_domande_con_risposta.end())
        {
            return 1;
        }else{
            return 0;
        }
    }
}

template<class T, class R>
// Aggiunge un nuovo elemento al vettore degli ID
void FileTest<T, R>::immettiNuovoElemento(const T id_domanda,const R id_risposta, const bool modalita_scrittura_in_struttura_dati)
{
    test t(id_risposta,id_domanda,0);
    if(modalita_scrittura_in_struttura_dati==DA_FILE)
    {
        t.ho_risposto = 0;
    }else{
        t.ho_risposto = 1;
    }
    _domande_con_risposta.push_back(t);
}

template<class T, class R>
void FileTest<T,R>::resettaIlPuntoDiAnalisi()
{
   _it_domande_con_risposta=_domande_con_risposta.begin();
}

template<class T, class R>
void FileTest<T,R>::scriviFileOutput()
{
    typename vector<test>::iterator _domande_con_risposta_iterator;
    _domande_con_risposta_iterator = _domande_con_risposta.begin();
    _file_output<< (*_domande_con_risposta_iterator).id_domanda << " " << (*_domande_con_risposta_iterator).id_risposta;
    _domande_con_risposta_iterator++;
    for (; _domande_con_risposta_iterator != _domande_con_risposta.end(); _domande_con_risposta_iterator++)
    {
        _file_output<< endl << (*_domande_con_risposta_iterator).id_domanda << " " << (*_domande_con_risposta_iterator).id_risposta;
    }
}

template<class T, class R>
const bool FileTest<T,R>::leggiFile()
{
    if(_file_input.eof())
    {
        return 1;
    }else{
        while(!_file_input.eof())
        {
            R id_risposta;
            T id_domanda;

            if(!(_file_input>>id_domanda>>id_risposta)||(getRispostaDaDomanda(id_domanda,ANALISI)!=R()))
            {
                return 1;
            }else{
                immettiNuovoElemento(id_domanda,id_risposta,DA_FILE);
            }
        }
        return 0;
    }
}

#endif // FILETEST_H
