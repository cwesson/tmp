
INCLUDE := include/ test/cpputest/include/
SRCS := bigint.cpp unittest.cpp biginttest.cpp complextest.cpp rationaltest.cpp tmathtest.cpp modinttest.cpp test/fixedtest.cpp test/mininttest.cpp test/comparetest.cpp test/lfsrtest.cpp
CPPUTESTLIB := test/cpputest/src/CppUTest/libCppUTest.a

CPP := g++
CPPFLAGS := -std=c++2b -g $(addprefix -I,$(INCLUDE))
LD := g++
LDARGS := 
OBJS := $(addsuffix .o,$(addprefix bin/,$(basename $(SRCS))))
DEPS := $(OBJS:%.o=%.d)

all: ut

ut: unittest

unittest: $(OBJS) $(CPPUTESTLIB)
	$(LD) $(LDARGS) -o $@ $^
	./unittest

$(CPPUTESTLIB): cpputest

cpputest:
	cd test/cpputest; cmake .
	make -C test/cpputest

bin/%.o: %.cpp
	@mkdir -p bin/test/
	$(CPP) $(CPPFLAGS) -MMD -c -o $@ -c $<

-include $(DEPS)

.NOTPARALLEL: clean realclean

clean:
	@echo CLEAN bin/
	@rm -f $(OBJS) $(DEPS) unittest

realclean: clean
	@echo REALCLEAN
	@rm -rf bin/ 
