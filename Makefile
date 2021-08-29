
INCLUDE := include/
SRCS := bigint.cpp unittest.cpp biginttest.cpp complextest.cpp rationaltest.cpp tmathtest.cpp modinttest.cpp

CPP := g++
CPPFLAGS := -std=c++17 -g $(addprefix -I,$(INCLUDE))
BINS := $(addsuffix .o,$(addprefix bin/,$(basename $(SRCS))))

all: ut

ut: unittest

unittest: $(BINS)
	$(CPP) -o $@ $?

bin/%.o: %.cpp
	@mkdir -p bin/
	$(CPP) $(CPPFLAGS) -c -o $@ $<

clean:
	rm -rf bin/
	rm -f unittest

