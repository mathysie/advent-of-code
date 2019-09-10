#ifndef VAK_H
#define VAK_H

#include "Unit.h"
#include <cstddef>

using namespace std;

class Vak {
public:
	char val;
	Unit* unit;

	Vak(char c) {unit = NULL, val = c;};
	// Units worden elders opgeruimd.
	~Vak() {unit = NULL;};
	// Geen move of copy instructies toestaan.
	Vak(const Vak&) = delete;
	Vak& operator= (const Vak&) = delete;
	Vak (Vak&&) = delete;
	Vak& operator= (Vak&&) = delete;
};

#endif