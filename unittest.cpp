
extern int biginttest();
extern int complextest();
extern int rationaltest();
extern int tmathtest();
extern int modinttest();

#include <iostream>
#include "smath.h"

int main(){
	biginttest();
	
	complextest();
	
	rationaltest();
	
	tmathtest();
	
	modinttest();
	
	/*typedef List< Int<1>, List< Int<2>, List< Int<4>, List< Int<8>>>>> list;
	
	std::cout << Length<list>::result << std::endl;
	std::cout << Sum<list>::result << std::endl;
	std::cout << Nth<list, 3>::result << std::endl;
	std::cout << Includes<list, Int<2>>::result << std::endl;
	std::cout << Includes<list, Int<32>>::result << std::endl;
	std::cout << Find<list, Int<1>>::result << std::endl;
	std::cout << Find<list, Int<4>>::result << std::endl;
	std::cout << Find<list, Int<8>>::result << std::endl;*/
	//std::cout << Find<list, Int<32>>::result << std::endl;
	
	return 0;
}

