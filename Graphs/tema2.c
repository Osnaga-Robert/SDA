#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 999

typedef struct graf //am definit o structura mai ampla pentru grafuri
{
    int n, m, d;
    float **mat_graf_ponderat;
    int **mat_graf_adiacenta;
    int *depozite;
    int total;
} graf; 

typedef struct task1 //o structura pentru output-ul task-ului 1
{
    int nod;
    float cost_drum[2];
    int *drum;
    int elem_drum;
} task1;

typedef struct nod //o lista in caz de avem nevoie
{
    int elem;
    struct nod *next;
} Nod, *List;

typedef struct //in final,o stiva 
{
    int *elements;
    int top;
    int maxSize;
} TStack;

void adauga_graf_ponderat(graf g, int i, int j, float a)
{
    g.mat_graf_ponderat[i][j] = a;
}

void printare_graf_ponderat(graf g)
{
    for (int i = 0; i < g.n; i++)
    {
        for (int j = 0; j < g.n; j++)
            printf("%f ", g.mat_graf_ponderat[i][j]);
        printf("\n");
    }
}

float dijkstra(graf g, int start, int end, task1 output, int *nr)
{
    float **cost, *distanta; //mai intai vom lua o matrice de cost de tip float si un vector de distanta care reprezinta distanta minima catre fiecare punct
    int *predecesor, *vizitat; //vom mai lua doi vector care prezinta predecesor, respectiv vizitarea unui noi sau nu
    int urm_nod;
    cost = (float **)malloc(g.n * sizeof(float *)); //alocam dinamic 
    for (int i = 0; i < g.n; i++)
        cost[i] = (float *)malloc(g.n * sizeof(float));
    distanta = (float *)malloc(g.n * sizeof(float));
    predecesor = (int *)malloc(g.n * sizeof(int));
    vizitat = (int *)malloc(g.n * sizeof(int));

    for (int i = 0; i < g.n; i++)
    {
        for (int j = 0; j < g.n; j++)
        {
            if (g.mat_graf_ponderat[i][j] == 0)
            {
                cost[i][j] = MAX; //daca in matricea ponderilor exista 0, atunci in matrice noastra com adauga o valoare maxima
            }
            else
            {
                cost[i][j] = g.mat_graf_ponderat[i][j]; //in caz contrat, vom adauga exact elementul
            }
        }
        distanta[i] = cost[i][start]; //vom initializa fiecare distanta de inceput
        predecesor[i] = start; 
        vizitat[i] = 0;
    }
    distanta[start] = 0; //distanta dintre nodul de inceput si el insusi este 0
    vizitat[start] = 1; //asta inseamna ca deja l-am vizitat

    for(int a = 0 ; a < g.n -1 ; a++)
    {
        float minim = MAX; //vom lua un minim de fiecare data cand calculam lungime minima dintre doua puncte
        for (int i = 0; i < g.n; i++)
            if (distanta[i] < minim && vizitat[i] == 0) //daca descoperim un minim intr-un nod nevizitat, atunci il schimbam,iar urm_nod va deveni chiar nodul respectiv
            {
                minim = distanta[i];
                urm_nod = i;
            }
        vizitat[urm_nod] = 1; //il notam ca si cum l-am vizitat
        for (int i = 0; i < g.n; i++)
        {
            if (vizitat[i] == 0)
            {
                if (minim + cost[i][urm_nod] < distanta[i]) // daca suma dintre minim si costul este mai mica decat distata miniminca, atunci vom adauga in vector aceea valoare
                {
                    distanta[i] = minim + cost[i][urm_nod];
                    predecesor[i] = urm_nod;
                }
            }
        }
    }

    int a = end; //aflam ruta pe care o parcurge start pana la end
    do
    {
        a = predecesor[a];
        *nr = *nr + 1;
        output.drum[*nr] = a;
    } while (a != start);
    float raspuns = distanta[end]; // returnam distanta totatla,dupa care eliberam memoria
    free(vizitat);
    free(predecesor);
    free(distanta);
    for (int i = 0; i < g.n; i++)
        free(cost[i]);
    free(cost);
    return raspuns;
}

void initStack(TStack *s, int maxSize) //functie pentru initializarea unei stive
{
    int *newst;
    newst = (int *)malloc(sizeof(int) * maxSize);
    if (newst == NULL)
    {
        printf("Eroare\n");
        exit(1);
    }
    s->elements = newst;
    s->maxSize = maxSize;
    s->top = -1;
}

int isEmptyStack(TStack *s)
{
    return (*s).top < 0;
}

int isFullStack(TStack *s)
{
    return s->top >= s->maxSize - 1;
}

void push(TStack *s, int elem) //push pe stiva
{
    if (isFullStack(s))
    {
        printf("Stiva plina\n");
        exit(1);
    }
    s->elements[++s->top] = elem;
}

int pop(TStack *s) //pop pe stiva
{
    if (isEmptyStack(s))
    {
        printf("Stiva goala\n");
        exit(1);
    }
    return s->elements[s->top--];
}

void DFS(graf g, int start, TStack *stiva, int *vizitat)
{
    vizitat[start] = 1;
    push(stiva, start);
    for (int j = 0; j < g.n; j++)
    {
        if (g.mat_graf_ponderat[start][j] != 0 && vizitat[j] == 0)
        {
            DFS(g, j, stiva, vizitat);
        }
    }
}

void modificat(float **g, int nr, int start, TStack *stiva, int *vizitat) //este acelasi algoritm ca la DFS, dar de data asta 
                                                                        //se aplica pe matricea transpusa si are niste elemente diferite la declararea functiei
{
    vizitat[start] = 1;
    push(stiva, start);
    for (int j = 0; j < nr; j++)
    {
        if (g[start][j] != 0 && vizitat[j] == 0)
        {
            modificat(g, nr, j, stiva, vizitat);
        }
    }
}

void reverse_matrix(graf g, float **a) //functie pentru inversarea grafului
{
    for (int i = 0; i < g.n; i++)
        for (int j = 0; j < g.n; j++)
            if (g.mat_graf_ponderat[i][j] != 0)
                a[j][i] = g.mat_graf_ponderat[i][j];
}

void initS(List *s) //initializare lista
{
    (*s)->next = NULL;
}

int emptyS(List *s)
{
    return ((*s)->next == NULL);
}

void push_list(List *s, int x) //push pe lista
{
    List nou = (List)malloc(sizeof(Nod));
    nou->elem = x;
    nou->next = (*s);
    (*s) = nou;
}

int pop_list(List *s) //pop pe lista
{
    List p;
    int rez;
    p = (*s)->next;
    rez = p->elem;
    (*s)->next = p->next;
    free(p);
    return rez;
}

int main()
{
    graf magazin; //ne luam la inceput un graf
    int u, v, nr_taskuri, depozit_task1;
    float total_task1 = 0;
    int *sir_task1, nr_noduri;
    float w;
    char tip[3];
    scanf("%d%d%d", &magazin.n, &magazin.m, &magazin.d); //citim tot ce ni se da din input
    magazin.mat_graf_ponderat = (float **)malloc(magazin.n * sizeof(float *));
    for (int i = 0; i < magazin.n; i++)
        magazin.mat_graf_ponderat[i] = (float *)malloc(magazin.n * sizeof(float));
    for (int i = 0; i < magazin.n; i++)
        for (int j = 0; j < magazin.n; j++)
            magazin.mat_graf_ponderat[i][j] = 0;
    for (int i = 0; i < magazin.m; i++)
    {
        scanf("%d%d%f", &u, &v, &w);
        adauga_graf_ponderat(magazin, u, v, w);
    }
    magazin.depozite = (int *)malloc(magazin.d * sizeof(int));
    for (int i = 0; i < magazin.d; i++)
    {
        scanf("%d", &magazin.depozite[i]);
    }
    scanf("%d", &nr_taskuri);
    scanf("%s", tip);
    if (!strcmp("e1", tip)) //daca tipul exercitiului este 1
    {
        for (int i = 0; i < nr_taskuri; i++) //repetam acelasi exercitiu de nr_taskuri ori luand mereu input-ul care va urma
        {
            if (i != 0)
            {
                scanf("%s", tip);
                printf("\n");
            }
            total_task1 = 0;
            scanf("%d", &depozit_task1); //depozitul de unde incepe cautarea
            scanf("%d", &nr_noduri);
            sir_task1 = (int *)malloc(nr_noduri * sizeof(int)); //nodurile prin care vom cauta costul minim
            task1 *output = (task1 *)malloc(2 * nr_noduri * sizeof(task1));
            for (int i = 0; i < nr_noduri; i++)
                scanf("%d", &sir_task1[i]);
            for (int i = 0; i < nr_noduri; i++)
            {
                int cnt = -1; //luam un cnt = - 1 pentru a afla cate elemente se afla pe stiva
                output[2 * i].nod = sir_task1[i]; //nodul cu care va incepe cautarea
                output[2 * i + 1].nod = depozit_task1;
                output[2 * i].drum = (int *)malloc(magazin.n * sizeof(int)); //alocam cu numarul de elemente maxime posibile
                output[2 * i + 1].drum = (int *)malloc(magazin.n * sizeof(int));
                output[2 * i].cost_drum[0] = dijkstra(magazin, depozit_task1, sir_task1[i], output[2 * i], &cnt); //aplicam algoritmul lui dijkstra de la depozit pana la pucntul ala
                output[2 * i].elem_drum = cnt + 1;//stocam nr de elemete de pe stiva
                cnt = -1;
                output[2 * i].cost_drum[1] = dijkstra(magazin, sir_task1[i], depozit_task1, output[2 * i + 1], &cnt);//aplicam invers
                output[2 * i + 1].elem_drum = cnt + 1;
                total_task1 += output[2 * i].cost_drum[0] + output[2 * i].cost_drum[1]; //total_task1 reprezinta suma finala totala
            }
            free(sir_task1); //dezalocam de fiecare data
            for (int i = 0; i < 2 * nr_noduri; i += 2) //printam rezultatul asa cum ni se cere
            {
                printf("%d\n", output[i].nod);
                printf("%.01f %.01f\n", output[i].cost_drum[1], output[i].cost_drum[0]);
                printf("%d", depozit_task1);
                for (int j = 0; j < output[i + 1].elem_drum; j++)
                {
                    printf(" %d", output[i + 1].drum[j]);
                }
                for (int j = 0; j < output[i].elem_drum; j++)
                {
                    printf(" %d", output[i].drum[j]);
                }
                printf("\n");
            }
            printf("%.01f", total_task1);
            for (int i = 0; i < 2 * nr_noduri; i++) //dupa care dezalocam restul memoriei
                free(output[i].drum);
            free(output);
        }
    }

    if (!strcmp("e2", tip)) //daca ne aflam la exercitiul 2
    {
        TStack output[5]; //vom lua o stiva pe care vom salva output-ul
        float **reverse; //o matrice transpusa
        int *vizitat; //un vector de vizitare care are acelasi scop ca la algoritmul lui dijkstra
        vizitat = (int *)malloc(magazin.n * sizeof(int));
        for (int i = 0; i < magazin.n; i++) //vom nota elementele din vizitat, astfel incat nodurile care sunt depozite sa fie notate cu -1 deoarece nu avem nevoie de aceste noduri
        {
            for (int j = 0; j < magazin.d; j++)
            {
                if (magazin.depozite[j] == i)
                {
                    vizitat[i] = -1;
                    break;
                }
                else
                {
                    vizitat[i] = 0;
                }
            }
        }
        reverse = (float **)malloc(magazin.n * sizeof(float *));
        for (int i = 0; i < magazin.n; i++)
            reverse[i] = (float *)malloc(magazin.n * sizeof(float));
        for (int i = 0; i < magazin.n; i++)
            for (int j = 0; j < magazin.n; j++)
                reverse[i][j] = 0;
        TStack start; //vom face o stiva in care vom stoca elementele din DFS
        initStack(&start, magazin.n);
        for (int i = 0; i < magazin.n; i++)
            start.elements[i] = 0;
        int inceput = 0; //vom cauta primul nod cu care sa incepem
        for (int i = 0; i < magazin.d; i++)
            if (inceput == magazin.depozite[i])
                inceput++;
        DFS(magazin, inceput, &start, vizitat); //apelam DFS
        for (int i = 0; i < magazin.n; i++) //daca mai exista ouncte in care nu a ajuns DFS-ul, atunci aceste sunt singure,motiv pentru care le punem pe stiva
            if (vizitat[i] == 0)
            {
                push(&start, i);
            }
        reverse_matrix(magazin, reverse);//forma matricea transpusa pentru a afla componentele tare conexe
        for (int i = 0; i < magazin.n; i++)//formam vectorul de vizitare exact ca prima data
        {
            for (int j = 0; j < magazin.d; j++)
            {
                if (magazin.depozite[j] == i)
                {
                    vizitat[i] = -1;
                    break;
                }
                else
                {
                    vizitat[i] = 0;
                }
            }
        }
        int nr = 0;
        while (start.top != 0) //incepem sa scoatem din lista pana putem
        {
            inceput = pop(&start); //scoatem primul element de pe stiva
            if (vizitat[inceput] == 0) //daca este nevizitat
            {
                initStack(&output[nr], 100); //initializam stiva de output
                modificat(reverse, magazin.n, inceput, &output[nr], vizitat); //un DFS putin modificat
                nr++; //calculam nr de componente tare conexe
            }
        }
        int ceva = 1; //algoritm pentru sortarea elementelor de pe stiva
        for (int i = 0; i < nr; i++)
        {
            ceva = 1;
            while (ceva == 1)
            {
                ceva = 0;
                for (int j = 0; j < output[i].top; j++)
                {
                    if (output[i].elements[j] > output[i].elements[j + 1])
                    {
                        int aux = output[i].elements[j];
                        output[i].elements[j] = output[i].elements[j + 1];
                        output[i].elements[j + 1] = aux;
                        ceva = 1;
                    }
                }
            }
        }

        ceva = 1; //algotitm pentru sortarea stivei
        while (ceva == 1)
        {
            ceva = 0;
            for (int i = 0; i < nr - 1; i++)
            {
                if (output[i].elements[0] > output[i + 1].elements[0] && i != nr - 1)
                {
                    TStack aux = output[i];
                    output[i] = output[i + 1];
                    output[i + 1] = aux;
                    ceva = 1;
                }
            }
        }
        printf("%d\n", nr); //printarea propriu-zisa
        for (int i = 0; i < nr; i++)
        {
            for (int j = 0; j <= output[i].top; j++)
            {
                printf("%d", output[i].elements[j]);
                if (j != output[i].top)
                    printf(" ");
            }
            if (i != nr - 1)
                printf("\n");
        }
        for (int i = 0; i < nr; i++)
            free(output[i].elements);
        free(vizitat);
        for (int i = 0; i < magazin.n; i++)
        {
            free(reverse[i]);
        }
        free(start.elements);
        free(reverse);
    }

    free(magazin.depozite);
    for (int i = 0; i < magazin.n; i++)
        free(magazin.mat_graf_ponderat[i]);
    free(magazin.mat_graf_ponderat);

    return 0;
}
