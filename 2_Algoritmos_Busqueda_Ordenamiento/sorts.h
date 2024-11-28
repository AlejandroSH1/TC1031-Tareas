/*
 * 2 Algoritmos de Búsqueda y ordenamiento
 * Alfredo Alejandro Soto Herrera
 * A01711368
 * 04/09/24
 */

#ifndef SORTS_H
#define SORTS_H

#include <iostream>
#include <vector>

using namespace std;

// Declaro la clase Sorts en donde se encuentran los sorts y searchs
template <class T>
class Sorts{
private:
//En private coloco los métodos que no se utilizarán en el main
  void swap(vector<T> &, int, int);
  void copyArray(vector<T> &, vector<T> &, int, int);
  void mergeArray(vector<T> &, vector<T> &, int, int, int);
  void mergeSplit(vector<T> &, vector<T> &, int, int);
public:
//Declaro los sorts y utilizo void ya que no se utilizará una copia del vector
  void ordenaSeleccion(vector<T> &);
  void ordenaBurbuja(vector <T> &);
  void ordenaMerge(vector <T> &);

// Declaro las busquedas
  int busqSecuencial(const vector<T> &, int);
  int busqBinaria(const vector<T> &, int);
};

/*
 * swap() cambia de posición 2 valores en un vector.
 * @param vector<T> &v, vector que se va a utilizar para cambiar de posición,
 * int, posición del primer valor a cambiar y j, posición del segundo valor.
 * @return void.
 */
template <class T>
void Sorts<T>::swap(vector<T> &v, int i, int j){
  T aux = v[i];
  v[i] = v[j];
  v[j] = aux;
}

/*
 * ordenaSeleccion() recibe un vector y lo ordena mediante el método de 
 * selección.
 * @param vector<T> &prueba, vector que se va a ordenar.
 * @return void.
 */
template <class T>
void Sorts<T>::ordenaSeleccion(vector<T> &prueba){
  for (int i = 0; i <= prueba.size() - 1; i++){
    int mini = i;
    for (int j = i; j <= prueba.size()-1; j++){
      if (prueba[j] < prueba[mini]){
        mini = j;
      }
    }
      if (mini != i){
        swap(prueba, i, mini);
      }
  }
}

/*
 * ordenaBurbuja() recibe un vector y lo ordena mediante el método de burbuja.
 * @param vector <T> &prueba, vector que se va a ordenar.
 * @return void.
 */
template <class T>
void Sorts<T>::ordenaBurbuja(vector<T> &prueba){
  for (int i = prueba.size() - 1; i > 0; i--) {
    for (int j = 0; j < i; j++) {
      if (prueba[j] > prueba[j + 1]) {
        swap(prueba, j, j + 1);
      }
    }
  }
}

/*
 * copyArray() copia los valores del vector original a uno nuevo.
 * @param vector<T> &A es el vector original, vector<T> &B el vector nuevo, 
 * int low la posición inicial e int high la posición final.
 * @return void.
 */
template<class T>
void Sorts<T>::copyArray(vector<T> &A, vector<T> &B, int low, int high){
  for (int i = low; i <= high; i++){
    A[i] = B[i];
  }
}

/*
 * mergeArray() comprueba los valores del vector A y si estan ordenados, se 
 * ingresan al vector B.
 * @param vector<T> &A es el vector original, vector<T> &B es la copia que
 * guardará los valores, int low la posición inicial, int mid la posición de
 * en medio e int high la posición final.
 * @return void.
 */
template<class T>
void Sorts<T>::mergeArray(vector<T> &A, vector<T> &B, int low, int mid, int high){
  int i = low;
  int j = mid + 1;
  int k = low;
  while (i <= mid && j <= high){
    if (A[i] < A[j]){
      B[k] = A[i];
      i++;
    } 
    else{
      B[k] = A[j];
      j++;
    }
    k++;
  }
  if (i > mid){
    for (; j <= high; j++){
      B[k++] = A[j];
    }
  }
  else{
    for (; i <= mid; i++){
      B[k++] = A[i];
    }
  }
}

/*
 * mergeSplit() divide el vector en 2 y llama a mergeArray() para ordenarlos.
 * @param vector<T> &A es el vector original, vector<T> &B es la copia, int
 * low la posición inicial e int high la posición final.
 * @return void.
 */
template<class T>
void Sorts<T> :: mergeSplit(vector<T> &A, vector<T> &B, int low, int high){
  if (high - low < 1){
    return;
  }
  int mid = (low + high) / 2;
  mergeSplit(A, B, low, mid);
  mergeSplit(A, B, mid + 1, high);
  mergeArray(A, B, low, mid, high);
  copyArray(A, B, low, high);
}

/*
 * ordenaMerge() recibe un vector y lo ordena mediante el método de merge,
 * apoyandose en mergeSplit().
 * @param vector <T> &prueba, vector que se va a ordenar.
 * @return void.
 */
template <class T>
void Sorts<T>::ordenaMerge(vector<T> &prueba){
  vector<T> tmp(prueba.size());

  mergeSplit(prueba,tmp,0,prueba.size()-1);
}

/*
 * busqSecuencial() recibe un vector y un valor a buscar y regresa la posición
 * del valor buscado, por medio de una busqueda que avanza de uno en uno.
 * @param const vector<T> &prueba es el vector en el que se va a buscar, int 
 * val es el valor a buscar.
 * @return int, posición del valor buscado.
 */
template<class T>
int Sorts<T>::busqSecuencial(const vector<T> &v, int val){
  int ind = 0;
  while (ind < v.size() && v[ind] < val){
    ind++;
  }
  if (ind >= v.size() || v[ind] != val){
    return -1;
  }
  return ind;
}

/*
 * busqBinaria() recibe un vector y un valor a buscar y regresa la posición, 
 * por medio del método de busqueda binaria.
 * @param const vector<T> &prueba es el vector en el que se va a buscar, int
 * val es el valor a buscar.
 * @return int, posición del valor buscado.
 */
template<class T>
int Sorts<T>::busqBinaria(const vector<T> &v, int val){
  int mid;
  int low = 0;
  int high = v.size() - 1;
  while (low <= high){
    mid = (low + high) / 2;
    if (v[mid] == val){
      return mid;
    }
    else if (v[mid] < val){
      low = mid + 1;
    }
    else{
      high = mid - 1;
    }
  }
  return -1;
}

#endif