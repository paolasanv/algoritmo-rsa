#include <iostream>
#include <cmath>
#include <random>
#include <stdint.h>

/** Eleva a a la b recortando con mod */
uint64_t potenciaMod(uint64_t a, uint64_t b, uint64_t mod){
    uint64_t res = 1;
    while(b >= 1){
	    if(n%2 != 0){
		    res = (res * a) % mod;
		    b--;
	    } else {
		    a = (a * a) % mod;
		    b /= 2;
	    }
    }
    return res;
}

/**Encuentra la combinación lineal de a y b que resulta en 1. */
int64_t mcde(uint64_t a, uint64_t b, int64_t &x, int64_t &y){
	if(a == 0){
		x = 0;
		y = 1;
		return b;
	}

	uint64_t x1, y1;
	uint64_t mcd = mcde(b%a, a, x1, y1);

	x = y1 - (b/a) * x1;
	y = x1;
	return mcd;
}

/** Encuentra el inverso multiplicativo módulo M. Es mejor obtenerlo
    con el algoritmo de euclides extendido */
uint64_t invMult(uint64_t a, uint64_t mod){

}

/** Encuentra el máximo común divisor entre a y b. */
int64_t mcd(uint64_t a, uint64_t b){
	if(a == 0){
		return b;
	}
	return mcd(b%a, a);
}

/** Nos dice si un número es primo o no */
bool esPrimo(uint64_t n){

}

/** Nos dice si 2 números son coprimos o primos relativos */
bool coprimos(uint64_t a, uint64_t b){

}

/** Nos regresa la función phi de euler de un número n */
uint64_t phiEuler(uint64_t n){

}

/** Función auxiliar para generar números aleatorios pequeños */
uint rand(uint start, uint end){
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(start, end-1);
    return dist(rng);
}
