/*
 * 1 Funciones Iterativas Recursivas
 * Alfredo Alejandro Soto Herrera
 * A01711368
 * 21/08/2024
 */

#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <iostream>

using namespace std;

class Funciones{
public:
  // Métodos de sumas
  int sumaIterativa(int n);
  int sumaRecursiva(int n);
  int sumaDirecta(int n);
};

/*
 * sumaIterativa(int n) realiza la suma de 1 hasta n con un método iterativo
 * gracias a un ciclo for.
 * Param: n, es el número hasta el cual se realizará la suma.
 * Return: la suma de 1 hasta n.
 */
int Funciones :: sumaIterativa(int n){
  int suma = 0;
  for(int i = 0; i <= n; i++){
    suma += i;
  }
  return suma;
}

/*
 * sumaRecursiva(int n) realiza la suma de 1 hasta n con un método recursivo.
 * Param: n, es el número hasta el cual se realizará la suma.
 * Return: la suma de 1 hasta n.
 */
int Funciones :: sumaRecursiva(int n){
  if(n == 0){
    return 0;
  }
  else
    return (sumaRecursiva(n-1)+n);
}

/*
 * sumaDirecta(int n) realiza la suma de 1 hasta n con un método directo, ya 
 * que se hace toda la suma en una sola operación.
 * Param: n, es el número hasta el cual se realizará la suma.
 * Return: la suma de 1 hasta n.
 */
int Funciones :: sumaDirecta(int n){
  return (n*(n+1))/2;
}


#endif