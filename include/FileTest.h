#ifndef FILETEST_H
#define FILETEST_H
#include <string>
#include <iostream>
#include<vector>
#include<algorithm>
#include <fstream>
#define ANALISI 0
#define FUNZIONAMENTO 1

#define DA_ANALISI 0
#define DA_FUNZIONAMENTO 1

#include "FileOutput.h"
#include "FileInput.h"


using namespace std;

template<class T, class R>
class FileTest : public FileInput , FileOutput
{
    struct test {
        R id_risposta;
        T id_domanda;
        bool ho_risposto;
    };
    public:
        FileTest(){};

        FileTest(const string nome_file):FileInput(nome_file),FileOutput(nome_file){
        };

        virtual ~FileTest();
        R getRispostaDaDomanda(const T id_domanda);
        bool hoFinitoLeDomande();
        void immettiNuovoElemento(const T id_domanda,const R id_risposta);
        void scriviFileOutput();
        bool leggiFile();

    protected:

    private:
        ofstream _output_test_file;
        ifstream _input_test_file;
        string _temp;
        string _nf;

        vector<int> _id_file;
        typename vector<int>::iterator _id_file_it;
        vector<test> _domande_con_risposta;
        typename vector<test>::iterator _domande_con_risposta_iterator;

};



template<class T, class R>
FileTest<T,R>::~FileTest()
{
    //dtor
}

template<class T, class R>

bool FileTest<T, R>::hoFinitoLeDomande(){ // Restituisce 1 se tutte le domande hanno ricevuto risposta
     bool found = 0;

    //Controlla che tutte le domande abbiano risposta
    _domande_con_risposta_iterator = _domande_con_risposta.begin();
    for (; _domande_con_risposta_iterator != _domande_con_risposta.end(); _domande_con_risposta_iterator++){
        if ((*_domande_con_risposta_iterator).ho_risposto == 0){

            found = 1;
        }
    }

    //Da errore se trova almeno una domanda non risposta

 if (found == 1){
        cerr << "Errore: domande non risposte trovate" << endl;
        return 0;
    }
 else {
        return 1;
    }
}

template<class T, class R>

R FileTest<T, R>::getRispostaDaDomanda(const T id_domanda){ //Restituisce ID della risposta dato l'ID della domanda
    bool found = 0;

    _domande_con_risposta_iterator = _domande_con_risposta.begin();

//Cerca un id che corrisponda:


    for (; _domande_con_risposta_iterator != _domande_con_risposta.end(); _domande_con_risposta_iterator++){
        if ((*_domande_con_risposta_iterator).id_domanda == id_domanda){

            //Trovato l'ID segna la domanda come risposta
            //e restituisce l'ID della risposta
            (*_domande_con_risposta_iterator).ho_risposto = 1;
            return (*_domande_con_risposta_iterator).id_risposta;
            found = 1;
        }
    }
    // Restituisce 0 in caso di ID domanda non trovato
    if (found == 0){
        cerr << "ID domanda non trovato" << endl;
        return 0;
    }
}

template<class T, class R>
// Aggiunge un nuovo elemento al vettore degli ID
void FileTest<T, R>::immettiNuovoElemento(const T id_domanda,const R id_risposta){


    test t;
    t.id_domanda = id_domanda;
    t.id_risposta = id_risposta;
    t.ho_risposto = 0;

    _domande_con_risposta.begin();
    _domande_con_risposta.push_back(t);



    _domande_con_risposta_iterator = _domande_con_risposta.begin();


}
template<class T, class R>

void FileTest<T, R>::scriviFileOutput(){   // Salva il file di test con id domanda e id risposta

     cout << "Inserisci nome del file di test (nel caso verra' creato):"<< endl;
     cin >> _nf;

     _output_test_file.open(_nf.c_str());
     if(!_output_test_file.is_open()){

              cout << "Test file did not open" ;
     }
     else{

    _domande_con_risposta_iterator = _domande_con_risposta.begin();

    for (; _domande_con_risposta_iterator != _domande_con_risposta.end(); _domande_con_risposta_iterator++){
        _output_test_file << (*_domande_con_risposta_iterator).id_domanda << " " << (*_domande_con_risposta_iterator).id_risposta << "\n";
    }

    _output_test_file.close();
    cout << "End writing" << endl;
}

}

template<class T, class R>

bool FileTest<T, R>::leggiFile(){ // Restituisce 0 nel caso il file non esista o abbia errori di sintassi

ifstream f(_nf.c_str());

    if (!f.good()){

    cout << "File di test non trovato" << endl;
    return 0;
}
_input_test_file.open(_nf.c_str());

    int id;

    while(!_input_test_file.eof()){
        getline(_input_test_file, _temp, ' ');
        id = atoi(_temp.c_str());

        if (id != 0)
            _id_file.push_back(id);

        getline(_input_test_file, _temp, '\n');
    }
    _id_file_it = _id_file.begin();



   for (int i = 0; i < _id_file.size(); i++) {
    int c = _id_file.at(i);
    for (int j = 0; j < _id_file.size(); j++) {
         if (c == _id_file.at(j) && i != j) {
            cout << "Trovato un errore di sintassi nel file di test: multipla ricorrenza dell' ID " << _id_file.at(i)  <<endl;
            return 0;
         }
    }
}
_input_test_file.close();


return 1;



}

#endif // FILETEST_H
