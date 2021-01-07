# Courier
It's basically a route optimization code for a courier that delivers packages( in C language)

Tema consta intr-o harta realizata cu ajutorul unui graf de statii.Fiecare varf al grafului contine un graf aferent clientilor statiei respective.Se vor face multiple operatii asupra matrcelor adiacente grafurilor noastre care vor influenta modul curierului de livrare a coletului

Fiecare client are un nume, o suma de plati si o distanta a unui drum direct catre statie. Fiecare statie contineun nume, un numar de clienti, un vector de clienti si graful aferent clientilor

Functii:


int nrStatie(char nume[])
---ia caracterul corespunzator statiei din client (numarul situat inaintea punctului)


int nrClient(char nume[])
---ia caracterul corespunzator clientului din client sau numarul statiei din statie(ultimul caracter de dupa punct)


Statie *alocareMemorieStatie(FILE *f, Statie *statie, Metrou *metrou)
---citeste datele despre clienti si aloca memoria pentru matrice


Statie *creareHarta(FILE *f, Metrou **metrou) 
---citeste datele despre statii si aloca memoria pentru matrice


void conexiune(FILE *f, FILE *g, Statie *statie)        
---afiseaza OK daca exista legatura intre clienti si NO daca nu


void legatura(FILE *f, FILE *g, Metrou *metrou, Statie *statie)
---afiseaza numele statiilor care au drum direct cu statia apelata si nu e blocat


void blocaj_tunel(FILE *f, Metrou *metrou)      
--- da o vloare mare drumului care semnifica faptul ca e indisponibil


void blocaj_strada(FILE *f, Statie *statie)     
---da o vloare mare strazii care semnifica faptul ca e indisponibila


void adauga_ruta(FILE *f, Metrou *metrou)  
---creaza un drum intre 2 statii si ii da o valoare citita din fisier


void sterge_ruta(FILE *f, Metrou *metrou)
---sterge un drum intre 2 statii prin atribuirea valorii 0  


void adauga_strada(FILE *f, Statie *statie)   
---creaza un drum intre 2 statii si ii da o valoare citita din fisier


void sterge_strada(FILE *f, Statie *statie)
---sterge o strada dintre 2 statii prin atribuirea valorii 0


void comanda_statie(FILE *f, FILE *g, Metrou *metrou ,Statie *statie)
---calculeaza suma adunata la fiecare statie si afiseaza numele statiilor care au suma mai mare sau egala cu o valoare citita 


void BF(FILE *g, Metrou *metrou, Statie *statie, int numar_statie, int poz_statie1, int poz_statie2, int index)
---implementare algoritm belmond ford pentru ambele cerinte(drum_statie/drum_metrou)

void drum(FILE *f, FILE *g, Metrou *metrou, Statie *statie, int index)
---apelarea functiei u algoritmul BF si afisarea solutiei

void timp_statie(FILE *f, FILE *g, Statie *statie)
---calcularea timpului minim prin metoda greedy


void alocareMatrice(FILE *f)
---citeste elementele matricei si aloca memorie 


int isSafe(int x, int y)
---daca urmatoarea mutare e viabila returneaza 1, altfel 0


void minimDrum(int x, int y, int visited[numar_strazi_matrice][numar_strazi_matrice], int *distanta, int *min)
---prin metoda back tracking imi gaseste fiecare solutie si o compar cu un minim predefinit.La final imi afiseaza distanta cea mai scurta dintr-un colt in altul

void alegereDrum()
---imi definesc variabilele care imi trebuie pentru a apela functia gasireDrum
