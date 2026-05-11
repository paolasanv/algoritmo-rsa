#include "Entidad.h"

// Forward declarations
uint64_t phiEuler(uint64_t n);
int64_t mcde(uint64_t a, uint64_t b, int64_t &x, int64_t &y);
int64_t mcd(uint64_t a, uint64_t b);
uint64_t potenciaMod(uint64_t a, uint64_t b, uint64_t mod);
uint64_t invMult(uint64_t a, uint64_t mod);
uint rand(uint a, uint b);
bool esPrimo(uint64_t a);
bool coprimos(uint64_t a, uint64_t b);

/** Construye una entidad usando dos números primos p y q */
Entidad::Entidad(std::string nombre, uint64_t p, uint64_t q)
    :nombre{nombre} {
        if(!esPrimo(p) || !esPrimo(q))
		    throw std::invalid_argument("p y q deben ser primos.");
	    if(p == q)
	       throw std::invalid_argument("p y q debe ser distintos.");

	    uint64_t n = p * q;
	    uint64_t phi = (p-1)*(q-1);

	    uint64_t e = 65537; // Por defecto
	    while(!coprimos(e,phi)){
		    e+=2;
	    }

	    uint64_t d = invMult(e,phi);
	    pub = {e,n};
	    priv = {d,n};
}

/** Construye una entidad usando primos y una "semilla" e */
Entidad::Entidad(std::string nombre, uint64_t p, uint64_t q, uint64_t e):
    nombre {nombre}{
        if(!esPrimo(p) || !esPrimo(q))
		    throw std::invalid_argument("p y q deben ser primos.");
	    if(p == q)
		    throw std::invalid_argument("p y q deben ser distintos.");

	    uint64_t n = p * q;
	    uint64_t phi = (p-1)*(q-1);

	    uint64_t d = invMult(e,phi);
	    pub = {e,n};
	    priv = {d,n};
}

/** Agrega una llave externa a esta entidad */
void Entidad::agregaLlave(std::string nombre, std::tuple<uint64_t, uint64_t> llave){
	entidades[nombre] = llave;
}

/** Cifra un caracter dependiendo para quien */
uint64_t Entidad::cifraCaracter(std::string nombre, unsigned char c){
	auto it = entidades.find(nombre);
	if(it == entidades.end()){
		throw std::invalid_argument("No se encontra una llave para: " + nombre);
	}
	auto [e, n] = it->second;
	uint64_t m = static_cast<uint64_t>(c);
	return potenciaMod(m, e, n);
}

/** Descifra un caracter que fue cifrado utilizando su llave pública */
unsigned char Entidad::descifraCaracter(uint64_t i){
	auto [d, n] = priv;
	uint64_t m = potenciaMod(i, d, n);
	return static_cast<unsigned char>(m);
}

/** Cifra una cadena de caracteres */
std::vector<uint64_t> Entidad::cifraMensaje(std::string nombre, std::string mensaje){
	std::vector<uint64_t> cifrado;
	for(unsigned char ch : mensaje) {
		cifrado.push_back(cifraCaracter(nombre, ch));
	}
	return cifrado;
}

/** Descifra un vector de números cifrados para esta entidad */
std::vector<uint64_t> Entidad::descifraMensaje(std::vector<uint64_t> cifrado){
	std::vector<uint64_t> descifrado;
	auto[d, n] = priv;
	for(uint64_t i : cifrado) {
		descifrado.push_back(potenciaMod(i, d, n));
	}
	return descifrado;
};

/** Convierte un vector de números descifrados a una cadena */
std::string Entidad::decodificarMensaje(std::vector<uint64_t> descifrado){
	std::string mensaje;
	for(uint64_t i : descifrado) {
		mensaje += static_cast<unsigned char>(i);
	}
	return mensaje;
};
