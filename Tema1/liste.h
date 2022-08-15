#ifndef HEADER_FILE

typedef struct node // liste din cerinta
{
    int timestamp;
    double value;
    struct node *prev;
    struct node *next;
} node, *list;

void add_last(list *lista, double x , int y) //adaugarea la coada listei
{
    list add = (list)malloc(sizeof(node));
    list rep;
    add->timestamp=y;
    add->value = x;
    if (*lista == NULL) //cazul in care lista este nula
    {
        add->next = NULL;
        add->prev = NULL;
        *lista = add;
    }
    else
    {
        rep = *lista;
        while (rep->next != NULL)
        {
            rep = rep->next;
        }
        rep->next = add;
        add->prev = rep;
        add->next = NULL;
    }
}

void print(list lista) // printarea listei
{
    while (lista != NULL)
    {
        printf("%d %.02lf\n",lista->timestamp, lista->value);
        lista = lista->next;
    }
}

void listfree(list *lista) //functie pentru eliberarea memoriei
{
    while (*lista != NULL)
    {
        list aux = *lista;
        *(lista) = (*lista)->next;
        free(aux);
    }
}

void delDL(list pos) // eliminarea din lista dintr-o anumita pozitie
{
    list prec, urm;
    prec = pos->prev; 
    if (pos->next != NULL)
        urm = pos->next;
    else
        urm = NULL;
    if (urm != NULL)
        prec->next = urm;// trecem peste el, urmand noul element
    else
        prec->next = NULL;
    if (urm != NULL)
        urm->prev = prec; 
    free(pos);
}

list pos(list s, double x)
{
    list p = s->next; // aflarea pozitiei

    while (p != NULL && x != p->value)
    {
        p = p->next;
    }
    if (p == NULL)
        return NULL; 
    else
        return p; 
}

list zecimale_2(list lista){
    list nou;
    nou = NULL;
    while(lista != NULL){
        double zecimals = roundf(lista->value * 100) / 100;
        add_last(&nou, zecimals,lista ->timestamp);
        lista = lista->next;
    }
    return nou;
}

#endif