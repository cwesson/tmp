
#include "bigint.h"

template<>
std::string bigint<uint64_t>::hex() const{
	char buff[HALFSIZE + 1] = {0};
	snprintf(&buff[0], sizeof(buff), "%016" PRIu64 "X%016" PRIu64 "X", hi, lo);
	return std::string(&buff[0]);
}

template<>
bigint<uint64_t> bigint<uint64_t>::mult(const uint64_t& a, const uint64_t& b){
	/*
	                  ah al
	                x bh bl
	-------------------------
	          ahbl+alblc albl
	ahbh+albhc  albh
	-------------------------
	*/
	const unsigned int shift = 32;
	const uint64_t mask = 0x00000000FFFFFFFFull;
	
	const uint32_t ah = (a >> shift);
	const uint32_t al = (a & mask);
	const uint32_t bh = (b >> shift);
	const uint32_t bl = (b & mask);

	const uint64_t albl = (uint64_t)al * (uint64_t)bl;
	const uint32_t alblc = (albl >> shift);
	const uint32_t alblp = (albl & mask);
	const uint64_t ahbl = ((uint64_t)ah * (uint64_t)bl) + alblc;
	const uint32_t ahblc = (ahbl >> shift);
	const uint32_t ahblp = (ahbl & mask);
	const uint64_t albh = ((uint64_t)al * (uint64_t)bh);
	const uint32_t albhc = (albh >> shift);
	const uint32_t albhp = (albh & mask);
	const uint64_t ahbh = ((uint64_t)ah * (uint64_t)bh) + albhc;
	const uint64_t i = ((uint64_t)ahblp + (uint64_t)albhp);
	const uint32_t ih = (i >> shift);
	const uint32_t il = (i & mask);

	const bigint<uint64_t> ret(
		ahbh + ahblc + ih,
		((uint64_t)il << 32) | alblp
	);

	return ret;
}
