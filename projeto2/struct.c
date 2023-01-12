#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "struct.h"

int existe = 0;

List list_new(void){
    List aux;
    aux = (List) malloc (sizeof (List_node));
    if (aux != NULL) {
        aux->info.ocur = 1;
        aux->next = NULL;
    }
    return aux;
}

int list_empty(List lista){
    return (lista->next == NULL ? 1 : 0);
}

List list_nodkill(List lista){
    List temp_ptr;
    while (list_empty (lista) == 0) {
        temp_ptr = lista;
        lista= lista->next;
        free (temp_ptr);
    }
    free(lista);
    return NULL;
}

int list_size(List lista){
    int count=0;
    while(lista->next!=NULL){
        count++;
        lista = lista->next;
    }
    return count;
}

void list_searchtok(List lista, palav chave, List *ant, List *atual){
    *ant = lista;
    *atual = lista->next;
    while ((*atual) != NULL && strcmp((*atual)->info.palavra,chave.palavra)!=0){
        *ant = *atual;
        *atual = (*atual)->next;
    }
    if ((*atual) != NULL && strcmp((*atual)->info.palavra,chave.palavra)==0){
        (*atual)->info.ocur++;
        existe = 1;
    } else if ((*atual) != NULL && (*atual)->info.code != chave.code)
        *atual = NULL;
}

void list_search_ocurr(List lista, palav chave, List *ant, List *atual){
    *ant = lista;
    *atual = lista->next;
    while((*atual) != NULL && (*atual)->info.ocur >= chave.ocur){
        *ant = *atual;
        *atual = (*atual)->next;
    }
}

void list_kill(List lista, palav it){
    List ant1;
    List atual1;
    //list_search (lista, it);
    list_searchtok (lista, it, &ant1, &atual1);
    if (atual1 != NULL) {
        ant1->next = atual1->next;
        free (atual1);
    }
}

void list_insert_ocurr(List lista, palav it) {
    List ant, atual;
    List no;
    no = (List) malloc (sizeof (List_node));
    if (no != NULL) {
        no->info = it;
        list_search_ocurr(lista, it, &ant, &atual);
        no->next = ant->next;
        ant->next = no;
    }
}

void list_insert(List lista, palav it){
    List no;
    List ant, inutil;
    no = (List) malloc (sizeof (List_node));
    if (no != NULL) {
        no->info = it;
        list_searchtok (lista, it, &ant, &inutil);
        if (existe == 0) {
            no->next = ant->next;
            ant->next = no;
        } else {
            //printf("Palavra: %s code: %s code_original: %s tem Ocurrencias: %d\n", no->info.palavra, no->info.code, no->info.code_orignal, inutil->info.ocur);
            it.ocur = inutil->info.ocur;
            list_kill(lista, it);
            list_insert_ocurr(lista, it);
        }
    }
    existe = 0;
}

void list_print(List lista){
    printf("------------------------------------\n");
    List l = lista->next;
    while (l) {
        printf("Palavra: %s\n", l->info.palavra);
        printf("Code Original: %s\n", l->info.code_orignal);
        printf("Code: %s\n", l->info.code);
        printf("Ocurrencias: %d\n", l->info.ocur);
        l = l->next;
    }
}

void word_compare(List lista, char string[]){
    printf("------------------------------------\n");
    List l = lista->next;
    while(l) {
        if (strlen(string) <= 5) { // esta palavra e automaticamente aceita
            //printf("Code original: %s\n", l->info.code_orignal);
            //printf("PALAVRA: %s\n", l->info.palavra);
            //printf("String: %s\n", string);
        } else {
            //printf("Code original: %s\n", l->info.code_orignal);
            //printf("Palavra: %s\n", l->info.palavra);
            //printf("String: %s\n", string);
            if (strstr(l->info.code_orignal, string) != NULL) {
                //printf("Encontrou");
                printf("Palavra: %s\n", l->info.palavra);
                printf("Code Original: %s\n", l->info.code_orignal);
                printf("Code: %s\n", l->info.code);
                printf("Ocurrencias: %d\n", l->info.ocur);
                printf("++++++++++++++++++++++++++++++++++++\n");
            } else {
                //printf("Nao encontrou\n");
            }
        }
        l = l->next;
    }
}
