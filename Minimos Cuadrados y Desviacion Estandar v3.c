/*El siguiente código brinda una ayuda a estudiantes de fundamentos de fisica para conocer el valor la pendiente, la ordenada al origen,
 su modelo matematico lineal, el significado fisico de la pendiente o la desvisdicion estandar de de una serie de datos seleccionados por el usuario, asi como el calculo de los errores de precicion y exactitud
 para finalmente se generara un archivo de texto con los resultados correspondientes*/

#include <stdio.h>      //Libreria Standard de entrada y salida
#include <stdlib.h>     //Libreria para reservar memoria dinamica y para limpiar la pantalla
#include <math.h>       //Libreria para realizar la raiz cuadrada (sqrt) al calcular la desviacion estandar
#define N 4             //Se define un dato cuyo enfoque es especificar que este programa funciona para cuatro series de valores leidos para calcular la desviacion estandar
#define Porcentaje 100
FILE *tex;              //Puntero a el archivo de texto
float* reservar(int tam);    //Se reserva la memoria de los arreglos que se usaran
float* llenar(float* Arr, int tam);   //Llena el arreglo indicado en el programa principal

//Datos que se emplearan para el calculo de la pendiente y la ordenada al origen:
float SumXY(float* ArrX, float* ArrY, int tam);
float SumV(float* Arr, int tam);
float SumX2(float* Arr, int tam);

void Datos(float* ArrX, float* ArrY, int n);      //Funcion que calcula e imprime los datos objetivo ademas de imprimir el significado fisico de los valores calculados con respecto al deseo del usuario

void imprimir(float* Arr, int tam);   // Funcion para imprimir los datos ingresados de ambos arreglos
void liberar(float* Arr);      // Libera la memoria reservada para ambos arreglos

float* Promedio(float* A1, float* A2, float* A3, float* A4, float* Vprom, int TAM2);
void Desviacion(float* ValA, float PP);
void EE(float VP, float PP);
void PorP(float PP, float* ValA);

//Programa principal:
int main()
{
	char direccion[]="Minimos Cuadrados y Desvicion Estandar.txt"; //Declaracion del arreglo para nombrar el archivo .txt donde se imprimiran los resultados
	tex = fopen(direccion, "wt");
	if (tex == NULL){						//Condicional que nos ayuda a determinar si el archivo pudo ser creado
		printf("El archivo no se pudo crear");
		return 1;
	}
	
	int TAM, TAM2, opcion, op;
	float *X, *Y, *Vpat, *A1, *A2, *A3, *A4, *Vprom, *ValA, PP, VP;
	
	printf("\nPrograma para calcular la desviacion estandar de valores introducidos por el usuario o\n");
	printf("   realizar regresion lineal y encontar el significado fisico segun sus magnitudes:\n\n");
	
	printf("1.Regresion lineal y significado fisico de magnitudes\n");
	printf("2.Desviacion estandar respecto a cuatro series de valores leidos\n");
	printf("\nIngrese la opcion deseada\n\n");
	printf("Opcion: ");
	scanf("%d", &opcion);
	
	switch(opcion){       //Se emplea una funcion switch para escoger que proceso se quiere realizar
		case 1:	     //Regresion lineal
			fprintf(tex, "Resultados del procedimiento\n");
			system("cls");
			printf("Regresion lineal:\n\n");
			printf("Introducir la cantidad de lecturas a Ingresar: ");
			scanf("%d", &TAM);
			X=reservar(TAM); //Reserva memoria para el arreglo de las X
			Y=reservar(TAM); //Reserva memoria para el arreglo de las Y
			system("cls"); //Estas funciones limpian la pantalla, meramente estetca del programa
			printf("\nIntroducir los valores de X\n\n");
			X = llenar(X, TAM); //Llena el arreglo de las X
			system("cls");
			printf("\nIntroducir los valores de Y\n\n");
			Y = llenar(Y, TAM);    //Llena el arreglo de las Y
			system("cls");
	
			Datos(X, Y, TAM);  // Calcula e imprime los datos que se buscan
	
			liberar(X); //Estas funciones liberan la memoria reservada previamente
			liberar(Y);				
		    break;
	  
	    case 2:     //Desviacion estandar
	    	fprintf(tex, "Resultados del procedimiento\n");
			system("cls");
			printf("Desviacion estandar y calculo de errores:\n\n");
	    	printf("Ingrese la cantidad de valores a introducir\n");
			scanf("%d", &TAM2);        //se pregunta al usuario el tamaño de las matrices a introducir
			
			Vpat = reservar (TAM2);    //El proceso como se especifica en el menu requiere cuatro arreglos
			A1 = reservar(TAM2);       // que representaran las series de valores leidos y registrados por el usuario 
			A2 = reservar(TAM2);       //  mas un arreglo que registre los promedios de dichas lecturas y otro 
			A3 = reservar(TAM2);       //  para registrar los valores patron aunque dicho arreglo de valores no sea
			A4 = reservar(TAM2);       //   utilizado.
			Vprom = reservar(TAM2);    //     -> Para estos 6 arreglos se hace reserva de memoria <-
			
			system("cls");
			printf("\nIntroducir los valores patron\n\n");
			Vpat = llenar(Vpat, TAM2);                                      //Llena la matriz con los valores patron
			
			system("cls");
			printf("\nIntroducir los valores de la primer lectura\n\n");
			A1 = llenar(A1, TAM2);                                      //Llena la matriz con la primer lectura de valores
			
			system("cls");
			printf("\nIntroducir los valores de la segunda lectura\n\n");
			A2 = llenar(A2, TAM2);                                      //Llena la matriz con la segunda lectura de valores
			
			system("cls");
			printf("\nIntroducir los valores de la tercera lectura\n\n");
			A3 = llenar(A3, TAM2);                                      //Llena la matriz con la tercera lectura de valores
			
			system("cls");
			printf("\nIntroducir los valores de la cuarta lectura\n\n");
			A4 = llenar(A4, TAM2);                                      //Llena la matriz con la cuarta lectura de valores
			
			Vprom = Promedio(A1, A2, A3, A4, Vprom, TAM2); //Esta funcion calcula el promedio de cada lectura y los almacena en un arreglo enfocado a dichos promedios
			
			system("cls");
			printf("Valores promedio:\n\n");
			imprimir(Vprom, TAM2); //Imprime Los valores promedio para que el usuario escoja que datos de lectura usara para calcular la desviacion estandar en dicho promedio
			op=0;
			PP=0;
			VP=0;
			printf("Escoja el valor deseado para calcular su desviacion estandar respecto al mismo\n");
			scanf("%d", &op);   //Se escoje el lugar donde se encuentra el promedio a escoger
			ValA = reservar(N); //Se reserva la memoria de un arreglo mas, usado para almacenar los valores leidos con respecto al promedio seleccionado
			
			PP = *(Vprom+(op-1)); //Usando la posicion que selecciono el usuario se recoje este valor y se alpacena en la variable PP
			VP = *(Vpat+(op-1));
			
			*(ValA+0) = *(A1+(op-1));  //Estas cuatro funciones se encargan de llenar el 
			*(ValA+1)= *(A2+(op-1));   //recion generado arreglo que almacena los valores
			*(ValA+2)= *(A3+(op-1));   //leidos respecto al promedio seleccionado
			*(ValA+3)= *(A4+(op-1));   //
			
			system("cls");
			/* Apartir de aqui comienza la salida del programa para el proceso escogido*/
			printf("Valores promedio:\n\n");
			fprintf(tex, "Valores promedio:\n\n");
			imprimir(Vprom, TAM2); //Imprime el arreglo de promedios
			printf("\nValor promedio seleccionado: %.2f\n\n\nValores leidos correspondientes a dicho Promedio:\n\n", PP);
			fprintf(tex,"\nValor promedio seleccionado: %.2f\n\n\nValores leidos correspondientes a dicho Promedio:\n\n", PP);
			imprimir(ValA, N); // imprime los valores leidos respecto al promedio seleccionado
			
			Desviacion(ValA, PP); //Funcion que calcula la desviacion estandar en el promedio que el usario selecciono
			EE(VP, PP);
			PorP(PP, ValA);
			
			liberar(Vpat);   //
			liberar(A1);     //
			liberar(A2);     //Se libera la memoria de todos los arreglos
			liberar(A3);     //con apuntador que se usaron en este 
			liberar(A2);     //proceso.
			liberar(Vprom);  //
			liberar(ValA);   //
			
	    	break;
	    	
	    default: printf("No ha ingresado un a opcion valida\n");	
	}
	
	return 0;
}

//Reserva de memoria
float* reservar(int tam)
{
	float* Arr=(float*)malloc(tam*sizeof(float));
	return Arr;
}

//Llenado de matrices
float* llenar(float* Arr, int tam)
{
	int i;
	
	for(i=0;i<tam;i++)
	{
		printf("%d.- ", i+1);
		scanf("%f", Arr+i);
	}
	
	return Arr;
}

//Calcula una parte de la formula de los minimos cuadrados (1/3)
float SumXY(float* ArrX, float* ArrY, int tam)
{
	int i;
	float S=0;
	
	for(i=0;i<tam;i++)
	{
		S += *(ArrX+i) * *(ArrY+i);
	}
	
	return S;
}

//(2/3)
float SumV(float* Arr, int tam)
{
	int i;
	float S=0;
	
	for(i=0;i<tam;i++)
	{
		S+= *(Arr+i);
	}
	
	return S;
}

//(3/3)
float SumX2(float* Arr, int tam)
{
	int i;
	float S=0;
	
	for(i=0;i<tam;i++)
	{
		S+= *(Arr+i) * *(Arr+i);
	}
	
	return S;
}

//Calcula los datos deseados e imprime informacion reelevante a deseo del usuario
void Datos(float* ArrX, float* ArrY, int n)
{
	float m, b, sumx, sumy, sumxy, sumx2;
	int op,op2,op3;
	
	
	sumx = SumV(ArrX, n);           //Estas funciones
	sumy = SumV(ArrY, n);           //calculan partes de
	sumxy = SumXY(ArrX, ArrY, n);   //la formula de los
	sumx2 = SumX2(ArrX, n);         //minimos cuadrados
	printf("Datos de X:\n\n");
	imprimir(ArrX, n); //Imprime a las X
	printf("Datos de Y:\n\n");
	imprimir(ArrY, n); //Imprime a las Y
	m=((n*sumxy) - (sumx*sumy)) / ((n*sumx2)-(sumx*sumx));  // Calcula la pendientee
	b=((sumy*sumx2) - (sumx*sumxy)) / ((n*sumx2)-(sumx*sumx)); // Calcula la ordenada al origen
	printf("La Pendiente es: %.2f\nLa Ordenada al origen es: %.2f\n", m, b); // imprime ambas m y b
	fprintf(tex, "La pendiente es: %.2f\nLa ordenada del origen es: %.2f\n", m, b); //Cualquier elemento escrito en la funcion fprintf se escribira en nuestro archivo .txt
	
	/*Los siguientes condicionales le permiten al usuario elegir magnitudes predeterminadas de un modelo matematico asi como saber ete mismo junto con su significado
	 fisico, como opcion extra el usuario puede determinar si desea modelos con pendientes adimensionales o con un significado fisico */ 
	
	printf("\nElija una opcion de las cuales se generaran modelos matematicos a partir de sus resultados");
	printf("\n");
	printf("1. Unidades que daran resultados adimencionales\n");
	printf("2. Unidades que daran un significado fisico especifico a la pendiente \n\n");
	printf("Opcion: ");
	scanf("%i", &op);
	system("cls");	
	switch(op){
		case 1: 
				printf("Seleccione una opcion:\n");
				printf("\n");
				printf("1.Peso (N) en X con Peso (N) en Y\n");
				printf("2.Volumen (V) en X con Volumen (V) en Y\n");
				printf("3.Masa (m) en X con Masa (m) en Y\n");
				printf("4.Presion (P) en X con Preion (P) en Y\n");
				printf("5.Altura (h) en X con Altura (h) en Y\n");
				printf("6.Diferencia de temperaturas (dt) en X con diferencia de temperaturas (dt) en Y\n");
				printf("7.Calor suministrado (Q) en X con calor suministrado (Q) en Y");
				printf("8.Temperatura (T) en X con Temperatura (T) en Y\n");
				printf("9.Longitud de onda (L) en X con Longitud de onda (L) en Y\n");
				printf("10.Periodo de la onda (t) en X con periodo de la onda (t) en Y\n\n");
				printf("Opcion: ");
				scanf("%i", &op2);
				system("cls");	
					switch(op2){
						case 1:	
								printf("El modelo matematico es:\n N[N]= %.2f[N/N]*N[N] + %.2f[N]\n", m, b);
								printf("El significado fisico de la pendiente es: Adimiensional\n");
								printf("El significado fisico de la ordenada al origen es: El error de calibracion\n");
								fprintf(tex, "El modelo matematico es:\n N[N]= %.2f[N/N]*N[N] + %.2f[N]\n", m, b);
								fprintf(tex, "El significado fisico de la pendiente es: Adimiensional\n");
								fprintf(tex, "El significado fisico de la ordenada al origen es: El error de calibracion\n");
								break;
						
						case 2:	
								printf("El modelo matematico es:\nV[V]= %.2f[m^3/m^3]*V[m^3] + %.2f[m^3]\n", m, b);
								printf("El significado fisico de la pendiente es: Adimensional\n");
								printf("El significado fisico de la ordenada al origen es: El error de calibracion\n");
								fprintf(tex, "El modelo matematico es:\nV[V]= %.2f[m^3/m^3]*V[m^3] + %.2f[m^3]\n", m, b);
								fprintf(tex, "El significado fisico de la pendiente es: Adimensional\n");
								fprintf(tex, "El significado fisico de la ordenada al origen es: El error de calibracion\n");
								break;
						
						case 3:
								printf("El modelo matematico es:\nm[kg]= %.2f[kg/kg]*m[kg] + %.2f[kg]\n", m, b);
								printf("El significado fisico de la pendiente es: Adimensional\n");
								printf("El significado fisico de la ordenada al origen es: El error de calibracion\n");
								fprintf(tex, "El modelo matematico es:\n m[kg]= %.2f[kg/kg]*m[kg] + %.2f[kg]\n", m, b);
								fprintf(tex, "El significado fisico de la pendiente es: Adimensional\n");
								fprintf(tex, "El significado fisico de la ordenada al origen es: El error de calibracion\n");
								break;
						
						case 4: 
								printf("El modelo matematico es:\nP[Pa]= %f.2[Pa/Pa]*Pa[Pa] + %f.2[Pa]\n", m, b);
								printf("El significado fisico de la pendiente es: Adimensional\n");
								printf("El significado fisico de la ordenada al origen es: El error de calibracion\n");
								fprintf(tex, "El modelo matematico es:\n P[Pa]= %f.2[Pa/Pa]*Pa[Pa] + %f.2[Pa]\n", m, b);
								fprintf(tex, "El significado fisico de la pendiente es: Adimensional\n");
								fprintf(tex, "El significado fisico de la ordenada al origen es: El error de calibracion\n");
								break;
						
						case 5:
								printf("El modelo matematico es:\nh[m]= %.2f[m/m]*h[m] + %f.2[m]\n", m, b);
								printf("El significado fisico de la pendiente es: Adimensional\n");
								printf("El significado fisico de la ordenada al origen es: El error de calibracion\n");
								fprintf(tex, "El modelo matematico es:\n h[m]= %.2f[m/m]*h[m] + %.2f[m]\n", m, b);
								fprintf(tex, "El significado fisico de la pendiente es: Adimensional\n");
								fprintf(tex, "El significado fisico de la ordenada al origen es: El error de calibracion\n");
								break;
						
						case 6: 
								printf("El modelo matematico es:\ndt[d°C]= %.2f[d°C/D°C]*dT[d°C] + %.2f[d°C]\n", m, b);
								printf("El significado fisico de la pendiente es: Adimesional\n");
								printf("El significado fisico de la ordenada al origen es: El error de calibracion\n");
								fprintf(tex, "El modelo matematico es:\n dt[d°C]= %.2f[d°C/d°C]*dT[d°C] + %.2f[d°C]\n", m, b);
								fprintf(tex, "El significado fisico de la pendiente es: Adimesional\n");
								fprintf(tex, "El significado fisico de la ordenada al origen es: El error de calibracion\n");
								break;
						
						case 7: 
								printf("El modelo matematico es:\nQ[J]= %.2f[J/J]*Q[J] + %.2f[J]\n", m, b);
								printf("El significado fisico de la pendiente es: Densidad\n");
								printf("El significado fisico de la ordenada al origen es: El error de calibracion\n");
								fprintf(tex, "El modelo matematico es:\n Q[J]= %.2f[J/J]*Q[J] + %.2f[J]\n", m, b);
								fprintf(tex, "El significado fisico de la pendiente es: Densidad\n");
								fprintf(tex, "El significado fisico de la ordenada al origen es: El error de calibracion\n");							
								break;
						
						case 8:	
								printf("El modelo matematico es:\nT[°C]= %.2f[°C/°C]*T[°C] + %.2f[°C]\n", m, b);
								printf("El significado fisico de la pendiente es: Adimensional\n");
								printf("El significado fisico de la ordenada al origen es: El error de calibracion\n");
								fprintf(tex, "El modelo matematico es:\n T[°C]= %.2f[°C/°C]*T[°C] + %.2f[°C]\n", m, b);
								fprintf(tex, "El significado fisico de la pendiente es: Adimensional\n");
								fprintf(tex, "El significado fisico de la ordenada al origen es: El error de calibracion\n");
								break;
						
						case 9: 
								printf("El modelo matematico es:\nL[m]= %.2f[m/m]*L[m] + %.2f[m]\n", m, b);
								printf("El significado fisico de la pendiente es: Densidad\n");
								printf("El significado fisico de la ordenada al origen es: El error de calibracion\n");
								fprintf(tex, "El modelo matematico es:\nL[m]= %.2f[m/m]*L[m] + %.2f[m]\n", m, b);
								fprintf(tex, "El significado fisico de la pendiente es: Densidad\n");
								fprintf(tex, "El significado fisico de la ordenada al origen es: El error de calibracion\n");
								break;
						
						case 10:
								printf("El modelo matematico es:\nt[s]= %.2f[s/s]*t[s] + %.2f[s]\n", m, b);
								printf("El significado fisico de la pendiente es: Adimensional\n");	
								printf("El significado fisico de la ordenada al origen es: El error de calibracion\n");					
								fprintf(tex, "El modelo matematico es:\nt[s]= %.2f[s/s]*t[s] + %.2f[s]\n", m, b);
								fprintf(tex, "El significado fisico de la pendiente es: Adimensional\n");	
								fprintf(tex, "El significado fisico de la ordenada al origen es: El error de calibracion\n");		
								break;
						
						default: printf("No ha ingresado una opcion valida\n"); 		
					
					}
					
		break;
		case 2: 
				printf("Seleccione una opcion:\n");
				printf("\n");
				printf("1.Volumen (V) en X con masa (m) en Y\n");
				printf("2.Masa (m) en X con Volumen (V) en Y\n");
				printf("3.Altura (h) en X con Presion (P) en Y\n");
				printf("4.Presion (P) en X con Altura (h) en Y\n");
				printf("5.Calor suministrado en (Q) en X con Temperatura (T) en Y\n");
				printf("6.Diferencia de temperaturas (dT) en X con Calor suministrad (Q) en Y\n");
				printf("7.Periodo de la onda (t) en X con Longitud de onda (L) en Y\n");
				printf("8.Intenciadad de corriente (I) en X con Diferencia de potencial (V) en Y\n");
				printf("9.Diferencia de potencial (V) en X con Intencidad de corriente (I) en Y\n");
				printf("10.Intencidad de corriente (I) en X con Fuerza Mafnetica (F) en Y\n");
				printf("11.Fuerza magnetica (F) en X con Intencidad de corriente (I) en Y\n\n");
				printf("Opcion: ");
				scanf("%i", &op3);
				system("cls");	 	
					switch(op3){
						case 1:
								printf("El modelo matematico es:\nm[kg]= %.2f[kg/m^3]*V[m^3] + %.2f[kg]\n", m, b);
								printf("El significado fisico de la pendiente es: Densidad\n");
								fprintf(tex, "El modelo matematico es:\nm[kg]= %f[kg/m^3]*V[m^3] + %f[kg]\n", m, b);
								fprintf(tex, "El significado fisico de la pendiente es: Densidad\n");
								break;
								
						case 2:	
								printf("El modelo matematico es:\nV[m^3]= %.2f[m^3/kg]*m[Kg] + %.2f[m^3]\n", m, b);
								printf("El significado fisico de la pendiente es: Volumen especifico\n");	
								fprintf(tex, "El modelo matematico es:\n V[m^3]= %.2f[m^3/kg]*m[Kg] + %.2f[m^3]\n", m, b);
								fprintf(tex, "El significado fisico de la pendiente es: Volumen especifico\n");	
								break;
								
						case 3:
								printf("El modelo matematico es:\nP[Pa]= %.2f[Pa/m]*h[m] + %.2f[Pa]\n", m, b);
								printf("El significado fisico de la pendiente es: Peso especifico \n");	
								fprintf(tex, "El modelo matematico es:\n P[Pa]= %.2f[Pa/m]*h[m] + %.2f[Pa]\n", m, b);
								fprintf(tex, "El significado fisico de la pendiente es: Peso especifico \n");	
								break;
								
						case 4:	
								printf("El modelo matematico es:\nh[m]= %.2f[m/Pa]*P[Pa] + %.2f[m]\n", m, b);
								printf("El significado fisico de la pendiente es: Peso especifico inverso\n");
								fprintf(tex, "El modelo matematico es:\nh[m]= %.2f[m/Pa]*P[Pa] + %.2f[m]\n", m, b);
								fprintf(tex, "El significado fisico de la pendiente es: Peso especifico inverso\n");
								break;
									
						case 5:
								printf("El modelo matematico es:\nT[°C]= %.2f[°C/J]*Q[J] + %.2f[°C]\n", m, b);
								printf("El significado fisico de la pendiente es: La inversa del calor específico\n");						
								fprintf(tex, "El modelo matematico es:\n T[°C]= %.2f[°C/J]*Q[J] + %.2f[°C]\n", m, b);
								fprintf(tex, "El significado fisico de la pendiente es: La inversa del calor específico\n");	
								break;
							
						case 6:	
								printf("El modelo matematico es:\nQ[J]= %.2f[J/d°C]*dT[d°C] + %.2f[J]\n", m, b);
								printf("El significado fisico de la pendiente es: Calor específico\n");
								fprintf(tex, "El modelo matematico es:\n Q[J]= %.2f[J/d°C]*dT[d°C] + %.2f[J]\n", m, b);
								fprintf(tex, "El significado fisico de la pendiente es: Calor específico\n");
								break;
								
						case 7:	
								printf("El modelo matematico es:\nL[m]= %.2f[m/s]*t[s] + %.2f[m]\n", m, b);
								printf("El significado fisico de la pendiente es: La rapidez de propagacion de la onda\n");			
								fprintf(tex, "El modelo matematico es:\n L[m]= %.2f[m/s]*t[s] + %.2f[m]\n", m, b);
								fprintf(tex, "El significado fisico de la pendiente es: La rapidez de propagacion de la onda\n");		
								break;
								
						case 8:
								printf("El modelo matematico es:\nV[V]= %.2f[V/A]*I[A] + %.2f[V]\n", m, b);
								printf("El significado fisico de la pendiente es: La resistencia electrica\n");			
								fprintf(tex, "El modelo matematico es:\n V[V]= %.2f[V/A]*I[A] + %.2f[V]\n", m, b);
								fprintf(tex, "El significado fisico de la pendiente es: La resistencia electrica\n");
								break;
						
						case 9:
								printf("El modelo matematico es:\nI[A]= %.2f[A/V]*V[V] + %.2f[I]\n", m, b);
								printf("El significado fisico de la pendiente es: La inversa de la resistencia electrica\n");			
								fprintf(tex, "El modelo matematico es:\n I[A]= %.2f[A/V]*V[V] + %.2f[A]\n", m, b);
								fprintf(tex, "El significado fisico de la pendiente es: La inversa de la resistencia electrica\n");
								break;		
						
						case 10:	
								printf("El modelo matematico es:\nF[N]= %.2f[N/A]*I[A] + %.2f[N]\n", m, b);
								printf("El significado fisico de la pendiente es: Fuerza de origen magnetico\n");			
								fprintf(tex, "El modelo matematico es:\n F[N]= %.2f[N/A]*I[A] + %.2f[N]\n", m, b);
								fprintf(tex, "El significado fisico de la pendiente es: Fuerza de origen magnetico \n");
								break;
						
						case 11:
								printf("El modelo matematico es:\nI[A]= %.2f[A/N]*F[N] + %.2f[A]\n", m, b);
								printf("El significado fisico de la pendiente es: La inversa de la fuerza de origen magnetico\n");			
								fprintf(tex, "El modelo matematico es:\n I[A]= %.2f[A/N]*F[N] + %.2f[A]\n", m, b);
								fprintf(tex, "El significado fisico de la pendiente es: La inversa de la fuerza de origen magnetico\n");
								break;			 			
						
						default: printf("No ha ingresado una opcion valida\n");			
			break;
						
					}
		
		
	}
	
}

//Imprime los arreglos correspondientes
void imprimir(float* Arr, int tam)
{
	int i;
	
	for(i=0; i<tam; i++)
	{
		printf("%d.-  %.2f\n", i+1, *(Arr+i));
		fprintf(tex, "%d.-  %.2f\n", i+1, *(Arr+i));
	}
	printf("\n\n");
}

//Libera la memoria empleada
void liberar(float* Arr)
{
	free(Arr);
}

//Calcula el promedio de las cuatro series de lecturas introducidas por el usuario y las guarda en un arreglo
float* Promedio(float* A1, float* A2, float* A3, float* A4, float* Vprom, int TAM2)
{
	int i;
	float prov;
	
	prov = 0;
	
	for(i=0; i<TAM2; i++)
	{
		prov = *(A1+i) + *(A2+i) + *(A3+i) + *(A4+i);
		*(Vprom+i) = prov / 4;
		prov = 0;
	}
	
	return Vprom;
}

//Calcula e imprime la Desviacion estandar en el promedio seleccionado por el usuario
void Desviacion(float* ValA, float PP)
{
	int i;
	float sum, Desv;
	
	sum = 0;
	Desv = 0;
	
	for(i=0; i<N; i++)  //Este ciclo for calcula una parte de la formula de la desviacion estandar que es almacenada en la variable sum
	{
		sum+=(PP - (*(ValA+i)))*(PP - (*(ValA+i)));
	}
	Desv = sqrt(sum/(N-1)); //Con lo obtenido en la variable sum , se usa junto con el resto de la formula para el resultado final de la Desviacion
	
	printf("La desviacion estandar respecto al valor promedio de %.2f es de %.2f\n", PP, Desv);
	fprintf(tex, "La desviacion estandar respecto al valor promedio de %.2f es de %.2f\n", PP, Desv);
}

void EE(float VP, float PP)
{
	float temp, ErE, E;
	
	temp = fabs(VP-PP);
	ErE = (temp/PP)*Porcentaje;
	E = fabs(Porcentaje-ErE);
	printf("\n\nEl error de exactitud es de: %.2f%c", ErE, 37);
	printf("\n\nEl Porcentaje de exactitud es de: %.2f%c", E, 37);
	fprintf(tex,"\n\nEl error de exactitud es de: %.2f%c", ErE, 37);
	fprintf(tex,"\n\nEl Porcentaje de exactitud es de: %.2f%c", E, 37);
}

void PorP(float PP, float* ValA){
	int i, val;
	float temp[N], prov, VMA, tempr, Epr, Porpre;
	
	for(i=0; i<N; i++){
		if(*(ValA+i)==PP){
			val=1;
		}else{
			val=0;
		}
	}
	
	if(val == 1){
		printf("\n\nEl error de precision es de: 0.00%c", 37);
		printf("\n\nEl porcentaje de precicion es del 100%c", 37);
		fprintf(tex,"\n\nEl error de precision es de: 0.00%c", 37);
		fprintf(tex,"\n\nEl porcentaje de precicion es del 100%c", 37);
		
	}else{
		prov=0;
		for(i=0; i<N; i++){
			
			if(*(ValA+i)<PP||*(ValA+i)>PP){
				temp[i]=fabs(PP-*(ValA+i));
			}else{
				temp[i]=0;
			}
		}
		for(i=0; i<N; i++){
			if(temp[i]>prov){
				prov = temp[i];
				VMA= *(ValA+i);
			}
		}
		tempr = fabs(PP-VMA);
		Epr = (tempr/PP)*Porcentaje;
		Porpre= fabs(Porcentaje-Epr);
		printf("\n\nEl error de precision es de: %.2f%c", Epr, 37);
		printf("\n\nEl Porcentaje de precision es de: %.2f%c", Porpre, 37);
		fprintf(tex, "\n\nEl error de precision es de: %.2f%c", Epr, 37);
		fprintf(tex, "\n\nEl Porcentaje de precision es de: %.2f%c", Porpre, 37);
	}
	
	
}

