#ifndef HEADER_FILE

void ufunctie(list *lista){
    list aux = *lista;
    list clone = NULL;
    while(aux != NULL){
        add_last(&clone,aux -> value,aux ->timestamp);
        aux = aux -> next;
    }
    list clone_1 = clone;
    listfree(&(*lista));
    *lista = NULL;
    list aux1=NULL;
    if(clone_1 -> prev == NULL){
        add_last(&aux1 ,clone_1->value,clone_1->timestamp);
        add_last(&(*lista),clone_1->value,clone_1->timestamp);
        clone_1 = clone_1 -> next;
    }
    list plimbare = aux1;
    //plimbare = plimbare -> prev;
    //printf("%d",aux1 -> timestamp);
    while(clone_1 != NULL){ 
        //printf("%d %d\n",clone_1 -> timestamp,plimbare -> timestamp);
        if(clone_1 ->timestamp - plimbare -> timestamp >= 100 && clone_1 ->timestamp - plimbare -> timestamp <=1000){ //daca lista se afla in intervalul mentionat atunci se or modifica valorile treptat
            add_last(&plimbare ,(clone_1 ->value + plimbare -> value) / 2,(clone_1 ->timestamp + plimbare -> timestamp) / 2);
            add_last(&(*lista),(clone_1 ->value + plimbare -> value) / 2,(clone_1 ->timestamp + plimbare -> timestamp) / 2);
        }
        else{
            add_last(&plimbare ,clone_1->value,clone_1->timestamp); //altfel adaugam valoarea nemodificata
            add_last(&(*lista),clone_1->value,clone_1->timestamp);
        }
        clone_1 = clone_1 -> next;
        plimbare = plimbare -> next;
    }
    listfree(&clone);
    listfree(&aux1);
}

int charToInt(char c){
	int num = 0;
	num = c - '0';
	return num;
}

void stfunctie(list lista, int nr){
    int mg_st;
    int mg_dr;
    list aux = lista;
    int counter = 0;
    sort(&aux);
    //print(lista);
    while(aux -> next != NULL){
        mg_st = mg_st + nr; // marginea din stanga 
        if(aux -> prev == NULL){
            if(aux -> value < round(aux -> value)) //rotunjirea marginei
                mg_st = round(aux ->value)-1; 
            else
                mg_st = round(aux -> value);
        }
        mg_dr = mg_st +nr; //marginea dindreapta
        //printf("[%d %d] %f\n",mg_st,mg_dr,aux -> value);
        while(mg_st < aux -> value && mg_dr > aux ->value && aux != NULL){
            counter++;
            aux = aux -> next;
        }
        if(counter != 0)
            printf("[%d, %d] %d\n",mg_st,mg_dr,counter); //printam marginile
        counter = 0;
        //aux = aux -> next;
    }
    counter = 1 ;
        while(mg_st < aux -> value && mg_dr < aux ->value){//modificam marginile
            mg_st = mg_st + nr; 
            mg_dr = mg_st +nr;
        }
    printf("[%d, %d] %d\n",mg_st,mg_dr,counter++);
}

void addDL (list *nou, list *pos) {
    (*nou)->next = (*pos)->next;
    (*nou)->prev = *pos;
    (*pos)->next = *nou;
}

    void printc(list lista){
        while(lista != NULL){
            printf("%d %.02lf\n",lista -> timestamp , lista ->value);
            lista= lista -> next;
        }
    }

void cfunctie(list *lista,int *n){
    list aux = *lista;
    list clone = NULL;
    while(aux != NULL){
        add_last(&clone,aux -> value,aux ->timestamp);
        aux = aux -> next;
    }
    list clone_1 = clone;
    listfree(&(*lista));
    *lista = NULL;
    while(clone_1 -> next != NULL){
        if(clone_1 -> next -> timestamp - clone_1 -> timestamp > 1000){ //daca depaseste o secunda
            *n = *n -1;
            double timestamp = clone_1 -> timestamp; // timestamp-ul curent
            double right_timestamp = clone_1 -> next -> timestamp; //vecinul din dreapta
            double left_timestamp = clone_1 -> timestamp; //vecinul din stanga
            // cele trei valori care nu se modifica
            double left1 = clone_1 -> prev -> prev -> value;
            double left2 = clone_1 -> prev -> value;
            double left3 = clone_1 -> value;
            double right1 = clone_1 -> next -> next -> next -> value;
            double right2 = clone_1 -> next -> next -> value;
            double right3 = clone_1 -> next -> value;
            double w1 = 0.070175438596491228070 , w2 = 0.22807017543859649 , w3 = 0.701754385964912280; //constantele care se calculeaza dupa o formula matematica
            while(right_timestamp > timestamp){
                *n = *n + 1;
                list aux11 = (list) malloc (sizeof(node));
                timestamp = timestamp + 200;
                double C = (timestamp - left_timestamp) / (right_timestamp - left_timestamp);
                double f = (1 - C) *(w1 * left1 + w2 * left2 + w3 * left3) + C * (w1 * right1 + w2 * right2 + w3 * right3);
                aux11 -> timestamp = timestamp;
                aux11 -> value = f ;
                addDL(&aux11,&clone_1);
                add_last(&(*lista),clone_1 -> value,clone_1 -> timestamp); //adaugarea elementului modificat
                clone_1 = clone_1 -> next;
                
            }
        }
        else{
            add_last(&(*lista),clone_1 -> value,clone_1 -> timestamp); //adaugarea elementului nemodificat
        }
        clone_1 = clone_1 -> next;
    }
    add_last(&(*lista),clone_1 -> value,clone_1 -> timestamp);// adaugarea ultimului elemnt deoarece nu se va citi ultimul element(din cauza ca while-ul este te tip lista -> next)
    listfree(&clone);
}

#endif