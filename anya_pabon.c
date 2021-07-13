/*
2. Variables y su funcion:
♦ apellido[] → cadena que contiene un apellido. esta funcion se usa para buscar un cliente por apellido.
♦ auxiliar → variable de tipo clientela usada para distinguir el dato leido por teclado, con el dato levantado por archivo.
♦ clientes → variable de tipo clientela (struct), para leer y editar datos del archivo.
♦ pArch → variable puntero de tipo FILE que siempre alude al archivo binario.
♦ *nom → variable de tipo char que alude al nombre del archivo binario.
♦ cadena[] → array de cadena, para convertir la misma en mayuscula.
♦ c → caracter para ser pasado a mayuscula.
♦ rang → variable que determina la longitud del archivo binario en su llenado inicial.
♦ archivo_texto → puntero de tipo FILE que apunta a un archivo de texto.
♦ nom_T → nombre del archivo de texto.
♦ dim → variable de tipo int que alude a la extension del archivo binario (su uso, con este codigo sin edicion, es demostrativo en cuanto
  conocer manejar la funcion ftell y usarla. Sin embargo, si se edita el codigo y el rango no es igual a dim, compila igual).
♦ control → variable que se compara con dim, de modo de que, si llegan a ser iguales, se ejecute una accion.
♦ k → variable de tipo int que contabiliza la variable i del bucle for. Si el codigo sale del for, pero por
  por opcion vuelve a entrar, el bucle for inicia en i=k, de modo que inicie donde quedó.
♦ opcion → variable que le pide al usuario que confirme o no si se le ha dado la informacion pedida.
♦ legajo → variable de tipo int que alude al id del cliente, de modo que podamos localizar su informacion de manera directa.
♦ porc → variable que guarda el porcentaje a sumar o restar a una categoria general de clientes.
♦ category → variable que guarda una de las tres categorias permitidas, para comparar.
♦ bandera → variable que permite controlar si en el ordenamiento, sigue existiendo un dato anterior que es mayor al que le sigue.
♦ cont_auxiliar → variable usada para servir de indice del array apellidos[ordenados].
♦ apellidos_ordenados[] → array en donde se ordenan segun apellido y nombre, todos los datos que componen el archivo.
♦ pArch2 → puntero FILE igual a pArch. pero usamos este nombre porque solo lo usamos cuando llamamos desde una funcion a otra funcion, y pide el mismo parametro.
♦ nom[] → cadena que guarda el nombre del archivo binario, igual que *nom, solo que lo usamos porque desde una funcion llamamos a otra. solo para diferenciar.
♦ confrmacion → variable que pide al usuario si es cliente correcto para dar de baja logica.
♦ total_clientes[] → array de tipo clientela que guarda todos los datos excepto aquellos con campo activo=0;

7. Control de Errores:
lineas: 144, 392, 436, 458, 639, 907.
*/


#include "anya_pabon.h"
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define rango 100

//punto A
//Esta funcion recibe un puntero a archivo y a cadena.
//solo crea el archivo en la carpeta donde se este ejecutando el codigo.
void crea_archivo (FILE *pArch, char *nom)
{
    pArch = fopen(nom, "wb");

    fclose(pArch);
}


//Esta funcion recibe por referencia la cadena, y luego, letra por letra, la convierte en mayuscula.
//
void conv_mayus (char cadena[])
{
    for (int i=0; i<strlen(cadena); i++) cadena[i]=toupper(cadena[i]);
}

//esta funcion recibe un caracgter por valor, lo convierte en mayuscula, y lo retorna.
char mayus_letra (char c)
{
    c=toupper(c);

    return c;
}

//esta funcion abre el archivo, y llena todos sus campos con 0, de inicio a fin.
void llenado_inicial (FILE *pArch, char *nom, int rang)
{
    //llena la variable con 0 en todos sus campos.
    clientela clientes={0,"0","0",'0',0.0,-1};

    //abre el archivo en modo write, de modo que elimine todo o cree desde 0 el archivo.
    pArch=fopen(nom, "wb");

    //si escuentra el archivo, entra.
    if (pArch!=NULL)
    {
        //se posiciona al inicio del archivo.
        fseek(pArch,0,SEEK_SET);

        //escribe en cada fila la variable.
        for (int i=0;i<rang;i++) fwrite(&clientes, sizeof(clientela),1,pArch);

        //cierra el archivo.
        fclose(pArch);
    }
    //en caso de no encontrar el archivo, tira este mensaje de error.
    else printf("\nERROR EN LA APERTURA.");
}

//esta funcion copia todo el archivo binario en un archivo de texto, de modo que podamos verlo.
void muestra_como_texto(FILE *pArch, char *nom, FILE *archivo_texto, char *nom_T)
{
    clientela clientes;

    pArch=fopen(nom,"rb");

    archivo_texto=fopen(nom_T,"wt");

    //entra si encuentra ambas rutas de archivos.
    if(pArch!=NULL && archivo_texto!=NULL)
    {
        //se posiciona al inicio del archivo binario.
        fseek(pArch,0,SEEK_SET);

        //se posiciona al inicio del archivo de texto.
        fseek(archivo_texto,0,SEEK_SET);

        //le da una fila de titulo al archivo de texto.
        fprintf(archivo_texto ,"%-10s%-10s%-15s%-20s%-20s%s\n", "ID", "Nombre", "Apellido", "Categoria", "Facturacion", "Activo");

        //con este bucle, se copia toda la informacion del archivo binario en el archivo de texto.
        while(!feof(pArch))
        {
            fread(&clientes,sizeof(clientela),1,pArch);

            fprintf(archivo_texto, "%-10d%-10s%-15s%-20c%-20.2lf%d\n", clientes.id, clientes.nombre, clientes.apellido, clientes.categoria, clientes.facturacion, clientes.activo);
        }

        fclose(pArch);
        fclose(archivo_texto);
    }
    else printf("\nERROR EN APERTURA.");
}


//punto B
void alta_de_datos(FILE *pArch, char *nom)
{
    clientela clientes, auxiliar;

    if ((pArch=fopen(nom, "r+b"))!=NULL)//se asegura de que abra de manera correcta el archivo
    {
        fseek(pArch,0,SEEK_SET); //nos ubica al inicio del archivo.

        printf("\tA continuaci%cn se le pedir%cn los datos del cliente.\n", 162, 160);

        //forza al usuario a ingresar un valor entre 0 y rango.
        //CONTROL DE ERROR #1.
        do
        {
            printf("\t%c Ingrese el ID del cliente: ",204);
            scanf("%d", &clientes.id);
            fflush(stdin);

            if (clientes.id>rango) printf("****ERROR. EL ID DEBE SER UN DATO MENOR O IGUAL A %d\n", rango);

        } while (clientes.id<0 || clientes.id>rango);

        fseek(pArch,0,SEEK_SET);

        //se ubica al final de la posicion anterior al numero de id, de modo que se escriba/lea exactamente en la fila
        //igual al numero de id.
        fseek(pArch,(clientes.id-1)*sizeof(clientela),SEEK_SET);

        //levanta el dato.
        fread(&auxiliar, sizeof(clientela),1,pArch);

        //con este bucle, se verifica que el campo este vacio.
        //como en llenado inicial, todos los id=0, entonces si el id levantado
        //es distinto de 0, quiere decir que ya tiene un cliente guardado, con lo cual ahi no puede escribir, asi que vuelve a pedir id.
        while (auxiliar.id!=0)
        {
            clientes.id=0;

            printf("*******YA EXISTE ESE LEGAJO. INGRESE OTRO.*******\n");
            printf("\t%c Ingrese el ID del cliente: ",204);
            scanf("%d", &clientes.id);
            fflush(stdin);

            fseek(pArch,(clientes.id-1)*sizeof(clientela),SEEK_SET);

            fread(&auxiliar, sizeof(clientela),1,pArch);
        }

        //lee el nombre del cliente, asegurandose que no ingrese cadena vacia.
        //importante. El archivo solo esta compuesto de nombre y apellido (NO nombreS y apellidoS).
        do
        {
            printf("\t%c Nombre: ",204);
            scanf("%s", clientes.nombre);
            fflush(stdin);

        } while (isalpha(clientes.nombre[0])==0 && isalpha(clientes.nombre[1])==0);

        //lee el apellido, asegurandose que no ingrese cadena vacia.
        do
        {
            printf("\t%c Apellido: ",204);
            scanf("%s", clientes.apellido);
            fflush(stdin);

        } while (isalpha(clientes.apellido[0])==0 && isalpha(clientes.apellido[1])==0);

        //lee la categoria, la conviertre a mayuscula y se asegura que sea una de las permitidas.
        do
        {
            printf("\t%c Ingrese la categor%ca (A, B o C): ",204,161);
            scanf("%c", &clientes.categoria);
            fflush(stdin);

            clientes.categoria=mayus_letra(clientes.categoria);

        } while (clientes.categoria!='A' && clientes.categoria!='B' && clientes.categoria!='C');

        //se asegura que no ingrese un numero negativo. De resto, consideramos que, aunque es contradictorio, la
        //facturacion inicial de un cliente dado de alta, es 0. Esto es modificable luego en el punto E.
        do
        {
            printf("\t%c Ingrese facturaci%cn (valor mayor o igual que \"0\"): ",204,162);
            scanf("%lf", &clientes.facturacion);
            fflush(stdin);

        } while (clientes.facturacion<0);

        //este punto se asegura que solo ingrese si esta activo, o no.
        //consideramos que sería ideal que en el alta de clientes, directamente este campo se llenara con 1}
        //pero dejamos que el usuario ingrese el estado.
        do
        {
            printf("\t%c Ingrese si est%c activo (\"1\" activo, \"0\" inactivo): ",204,160);
            scanf("%d", &clientes.activo);
            fflush(stdin);

        } while(clientes.activo!=1 && clientes.activo!=0);

        //convierte en mayuscula las dos cadenas.
        conv_mayus(clientes.nombre);
        conv_mayus(clientes.apellido);

        //se posicion al final del byte anterior del id ingresado correctamente.
        fseek(pArch,(clientes.id-1)*sizeof(clientela),SEEK_SET);

        //escribe el dato en la fila de igual numero que el id.
        fwrite(&clientes,sizeof(clientela),1,pArch);

        fclose(pArch); //cierra el archivo.

        printf("CLIENTE REGISTRADO EXITOSAMENTE!\n");

        system("pause");
    }
    else printf("\nERROR EN LA APERTURA!"); //salta error en caso de no abrirlo bien.
}

//punto D
//esta funcion entra en el archivo, y compara desde el inicio el apellido con los apellidos guardados
//hasta que lo encuentre o se termine el archivo. En caso de encontrarlo, retorna toda la info de ese cliente.
//y le pregunta al usuario si ese era la informacion que buscaba (pues pueden haber dos o mas apellidos iguales).
//en caso de que si sea la informacion, termina la funcion, de lo contrario, busca el siguiente apellido igual.
//de no encontrarlo y acabarse el archivo, tira un mensaje de error. De encontrarlo, le dice la informacion y le
//pide validar de vuelta.
void buscar_apellido (FILE *pArch, char *nom, char apellido[])
{
    clientela clientes;

    int opcion=-1, dim, k=0, control=1;

    //convierte en mayuscula el apellido.
    conv_mayus(apellido);

    clientes.id=0;

    if ((pArch=fopen(nom, "rb"))!=NULL)
    {
        fseek(pArch,0,SEEK_END);

        dim=ftell(pArch)/sizeof(clientela);

        fseek(pArch,0,SEEK_SET);

        //este bucle esta para ejecutarse hasta que encuentre el apellido del cliente buscado.
        //de no existir, se rompe el bucle y se sale de la funcion.
        //de haber mas de 1 vez el apellido, se ejecuta hasta q emita la informacion del apellido buscado.
        //si imprime todos los apellidos repetidos y aun asi no encuentra la informacion desea, entonces no se cargó
        //ese usuario, e imprime mensaje de error.
        do
        {
            //en principio, el codigo esta para ejecutarse desde 0 hasta el final del archivo.
            for (int i=k;i<=dim;i++)
            {
                fread(&clientes, sizeof(clientes), 1, pArch);

                //si el apellido a buscar coincide con uno en el archivo, se sale del bucle determinado.
                if (strcmp(apellido, clientes.apellido)==0) break;

                //si control y dim son iguales, quiere decir que llego al final del archivo, y no encontro el apellido
                //entra el el if, tira el mensaje, y se sale de la funcion.
                if (control==dim)
                {
                    printf("****EL CLIENTE NO EXISTE****\n");

                    fclose(pArch);

                    system("pause");

                    return 0;
                }

                k=i;

                control+=1;
            }

        //imrpime la informacion leida.
        printf("\n\n***");
        printf("\nID\t\tNombre\t\tApellido\t\tCategor%ca\t\tFacturaci%cn\t\tActivo\n",161,162);
        printf("%-16d%-17s%-25s%-24c%-24.2f%d\n", clientes.id, clientes.nombre, clientes.apellido,
                clientes.categoria, clientes.facturacion, clientes.activo);

        //pide que se confirme si era la informacion esperada.
        printf("\n\tEste era el cliente que buscaba? (\"1\" para confirmar, \"0\" para negar): ");//hace esta pregunta, en caso de que haya clientes con mismo apellido

        while (opcion!=0 && opcion!=1) scanf("%d", &opcion);

        //si niega que sea la informacion, modificamos el apellido, y vuelve a ejecutarse el bucle.
        if (opcion!=1)
        {
            strcpy(clientes.apellido,"no");

            opcion=-1;
        }

    } while (opcion!=1);

        fclose(pArch);

        system("pause");
    }
    else printf("\nERROR EN LA APERTURA.");
}


//punto D
//al igual que la funcion anterior, esta funcion ubica, de manera directa y en caso de que exista,
//toda la informacion de un cliente. De lo contrario, imprime error.
void buscar_id (FILE *pArch, char *nom, int legajo)
{
    clientela clientes;

    if ((pArch=fopen(nom, "rb"))!=NULL)
    {

        //se posiciona al final del byte anterior al pasado por el parametro "legajo" de la funcion.
        fseek(pArch,(legajo-1)*sizeof(clientela), SEEK_SET);

        fread(&clientes,sizeof(clientela),1,pArch);

        //si el dato levantado tiene como id=0, quiere decir que ese campo esta vacio.
        if (clientes.id==0) printf("\n***ESTE NUMERO DE ID NO PERTENECE A NINGUN CLIENTE***\n");

        //si lo anterior es falso, entra en else e imprime todos los datos del cliente.
        else
        {
            printf("\n\n***");
            printf("\nID\t\tNombre\t\tApellido\t\tCategor%ca\t\tFacturaci%cn\t\tActivo\n",161,162);

            printf("%-16d%-17s%-25s%-24c%-24.2f%d\n", clientes.id, clientes.nombre, clientes.apellido,
                   clientes.categoria, clientes.facturacion, clientes.activo);
        }

        system("pause");

        fclose(pArch);
    }
    else printf("\nERROR EN LA APERTURA");
}


//punto E.
//esta funcion modifica de categoria e ingresos a un cliente, ingresando su id (legajo).
void modifica_cat_ing_id (FILE *pArch, char *nom, int legajo)
{
    int control=0;

    clientela clientes, auxiliar;

    if ((pArch=fopen(nom, "r+b"))!=NULL)
    {
        //se posiciona al final del bute anterior de legajo.
        fseek(pArch,(legajo-1)*sizeof(clientela), SEEK_SET);

        //lee el dato en la misma posicion de legajo pasado.
        fread(&clientes,sizeof(clientela),1,pArch);

        //CONTROL DE ERORRES #2
        //controla que no se siga ejecutando el codigo cuando el cliente no existe.
        if (clientes.id==0)
        {
            printf("******ERROR. ESTE CLIENTE NO ESTA CARGADO EN EL SISTEMA******\n");

            fclose(pArch);

            system("pause");

            return 0;
        }

        //consulta si quiere cambiar a ese cliente.
        printf("\t\tEst%c seguro que desea modificar de categr%ca e ingresos a %s %s?\n",160,161,clientes.nombre, clientes.apellido);

        //se asegura que responda una de las dos opciones posibles.
        do
        {
            printf("\t\t(\"1\" para confirmar, \"0\" para salir): ");
            scanf("%d", &control);
            fflush(stdin);

        } while (control!=1 && control!=0);

        //en caso de que niegue, se sale de la funcion.
        if (control==0)
        {
            return 0;

            system("pause");
        }

        //en caso de afirmar, pide los nuevos datos.
        else
        {
            //esta funcion la va a repetir mientra no ingrese una de las letras establecidas, o repita la misma letra ya puesta.
            do
            {
                printf("\t\t %cIngrese la nueva categor%ca (A,B o C): ",204,161);
                scanf("%c", &auxiliar.categoria);
                fflush(stdin);

                auxiliar.categoria=mayus_letra(auxiliar.categoria);

                //CONTROL DE ERRORES #3
                //bien podria pensarse que cambiar la categoria puede ser mantener la que se tenia. pero tomamos el
                //CAMBIAR de modo exclusivo.
                if (auxiliar.categoria==clientes.categoria)
                {
                    printf("******ERROR. ESTA REPITIENDO CATEGORIA******\n");

                    auxiliar.categoria='I';
                }
                else clientes.categoria=auxiliar.categoria;

            } while (auxiliar.categoria!='A' && auxiliar.categoria!='B' && auxiliar.categoria!='C');

            //controla que ingrese un valor positivo y diferente al anterior.
            do
            {
                auxiliar.facturacion=clientes.facturacion;

                printf("\t\t %cIngrese nueva facturaci%cn: ",204, 162);
                scanf("%lf",&clientes.facturacion);
                fflush(stdin);

                //CONTROL DE ERRORES #4
                //si ambas facturaciones son iguales, le imprime este error, pues no CAMBIA.
                if (clientes.facturacion==auxiliar.facturacion)
                {
                    printf("******ERROR. ESTA REPITIENDO FACTURACION******\n");

                    clientes.facturacion=-1;
                }

                //si lo anterior es falso, le asigna la nueva facturacion.
                else clientes.facturacion==auxiliar.facturacion;

            } while (clientes.facturacion<0);

            //retrocede un byte en el archivo para escribir donde corresponde.
            fseek(pArch, -sizeof(clientela), SEEK_CUR);

            //graba el dato en el archivo.
            fwrite(&clientes,sizeof(clientela),1,pArch);
        }

        printf("MODIFICACION EXITOSA.\n");

        system("pause");

        fclose(pArch);
    }
}


//punto E
//esta funcion modifica de categoria e ingresos a un cliente, ingresando su apellido.
//es una funcion similar a buscar por apellido. Con lo cual, no volveremos a explicar lo mismo.
void modifica_cat_fac_ape (FILE *pArch, char *nom, char apellido[])
{
    clientela clientes, auxiliar;

    int opcion=-1, dim, k=0, control=1;

    conv_mayus(apellido);

    if ((pArch=fopen(nom, "r+b"))!=NULL)
    {
        fseek(pArch,0,SEEK_END);

        dim=ftell(pArch)/sizeof(clientela);

        fseek(pArch,0,SEEK_SET);

    do
    {
        for (int i=k;i<=dim;i++)
        {
            fread(&clientes, sizeof(clientes), 1, pArch);

            if (strcmp(apellido, clientes.apellido)==0) break;

            if (control==dim)
            {

                printf("****EL CLIENTE NO EXISTE****\n");

                fclose(pArch);

                system("pause");

                return 0;
            }

            k=i;

            control+=1;
        }

        //le pasa a la variable auxiliar los dos datos q queremos cambiar y por ende, modificar.
        auxiliar.categoria=clientes.categoria;
        auxiliar.facturacion=clientes.facturacion;

        //consulta si es el cliente buscado.
        printf("\t\tEl cliente que desea modificar es %s %s?\n",clientes.nombre, clientes.apellido);
        printf("\t\t(\"1\" para confirmar, \"0\" para seguir buscando): ");

        //se asegura que ingrese una de las opciones correctas.
        while (opcion!=0 && opcion!=1) scanf("%d", &opcion);

        fflush(stdin);

        if (opcion==0)
        {
            //esto lo hace, en caso de que haya dos apellidos iguales, busque el que sigue.
            strcpy(clientes.apellido,"sigue");

            opcion=-1;
        }

    } while(opcion!=1);

        //se asegura que ingrese una NUEVA categoria entre las tres posibles.
        do
        {
            printf("\t\t%c Ingrese la  nueva categor%ca (A,B o C): ",204, 161);
            scanf("%s", &clientes.categoria);
            fflush(stdin);

            clientes.categoria=mayus_letra(clientes.categoria);

            if (clientes.categoria==auxiliar.categoria)
            {
                printf("******ERROR. ESTA REPITIENDO CATEGORIA******");

                clientes.categoria='I';
            }

        } while (clientes.categoria!='A' && clientes.categoria!='B' && clientes.categoria!='C');

        //se asegura que ingrese una NUEVA facturacion y que sea positiva.
        do
        {
            printf("\t\t%c Ingrese la nueva facturaci%cn: ",204,162);
            scanf("%lf", &clientes.facturacion);

            if (clientes.facturacion==auxiliar.facturacion)
            {
                printf("******ERROR. ESTA REPITIENDO LA FACTURACION******");

                clientes.facturacion=-1;
            }

        } while (clientes.facturacion<0);

        fseek(pArch,-sizeof(clientela),SEEK_CUR);

        fwrite(&clientes,sizeof(clientela),1,pArch);

        fclose(pArch);

        printf("MODIFICACION EXITOSA.\n");

        system("pause");
    }
    else printf("\nERROR EN LA APERTURA.");
}


//esta cumple con el item F
//esta funcion pregunta categoria y cantidad porcentual a sumar o restar, y la aplica a todos los clientes cuya categoria sea igual.
void actualiza_facturacion_global (FILE *pArch, char *nom)
{
    clientela clientes;

    float porc;

    int opcion, dim;

    char category;

    if ((pArch=fopen(nom,"rb+"))!=NULL)
    {
        fseek(pArch,0,SEEK_END);

        dim=ftell(pArch)/sizeof(clientela);

        printf("\tEst%c por actualizar todas las facturaciones correspondientes a una categor%ca.\n",160,161);

        //controla la opcion.
        do
        {
            printf("\tVa a realizar:\n\t\t1. Aumento.\n\t\t2. Disminuci%cn.\n",162);
            scanf("%d", &opcion);
            fflush(stdin);

        } while (opcion!=1 && opcion!=2);

        //controla que ingrese un porcentaje acorde a la opcion de disminucion o aumento.
        do
        {
            printf("\t\t%c Ingrese el porcentaje: \n",204);
            printf("\t\t(aclaraci%cn: si es 1%c, ingrese 1, si es 15.6%c, ingrese 15.6, y as%c sucesivamente.): ",162,37,37,161);
            scanf("%f", &porc);
            fflush(stdin);

            //CONTROL DE ERRORES #5
            //en caso de aplica un descuento de mas de 100%, la empresa pierde. controla que eso no pase.
            if (opcion==2 && porc>100)
            {
                printf("****NO PUEDE HACER UN DESCUENTO DE MAS DEL 100%c, PIERDES DINERO****\n",37);

                porc=-1;
            }

        } while(porc<=0);

        //controla que sea una de las tres categorias permitidas.
        do
        {
            printf("\t\t%c Ingrese categor%ca (A, B o C): ",204, 161);
            scanf("%c",&category);
            fflush(stdin);

            category=mayus_letra(category);

        } while (category!='A' && category!='B' && category!='C');

        if (opcion==1) porc=(porc/100)+1;
        else porc=(100-porc)/100;
        //de este modo podre operar matematicamente;

        fseek(pArch,0,SEEK_SET);

        for(int i=0; i<dim;i++)
        {
            //lee el dato.
            fread(&clientes,sizeof(clientes),1,pArch);

            //compara que las categorias sean iguales para ejecutar.
            if (clientes.categoria==category)
            {
                //realiza la operacion.
                clientes.facturacion=clientes.facturacion*porc;

                //retrocede un byte.
                fseek(pArch,-sizeof(clientela),SEEK_CUR);

                //escribe, en la misma posicion que leyó, la varible con la facturacion modificada.
                fwrite(&clientes,sizeof(clientela),1,pArch);

                fflush(pArch);
                //no entiendo este parametro.
            }
        }
        fclose(pArch);

        printf("ACTUALIZACION EXITOSA POR CATEGORIA.\n");

        system("pause");
    }
    else printf("ERROR EN LA APERTURA.\n");
}


//cumple en punto G
//esta funcion realiza un ordenamiento por burbujeo, y emite los datos en orden ascendente por apellido y nombre.
void ordena_emite_archivo (FILE *pArch, char *nom)
{
    int dim, bandera=1, cont_aux=0;

    pArch=fopen(nom, "rb");

    fseek(pArch,0,SEEK_END);

    dim=ftell(pArch)/sizeof(clientela);

    clientela apellidos_ordenados[dim], clientes;

    if (pArch!=NULL)
    {
        fseek(pArch,0,SEEK_SET);

        for (int i=0; i<dim; i++)
        {
            fread(&clientes,sizeof(clientela),1,pArch);

            //aqui solo vamos a guardar los datos de clientes con id difernete de 0, es decir, clientes con informacion relevante.
            if(clientes.id!=0)
            {
                apellidos_ordenados[cont_aux]=clientes;

                //usamos este contaador auxiliar para ir en orden la carga del vector.
                cont_aux+=1;
            }
        }

        //ordenamiento por burbujeo. Ordena de A a Z los apellidos.
        //se ejecuta siempre que bandera sea 1, es decir, cada que, la ejecucion del codigo,
        //en la parte del for, se encuentre que un apellido que precede, sea mayor a un apellido que le sigue.
        while(bandera)
        {
            bandera=0;

            for (int i=0;i<cont_aux-1;i++)
            {
                //si el apellido anterior es mayor al apellido siguiente, entonces los cambia de lugar.
                if (strcmp(apellidos_ordenados[i].apellido,apellidos_ordenados[i+1].apellido)>0)
                {
                    bandera=1;

                    clientes=apellidos_ordenados[i];

                    apellidos_ordenados[i]=apellidos_ordenados[i+1];

                    apellidos_ordenados[i+1]=clientes;
                }
            }
        }

        bandera=1;

        //esta parte, ordena el array, pero ahora por apellido, cumpliendo 2 condiciones.
        //1 que si los apellidos son iguales Y el nombre del strcut que esta en la posicion del array anterior es mayor al que le sigue
        //haga el cambio.
        while(bandera)
        {
            bandera=0;

            for (int i=0;i<cont_aux-1;i++)
            {
                if (strcmp(apellidos_ordenados[i].apellido,apellidos_ordenados[i+1].apellido)==0)
                {
                    if (strcmp(apellidos_ordenados[i].nombre,apellidos_ordenados[i+1].nombre)>0)
                    {
                        clientes=apellidos_ordenados[i];

                        apellidos_ordenados[i]=apellidos_ordenados[i+1];

                        apellidos_ordenados[i+1]=clientes;

                        bandera=1;
                    }
                }
            }
        }
        //titulo
        printf("\t\t\t\t\t==============================\n");
        printf("\t\t\t\t\t Datos ordenados por Apellido\n");
        printf("\t\t\t\t\t==============================\n\n");
        printf("id\t\tNombre\t\tApellido\t\tCategor%ca\t\tFacturaci%cn\t\tActivo\n",161,162);

        //imprime el array ahora ordenado.
        for (int i=0;i<cont_aux;i++)
        {
            printf("%-16d%-16s%-24s%-24c%-24.3f%d\n",apellidos_ordenados[i].id, apellidos_ordenados[i].nombre,
                   apellidos_ordenados[i].apellido, apellidos_ordenados[i].categoria,
                   apellidos_ordenados[i].facturacion, apellidos_ordenados[i].activo);
        }

        fclose(pArch);

        system("pause");
    }
    else printf("\nERROR EN LA APERTURA.");
}


//Punto C.2
//emite los clientes con status de activos
void emite_activos (FILE *pArch2, char nom[])
{
    clientela clientes;

    pArch2=fopen(nom, "rb");

    if (pArch2!=NULL)
    {
        //encabezadp.
        printf("\t\t\t\t\t==============================\n");
        printf("\t\t\t\t\t Clientes con Cuentas Activas\n");
        printf("\t\t\t\t\t==============================\n\n");
        printf("id\t\tNombre\t\tApellido\t\tCategor%ca\t\tFacturaci%cn\t\tActivo\n",161,162);

        //se posiciona al inicio.
        fseek(pArch2,0,SEEK_SET);

        //se ejecuta hasta el final del archivo el ciclo.
        while (!feof(pArch2))
        {
            //lee el dato.
            fread(&clientes,sizeof(clientela),1,pArch2);

            //confirma q su status sea activo.
            if (clientes.activo==1)
            {
                //imrpime el dato.
                printf("%-16d%-16s%-24s%-24c%-24.3f%d\n",clientes.id, clientes.nombre,
                       clientes.apellido, clientes.categoria,
                       clientes.facturacion, clientes.activo);
            }
        }

        fclose(pArch2);

        system("pause");
    }
    else printf("\nERROR EN LA APERTURA.");
}

//Punto C.1 y C.3 (parcial)
//emite todos los datos guardados en el archivo, sea  con status activo, inactivo o vacio.
void emite_todo (FILE *pArch2, char nom[])
{
    clientela clientes;

    if ((pArch2=fopen(nom,"rb"))!=NULL)
    {
        fseek (pArch2,0,SEEK_SET);

        //titulo
        printf("\t\t\t\t\t===============================\n");
        printf("\t\t\t\t\t  Listado General del Archivo \n");
        printf("\t\t\t\t\t===============================\n\n");
        printf("id\t\tNombre\t\tApellido\t\tCategor%ca\t\tFacturaci%cn\t\tActivo\n",161,162);

        //se ejecuta hasta llegar al final.
        while (!feof(pArch2))
        {
            //lee el dato.
            fread(&clientes,sizeof(clientela),1,pArch2);

            //imrpime el dato
            printf("%-16d%-16s%-24s%-24c%-24.3f%d\n",clientes.id, clientes.nombre,
            clientes.apellido, clientes.categoria,
            clientes.facturacion, clientes.activo);
        }

        fclose(pArch2);

        system("pause");

    }
    else printf("\nERROR EN LA APERTURA.");
}

//cumple el punto H
//permite cambiar el status de un cliente de activo a inactivo solamente pasandole su id.
void baja_logica (FILE *pArch, char *nom, int legajo)
{
    clientela clientes;

    int confirmacion;

    pArch=fopen(nom, "rb+");

    if(pArch!=NULL)
    {
        //se posiciona al final del byte anterior.
        fseek(pArch,(legajo-1)*sizeof(clientela),SEEK_SET);

        //lee el dato que sigue, o sea, el del lelgajo.
        fread(&clientes,sizeof(clientela),1,pArch);

        //controla que el status del cliente fuese activo de antemano. De lo contrario, entra aqui.
        if (clientes.activo==0)
        {
            printf("****ERROR. ESTE CLIENTE YA SE ENCUENTRA INACTIVO.****\n");

            system("pause");

            return 0;
        }

        //CONTROL DE ERROR #6
        //en caso de que le pasase un cliente cuyo id no corresponde con nadie, se sale
        if (clientes.id==0)
        {
            printf("****ERROR. ESTE CLIENTE NO EXISTE****\n");

            system("pause");

            return 0;
        }

        //pregunta de confirmacion en caso de que pase las dos condiciones anteriores.
        printf("\t\tEst%c seguro de dar de baja a %s %s, de categor%ca %c y facturaci%cn %.2f?\n",160,
               clientes.nombre,clientes.apellido,161,clientes.categoria,162,clientes.facturacion);

        //se asegura que solo escriba una de las dos opciones aceptables.
        do
        {
            printf("\t\t(Ingrese \"1\" para confirmar, \"0\" para negar): ");

            scanf("%d", &confirmacion);

            fflush(stdin);

        } while(confirmacion!=1 && confirmacion!=0);

        //si el usuario niega que fuera el cliente, se sale del codigo.
        if (confirmacion==0)
        {
            system("pause");

            return 0;
        }

        //en caso de afimar, hace el cambio y lo escribe en el archivo.
        else
        {
            clientes.activo=0;

            fseek(pArch,-sizeof(clientela),SEEK_CUR);

            fwrite(&clientes,sizeof(clientela),1,pArch);
        }

        fclose(pArch);

        printf("\t\tDADA DE BAJA EXITOSA!\n\n");

        //llama a la funcion.
        emite_activos(pArch,nom);

        system("pause");
    }
    else printf("\nERROR EN LA APERTURA.");
}


//cumple el apartado I
//pasa toda la informacion de clientes con status de activo a un array. Crea el mismo archivo de 0, y copia el array.
//esta funcion tiene comentadas las acciones de remove, para poder cumplir con la consigna de poder pasar los dos archivos.
//si se quita el comentario, elimina el archivo auxiliar y deja solo el actual y todo funciona como debería.
void elimina_clientes_inactivos (FILE *pArch, char *nom)
{
    int dim;

    FILE *nuevo_archivo;

    char nombre[]="clientes_nuevos.dat";

    //abre el archivo.
    pArch=fopen(nom, "rb");

    fseek(pArch,0,SEEK_END);

    dim=ftell(pArch)/sizeof(clientela);

    clientela clientes, total_clientes[dim];

    //forma inicia de todos las filas de los campos del archivo.
    clientela clientes2={0,"0","0",'0',0.0,-1};

    if (pArch!=NULL)
    {
        fseek(pArch,0,SEEK_SET);

        for (int i=0;i<dim;i++)
        {
            fread(&clientes,sizeof(clientela),1,pArch);

            //guarda solo clientes con status activo
            if (clientes.activo==1) total_clientes[i]=clientes;

            //guarda, en caso no cumplirse el caso anterior, un fila llena de 0;
            else total_clientes[i]=clientes2;
        }

        fclose(pArch);
    }
    else printf("\nERROR EN LA APERTURA.");

    //crea el archivo, que en este caso ya existe, con lo cual, como esta programado de abrir con "wb", borra todo lo anterior.
    crea_archivo(nuevo_archivo,nombre);

    //llena todo de 0
    llenado_inicial(nuevo_archivo,nombre,dim);

    //abre el archivo recien creado en modo de lectura-escritura.
    nuevo_archivo=fopen(nombre, "rb+");

    if (nuevo_archivo!=NULL)
    {
        //se pone al inicio del archivo.
        fseek(nuevo_archivo,0,SEEK_SET);

        //copia todo el array en el archivo nuevo
        for (int i=0; i<dim;i++) fwrite(&total_clientes[i],sizeof(clientela),1,nuevo_archivo);

        fclose(nuevo_archivo);

        //elimina el archivo viejo.
        //remove(nom);

        //renombra al archio nuevo.
        //rename(nombre,nom);

        //elimina el archivo nuevo creado.
        //remove(nombre);
    }
    else printf("\nERROR EN LA APERTURA.");
}

//cumple el punto C, segun la opcion pasada por teclado.
//imprime los datos activos (opcion=1), todos los datos (2), o todos los datos despues de eliminar los inactivos (3).
void listar (FILE *pArch, char *nom, int opcion)
{
    clientela clientes;

    if ((pArch=fopen(nom, "r+b"))!=NULL)
    {
        //leyenda en el encabezado
        printf("\n\n***\n");
        printf("Leyenda\n1. Activo.\n0. Inactivo.\n-1. Vac%co.\n\n",161);

        fseek(pArch,0,SEEK_SET);

        //segun la opcion, se encarga de imprimir la informacion solicitada.
        switch (opcion)
        {
        case 1:
            emite_todo(pArch,nom);

            fclose(pArch);

            break;

        case 2:
            emite_activos(pArch,nom);

            fclose(pArch);

            break;

        case 3:
            elimina_clientes_inactivos(pArch,nom);

            emite_todo(pArch,nom);

            fclose(pArch);

            break;
        }
    }
    else printf("\nERROR EN LA APERTURA.");
}

