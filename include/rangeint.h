
template<signed long long int min, signed long long int max>
class rangeint {
	public:
		rangeint<min, max>():
			value(0){}
		rangeint<min, max>(signed long long int v):
			value(v){}
	
	private:
		signed long long int value;
}

