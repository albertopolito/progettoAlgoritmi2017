#include <iostream>
#include<stdio.h>
#include "GestioneRefertazione.h"
using namespace std;

int main()
{
    GestioneRefertazione<int,int> referto_medico("risposte.txt","domande.txt","start.txt");
    if(referto_medico.analisiSintatticaSemanticaEdInizializzazione())
    {
        cerr<<"errore nell'apertura o nella lettura dei file immessi"<<endl;
        exit(1);
    }else{
        string nome_file_test;
        short int modalita_apertura;
        cout<<"immetti il nome intero del file di test"<<endl;
        cin>>nome_file_test;
        cout<<"immetti 0 se vuoi leggere il file di test e 1 se invece intendi scriverlo"<<endl;
        cin>>modalita_apertura;
        while(modalita_apertura>1||modalita_apertura<0)
        {
            cout<<"errore nella scelta"<<endl;
            cout<<"immetti 0 se vuoi leggere il file di test e 1 se invece intendi scriverlo"<<endl;
            cin>>modalita_apertura;
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
                                   cout<<endl<<referto_medico.getNuovaDomanda()<<endl;
                                   int risposta;
                                   int i=0;
                                   vector<string> risposte=referto_medico.getRisposta();
                                   for(vector<string>::iterator it=risposte.begin();it!=risposte.end();it++)
                                   {
                                       i++;
                                       cout<<i<<" "<<*it<<endl;
                                   }
                                   cin>>risposta;
                                   while(risposta<1||risposta>i||referto_medico.setRisposta(risposte[--risposta]))
                                   {
                                       cout<<"la risposta non è corretta, immetti una nuova risposta"<<endl;
                                       cin>>risposta;
                                   }
                                }
                                cout<<"fine scrittura file di test"<<endl;
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
        }else{
            cerr<<"file di test corrotto o non esistente"<<endl;
            exit(1);
        }
    }
    cout<<"fine refertazione"<<endl;
}
