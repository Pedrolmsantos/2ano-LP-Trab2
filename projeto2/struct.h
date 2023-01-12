typedef struct lnode* List;
typedef struct Palavra palav;
typedef struct Palavra{
    char palavra[20];
    char code[20];
    char code_orignal[20];
    int ocur;
}Palavra;
typedef struct lnode {
    palav info;
    List next;
} List_node;

List list_new(void);

int list_empty(List lista);

List list_nodkill(List lista);

int list_size(List lista);

void list_searchtok(List lista, palav chave, List *ant, List *atual);

void list_search_ocurr(List lista, palav chave, List *ant, List *atual);

List list_search(List lista, palav it);

void list_kill(List lista, palav it);

void list_insert(List lista, palav it);

void list_insert_ocurr(List lista, palav it);

void list_print(List lista);

void word_compare(List lista, char string[]);
