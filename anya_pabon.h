#ifndef ANYA_PABON_H_INCLUDED
#define ANYA_PABON_H_INCLUDED
#include <stdio.h>

typedef struct cartera
{
    int id;
    char nombre[30];
    char apellido[30];
    char categoria; //A o B o C
    double facturacion;
    int activo; //1 activo, 0 inactivo

} clientela;

void crea_archivo (FILE *pArch, char *nom);

void conv_mayus (char cadena[]);

char mayus_letra (char c);

void llenado_inicial (FILE *pArch, char *nom, int rang);

void muestra_como_texto(FILE *pArch, char *nom, FILE *archivo_texto, char *nom_T);

void buscar_apellido (FILE *pArch, char *nom, char apellido[]);

void buscar_id (FILE *pArch, char *nom, int legajo);

void modifica_cat_ing_id (FILE *pArch, char *nom, int legajo);

void modifica_cat_fac_ape (FILE *pArch, char *nom, char apellido[]);

void actualiza_facturacion_global (FILE *pArch, char *nom);

void ordena_emite_archivo (FILE *pArch, char *nom);

void emite_activos (FILE *pArch2, char nom[]);

void baja_logica (FILE *pArch, char *nom, int legajo);

void elimina_clientes_inactivos (FILE *pArch, char *nom);

void listar (FILE *pArch, char *nom, int opcion);

#endif // ANYA_PABON_H_INCLUDED
