#include "Entidad.h"
#include <iostream>
#include <string>
#include <stdint.h>

/** intercambiar los nombres para ejecutar el main
    solo si ya pasaron todos los test :) */
int main(){
    uint64_t p = 2274464659;
    uint64_t q = 7208606003;

    Entidad a("Chochos", p, q);
    Entidad b("Chipotles", q, p);
    std::string m1("Si lo puedes imaginar, ¡lo puedes programar! -Programación ATS");
    std::string m2("без трудна не выловишь и рыбку из пруда. -Proverbio Ruso");

    std::cout << "Lona expuesta de Chochos:\n" <<
	"\tPU = (" << std::get<0>(a.pub) << ", " << std::get<1>(a.pub) << ")\n";

    std::cout << "Lona expuesta del Chipotles:\n" <<
	"\tPU = (" << std::get<0>(b.pub) << ", " << std::get<1>(b.pub) << ")\n";
    
    a.agregaLlave(b.nombre, b.pub);
    b.agregaLlave(a.nombre, a.pub);

    std::cout << "Chipotles: " <<
	b.decodificarMensaje(b.descifraMensaje(a.cifraMensaje(b.nombre, m1)))
	      << '\n';
    std::cout << "Chochos: " <<
	a.decodificarMensaje(a.descifraMensaje(b.cifraMensaje(a.nombre, m2)))
	      << '\n';
    return 0;
}
