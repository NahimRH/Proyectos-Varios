#include <stdio.h>
#include <stdlib.h>

#define fil 5
#define col 10

#define pA 73
#define pN 51

#define qui 500
#define dos 200
#define cien 100
#define cin 50

#define M1 10
#define M2 5
#define M3 2
#define M4 1

struct nodoCoche{
	int placas;
	int turno;
    struct nodoCoche *ptrSiguiente;
};

typedef struct nodoCoche NodoCoche;
typedef NodoCoche *ptrNodoCoche;

//Funciones de la Cola
int vacia(ptrNodoCoche *ptrPrim);
void insertar(ptrNodoCoche *ptrPrim, ptrNodoCoche *ptrUlt, int placa, int turno);
void pasarTurno(ptrNodoCoche *ptrPrim, ptrNodoCoche *ptrUlt);

//Funciones del autocinema
int pago(int costo);
int cambio(int suma, int costo);

int main()
{
	int i, j, k = 0, opcion, opcion2, placa, lug, turno = 0, lugares[fil][col], adultos, ninos, costo, total=0;
	
	ptrNodoCoche ptrPrim = NULL;
	ptrNodoCoche ptrUlt = NULL;
	
	
	for(i=0; i<fil; i++)
	{
		for(j=0; j<col; j++)
		{
			k++;
			lugares[i][j] = k;
		}
	}
	
	do
	{
		printf("Bienvenido al cine\n'El vato de EDA'\n\n");
		printf("Escoger una opcion\n1)Introducir cola de autos\n2)Comprar nuevo boleto\n3)Salir\n\n");
		scanf("%d", &opcion);
        switch(opcion)
		{
			case 1:
				system("cls");
				do
				{
					system("cls");
					printf("Introducir coches a la cola:\n\nEscoger una opcion\n");
					printf("1)Insertar coche a la cola\n2)Volver\n");
					scanf("%d", &opcion2);
		        	switch(opcion2)
					{
        				case 1:
        					system("cls");
        					printf("\nInsertar coche a la cola:\n\n");
           	 				printf("Introduce las placas del auto (enteros): ");
           		 			scanf("%d", &placa);
           		 			turno++;
           					insertar(&ptrPrim, &ptrUlt, placa, turno);
           					system("cls");
            				break;
            				
            			case 2:
            				break;
            			
            			default:
							system("cls");
							printf("Opcion no valida");
							break;
            		}
				}while(opcion2 != 2);
				system("cls");
				break;
				
        	case 2:
        		system("cls");
        		do
        		{
        			printf("Turno: %d\nPlacas: %d\n", ptrPrim -> turno, ptrPrim -> placas);
        			pasarTurno(&ptrPrim, &ptrUlt);
          	   		printf("Compra de nuevo boleto:\n\nEscoja su lugar (0's no disponibles):\n\n ");
            		for(i=0; i<fil; i++)
					{
						for(j=0; j<col; j++)
						{
							printf("\t%d", lugares[i][j]);
						}
						printf("\n\n");
					}
				
					printf("\nLugar: ");
					scanf("%d", &lug);
				
					for(i=0; i<fil; i++)
					{
						for(j=0; j<col; j++)
						{
							if(lug == lugares[i][j])
							{
								lugares [i][j] = 0;
							}
						}
					}
				
					system("cls");
					printf("Introducir cantidad de adultos\n");
					scanf("%d", &adultos);
					printf("Introducir cantidad de ni%cos\n", 164);
					scanf("%d", &ninos);
					system("cls");
					printf("Adulto $%d x(%d) = $%d\nNi%co   $%d x(%d) = $%d", pA, adultos,pA*adultos, 164, pN, ninos, pN*ninos);
					costo = adultos*pA + ninos*pN;
					total+=pago(costo);
					if(ptrPrim == NULL)
        			{
        				printf("\nCola de autos finalizada\n\nResumen diario:\n\nAutos atendidos: %d\nDinero Recaudado: %d\n", turno, total);
        			}
					else
        			{
        				printf("\nCompra terminada, SIGUIENTE\n\n");
        			}
        		}while(ptrPrim == NULL);
				
				break;
				
			case 3:
				return 0;

			default:
        		system("cls");
				printf("\nOpcion no valida");
            	break;
        }
    	
    }while (opcion != 3);
	
	return 0;
}

//Funciones de la Cola
int vacia(ptrNodoCoche *ptrPrim)
{
    if (*ptrPrim == NULL)
    {
        return 1;
    }
	else
	{
        return 0;
    }
}

void insertar(ptrNodoCoche *ptrPrim, ptrNodoCoche *ptrUlt, int placa, int turno)
{
	ptrNodoCoche ptrNuevo;
	
	ptrNuevo = malloc(sizeof(NodoCoche));
	if(ptrNuevo != NULL)
	{
		ptrNuevo -> placas = placa;
		ptrNuevo -> turno = turno;
		ptrNuevo -> ptrSiguiente = NULL;
		if(vacia(ptrPrim))
		{
			*ptrPrim = ptrNuevo;
			*ptrUlt = ptrNuevo;
		}
		else
		{
			(*ptrUlt) -> ptrSiguiente = ptrNuevo;
			*ptrUlt = ptrNuevo;
		}
	}
	else
	{
		printf("No se asigno memoria");
	}
}

void pasarTurno(ptrNodoCoche *ptrPrim, ptrNodoCoche *ptrUlt)
{
	int valorElim;
	ptrNodoCoche ptrTemp;
	
	if(!vacia(ptrPrim))
	{
		valorElim = (*ptrPrim) -> placas;
		ptrTemp = *ptrPrim;
		if(*ptrPrim == *ptrUlt)
		{
			*ptrPrim = NULL;
			*ptrUlt = NULL;
		}
		else
		{
			*ptrPrim = (*ptrPrim) -> ptrSiguiente;
		}
	}
	free(ptrTemp);
}

int pago(int costo)
{
	int bill, b1=0, b2=0, b3=0, b4=0, b5=0, suma, res;
	
	do
	{
		suma = b1*qui + b2*dos + b3*cien + b4*cin;
		if(suma >= costo)
		{
			res = suma - cambio(suma, costo);
			break;
		}
		printf("\nCosto total: $%d\n\nEscoja billetes a introducir:\n\n1)500\n2)200\n3)100\n4)50\n5)Terminado\n\nOpcion: ", costo);
		scanf("%d", &bill);
		switch(bill)
		{
			case 1:
				system("cls");
				printf("Billetes de %d introducidos: ", qui);
				scanf("%d", &b1);
				break;
			
			case 2:
				system("cls");
				printf("Billetes de %d introducidos: ", dos);
				scanf("%d", &b2);
				break;
			
			case 3:
				system("cls");
				printf("Billetes de %d introducidos: ", cien);
				scanf("%d", &b3);
				break;
				
			case 4:
				system("cls");
				printf("Billetes de %d introducidos: ", cin);
				scanf("%d", &b4);
				break;
				
			case 5:
				break;
				
			default:
				system("cls");
				printf("\nOpcion no valida");
            	break;
		}
	}while(bill != 5);
	
	return res;
}

int cambio(int suma, int costo)
{
	int x = 0, y = 0, m1=0, m2=0, m3=0, m4=0;
	
	x = suma - costo;
	while(x - M1 >= 0)
	{
		m1++;
		x-=M1;
	}
	while(x - M2 >= 0)
	{
		m2++;
		x-=M2;
	}
	while(x - M3 >= 0)
	{
		m3++;
		x-=M3;
	}
	while(x - M4 >= 0)
	{
		m4++;
		x-=M4;
	}
	system("cls");
	printf("\nCosto: $%d\nDinero introducido: $%d\n\nCambio:", costo, suma);
	printf("\nMonedas de a $%d: %d\nMonedas de a $%d: %d\nMonedas de a $%d: %d\nMonedas de a $%d: %d\nTotal de cambio: $%d\n", M1, m1, M2, m2, M3, m3, M4, m4, suma-costo);
	y = m1*M1 + m2*M2 + m3*M3 + m4*M4;
	
	return y;
}
