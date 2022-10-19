#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include<string.h>
#include"liste.h"
#include"e1e2e3.h"
#include"ucst.h"


int main(int argc,char *argv[])
{
    list lista; //lista propriu-zia
    lista = NULL; //incrementarea rimului element cu NULL
    int nr_elem_input; //nr de elemente adaugat de la tastatura
    double numar_input1; // value
    int numar_input2;  //timestamp
    scanf("%d", &nr_elem_input);
    for (int i = 0; i < nr_elem_input; i++)
    {
        scanf("%d%lf",&numar_input2,&numar_input1); //citire de la tastatura 
        add_last(&lista, numar_input1,numar_input2); //adaugare in lista
    }
    list clona = lista; //clona pentru usurarea eliberarii memoriei
    for(int i = 1 ;i < argc ;i++){ //un for pentru a cauta printre argumente si rularea acestora in ordinea corespunzatoare
        if(argc != 2 && ((strcmp(argv[i],"--e2") == 0) || (strcmp(argv[i],"--e3") == 0))){
            
            }
        if(strcmp(argv[i],"--e1") ==0){
            clona = medie_lista(clona,&nr_elem_input);
        }
        if(strcmp(argv[i],"--e2") == 0){
            nr_elem_input -= 4;
            ex2(&clona,nr_elem_input);
        }
        if(strcmp(argv[i],"--e3") == 0){
            nr_elem_input -= 4;
            ex3(&clona,nr_elem_input);

        }
        if(strcmp(argv[i],"--u") == 0){
           ufunctie(&clona);
        }
        if(strstr(argv[i],"--st") != 0){
            int nr=0;
            for(int j = 4 ; j < strlen(argv[i]) ; j++){
                int c = 0;
                c = charToInt(*(argv[i]+j));
                nr = nr * 10 + c;
            }
            stfunctie(clona,nr);
        }
        if(strcmp(argv[i],"--c") == 0){
           cfunctie(&clona,&nr_elem_input);
        }
    }
    if(strcmp(argv[1],"--e1") == 0 || strcmp(argv[1],"--e2") == 0 || strcmp(argv[1],"--e3") == 0 || strcmp(argv[1],"--u") == 0 || strcmp(argv[1],"--c") == 0){
        printf("%d\n",nr_elem_input); // printarea output-ului
        print(clona);
    }
    listfree(&clona); //eliberarea memoriei

    return 0;
}