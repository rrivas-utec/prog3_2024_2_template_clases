#include <iostream>
#include <vector>
#include <list>

template <typename T, size_t sz>
auto generar_vector() {
    return std::vector<T>(sz);
}

void ejemplo_1() {
    auto v1 = generar_vector<int, 10>();
    std::cout << v1.size() << std::endl;
}

template <typename T, size_t sz, template<typename ...> class ContainerTemplate>
auto generar_contenedor() {
    return ContainerTemplate<T>(sz);
}

void ejemplo_2() {
    auto lst1 = generar_contenedor<double, 20, std::vector>();
    std::cout << lst1.size() << std::endl;
}

template<template<typename ...> typename ContainerType, typename T>
void actualizar_arreglo(ContainerType<T>& target, const int* source, int sz, int offset) {
    for (int i = 0; i < sz; ++i)
        target[offset+i] = source[i];
}

template <template<typename ...> typename ContainerType, typename T>
void concatenar_rest_arreglos(ContainerType<T>& result, size_t offset) {}

template <template<typename ...> typename ContainerType, typename T, size_t first_sz, size_t ...sz>
auto concatenar_rest_arreglos(ContainerType<T>& result, size_t offset, T (&first_arr)[first_sz], T (&... a)[sz]) {
    actualizar_arreglo<ContainerType>(result, first_arr, first_sz, offset);
    concatenar_rest_arreglos<ContainerType>(result, first_sz + offset, a...);
}

template <template <typename ...> class ContainerType, typename T, size_t first_sz, size_t ...sz>
auto concatenar_arreglos(T (&first_arr)[first_sz], T (&... a)[sz]) {
    auto n = (...+sz)+first_sz;  // Folding expression
    ContainerType<T> result(n);        // Creando un arreglo estatico
    actualizar_arreglo<ContainerType>(result, first_arr, first_sz, 0); // Actualizando el arreglo estatico
    concatenar_rest_arreglos<ContainerType>(result, first_sz, a...);
    for (int i = 0; i < n; ++i)
        std::cout << result[i] << " ";
    return result;
}

template <typename T>
void show_type(T) {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}

template <typename Container, size_t sz>
auto generar_contenedor_2() {
    return Container(sz);
}


void ejemplo_4() {
    auto c = generar_contenedor_2<std::vector<int>, 20>();
}

template <typename Container>
auto show_item_type(Container c) {
    typename Container::value_type var;
    show_type(var);
}

void ejemplo_5() {
    std::vector<double> v;
    show_item_type(v);
}

void ejemplo_3() {
    int arr1[] = {10, 20, 30, 40};
    int arr2[] = {50, 60};
    int arr3[] = {70, 80, 90};
    auto c1 = concatenar_arreglos<std::vector>(arr1, arr2, arr3);
    std::cout << std::endl;
    show_type(c1);
   // concatenar_arreglos(arr1, arr2, arr3);
}


int main() {
//    ejemplo_1();
//    ejemplo_3();
    ejemplo_5();
    return 0;
}
