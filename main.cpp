#include <iostream>
#include<stdio.h>
#include<stdlib.h>
#include "GestioneRefertazione.hpp"
using namespace std;

int main(int argc, char*argv[])
{
    //parte di codice necessaria per il riconoscimento dei file da riga di codice con nomi spaziati
    stringstream riga_di_codice;
    int numero_file=0;
    for(int i=1;i<argc;i++)
    {
        int j=0;
        bool trovato_un_file=0;
        while(argv[i][j]!='\0'&&trovato_un_file==0)
        {
            if(argv[i][j]=='.')
            {
                trovato_un_file=1;
                numero_file++;
            }
            j++;
        }
        riga_di_codice<<argv[i]<<" ";
    }
    if(numero_file==3){
        string nome_file_risposte;
        string nome_file_domande;
        string nome_file_start;
        string estensioni;
        getline(riga_di_codice,nome_file_risposte,'.');
        riga_di_codice>>estensioni;
        nome_file_risposte+=".";
        nome_file_risposte+=estensioni;
        riga_di_codice.ignore();
        getline(riga_di_codice,nome_file_domande,'.');
        riga_di_codice>>estensioni;
        nome_file_domande+=".";
        nome_file_domande+=estensioni;
        riga_di_codice.ignore();
        getline(riga_di_codice,nome_file_start,'.');
        riga_di_codice>>estensioni;
        nome_file_start+=".";
        nome_file_start+=estensioni;
        //fine generazione nomi dei file
        GestioneRefertazione<int ,int> referto_medico(nome_file_risposte,nome_file_domande,nome_file_start);
        if(referto_medico.analisiSintatticaSemanticaEdInizializzazione())
        {
            cerr<<"errore nell'apertura o nella lettura dei file immessi"<<endl;
            exit(1);
        }else{
            string nome_file_test;
            string modalita_apertura;
            cout<<"immetti il nome intero del file di test"<<endl;
            getline(cin,nome_file_test);
            cout<<"immetti 0 se vuoi leggere il file di test e 1 se invece intendi scriverlo"<<endl;
            cin>>modalita_apertura;
            while(modalita_apertura!="1"&&modalita_apertura!="0")
            {
                cout<<"errore nella scelta"<<endl;
                cout<<"immetti 0 se vuoi leggere il file di test e 1 se invece intendi scriverlo"<<endl;
                cin>>modalita_apertura;
            }
            referto_medico.setModalitaDiFunzionamentoFileTest(atoi(modalita_apertura.c_str()));
            if(!referto_medico.apriLetturaScritturaFileTest(nome_file_test))
            {
                switch(atoi(modalita_apertura.c_str()))
                {
                    case LETTURA:   cout<<endl<<"inizio lettura domande"<<endl;
                                    while(!referto_medico.fineDomande())
                                    {
                                    cout<<endl<<"D: "<<referto_medico.getNuovaDomanda()<<endl;
                                    cout<<"R: "<<referto_medico.getRisposta()<<endl;
                                    }
                                    cout<<endl<<"fine lettura domande"<<endl<<endl;
                                    break;
                    case SCRITTURA: while(!referto_medico.fineDomande())
                                    {
                                    cout<<endl<<referto_medico.getNuovaDomanda()<<endl;
                                    int risposta;
                                    int i=0;
                                    vector<string> risposte=referto_medico.getRispostePossibili();
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
                cin.ignore();
                getline(cin,nome_file_log);
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
        cout<<"refertazione conclusa con successo"<<endl;
    }else{
        cerr<<"non conformita' nel numero dei file iniziali"<<endl;
        exit(1);
    }
}
