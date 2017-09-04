#include <iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string>
#include "GestioneRefertazione.h"
using namespace std;

int main()
{
    GestioneRefertazione<string,string> referto_medico("answers.txt","nome.txt","starting_sequence.txt");
    if(referto_medico.analisiSintatticaSemanticaEdInizializzazione())
    {
        cerr<<"Errore apertura o lettura file"<<endl;
        exit(1);
    }else{
        string nome_file_test;
        bool modalita_apertura;
        cout<<"Nome File Test: > "<<endl;
        cin>>nome_file_test;
        if(nome_file_test.find(".")==string::npos)
        {
            nome_file_test.append(".txt");
        }
        cout<<"[0] Leggere il File"<<endl;
        cout<<"[1] Scrivere il File"<<endl;
        cout<<"> "<<endl;
        while(!cin>>modalita_apertura)
        {
            cout<<"Errore nella scelta"<<endl;
            system("cls");
            cout<<"[0] Leggere il File"<<endl;
            cout<<"[1] Scrivere il File"<<endl;
            cout<<"> "<<endl;
        }
        referto_medico.setModalitaDiFunzionamentoFileTest(modalita_apertura);
        if(!referto_medico.apriLetturaScritturaFileTest(nome_file_test))
        {
            switch(modalita_apertura)
            {
                case LETTURA:
                                break;
                case SCRITTURA: while(!referto_medico.fineDomande())
                                {
                                   cout<<referto_medico.getNuovaDomanda()<<endl;
                                   int risposta;
                                   int i=0;
                                   vector<string> risposte=referto_medico.getRisposta();
                                   for(vector<string>::iterator it=risposte.begin();it!=risposte.end();it++)
                                   {
                                       i++;
                                       cout<<i<<" "<<*it<<endl;
                                   }
                                   while(!cin>>risposta||referto_medico.setRisposta(referto_medico.getRisposta()[risposta--]))
                                   {
                                       cout<<"la risposta non è corretta, immetti una nuova risposta"<<endl;
                                   }
                                }
                                referto_medico.scriviFileTest();
                                break;
            }
            string nome_file_log;
            cout<<"immettere il nome per intero del file di log"<<endl;
            cin>>nome_file_log;
            if(referto_medico.daFileDiTestAFileDiLog(nome_file_log))
            {
                cerr<<"errore nell'apertura o nella scrittura del file immesso"<<endl;
                exit(1);
            }
        }
    }
    cout<<"fine refertazione"<<endl;
}
