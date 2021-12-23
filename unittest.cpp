
extern int biginttest();
extern int complextest();
extern int rationaltest();
extern int tmathtest();
extern int modinttest();

#include "CppUTest/CommandLineTestRunner.h"
#include <iostream>
#include "tmp/smath.h"
#include "tmp/list.h"

int main(int argc, char* argv[]){
	biginttest();
	
	complextest();
	
	rationaltest();
	
	tmathtest();
	
	modinttest();

	CommandLineTestRunner::RunAllTests(argc, argv);
	
	typedef tmp::List< tmp::Int<1>, tmp::List< tmp::Int<2>, tmp::List< tmp::Int<4>, tmp::List< tmp::Int<8>>>>> list;
	
	static_assert(tmp::Length<list>::result == 4);
	static_assert(tmp::Sum<list>::result == 15);
	static_assert(tmp::Product<list>::result == 64);
	static_assert(tmp::Nth<list, 3>::result == 8);
	static_assert(tmp::Includes<list, tmp::Int<2>>::result == true);
	static_assert(tmp::Includes<list, tmp::Int<32>>::result == false);
	static_assert(tmp::Find<list, tmp::Int<1>>::result == 0);
	static_assert(tmp::Find<list, tmp::Int<4>>::result == 2);
	static_assert(tmp::Find<list, tmp::Int<8>>::result == 3);
	//std::cout << tmp::Find<list, tmp::Int<32>>::result << std::endl;
	
	std::cout << "log(2)=" << tmp::smath<64>::log << std::endl;
	std::cout << "log2(20)=" << tmp::smath<20, 2>::log << std::endl;
	std::cout << "log2(3)=" << tmp::smath<3, 2>::log << std::endl;
	std::cout << "log3(20)=" << tmp::smath<20, 3>::log << std::endl;
	
	return 0;
}

