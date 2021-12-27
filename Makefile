
INCLUDE := include/ test/cpputest/include/
SRCS := src/bigint.cpp unittest.cpp test/biginttest.cpp test/complextest.cpp test/rationaltest.cpp test/tmathtest.cpp test/modinttest.cpp test/fixedtest.cpp test/mininttest.cpp test/comparetest.cpp test/lfsrtest.cpp test/listtest.cpp test/smathtest.cpp
CPPUTESTLIB := test/cpputest/src/CppUTest/libCppUTest.a

CPP := g++
CPPFLAGS := -std=c++2b -g $(addprefix -I,$(INCLUDE))
LD := g++
LDARGS := 
OBJS := $(addsuffix .o,$(addprefix bin/,$(basename $(SRCS))))
DEPS := $(OBJS:%.o=%.d)

.PHONY: all clean realclean ut cpputest

all: ut

ut: unittest

unittest: $(OBJS) $(CPPUTESTLIB)
	$(LD) $(LDARGS) -o $@ $^
	./unittest

cpputest: $(CPPUTESTLIB)

$(CPPUTESTLIB):
	cd test/cpputest; cmake .
	make -C test/cpputest

bin/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CPP) $(CPPFLAGS) -MMD -c -o $@ -c $<

-include $(DEPS)

.NOTPARALLEL: clean realclean

clean:
	@echo CLEAN bin/
	@rm -f $(OBJS) $(DEPS) unittest

realclean: clean
	@echo REALCLEAN
	@rm -rf bin/ 
