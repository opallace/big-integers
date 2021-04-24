#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

//test
#include <time.h>
//test

#include "../bn.h"

int main(){
	BIGNUM *a = int_to_bn(-99);
	BIGNUM *b = int_to_bn(-9);
	BIGNUM *result = init_bn();

	sum_bn(a, b, result);
	println_bn(result);

	return 0;
}