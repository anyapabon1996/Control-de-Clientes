/*1. Archivos usados:
clientes.dat → archivo binario.
control.dat → archivo de texto, en donde paso toda la informacion guardada en el binario, para poder verla.
clientes_nuevos.dat → archivo binario despues de la eliminacion de los inactivos.

2. Variables y su funcion:
♦tiempo_hora y *miTiempo → para emitir la fecha actual.
♦last_name → para realizar las muestras y modificaciones de archivos buscando el apellido.
♦id → para realizar las muestras y modificaciones de archivos buscando el id.
♦rango → para, al momento de crear el archivo, llenar el mismo de manera inicial hasta el rango establecido.
la constante simbolica rango es destacable, debido a que el programa solo lee, escribe o reescribe datos, pero no agrega datos mas allà del rango,
con lo cual, si rango es 100, agregar un cliente con id mayor a 100, arrojarà un mensaje de error.
♦option → la usamos para movernos en el menu del switch.
♦opcion → la usamos para movernos en el submenu desplegado segun option.
♦nombre_archivoB → archivo binario.
♦nombre_archivoT → archivo de texto.
♦archivo → puntero de tipo FILE al archivo binario.
♦archivoT → puntero de tipo FILE  al archivo de texto.

post condiciones:
♦ puntos no resueltos: el sistema contempla ciertas limitaciones:
1) establecí un rango que 100 archivos como cantidad posible a llenar en el mismo. Esto puede ser modificado con la variable simbolica rango.}
2) no hay opcion de agregado, con lo cual, solo se puede registrar clientes con id menor o igual al rango. Esto por eleccion propia.
3) si ek usuario, en el menu, en lugar de ingresar una opcion numero, elige una alfabetica, el sistema se paraliza.
4) EL ITEM DE ELIMINACION DE CLIENTES INACTVOS, TIENE COMENTADAS LAS FUNCIONES DE REMOVE Y RENAME. para que funcione bien el programa, DESCOMENTAR ESAS LINEAS (1023,1026,1029)
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#define rango 100
#include "anya_pabon.h"

int main()
{
    time_t tiempo_hora;

    time(&tiempo_hora);

    struct tm *miTiempo=localtime(&tiempo_hora);

    char last_name[30];

    int id,opcion=-1, option;

    //nombre del archivo binario
    char nombre_archivoB[]="clientes.dat";

    //nombre del archivo de texto.
    char nombre_archivoT[]="Control.dat";

    //puntero al archivo binario
    FILE *archivo;

    //puntero a archivo de texto
    FILE *archivoT;

    //llna la cadena de puros 0.
    memset(last_name,0,strlen(last_name));

    printf("Anyair Studios\n");
    printf("%d/%d/%d\n",miTiempo->tm_mday, miTiempo->tm_mon+1,miTiempo->tm_year+1900);
    printf("Bienvenid@\n\n");
    do
    {
        printf("\n\t%cMENU%c\n",201,187);
        printf("1. Crear archivo.\n2. Alta de clientes.\n3. Listado de clientes.\n4. Buscar cliente.\n5. Actualiza categor%ca y facturaci%cn de cliente.\n",161,162);
        printf("6. Actualiza facturaci%cn por categor%ca.\n7. Datos ordenados por apellido.\n8. Baja l%cgica.\n9. Elimina clientes inactivos.\n",162,161,162);
        printf("0. Terminar.");

        printf("\n\nOpci%cn: ",162);

        option=-1;

        //se asegura de que la opcion este en el rango permitido por el codificado.
        while (option<0 || option>9) scanf("%d",&option);

        switch (option)
        {
        case 1:
            //llama a la funcion
            crea_archivo(nombre_archivoB, nombre_archivoB);

            //llama a la funcion
            llenado_inicial(archivo, nombre_archivoB, rango);

            //mensaje al usuario.
            printf("ARCHIVO CREADO EXITOSAMENTE.\n");

            //colocamos el mensaje al usuario y esta pausa aqui, porque esta misma funcion es reutilizada en la opcion 9, con lo cual
            //este mensaje y pausa no le corresponden.
            system("pause");

            break;

        case 2:
            //llama a la funcion
            alta_de_datos(archivo, nombre_archivoB);

            break;

        case 3:
            printf("\tListar por\n\t\t1. Total de archivos.\n\t\t2. Clinetes activos.\n\t\t3. Clientes despu%cs de eliminar los inactivos.\n",130);

            opcion=-1;

            //se asegura que la opcion este en el rango establecido por el sub-menu.
            while(opcion<=0 || opcion>3) scanf("%d",&opcion);

            fflush(stdin);

            //llama a la funcion
            listar(archivo,nombre_archivoB,opcion);

            break;

        case 4:
            printf("\tBuscar por\n\t\t1. ID.\n\t\t2. Apellido.\n");

            //se asegura q solo agregue una de las dos opciones viables.
            do
            {
                scanf("%d", &opcion);
                fflush(stdin);

            } while (opcion!=1 && opcion!=2);

            if (opcion==1)
            {
                printf("\t\t%c Ingrese ID del cliente: ",204);

                id=-1;

                //se asegura q ingrese un numero positivo.
                while(id<0) scanf("%d", &id);

                fflush(stdin);

                //llama a la funcion
                buscar_id(archivo, nombre_archivoB, id);
            }
            else
            {
                //se asegura que el usuario ingrese letras y no espacio vacío.
                do
                {
                    printf("\t\t%c Ingrese apellido: ",204);
                    scanf("%s", last_name);
                    fflush(stdin);

                } while(isalpha(last_name[0])==0 && isalpha(last_name[1])==0);

                //llama a la funcion
                buscar_apellido(archivo, nombre_archivoB, last_name);
            }

            break;

        case 5:
            printf("\t1. Actualiza por apellido.\n\t2. Actualiza por ID.\n");

            opcion=-1;

            //se asegura q ingrese una de las dos opciones establecidas.
            while(opcion!=1 && opcion!=2) scanf("%d", &opcion);

            fflush(stdin);

            if (opcion==1)
            {
                 //se asegura que el usuario ingrese letras y no espacio vacío.
                do
                {
                    printf("\t\t%c Ingrese apellido: ",204);
                    scanf("%s", last_name);
                    fflush(stdin);

                } while(isalpha(last_name[0])==0 && isalpha(last_name[1])==0);

                //llama a la funcion
                modifica_cat_fac_ape(archivo, nombre_archivoB, last_name);
            }
            else
            {
                id=-1;

                printf("\t\t%c Ingrese ID del cliente: ",204);

                //se asegura que ingrese un numero positivo.
                while(id<0) scanf("%d", &id);

                fflush(stdin);

                //llama a la funcion
                modifica_cat_ing_id (archivo, nombre_archivoB, id);
            }

            break;

        case 6:
            //llama a la funcion
            actualiza_facturacion_global(archivo, nombre_archivoB);

            break;

        case 7:
            //llama a la funcion
            ordena_emite_archivo(archivo,nombre_archivoB);

            break;

        case 8:
            printf("\t%c Ingrese el legajo del cliente al que desea dar de baja:",204);

            id=-1;

            //se asegura que ingrese un numero positivo
            while (id<0) scanf("%d", &id);

            fflush(stdin);

            //llama a la funcion
            baja_logica(archivo,nombre_archivoB,id);

            break;

        case 9:
            //llama a la funcion
            elimina_clientes_inactivos(archivo,nombre_archivoB);

            //colocamos este mensaje aqui,porque la opcion 3 tambien llama ala funcion elimina clientes inactivos, y no queremos que lance este mensaje.
            printf("ELIMINACION COMPLETA DE CLIENTES INACTIVOS!\n");

            //colocamos este pause aqui, porque si no, tambien lo ejecutaria la opcion 3, como el caso anterior, y emitiria entonces dos pause.
            system("pause");

            break;
        }

    } while (option!=0);

    //pasa toda a la informacion cargada o modificada al archivo de texto.
    muestra_como_texto(archivo, nombre_archivoB, archivoT, nombre_archivoT);

    printf("\n\n\t\tTen lindo d%ca. Nos volveremos a leer.\n",161);

    return 0;
}


