#include "math_utils.h"

int mod(int n, int p) {
	return ((n % p) + p) %p;
}