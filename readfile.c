#include "readfile.h"

list scroll_txt_file(char *file, list l){
    FILE *fp;
    unsigned int x=0;
    unsigned char y=0;
    list lista_ordinata=NULL;

    if((fp=fopen(file, "rb"))==NULL){
        printf("ERRORE: apertura file: %s\n", file);
        exit(1);
    }
    while((fread(&x, 1, 1, fp)) > 0){     
        if( x > 0x7E ){
            fread(&y, 1, 1, fp);                 
            x<<=8;
            x+=y;            
            y=0;
        }
    l = cons(l, x);
    x=0;
    }
    fclose(fp);
    lista_ordinata = ordina_lista(l);    
    return lista_ordinata;
}

list ordina_lista( list l){
    list lista_ordinata=NULL;  
    while ( l!= NULL ){              
        lista_ordinata = insOrd( lista_ordinata, l->value );                
        l = l->next;
    }
    return lista_ordinata;
}

list insOrd( list l, info_carattere e){
	if(l==NULL)
		return cons_el( e, l );
	else if(e.presenze < l->value.presenze )
		return cons_el ( e, l );
	else 
        return cons_el( l->value, insOrd( l->next, e ) );
}

list cons_el( info_carattere m,  list lista_ordinata){
    list aux;
    aux=(list)malloc(sizeof(nodo));
    aux->value=m;    
    aux->next=lista_ordinata;
    return aux;
}

list cons (list l,unsigned int x) {
    if(member(l,x)){
        add_presenza(l,x);
        return l;
    } else {
        list aux;
        aux=(list)malloc(sizeof(nodo));
        aux->value.carattere=x;
        aux->value.presenze=1;
        aux->next=l;
        return aux;
    }
}

int add_presenza( list l, unsigned int x){
    int trovato = 0;
    while((l!=NULL) && !trovato){
        if(l->value.carattere == x){
            l->value.presenze++;
            trovato = 1;
        } else
            l = l->next;
    }
    return trovato;   
}

int member( list l, unsigned int x){
    int trovato = 0;
    while((l!=NULL) && !trovato){
        if(l->value.carattere == x)
            trovato = 1;
        else
            l = l->next;
    }
    return trovato;   
}

void show_list(list l){
    while(l!=NULL){
        printf("%x - %d \n", l->value.carattere, l->value.presenze);
        l=l->next;
    }        
}
