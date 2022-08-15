#ifndef HEADER_FILE

list medie_lista(list lista, int *n)
{
    double medie = 0,sigma;
    list clona_2_zecimale_2 =lista;
    list clona_2_zecimale_3 ;
    clona_2_zecimale_3 = NULL; // clonarea listei pentru a avea cu ce a lucra, urmand ca lista propriu ziasa sa fie noul output
    while(lista != NULL){
        add_last(&clona_2_zecimale_3,lista->value,lista->timestamp);
        lista = lista -> next;
    }
    list clona_2_zecimale = clona_2_zecimale_3;
    while (clona_2_zecimale -> next -> next -> next -> next != NULL )
    {
        double x1 = clona_2_zecimale->value; //valorile corespunzatoare pentru care se va calcula media
        double x2 = clona_2_zecimale->next->value;
        double x3 = clona_2_zecimale->next->next->value;
        double x4 = clona_2_zecimale->next->next->next->value;
        double x5 =  clona_2_zecimale->next->next->next->next->value; 
        medie = (x1 + x2 +x3 +x4 + x5) / 5;
        // formula din cerinta
        sigma = sqrt(((medie - x1) * (medie - x1) + (medie - x2) * (medie - x2) + (medie - x3) * (medie - x3) + (medie - x4) * (medie - x4) + (medie - x5) * (medie - x5)) / 5);
        sigma = round(sigma * 100) / 100;
        medie = round(medie * 100) / 100;
        clona_2_zecimale = clona_2_zecimale -> next;
            if (x3 < medie - sigma || x3 > medie + sigma) // eliminarea elementului din lista daca nu se afal intre cele doua limite
            {
                *n = *n - 1;
                list p;
                p = pos(clona_2_zecimale_2, x3);
                delDL(p);
            }
    }
    listfree(&clona_2_zecimale_3);
    return clona_2_zecimale_2;
}

int newcounter(list lista) // renumararea elementelor din lista
{
    int count = 0;
    while (lista != NULL)
    {
        count++;
        lista = lista->next;
    }
    return count;
}

void switch_int(int *a, int *b){
    int aux;
    aux = *a;
    *a = *b;
    *b = aux;
}

void switch_float(double *a,double *b){
    double aux;
    aux = *a;
    *a = *b;
    *b = aux;
}

void sort(list *lista){ //sortarea elementelor dintr-o lista
    int ok;
    list aux = *lista;
    list ver = NULL;
    if(aux == NULL)
        return;
    do{
        ok = 0;
        aux = *lista;
        while(aux -> next != ver){
            if(aux -> value > aux -> next -> value){ 
                switch_float(&aux->value,&aux->next->value);   //folosim o sortare prin interschimbare       
                ok = 1;
            }
            aux = aux -> next;
        }
        ver = aux;
    }while(ok);
}

void ex2 (list *lista , int n){
    list aux = *lista;
    list clone = NULL;
    while(aux != NULL){
        add_last(&clone,aux -> value,aux ->timestamp);
        aux = aux -> next;
    }
    list clone_1 = clone;
    listfree(&(*lista));
    *lista = NULL;
    while(clone_1 -> next -> next -> next -> next != NULL){
        list lista_5 = NULL;
        add_last(&lista_5,clone_1 -> value, clone_1 ->timestamp);
        add_last(&lista_5,clone_1 -> next -> value, clone_1 -> next -> timestamp);
        add_last(&lista_5,clone_1 ->next -> next ->  value, clone_1 ->next -> next -> timestamp);
        add_last(&lista_5,clone_1 -> next -> next -> next -> value, clone_1 ->next -> next -> next -> timestamp);
        add_last(&lista_5,clone_1 -> next -> next -> next -> next -> value, clone_1 ->next -> next -> next -> next -> timestamp);
        sort(&lista_5); //sortam elementele
        add_last(&(*lista),lista_5 -> next -> next -> value,lista_5 -> next -> next ->timestamp); //extragem elementrul din mijloc(al treilea element)
        clone_1 = clone_1 -> next;
        listfree(&lista_5);
   }
    listfree(&clone);
}

double adunare (list lista){
    double sum = 0;
    list aux = lista;
    while(aux != NULL){
        sum += aux -> value;
        aux = aux -> next;
    }
    return sum;
}

void ex3(list *lista, int n){
    list aux = *lista;
    list clone = NULL;
    while(aux != NULL){
        add_last(&clone,aux -> value,aux ->timestamp);
        aux = aux -> next;
    }
    listfree(&(*lista));
    list clone_1 = clone;
    while(clone_1 -> next -> next -> next -> next != NULL){
        list lista_5 = NULL;
        double suma = 0 , medie = 0;
        add_last(&lista_5,clone_1 -> value, clone_1 ->timestamp);
        add_last(&lista_5,clone_1 -> next -> value, clone_1 -> next -> timestamp);
        add_last(&lista_5,clone_1 ->next -> next ->  value, clone_1 ->next -> next -> timestamp);
        add_last(&lista_5,clone_1 -> next -> next -> next -> value, clone_1 ->next -> next -> next -> timestamp);
        add_last(&lista_5,clone_1 -> next -> next -> next -> next -> value, clone_1 ->next -> next -> next -> next -> timestamp);
        suma = adunare(lista_5);
        medie = suma / 5;
        //printf("%f\n",medie);
        add_last(&(*lista),medie,lista_5 -> next -> next ->timestamp); //adaugarea mediei in urma celor 5 elemente
        clone_1 = clone_1 -> next;
        listfree(&lista_5);
   }
   listfree(&clone);
}

#endif