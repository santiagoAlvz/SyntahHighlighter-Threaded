// ejemplo 2.- multiplica dos números enteros y muestra el resultado
#include <stdio.h>
int main() {
	int multiplicador; // se define multiplicador como un entero 
	int multiplicando; // se define multiplicando como un entero 
	int res; // se define resultado como un entero*/
	float otraVariable = 2.3;
	multiplicador = 1000; // se asignan valores*/
	multiplicando = 2;
	res = multiplicador*multiplicando;
	printf("Resultado =%d",res); // se muestra el resultado
	if(res >= 10){
		cout<<"El resultado es mayor o igual a 10"<<endl;
	} else {
		cout<<"Contaré cada número que falte para llegar a 10"<<endl;
		do {
			res++;
			cout<<res<<endl;
		} while(res < 10);
	}
	return 0;
}
