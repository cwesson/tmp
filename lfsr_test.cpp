#include "lfsr.h"

int main() {
	unsigned int count = 0;
	lfsr::LFSR<16, 16, 14, 13, 11> lfsr16(0xACE1);
	++lfsr16;
	++count;
	std::cout << std::hex << lfsr16.state() << std::endl;
	do{
		if(count == 4){
			std::cout << lfsr16.state() << std::endl;
		}
		lfsr16++;
		++count;
	} while(lfsr16.state() != 0xACE1);
	std::cout << "period: " << count << std::endl;
	
	auto shift(lfsr16 >> 4);
	std::cout << shift.state() << std::endl;
	std::cout << lfsr16.state() << std::endl;

	return 0;
}
