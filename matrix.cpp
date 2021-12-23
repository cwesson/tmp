
#include "tmp/matrix.h"
#include <iostream>
#include <assert.h>

int main(){
	matrix<3, 3, int> A{
		0, 1, 2,
		10,11,12,
		20,21,22
	};
	
	matrix<1, 2, int> AA = {1, 2};
	
	matrix<3, 3, int> B = A + A;
	
	matrix<3, 3, int> C = 5*A;
	
	for(unsigned int r = 0; r < 3; ++r){
		for(unsigned int c = 0; c < 3; ++c){
			std::cout << B[r][c] << " ";
		}
		std::cout << std::endl;
	}
	
	for(unsigned int r = 0; r < 3; ++r){
		for(unsigned int c = 0; c < 3; ++c){
			std::cout << C[r][c] << " ";
		}
		std::cout << std::endl;
	}
	
	matrix<3, 1, int> D;
	D[0][0] = 1;
	D[1][0] = 2;
	D[2][0] = 3;
	matrix<1, 3, int> E;
	E[0][0] = 4;
	E[0][1] = 5;
	E[0][2] = 6;
	matrix<3, 3, int> P = D*E;
	matrix<3, 3, int> F;
	F[0][0] = 1*4;
	F[0][1] = 1*5;
	F[0][2] = 1*6;
	F[1][0] = 2*4;
	F[1][1] = 2*5;
	F[1][2] = 2*6;
	F[2][0] = 3*4;
	F[2][1] = 3*5;
	F[2][2] = 3*6;
	assert(P == F);
	
	for(unsigned int r = 0; r < 3; ++r){
		for(unsigned int c = 0; c < 3; ++c){
			std::cout << P[r][c] << " ";
		}
		std::cout << std::endl;
	}
	
	/*matrix<2,3,int> G({
		{1,2,3},
		{4,5,6}
	});
	
	for(unsigned int r = 0; r < 2; ++r){
		for(unsigned int c = 0; c < 3; ++c){
			printf("%d ", G[r][c]);
		}
		printf("\n");
	}*/
	
	return 0;
}

