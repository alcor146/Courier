#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define INFINIT 100000



typedef struct Graph_Metrou
{

    int N, M;
    int **matrice_de_adiacenta_distanta;
} Metrou;


typedef struct Client
{

    char *nume_client;
    int suma_de_plati;
    int timp_fata_de_statia_de_metrou;

} Client;


typedef struct Grapf_Client
{

    int strazi_intre_clienti;
    int **matrice_de_adiacenta_timp;
} G_client;


typedef struct Statie_metrou
{

    char *nume;
    int numar_clienti;
    Client *cl;
    G_client *gClient;
} Statie;



int numar_strazi_matrice;

int **matrice_de_parcurgere_strazi_pana_la_sediu;



int nrStatie(char nume[])        //ia caracterul corespunzator statiei din client
{
    int numar_statie;

    if(nume[strlen(nume)-2] == '.')
        numar_statie = (nume[strlen(nume)-3] - '0');

    else
        numar_statie = (nume[strlen(nume)-4] - '0');

    return numar_statie-1;
}


int nrClient(char nume[])        //ia caracterul corespunzator clientului din client sau numarul statiei din statie(ultimul/penultimul caracter)
{
    int numar_client;

        numar_client = (nume[strlen(nume)-1] - '0');

    if(nume[strlen(nume)-2] >= '0' && nume[strlen(nume)-2] <= '9')
        numar_client += 10*(nume[strlen(nume)-2] - '0');   

    return numar_client -1;
}



Statie *alocareMemorieStatie(FILE *f, Statie *statie, Metrou *metrou)   //citeste si aloca memorie pt clienti
{
    int i, j;
    int lungime, latime;

    for(i=0; i<metrou->N; i++)
    {
        statie[i].nume = (char*)malloc(sizeof(char)*15);
        if(statie[i].nume == NULL)
        {
            printf("wefnwej");
        }

        fscanf(f, "%s", statie[i].nume);
       // printf("%s\n", statie[i].nume);

        fscanf(f, "%d\n", &statie[i].numar_clienti);
        //printf("%d\n", statie[i].numar_clienti);

        statie[i].cl = (Client*)malloc(sizeof(Client)*(statie[i].numar_clienti));


        for(j=0; j<statie[i].numar_clienti; j++)
        {
            statie[i].cl[j].nume_client = (char*)malloc(sizeof(char)*15);
            fscanf(f, "%s", statie[i].cl[j].nume_client);
            //printf("%s\n", statie[i].cl[j].nume_client);

            fscanf(f, "%d\n", &statie[i].cl[j].timp_fata_de_statia_de_metrou);
            
            //printf("%d\n", statie[i].cl[j].timp_fata_de_statia_de_metrou);

            fscanf(f, "%d\n", &statie[i].cl[j].suma_de_plati);
            
            //printf("%d\n", statie[i].cl[j].suma_de_plati);
        }

        statie[i].gClient = (G_client*)malloc(sizeof(G_client));


        statie[i].gClient->matrice_de_adiacenta_timp = (int**)malloc((statie[i].numar_clienti)*sizeof(int*));

        for(j=0; j<statie[i].numar_clienti; j++)
            statie[i].gClient->matrice_de_adiacenta_timp[j] = (int*)calloc(statie[i].numar_clienti, sizeof(int));
        

        char numeClient1[15], numeClient2[15];

        fscanf(f, "%d\n", &statie[i].gClient->strazi_intre_clienti);
        
        //printf("%d\n", statie[i].gClient->strazi_intre_clienti);

        for(j=0; j<statie[i].gClient->strazi_intre_clienti; j++)
            {
                fscanf(f, "%s", numeClient1);
                //printf("%s\n", numeClient1);

                lungime = nrClient(numeClient1);
                //printf("%d\n", lungime);


                fscanf(f, "%s", numeClient2);
                //printf("%s\n", numeClient2);

               latime = nrClient(numeClient2);
                //printf("%d\n", latime);


                fscanf(f, "%d\n", &statie[i].gClient->matrice_de_adiacenta_timp[lungime][latime]);
                //printf("%d\n", statie[i].gClient->matrice_de_adiacenta_timp[lungime][latime]);
                
                statie[i].gClient->matrice_de_adiacenta_timp[latime][lungime] = statie[i].gClient->matrice_de_adiacenta_timp[lungime][latime];
            }
    }    

    return statie;
}



Statie *creareHarta(FILE *f, Metrou **metrou)   //citeste si aloca memorie pt statii si metrou
{

    Statie *statie;

    int i, j, l;

    int lungime, latime;

    (*metrou) = (Metrou*)malloc(sizeof(Metrou));

    if(*metrou == NULL)
    {
        printf("JUST WHY");
    }

    fscanf(f, "%d\n", &(*metrou)->N);
    
    //printf("%d\n", (*metrou)->N);


    statie = (Statie*)malloc(((*metrou)->N)*sizeof(Statie));

    statie = alocareMemorieStatie(f, statie, *metrou);


    fscanf(f, "%d\n", &(*metrou)->M);
    
    //printf("%d\n", (*metrou)->M);

    (*metrou)->matrice_de_adiacenta_distanta = (int **)malloc(sizeof(int*)*((*metrou)->N));

    for(i=0; i<(*metrou)->N; i++)
        (*metrou)->matrice_de_adiacenta_distanta[i] = (int *)calloc((*metrou)->N, sizeof(int));


    for(i=0; i<(*metrou)->M; i++)
    {
        char numeStatie1[15], numeStatie2[15];

        fscanf(f, "%s", numeStatie1);
        //printf("%s\n", numeStatie1);

        fscanf(f, "%s", numeStatie2);
        //printf("%s\n", numeStatie2);

        lungime = nrClient(numeStatie1);
        //printf("%d\n", lungime);
        latime= nrClient(numeStatie2);
        //printf("%d\n", latime);

        fscanf(f, "%d\n", &(*metrou)->matrice_de_adiacenta_distanta[lungime][latime]);
        
        //printf("%d\n", (*metrou)->matrice_de_adiacenta_distanta[lungime][latime]);
        (*metrou)->matrice_de_adiacenta_distanta[latime][lungime] = (*metrou)->matrice_de_adiacenta_distanta[lungime][latime]; 

    }

    return statie;

}




void conexiune(FILE *f, FILE *g, Statie *statie)        //afiseaza OK daca exista legatura intre clienti si NO daca nu
{
    char client1[15], client2[15];

    fscanf(f, "%s", client1); 
    fscanf(f, "%s", client2);

    int lungime = nrClient(client1);    //pozitiile in matrice folosind functiile de mai sus
    int latime = nrClient(client2);
    int i = nrStatie(client1);  

    if(statie[i].gClient->matrice_de_adiacenta_timp[lungime][latime] != 0)
        {
            if(statie[i].gClient->matrice_de_adiacenta_timp[lungime][latime] != INFINIT)
                     fprintf(g, "OK\n");
        }

    else
        fprintf(g, "NO\n");
}





void legatura(FILE *f, FILE *g, Metrou *metrou, Statie *statie)     //afiseaza numele statiilor care au drum direct cu statia apelata si nu e blocat
{
    char statie_legata[15];

    fscanf(f, "%s", statie_legata);

    int i;

    int lungime = nrClient(statie_legata);  //linia din matrice corespunzatoare statiei

    for(i=0; i<metrou->N; i++)
        {
            if(metrou->matrice_de_adiacenta_distanta[lungime][i] != 0)
                if(metrou->matrice_de_adiacenta_distanta[lungime][i] != INFINIT)
                    fprintf(g, "%s ", statie[i].nume);
        }

    fprintf(g, "\n");   
}


void blocaj_tunel(FILE *f, Metrou *metrou)      // da o vloare mare drumului care semnifica faptul ca e indisponibil
{
    char statie1[15], statie2[15];

    fscanf(f, "%s", statie1);
    fscanf(f, "%s", statie2);

    int lungime = nrClient(statie1);
    int latime= nrClient(statie2);

    if(metrou->matrice_de_adiacenta_distanta[lungime][latime] != 0)         
        {
            metrou->matrice_de_adiacenta_distanta[lungime][latime] = INFINIT;
            metrou->matrice_de_adiacenta_distanta[latime][lungime] = INFINIT;
        }    
}


void blocaj_strada(FILE *f, Statie *statie)     //da o vloare mare strazii care semnifica faptul ca e indisponibila
{
    char client1[15], client2[15];

    fscanf(f, "%s", client1);
    fscanf(f, "%s", client2);
  
    int lungime = nrClient(client1);
    int latime= nrClient(client2);

    if(statie[ nrStatie(client1) ].gClient->matrice_de_adiacenta_timp[lungime][latime]  != 0)
       {
         statie[ nrStatie(client1) ].gClient->matrice_de_adiacenta_timp[lungime][latime] = INFINIT;
         statie[ nrStatie(client1) ].gClient->matrice_de_adiacenta_timp[latime][lungime] = INFINIT;
       }
}

    
void adauga_ruta(FILE *f, Metrou *metrou)       
{
    char statie1[15], statie2[15];
    int distanta;

    fscanf(f, "%s", statie1);
    fscanf(f, "%s", statie2);
    fscanf(f, "%d", &distanta);

    int lungime = nrClient(statie1);
    int latime= nrClient(statie2);

    if(metrou->matrice_de_adiacenta_distanta[lungime][latime] == 0)         
     {
           metrou->matrice_de_adiacenta_distanta[latime][lungime] = distanta;   //creaza un drum intre 2 statii si ii da o valoare citita din fisier
           metrou->matrice_de_adiacenta_distanta[lungime][latime] = distanta;
           
     }
}

void sterge_ruta(FILE *f, Metrou *metrou)   
{
    char statie1[15], statie2[15];

    fscanf(f, "%s", statie1);
    fscanf(f, "%s", statie2); 

    int lungime = nrClient(statie1);
    int latime= nrClient(statie2);
    
    metrou->matrice_de_adiacenta_distanta[lungime][latime] = 0;     //sterge un drum intre 2 statii prin atribuirea valorii 0
    metrou->matrice_de_adiacenta_distanta[latime][lungime] = 0;     
}


void adauga_strada(FILE *f, Statie *statie)     
{
    char client1[15], client2[15];
    int distanta;

    fscanf(f, "%s", client1);
    fscanf(f, "%s", client2);
    fscanf(f, "%d", &distanta);

    int lungime = nrClient(client1);
    int latime= nrClient(client2);
    int i = nrStatie(client1);


    if(statie[i].gClient->matrice_de_adiacenta_timp[lungime][latime] == 0)
        {
            statie[i].gClient->matrice_de_adiacenta_timp[lungime][latime] = distanta;       //creaza un drum intre 2 statii si ii da o valoare citita din fisier
            statie[i].gClient->matrice_de_adiacenta_timp[latime][lungime] = distanta;
        }
}


void sterge_strada(FILE *f, Statie *statie)
{
    char client1[15], client2[15];

    fscanf(f, "%s", client1);
    fscanf(f, "%s", client2);

    int lungime = nrClient(client1);
    int latime= nrClient(client2);
    int i = nrStatie(client1);

    statie[i].gClient->matrice_de_adiacenta_timp[lungime][latime] = 0;       //sterge o strada dintre 2 statii prin atribuirea valorii 0
    statie[i].gClient->matrice_de_adiacenta_timp[latime][lungime] = 0;    

}


void comanda_statie(FILE *f, FILE *g, Metrou *metrou ,Statie *statie)   //calculeaza suma adunata la fiecare statie si afiseaza numele statiilor 
                                                                        //care au suma mai mare sau egala cu o valoare citita 
{
    int valoare_suma, i, j;
    int suma_statie;

    fscanf(f, "%d", &valoare_suma);

    for(i=0; i<metrou->N; i++)
    {
        suma_statie = 0;

        for(j=0; j<statie[i].numar_clienti; j++)
            suma_statie += statie[i].cl[j].suma_de_plati;

        if(suma_statie >= valoare_suma)
                fprintf(g, "%s ", statie[i].nume);
   
    }

    fprintf(g, "\n");

}



void BF(FILE *g, Metrou *metrou, Statie *statie, int numar_statie, int poz_statie1, int poz_statie2, int index)
{
    int i, j, k, m;
    char drum[200] = "";
    int lungime;

    if(index == 0)              //daca cerinta este drum_statie, ne raportam la graful matroului
        lungime = metrou->N;    //altfel, la cel al clientilor
    else                                             
        lungime = statie[numar_statie].numar_clienti;
        

        int dist[lungime];
        int pred[lungime];
    

    for ( i = 0; i < lungime; i++)
        {
          dist[i] = INFINIT;
          pred[i]= -1;
        }
    
    dist[poz_statie1]=0; 

    
    for (i = 0; i < lungime -1 ; i++)
        for (j = 0; j < lungime ; j++)
            for (k = 0; k< lungime ; k++)
               {
                    if(index == 0)
                    {
                    if (metrou->matrice_de_adiacenta_distanta[j][k]!=0 
                        &&dist[k] >dist[j]+metrou->matrice_de_adiacenta_distanta[j][k])
                        {
                        dist[k] =dist[j]+metrou->matrice_de_adiacenta_distanta[j][k];
                        pred[k]=j;
                        }
                    }

                    else
                    {
                    if (statie[numar_statie].gClient->matrice_de_adiacenta_timp[j][k] != 0 
                        &&dist[k] >=dist[j]+statie[numar_statie].gClient->matrice_de_adiacenta_timp[j][k])
                        {
                        dist[k] =dist[j]+statie[numar_statie].gClient->matrice_de_adiacenta_timp[j][k];
                        pred[k]=j;
                        }
                    }
               }       

       int aux[15], n=0;

do
    {
         aux[n] = poz_statie2;
         n++;                                       //parcurgem vectorul de predecesori de la statia la care trebuie sa ajungem la cea de la care am plecat
                                                    //tinem minte pozitiile statiilor corespunzatoare de pe parcurs intr-un vector aux
         poz_statie2 = pred[poz_statie2];           //parcurgem vectorul aux de la final la inceut si afisam statiile corespunzatoare pozitiilor din vector

    } while(poz_statie2 != pred[poz_statie1]);      

    if(index == 0)
    {
        for(i=n-1; i>=0; i--)
            {
            strcat(drum, statie[aux[i]].nume);
            strcat(drum, " ");
            }    
    }

    else if(index == 1)
    {
        for(i=n-1; i>=0; i--)
            {
            strcat(drum, statie[numar_statie].cl[aux[i]].nume_client);
            strcat(drum, " ");
            }
    }

    fprintf(g, "%s\n", drum);

}



void drum(FILE *f, FILE *g, Metrou *metrou, Statie *statie, int index)
{
    char nume1[15], nume2[15];      //numele statiilor/clientilor
    int variabila_irelevanta;

    fscanf(f, "%s", nume1);
    fscanf(f, "%s", nume2);

    int poz_1 = nrClient(nume1);      //pozitiile clientilor/ statiilor daca ne referim la drum_metrou
    int poz_2 = nrClient(nume2);

    if(index == 0)          //drum_metrou
        BF(g, metrou, statie, 0, poz_1, poz_2, 0);  //poz statiei e irelevanta   

    else                    //drum_strada
        {
            int poz = nrStatie(nume1);      //poz statiei in drum_statie
            BF(g, metrou, statie, poz, poz_1, poz_2, 1);   
        }
}




void timp_statie(FILE *f, FILE *g, Statie *statie)
{
    char nume_statie[15];
    int min = INFINIT;

    fscanf(f, "%s", nume_statie);

    int poz_statie = nrClient(nume_statie);      //indexul statiei la care ne raportam

    int i, poz, timp = 0;

    int visited[statie[poz_statie].numar_clienti];

    for(i=0; i<statie[poz_statie].numar_clienti; i++)
        {
            visited[i] = 0;

            if(statie[poz_statie].cl[i].timp_fata_de_statia_de_metrou < min)     // determinarea celui mai apropiat client
            {
                min = statie[poz_statie].cl[i].timp_fata_de_statia_de_metrou;
                poz = i;
            }
        }
  

    timp += statie[poz_statie].cl[poz].timp_fata_de_statia_de_metrou;       //adaugam timpul de la statie la cel mai apropiat client
    visited[poz] = 1;                                                       //il marcam ca vizitat

    int aux, j;

    for(i=0; i<statie[poz_statie].numar_clienti -1; i++)    
        {   
            min = INFINIT; 
            
                for(j=0; j<statie[poz_statie].numar_clienti; j++)      //pt fiecare client 
                    if(visited[j] == 0)                                //nevizitat
                        if(statie[poz_statie].gClient->matrice_de_adiacenta_timp[poz][j] < min              //aflam distanta pana la el
                            && statie[poz_statie].gClient->matrice_de_adiacenta_timp[poz][j] != 0)          //si care este cel mai apropiat de poz actuala
                                {
                                    min = statie[poz_statie].gClient->matrice_de_adiacenta_timp[poz][j];
                                    aux = j;
                                }
        
                    

            if(min != INFINIT) 
                        {   visited[aux] = 1;
                            timp += statie[poz_statie].gClient->matrice_de_adiacenta_timp[poz][aux];        //dupa ce l-am gasit il adaugam la timp
                            poz = aux;
                        }        
        }

    timp += statie[poz_statie].cl[poz].timp_fata_de_statia_de_metrou;       //adaugam timpul de la ultimul client inapoi la statie

    fprintf(g, "%d\n", timp);

}


void alocareMatrice(FILE *f, int n)
{
    int i, j;

    matrice_de_parcurgere_strazi_pana_la_sediu = (int **)malloc(n*sizeof(int*));

    for(i=0; i<n; i++)
        matrice_de_parcurgere_strazi_pana_la_sediu[i] = (int *)malloc(n*sizeof(int));

    for(i=0; i<n; i++)
        for(j=0; j<n; j++)
            fscanf(f, "%d", &matrice_de_parcurgere_strazi_pana_la_sediu[i][j]);

}


int isSafe(int x, int y)    //daca se afla in matrice
{
    return (x >= 0 && x < numar_strazi_matrice && y >= 0 && y < numar_strazi_matrice);
}




void minimDrum(int x, int y, int visited[numar_strazi_matrice][numar_strazi_matrice], int *distanta, int *min)        //imi gaseste fiecare drum
{                                                                                                                     //face suma elementelor parcurse
                                                                                                                      //daca gaseste un frum mai scurt il afieaza
    if (x == numar_strazi_matrice - 1 && y == numar_strazi_matrice - 1) 
    {
        if(*distanta + matrice_de_parcurgere_strazi_pana_la_sediu[x][y] < *min)
            *min = *distanta + matrice_de_parcurgere_strazi_pana_la_sediu[x][y];
        return;
    }

 
    visited[x][y] = 1;
    *distanta += matrice_de_parcurgere_strazi_pana_la_sediu[x][y];   //pozitia la care suntem la momentul asta
    

    if (isSafe(x, y)) 
    {
       
        if (x + 1 < numar_strazi_matrice && !visited[x + 1][y])
            minimDrum(x + 1, y, visited, distanta, min);
            

        if (y + 1 < numar_strazi_matrice && !visited[x][y + 1])
            minimDrum(x, y + 1, visited, distanta, min);
            
    }
    
    visited[x][y] = 0;                                                //ne intoarcem pana gasim inca o cale
    *distanta -= matrice_de_parcurgere_strazi_pana_la_sediu[x][y];
}


void gasireDrum(FILE *f)                                            //initializam matricea de pozitii vizitate
{                                                                   //apelam functia minimDrum
    int visited[numar_strazi_matrice][numar_strazi_matrice];
    int distanta = 0;
    int minim = 1000;

    for(int i=0; i<numar_strazi_matrice; i++)
        for(int j=0; j<numar_strazi_matrice; j++)
            visited[i][j] = 0;

    minimDrum(0, 0, visited, &distanta, &minim);

    fprintf(f, "%d\n", minim);


}



void eliberareMemorie(Statie *statie, Metrou *metrou)
{
int i, j;

      for(i=0; i<metrou->N; i++)
    {
        free(statie[i].nume);

        for(j=0; j<statie[i].numar_clienti; j++)
            free(statie[i].cl[j].nume_client);

        free(statie[i].cl);

        for(j=0; j<statie[i].numar_clienti; j++)
            free(statie[i].gClient->matrice_de_adiacenta_timp[j]);

        free(statie[i].gClient->matrice_de_adiacenta_timp);
        free(statie[i].gClient);
    }

    free(statie);

    for(i=0; i<metrou->N; i++)
        free(metrou->matrice_de_adiacenta_distanta[i]);

    free(metrou->matrice_de_adiacenta_distanta);
    free(metrou);

}

        



int main(int argc, char *argv[])
{

    FILE *f1 = fopen(argv[1], "rt");
    if(f1 == NULL)
    {
        printf("sad reacts only\n");
    }


    FILE *f2 = fopen(argv[2], "wt");
    if(f2 == NULL)
    {
        printf("huehuehue\n");
    }

    Metrou *metrou;
    Statie *statie;

    int i;

    statie = creareHarta(f1, &metrou);

    int numar_operatii;
    char nume_operatie[15];

    fscanf(f1, "%d", &numar_operatii);

    for(i=0; i<numar_operatii; i++)
    {
        fscanf(f1, "%s", nume_operatie);


        if(strcmp(nume_operatie, "conexiune") == 0)             conexiune(f1, f2, statie);
        else if(strcmp(nume_operatie, "legatura") == 0)         legatura(f1, f2, metrou, statie);
        else if(strcmp(nume_operatie, "blocaj_tunel") == 0)     blocaj_tunel(f1, metrou);
        else if(strcmp(nume_operatie, "blocaj_strada") == 0)    blocaj_strada(f1, statie);
        else if(strcmp(nume_operatie, "adauga_ruta") == 0)      adauga_ruta(f1, metrou);
        else if(strcmp(nume_operatie, "sterge_ruta") == 0)      sterge_ruta(f1, metrou);
        else if(strcmp(nume_operatie, "adauga_strada") == 0)    adauga_strada(f1, statie);
        else if(strcmp(nume_operatie, "sterge_strada") == 0)    sterge_strada(f1 , statie);
        else if(strcmp(nume_operatie, "drum_strada") == 0)      drum(f1, f2, metrou, statie, 1);
        else if(strcmp(nume_operatie, "drum_metrou") == 0)      drum(f1, f2, metrou, statie, 0);
        else if(strcmp(nume_operatie, "timp_statie") == 0)      timp_statie(f1, f2, statie);
        else if(strcmp(nume_operatie, "comanda_statie") == 0)   comanda_statie(f1, f2, metrou, statie);
    }

    fscanf(f1, "%d", &numar_strazi_matrice);
    if(numar_strazi_matrice > 0)
        {
        alocareMatrice(f1, numar_strazi_matrice);
        gasireDrum(f2);

        for(i=0; i<numar_strazi_matrice; i++)  
            free(matrice_de_parcurgere_strazi_pana_la_sediu[i]);
                        
        free(matrice_de_parcurgere_strazi_pana_la_sediu);
    }

    eliberareMemorie(statie, metrou);



fclose(f1);
fclose(f2);



    return 0;
}
