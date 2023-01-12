#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <locale.h>
#include <wctype.h>
#include <ctype.h>
#include "struct.h"
#define MINIMO 2
#define MAXIMO 99999
GtkWidget* window;
GtkWidget* grid;
GtkWidget* button;
GtkWidget *toggle;
GtkWidget *conteudo1;
GtkWidget *label_user;
GDateTime *LastPressed = NULL;
char button_str[4]="", buffer_ni[30]="", buffer[15], buffer_total[40], buffer_palavra[40], buffer_numero[40], palavra[15];
List tab[99999];
int x=0, v=0, j=0, n=0, espaco=0, b=0, toggle_check=0, count=0, flag=0;
char* btnn[9] = { ".!?", "abc", "def", "ghi", "jkl", "mno","pqrs", "tuv", "wxyz"};

char* to_code(char *s, char code[]){
    int size=0;
    while(*s != '\0'){
        if (*s == 'a' || *s == 'A' || *s == 'b' || *s == 'B' || *s == 'c' || *s == 'C') {
            code[size++] = '2';
        }
        if (*s == 'd' || *s == 'D' || *s == 'e' || *s == 'E' || *s == 'f' || *s == 'F') {
            code[size++] = '3';
        }
        if (*s == 'g' || *s == 'G' || *s == 'h' || *s == 'H' || *s == 'i' || *s == 'I') {
            code[size++] = '4';
        }
        if (*s == 'j' || *s == 'J' || *s == 'k' || *s == 'K' || *s == 'l' || *s == 'L') {
            code[size++] = '5';
        }
        if (*s == 'm' || *s == 'M' || *s == 'n' || *s == 'N' || *s == 'o' || *s == 'O') {
            code[size++] = '6';
        }
        if (*s == 'p' || *s == 'P' || *s == 'q' || *s == 'Q' || *s == 'r' || *s == 'R' || *s == 's' || *s == 'S') {
            code[size++] = '7';
        }
        if (*s == 't' || *s == 'T' || *s == 'u' || *s == 'U' || *s == 'v' || *s == 'V') {
            code[size++] = '8';
        }
        if (*s == 'w' || *s == 'W' || *s == 'x' || *s == 'X' || *s == 'y' || *s == 'Y' || *s == 'z' || *s == 'Z') {
            code[size++] = '9';
        }
        s++;
    }
    code[size] = '\0';
    return code;
}

char* analisar(char string[]){
    int tm_string = strlen(string);
    char temp[20];
    int h=0;
    for (int i = 0; i<tm_string; i++) {
        if(isalpha(string[i])){
          temp[h++] = string[i];
        }
    }
    temp[h]='\0';
    printf("string: %s\n", temp);
    strcpy(string, temp);
    return string;
}

void ver (List *tab){
    for(int i=2; i<99999; i++){
        if(!list_empty(tab[i])){
            list_print(tab[i]);
        }
    }
}

char convertch(wint_t char1){
    //printf("%d",char1);
    char ch;
    int char2 = char1;
    if(iswpunct(char1)){
        ch = '*';
        return ch;
    }
    switch (char2){
        case 225: case 224: case 227 : case 226 :
            ch = 'a';
            return ch;
        case 232 : case 233 : case 234 :
            ch = 'e';
            return ch;
        case 236 : case 237 : case 238 :
            ch = 'i';
            return ch;
        case 243: case 242 : case 244 : case 245 :
            ch = 'o';
            return ch;
        case 249 : case 250 : case 251 :
            ch = 'u';
            return ch;
        case 231:
            ch = 'c';
            return ch;
        default:
            ch = char2;
            return ch;
    }
}

void aux(char string[],char code[],List tab[]){
    long int posicao;
    if (!isalpha(string[strlen(string)-1])) string[strlen(string)-1] = '\0';
    Palavra temp;
    for(int i=0;i<strlen(string);i++) string[i] = (char)tolower(string[i]);
    strcpy(temp.palavra, string);
    to_code(string, code);
    strcpy(temp.code_orignal, code);
    if (strlen(code) > 5) {
        code[5] = '\0';
    }
    strcpy(temp.code, code); // tou a guardar o codigo pequeno e nao o original
    temp.ocur = 1;
    posicao = atoi(code);
    list_insert(tab[posicao], temp);
}

int get_button(const char* text){
    if(g_strcmp0(text," 1\n.!?")==0){
        return 1;
    }else if(g_strcmp0(text," 2\nabc")==0){
        return 2;
    }else if(g_strcmp0(text," 3\ndef")==0){
        return 3;
    }else if(g_strcmp0(text," 4\nghi")==0){
        return 4;
    }else if(g_strcmp0(text," 5\njkl")==0){
        return 5;
    }else if(g_strcmp0(text," 6\nmno")==0){
        return 6;
    }else if(g_strcmp0(text," 7\npqrs")==0){
        return 7;
    }else if(g_strcmp0(text," 8\ntuv")==0){
        return 8;
    }else if(g_strcmp0(text," 9\nwxyz")==0){
        return 9;
    }else if(g_strcmp0(text,"*")==0){
        return 10;
    }else if(g_strcmp0(text,"0")==0){
        return 11;
    }else if(g_strcmp0(text,"#")==0){
        return 12;
    }
    return 0;
}

void button_clicked(GtkButton *widget, gpointer data) {
    if(!toggle_check){
        char num_input[2];
        const gchar *text = gtk_button_get_label (widget);
        int a = get_button(text);
        char code[20];
        sprintf(num_input, "%d", a);
        int i = strlen(buffer);
        //g_print("clicked %d\n",  a);
        if(a == 12){
            int tm_buffer_ni = strlen(buffer_ni);
            for(int i=0; i<tm_buffer_ni; i++) buffer_ni[i] = '\0';
            if((strlen(buffer_total)==0)) return;
            if(strlen(buffer_total)<=1 && buffer_total[0]==' '){
                buffer_total[0]='\0';
                return;
            }
            char* token;
            char buffer_aux[80];

            strcpy(buffer_aux,buffer_total);
            j=0;
            n--;

            if (buffer_total[strlen(buffer_total)-1] == ' ') {
                int tm_buffer = strlen(buffer);
                for(int r=0;r<tm_buffer;r++){
                    buffer[r]='\0';
                }
                int tm_buffer_palavra = strlen(buffer_palavra);
                for(int r=0;r<tm_buffer_palavra;r++){
                    buffer_palavra[r]='\0';
                }
                int tm_buffer_numero = strlen(buffer_numero);
                for(int r=0;r<tm_buffer_numero;r++){
                    buffer_numero[r]='\0';
                }
                espaco = 1;
                buffer_total[strlen(buffer_total)-1]='\0';
                token = strtok(buffer_total," ");
                if(token!=NULL) strcpy(palavra,token);
                while(token!=NULL){
                    token = strtok(NULL," ");
                    if(token!=NULL){
                        strcpy(palavra,token);
                    }
                }
                strcpy(buffer_total,buffer_aux);
                strcpy(buffer_numero,to_code(palavra,buffer_numero));
            } else {
                if(espaco){
                    //buffer_total[strlen(buffer_total)-1]='\0';
                    buffer_total[(strlen(buffer_total)-strlen(palavra))]='\0';
                    strcat(buffer_total," ");
                    strcat(buffer_total,buffer_numero);

                    palavra[0] = '\0';
                    espaco=0;
                } else {
                    buffer_total[strlen(buffer_total)-1] = '\0';
                    buffer_numero[strlen(buffer_numero)-1]='\0';
                }
            }

            if(espaco){
                buffer_total[strlen(buffer_total)-1]='\0';
                buffer_numero[strlen(buffer_numero)-1]='\0';
            }
            buffer[strlen(buffer)-1] = '\0';
            gtk_label_set_text((GtkLabel*)label_user,buffer_total);
            if(strlen(buffer_numero)==0){
                int tm_buffer_numero = strlen(buffer_numero);
                for(int r=0;r<tm_buffer_numero;r++){
                    buffer_numero[r]='\0';
                }
            }
        }else if(a==10){
            int tm_buffer_ni = strlen(buffer_ni);
            for(int i=0; i<tm_buffer_ni; i++) buffer_ni[i] = '\0';
            j++;
            int posicao=0;
            char string[30];
            strcpy(string,buffer_numero);
            char string_posicao[20];
            strcpy(string_posicao, string);
            if (strlen(string)<=5){
                List lista = tab[atoi(string)];
                //list_print(lista);
                if(!list_empty(lista)){
                    for(int h=0;h<j;h++){
                        if(lista->next != NULL){
                            lista = lista->next;
                        }else{
                            lista = tab[atoi(string)];
                            lista = lista->next;
                            //list_print(lista);
                            j=1;
                        }
                    }
                    int tm_buffer = strlen(buffer);
                    for(int r=0;r<tm_buffer;r++){
                        buffer[r]='\0';
                    }
                    strcpy(buffer, lista->info.palavra);
                }else{
                    int tm_buffer = strlen(buffer);
                    for(int r=0;r<tm_buffer;r++){
                        buffer[r]='\0';
                    }
                    gtk_label_set_text((GtkLabel*)label_user,buffer_total);
                }
            } else if (strlen(string)>5){
                string_posicao[5]='\0';
                posicao = atoi(string_posicao);
                List lista2 = tab[posicao];
                //list_print(lista2);
                if(!list_empty(lista2)){
                    for(int h=0;h<j;h++){
                        if((lista2->next != NULL)){
                            lista2 = lista2->next;
                        }else{
                            lista2 = tab[posicao];
                            lista2 = lista2->next;
                            //list_print(lista2);
                            j=1;
                        }

                        while (strstr(lista2->info.code_orignal, string) == NULL) {
                            if((lista2->next != NULL)){
                                lista2 = lista2->next;
                            }else{
                                lista2 = tab[posicao];
                                lista2 = lista2->next;
                                //list_print(lista2);
                            }
                        }
                    }

                    int tm_buffer = strlen(buffer);
                    for(int r=0;r<tm_buffer;r++){
                        buffer[r]='\0';
                    }
                    strcpy(buffer,lista2->info.palavra);
                }else{
                    gtk_label_set_text((GtkLabel*)label_user,buffer_total);
                }

            }
            strcpy(buffer_palavra,buffer_total);
            int sizeint=0;
            int tmp_buffer_palavra = strlen(buffer_palavra);
            for(int i=0;i<tmp_buffer_palavra;i++) if(isdigit(buffer_palavra[i])) sizeint++;
            buffer_palavra[strlen(buffer_palavra)-strlen(buffer_numero)]= '\0';
            strcat(buffer_palavra,buffer);
            gtk_label_set_text((GtkLabel*)label_user,buffer_palavra);
        }else if(a==11){ //espaço
            int tm_buffer_ni = strlen(buffer_ni);
            for(int i=0; i<tm_buffer_ni; i++) buffer_ni[i] = '\0';
            j=0;
            if(!isalpha(buffer[0])){
                buffer[0]='\0';
            }
            if(strlen(buffer)==0){
                strcat(buffer_total," ");
                gtk_label_set_text((GtkLabel*)label_user,buffer_total);
                int tm_buffer = strlen(buffer);
                int tm_buffer_numero = strlen(buffer_numero);
                for(int r=0;r<tm_buffer_numero;r++){
                    buffer_numero[r]='\0';
                }
                for(int r=0;r<tm_buffer;r++){
                    buffer[r]='\0';
                }
                return;
            }else{
                if(strlen(buffer_palavra)>0) strcpy(buffer_total,buffer_palavra); // sem esta condicao caso metas um numero e des espaco sem carregar no asterisco como o buffer_palavra é vazio o teu numero vai desaparecer da label
                strcat(buffer_total," ");
                gtk_label_set_text((GtkLabel*)label_user,buffer_total);
            }
            int tm_buffer = strlen(buffer);
            int tm_buffer_numero = strlen(buffer_numero);
            for(int r=0;r<tm_buffer_numero;r++){
                buffer_numero[r]='\0';
            }
            n=0;

            Palavra temp;
            strcpy(temp.palavra, buffer);
            strcpy(code,to_code(buffer,code));
            strcpy(temp.code_orignal, code);
            code[5]='\0';
            strcpy(temp.code, code);
            //list_print(tab[atoi(code)]);
            list_insert(tab[atoi(code)], temp);
            for(int r=0;r<tm_buffer;r++){
                buffer[r]='\0';
            }
        }else if(a==1){
            printf("buffer: %s\n", buffer);
            if(strlen(buffer)!=0){
              strcpy(buffer_total, buffer_palavra);
              buffer[0]='\0';
            }
            GTimeSpan diff;
            GDateTime *now = g_date_time_new_now_local();
            if(strlen(buffer_ni)>0) buffer_total[strlen(buffer_total)-strlen(buffer_ni)]= '\0';
            for(int f=0;f<a;f++){
                strcpy(button_str,btnn[f]);
            }
            if (LastPressed != NULL){
                diff = g_date_time_difference(now,LastPressed);

                if (diff < 500000){
                    if (x<strlen(button_str)-1 && button_str[x]<128) x++;
                    else if (x<strlen(button_str)-2 && button_str[x]>127) x++;
                    else x=0;
                }else{
                    x=0;
                    v++;
                }
            }
            if (v > 0 && buffer_ni[v-1]>192){
                buffer_ni[v--] = 0;
                buffer_ni[v] = 0;
            }
            if (button_str[x]>127){
                buffer_ni[v++] = button_str[x++];
                buffer_ni[v] = button_str[x];
            }
            else buffer_ni[v] = button_str[x];
            LastPressed = g_date_time_new_now_local();
            printf("buffer_total = %s\n", buffer_total);
            printf("buffer_ni = %s\n", buffer_ni);
            strcat(buffer_total,buffer_ni);
            gtk_label_set_text((GtkLabel *) label_user, buffer_total);
        } else{
            int tm_buffer_ni = strlen(buffer_ni);
            for(int i=0; i<tm_buffer_ni; i++) buffer_ni[i] = '\0';
            if(espaco){
                buffer_total[(strlen(buffer_total)-strlen(palavra))]='\0';
                strcat(buffer_total,buffer_numero);
                espaco=0;
            }
            j=0;
            i = strlen(buffer);
            buffer[i] = num_input[0];
            n = strlen(buffer_numero);
            buffer_numero[n++] = num_input[0];
            buffer[i+1] = '\0';
            strcat(buffer_total,num_input);
            gtk_label_set_text((GtkLabel*)label_user,buffer_total);
        }
    }else{ // modo nao inteligente
        GTimeSpan diff;
        GDateTime *now = g_date_time_new_now_local();
        char num_input[2];
        const gchar *text = gtk_button_get_label (widget);
        int a = get_button(text);
        sprintf(num_input, "%d", a);
        if(a<10){
            if(strlen(buffer_ni)>0) buffer_total[strlen(buffer_total)-strlen(buffer_ni)]= '\0';
            for(int f=0;f<a;f++){
                strcpy(button_str,btnn[f]);
            }
            if (LastPressed != NULL){
                diff = g_date_time_difference(now,LastPressed);

                if (diff < 500000 && b==a){
                    if (x<strlen(button_str)-1 && button_str[x]<128) x++;
                    else if (x<strlen(button_str)-2 && button_str[x]>127) x++;
                    else x=0;
                }else{
                    x=0;
                    v++;
                }
            }
            if (v > 0 && buffer_ni[v-1]>192){
                buffer_ni[v--] = 0;
                buffer_ni[v] = 0;
            }
            if (button_str[x]>127){
                buffer_ni[v++] = button_str[x++];
                buffer_ni[v] = button_str[x];
            }
            else buffer_ni[v] = button_str[x];
            LastPressed = g_date_time_new_now_local();
            strcat(buffer_total,buffer_ni);
            gtk_label_set_text((GtkLabel *) label_user, buffer_total);
            b = a;
        }else if(a==10){ // asterisco
            v = strlen(buffer_ni);
            if(strlen(buffer_ni)==0){
                //v=0;
                x=0;
                LastPressed = NULL;
                int tm_buffer_cap = strlen(buffer_ni);
                for(int r=0;r<tm_buffer_cap;r++){
                    buffer_ni[r]='\0';
                }
                button_str[0]='\0';
                return;
            }
            char code[20];
            Palavra temp;
            strcpy(temp.palavra, buffer_ni);
            strcpy(code,to_code(buffer_ni,code));
            strcpy(temp.code_orignal, code);
            code[5]='\0';
            strcpy(temp.code, code);
            //list_print(tab[atoi(code)]);
            strcpy(temp.palavra, analisar(temp.palavra));
            list_insert(tab[atoi(code)], temp);
            v = strlen(buffer_ni);
        }else if(a==11){ // espaco
            v = strlen(buffer_ni);
            strcat(buffer_total," ");
            //v=0;
            x=0;
            LastPressed = NULL;
            int tm_buffer_cap = strlen(buffer_ni);
            for(int r=0;r<tm_buffer_cap;r++){
                buffer_ni[r]='\0';
            }
            button_str[0]='\0';
            gtk_label_set_text((GtkLabel *) label_user, buffer_total);
            v = strlen(buffer_ni);
        }else if(a==12){
            v = strlen(buffer_ni);
            flag=1;
            buffer_total[strlen(buffer_total)-1]='\0';
            gtk_label_set_text((GtkLabel *) label_user, buffer_total);
            button_str[0]='\0';
            x=0;
            LastPressed = NULL;
            if(strlen(buffer_ni)>0){
                //if((v-1)>=0) v--;
                buffer_ni[strlen(buffer_ni)-1]='\0';
            } else if(strlen(buffer_ni)<=0){
                //v = 0;
                buffer_ni[0] = '\0';
            }
            v = strlen(buffer_ni);
        }
    }

}

void toogle_signal(GtkWidget *widget, gpointer button) {
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget))) {
        strcpy(buffer_total, gtk_label_get_text((GtkLabel*)label_user));
        v=0;
        x=0;
        LastPressed = NULL;
        int tm_buffer_cap = strlen(buffer_ni);
        for(int r=0;r<tm_buffer_cap;r++){
            buffer_ni[r]='\0';
        }
        button_str[0]='\0';
        toggle_check = 1;
    } else {
        strcpy(buffer_total, gtk_label_get_text((GtkLabel*)label_user));
        strcpy(buffer_palavra, gtk_label_get_text((GtkLabel*)label_user));
        toggle_check = 0;
    }
}

int save_changes(){
    FILE *f = fopen("lusiadas1.txt", "w+");
    for(int i=MINIMO; i<MAXIMO;i++){
        if (!list_empty(tab[i])) {
            while (tab[i]->next != NULL) {
                tab[i] = tab[i]->next;
                fprintf(f, "%s\n%s\n%s\n%d\n", tab[i]->info.palavra, tab[i]->info.code, tab[i]->info.code_orignal, tab[i]->info.ocur);
            }
        }
    }
    return 0;
}

void ler_ficheiro(FILE *fp){
    wint_t wc;
    char *token;
    char ch;
    int u=0;
    char code[20];
    while((wc=fgetwc(fp))!=WEOF){
        char line[200] = {'\0'};
        int i=0;
        wc = towlower(wc);
        ch = convertch(wc);
        if(ch!='*') {
            line[i++] = ch;
        }
        u++;
        while(((wc=fgetwc(fp))!='\n' && wc !=WEOF)){
            wc = towlower(wc);
            ch = convertch(wc);
            if(ch!='*'){
                line[i++] = ch;
            }
        }
        if(!isdigit(line[0]) && !isdigit(line[1]) && !isdigit(line[2])){
            token = strtok(line, " ");
            if(token!=NULL && isalpha(*token)) aux(token,code,tab);
            while( token != NULL ) {
                token = strtok(NULL, " ");
                if(token!=NULL && isalpha(*token)) aux(token,code,tab);
            }
        }

    }
}

void ler_ficheiro_gravado(FILE *file){
    Palavra temp;
    while (fscanf(file, "%s", temp.palavra) != EOF) {
        fscanf(file, "%s", temp.code);
        fscanf(file, "%s", temp.code_orignal);
        fscanf(file, "%d", &temp.ocur);
        list_insert(tab[atoi(temp.code)], temp);
    }
}

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "en_US.UTF-8");
    //char code[20];

    for(int i=MINIMO; i<MAXIMO; i++) tab[i] = list_new();

    if(access("lusiadas1.txt", F_OK ) == 0 ) {
        FILE *fp = fopen("lusiadas1.txt", "r");
        ler_ficheiro_gravado(fp);
    } else if(access("lusiadas.txt", F_OK ) == 0){
        FILE *fp1 = fopen("lusiadas.txt", "r");
        ler_ficheiro(fp1);
    } else {
        printf("Problemas na leitura do ficheiro\n");
        return -1;
    }


    gchar* values[12] = { " 1\n.!?", " 2\nabc", " 3\ndef", " 4\nghi", " 5\njkl", " 6\nmno"," 7\npqrs", " 8\ntuv", " 9\nwxyz","*", "0", "#"};
    gtk_init(&argc, &argv);
    buffer[0] = '\0';
    window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(window), 5, 5);
    gtk_window_set_title(GTK_WINDOW(window), "Phone");
    gtk_container_set_border_width(GTK_CONTAINER(window), 15);
    GtkWidget* vbox=gtk_box_new(GTK_ORIENTATION_VERTICAL,1);
    gtk_container_add(GTK_CONTAINER(window), vbox);
    conteudo1=gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    toggle = gtk_toggle_button_new_with_label("DISABLE T9");
    g_signal_connect(G_OBJECT(toggle), "clicked", G_CALLBACK(toogle_signal), NULL);
    gtk_container_add(GTK_CONTAINER(vbox), conteudo1);
    label_user = gtk_label_new(NULL);
    gtk_box_pack_start(GTK_BOX(vbox), label_user, FALSE, FALSE, 5);
    gtk_container_add(GTK_CONTAINER(vbox), toggle);
    grid= gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(grid), 2);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 2);
    int i = 0;
    int j = 0;
    int pos= 0;
    int num=0;
    for (i=0; i < 4; i++) {
        for (j=0; j < 3; j++) {
            num++;
            button= gtk_button_new_with_label(values[pos]);
            //  gtk_box_pack_start(GTK_BOX(grid), button, TRUE, TRUE, 5);
            g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(button_clicked), NULL);
            gtk_grid_attach(GTK_GRID(grid), button, j, i, 1, 1);
            pos++;
        }
    }
    gtk_box_pack_start(GTK_BOX(vbox), grid, FALSE, FALSE, 5);
    //gtk_container_add(GTK_CONTAINER(vbox), grid);


    g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_widget_show_all(window);
    gtk_main();
    save_changes();
    return 0;
}
