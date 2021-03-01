#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX 30
#define INICIAL 0

typedef struct sublista {
    float importe;
    struct sublista *sig;
} tsublista;

typedef struct lista {
    int codigo;
    char nya[MAX];
    struct lista *sig;
    tsublista *sub;
} tlista;

void inicializar(tlista **lis);
int es_letra(char n);
void carga_iniciales(char nombre[]);
void carga_vendedor(tlista *aux);
tlista *genera_lista();
void carga_lista(tlista **lis);
tsublista *genera_sublista();
void carga_sublista(tlista **lis);
void mostrar_vendedor(tlista *aux);
void mostrar(tlista *lis);
void ventas_maximo(tlista *lis);
void ventas_minimo(tlista *lis);
void modificar_sublista(tlista **lis);
void destruir_sublista(tsublista *sub);
void elimina_sublista(tlista **lis);
void elimina_sub_simple(tlista **lis);

///, eliminar la sublista , eliminar vendedor , destruir todo , como sacar dos maximos, dos minimos

int main() {
    tlista *l;
    inicializar(&l);
    carga_lista(&l);
    carga_lista(&l);
    //carga_lista(&l);
    carga_sublista(&l);
    carga_sublista(&l);
    //carga_sublista(&l);
    mostrar(l);
    //ventas_maximo(l);
    //ventas_minimo(l);
    //modificar_sublista(&l);
    //mostrar(l);
    //elimina_sublista(&l);
    elimina_sub_simple(&l);         ///me falla cuando elimino el ultimo o unico de la sublista

    mostrar(l);
    return 0;
}

void inicializar(tlista **lis) {
    (*lis) = NULL;
}

int es_letra(char n) {
    if((n>64 && n<91) || (n>96 && n<123))
        return 1;
    else
        return 0;
}

void carga_iniciales(char nombre[]) {
    if(es_letra(nombre[INICIAL]))
        nombre[INICIAL] = toupper(nombre[INICIAL]);
    int i;
    for(i=0; i<strlen(nombre); i++) {
        if(!es_letra(nombre[i]) && es_letra(nombre[i+1]))
            nombre[i+1] = toupper(nombre[i+1]);
    }
}

void carga_vendedor(tlista *aux) {
    printf("Ingrese codigo del vendedor: ");
    fflush(stdin);
    scanf("%d",&aux->codigo);
    printf("Ingrese nombre y apellido: ");
    fflush(stdin);
    gets(aux->nya);
    carga_iniciales(aux->nya);
}

tlista *genera_lista() {
    tlista *aux = malloc(sizeof(tlista));
    carga_vendedor(aux);
    aux->sig = NULL;
    aux->sub = NULL;
    return aux;
}

void carga_lista(tlista **lis) {
    tlista *aux = genera_lista();
    if(*lis == NULL) {
        *lis = aux;
    } else {
        aux->sig = *lis;
        *lis = aux;
    }
}

tsublista *genera_sublista() {
    tsublista *aux = malloc(sizeof(tsublista));
    printf("Ingrese el importe de la venta realizada: ");
    fflush(stdin);
    scanf("%f",&aux->importe);
    aux->sig = NULL;
    return aux;
}

void carga_sublista(tlista **lis) {
    if((*lis) == NULL) {
        puts("Lista vacia!");
        system("pause");
    } else {
        int ref;
        printf("Ingrese el codigo del vendedor a cargar venta: ");
        fflush(stdin);
        scanf("%d",&ref);
        tlista *aux = *lis;
        while(aux != NULL && aux->codigo != ref) {
            aux = aux->sig;
        }
        if(aux == NULL) {
            puts("No se encontro el vendedor");
            system("pause");
        } else {
            tsublista *nuevosub = genera_sublista();
            if(aux->sub == NULL)
                aux->sub = nuevosub;
            else {
                tsublista *auxsub = aux->sub;           ///CARGA AL FINAL (TAMBIEN SE PUEDE CARGAR ADELANTE Y EVITAR DECLARAR AUXSUB)
                while(auxsub->sig != NULL)              ///HACIENDO DIRECTAMENTE nuevosub->sig = aux->sub; y aux->sub = nuevosub;
                    auxsub = auxsub->sig;
                auxsub->sig = nuevosub;
            }
        }
    }
}

void mostrar_vendedor(tlista *aux) {
    puts("--------------------------");
    printf("Codigo: %d",aux->codigo);
    printf("\nNombre: %s",aux->nya);

    if(aux->sub == NULL)
        printf("\n\tNo registra ventas realizadas.\n");
    else {
        tsublista *auxsub = aux->sub;
        puts("\n\tVentas realizadas:");
        while(auxsub != NULL) {
            printf("\tImporte: $%g\n",auxsub->importe);
            auxsub = auxsub->sig;
        }
    }
    puts("--------------------------");
}

void mostrar(tlista *lis) {
    tlista *aux = lis;
    if(aux == NULL) {
        puts("Lista vacia!");
        system("pause");
    } else {
        printf("Lista de vendedores: \n");
        while(aux != NULL) {
            mostrar_vendedor(aux);
            aux = aux->sig;
        }
        system("pause");
    }
}

void ventas_maximo(tlista *lis) {
    if(lis == NULL)
        puts("Lista vacia!");
    else {
        float max = 0, suma = 0;
        tlista *maximo, *aux = lis;
        while(aux != NULL) {
            if(aux->sub != NULL) {
                tsublista *auxsub = aux->sub;
                while(auxsub != NULL) {
                    suma += auxsub->importe;
                    auxsub = auxsub->sig;
                }
                if(suma > max) {
                    max = suma;
                    maximo = aux;
                }
                suma = 0;
            }
            aux = aux->sig;
        }
        if(max == 0)
            puts("No hay ventas realizadas");
        else
            printf("El vendedor con mas ventas es: %s\nCon un total de : $%g\n",maximo->nya,max);
    }
    system("pause");
}

void ventas_minimo(tlista *lis) {
    if(lis == NULL) {
        puts("Lista vacia!");
    } else {
        float min = 0, suma = 0;
        tlista *aux = lis, *minimo;
        while(aux != NULL) {
            if(aux->sub != NULL) {
                tsublista *auxsub = aux->sub;
                while(auxsub != NULL) {
                    suma =+ auxsub->importe;
                    auxsub = auxsub->sig;
                }
                if(min == 0) {
                    min = suma;
                    minimo = aux;
                } else if(suma < min) {
                    min = suma;
                    minimo = aux;
                }
                suma = 0;
            }
            aux = aux->sig;
        }
        if(min == 0)
            puts("No hay ventas realizadas");
        else
            printf("El vendedor con menos ventas es: %s\nCon un total de : $%g\n",minimo->nya,min);
    }
    system("pause");
}

void modificar_sublista(tlista **lis) {
    if((*lis) == NULL) {
        puts("Lista vacia!");
        system("pause");
    } else {
        int ref;
        printf("Ingrese codigo del vendedor a modificar venta: ");
        fflush(stdin);
        scanf("%d",&ref);
        tlista *aux = *lis;
        while(aux != NULL && aux->codigo != ref)
            aux = aux->sig;
        if(aux == NULL) {
            puts("Vendedor no encontrado");
        } else if(aux->sub == NULL) {
            puts("Vendedor sin ventas cargadas");
        } else {
            mostrar_vendedor(aux);
            tsublista *auxsub = aux->sub;
            float referencia;
            printf("Ingrese el monto de la venta a modificar: ");
            fflush(stdin);
            scanf("%f",&referencia);
            while(auxsub != NULL && auxsub->importe != referencia)
                auxsub = auxsub->sig;
            if(auxsub == NULL)
                puts("No se encontro el importe de la venta cargada");
            else {
                printf("Ingrese nuevo monto de venta realizada: ");
                fflush(stdin);
                scanf("%f",&auxsub->importe);
                puts("Modificacion realizada correctamente.");
            }
        }
    }
    system("pause");
}

void destruir_sublista(tsublista *sub) {
    if(sub != NULL) {
        destruir_sublista(sub->sig);
        free(sub);
    }
}

void elimina_sublista(tlista **lis) {
    if(*lis == NULL)
        puts("Lista vacia");
    else {
        int ref;
        printf("Ingrese codigo de referencia a borrar sublista: ");
        fflush(stdin);
        scanf("%d",&ref);
        tlista *aux = *lis;
        while(aux != NULL && aux->codigo != ref)
            aux = aux->sig;
        if(aux == NULL)
            puts("Nodo no encontrado");
        else {
            if(aux->sub == NULL)
                puts("El nodo no tiene sublista");
            else {
                printf("Vendedor encontrado:\n");
                mostrar_vendedor(aux);
                destruir_sublista(aux->sub);
                aux->sub = NULL;
                puts("Sublista eliminada correctamente");
            }
        }
    }
    system("pause");
}

void elimina_sub_simple(tlista **lis) {
    if(*lis == NULL)
        puts("Lista vacia");
    else {
        int ref;
        printf("Ingrese el codigo del vendedor a eliminar venta: ");
        fflush(stdin);
        scanf("%d",&ref);
        tlista *aux = *lis;
        while(aux != NULL && aux->codigo != ref)
            aux = aux->sig;
        if(aux == NULL)
            puts("No encontrado");
        else {
            if(aux->sub == NULL)
                puts("El vendedor no posee ventas");
            else {
                printf("Vendedor encontrado:\n");
                mostrar_vendedor(aux);
                tsublista *auxsub = aux->sub, *ant = aux->sub;
                float referencia;
                printf("Ingrese monto de venta a eliminar: ");
                fflush(stdin);
                scanf("%f",&referencia);
                while(auxsub != NULL && auxsub->importe != referencia) {
                    ant = auxsub;
                    auxsub = auxsub->sig;
                }
                if(auxsub == NULL) {
                    puts("Importe no encontrado");
                } else if(auxsub->sig == NULL) {
                    ant = auxsub->sig;
                    free(auxsub);
                    puts("Eliminado correctamente");
                } else {
                    ant->sig = auxsub->sig;
                    free(auxsub);
                    puts("Eliminado correctamente");
                }
            }
        }
    }
    system("pause");
}



