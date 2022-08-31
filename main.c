#include "list.c"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct {
  const char *nombre;
  int cantnivel;
} item;

typedef struct {
  List *equipable;
  List *consumible;
} inventario;

typedef struct {
  const char *nombre;
  inventario *inv;
} personaje;

void Imports();
void agregarDatos(const char *per, const char *it, const char *ty,
                  const char *nc, List *usuarios, List *items);
char *buscar(List *usuario, const char *per);
const char *get_csv_field (char * tmp, int k);

int main(void) {
  // Menú
  int opcion = -1;
  printf("Bienvenidos al menú de opciones del juego RPG, elegíd un número:\n");
  while (opcion != 0) {

    // Mostar en pantalla
    printf("1.- Importar \n");
    printf("2.- Mostrar personajes \n");
    printf("0.- Salir\n");

    // Pedir opcion
    scanf("%d", &opcion);
    switch (opcion) {
    case 1:
      Imports();
    case 0:
      break;
    }
  }

  return 0;
}

void Imports() {
  // Definicion de listas
  List *usuarios = createList();
  List *items = createList();

  // piede la lista de items
  FILE *archivo = fopen("Items - Items.csv", "r");

  // Se asegura que el nombre del archivo este bien ingresado

  char *linea = (char *)malloc(1024 * sizeof(char *));
  const char *per, *it, *ty, *nc;

  fgets(linea, 1023, archivo);
  while (fgets(linea, 1023, archivo) != NULL) {

    per = get_csv_field(linea, 4);
    it = get_csv_field(linea, 2);
    ty = get_csv_field(linea, 1);
    nc = get_csv_field(linea, 3);

    agregarDatos(per, it, ty, nc, usuarios, items);
  }
  printf("Se cargaron los datos.\n");
}

void agregarDatos(const char *per, const char *it, const char *ty,
                  const char *nc, List *usuarios, List *items) {

  item *newItem = (item *)malloc(sizeof(item *));
  personaje *newPersonaje = (personaje *)malloc(sizeof(personaje *));

  newItem->nombre = it;
  newItem->cantnivel = atoi(nc);

  char *aux = buscar(usuarios, per);

  printf("cargando...");

  if (strcmp(aux, per) == 0) {
    // agregar el item a la lista del personaje ingresado
    if (strcmp(newItem->nombre, "consumible") == 0) {
      newPersonaje->nombre = per;
      pushFront(items, newItem);
      pushFront(newPersonaje->inv->consumible, items);
    }
  } else {
    // crear nodo y agregar el item al nuevo nodo
    newPersonaje->nombre = per;
    pushFront(usuarios, per);
    pushFront(items, newItem);
    pushFront(newPersonaje->inv->consumible, items);
  }
  printf("datos cargados.\n");
}

char *buscar(List *usuario, const char *per) {
  char *aux = firstList(usuario);
  while (strcmp(per, aux) != 0 && aux != NULL) {
    aux = (char *)nextList(usuario);
  }
  return aux;
}

const char *get_csv_field (char * tmp, int k) {
    int open_mark = 0;
    char* ret=(char*) malloc (100*sizeof(char));
    int ini_i=0, i=0;
    int j=0;
    while(tmp[i+1]!='\0'){

        if(tmp[i]== '\"'){
            open_mark = 1-open_mark;
            if(open_mark) ini_i = i+1;
            i++;
            continue;
        }

        if(open_mark || tmp[i]!= ','){
            if(k==j) ret[i-ini_i] = tmp[i];
            i++;
            continue;
        }

        if(tmp[i]== ','){
            if(k==j) {
               ret[i-ini_i] = 0;
               return ret;
            }
            j++; ini_i = i+1;
        }

        i++;
    }

    if(k==j) {
       ret[i-ini_i] = 0;
       return ret;
    }


    return NULL;
}
