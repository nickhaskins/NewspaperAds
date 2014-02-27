
GTEST_DIR=GoogleTest

# Flags passed to the preprocessor.
# Set Google Test's header directory as a system directory, such that
# the compiler doesn't generate warnings in Google Test headers.
CPPFLAGS += -isystem $(GTEST_DIR)/include

# Flags passed to the C++ compiler.
CXXFLAGS += -g -Wall -Wextra -pthread

TESTS+=all_tests
TESTS+=newspaper_tests
TESTS+=ad_tests
TEST_DEPENDENCIES=

# All Google Test headers.  Usually you shouldn't change this
# definition.
GTEST_HEADERS = $(GTEST_DIR)/include/gtest/*.h \
	            $(GTEST_DIR)/include/gtest/internal/*.h

# REMINDER: they have to be tabs (\t) for the Makefile to work
	            
all: main $(TESTS)


main: main.o newspaper.o ad.o
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $^ -o $@

main.o: main.cpp ad_real.h newspaper_real.h $(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c main.cpp -o $@

clean: 
	rm -f $(TESTS) main gtest.a gtest_main.a *.o

################################################################################
# 
# ad
# 
################################################################################
ad.o: ad.h ad_real.h ad_real.cpp common.h
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c ad_real.cpp -o $@

ad_tests.o: ad_tests.cpp ad.h ad_real.h common.h $(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c ad_tests.cpp

AD_TEST_DEPENDENCIES=ad_tests.o ad.o gtest_main.a
TEST_DEPENDENCIES+=$(AD_TEST_DEPENDENCIES)
ad_tests: $(AD_TEST_DEPENDENCIES)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -lpthread $^ -o $@

################################################################################
# 
# newspaper
# 
################################################################################
newspaper.o: newspaper.h newspaper_real.h newspaper_real.cpp ad.h common.h
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c newspaper_real.cpp -o $@

newspaper_tests.o: newspaper_tests.cpp newspaper.h newspaper_real.h ad.h common.h $(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c newspaper_tests.cpp

NEWSPAPER_TEST_DEPENDENCIES=newspaper_tests.o newspaper.o gtest_main.a
TEST_DEPENDENCIES+=$(NEWSPAPER_TEST_DEPENDENCIES)
newspaper_tests: $(NEWSPAPER_TEST_DEPENDENCIES)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -lpthread $^ -o $@

	
################################################################################
# 
# all tests
# 
################################################################################
all_tests: $(TEST_DEPENDENCIES) gtest_main.a
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -lpthread $^ -o $@	

# Usually you shouldn't tweak such internal variables, indicated by a
# trailing _.
GTEST_SRCS_ = $(GTEST_DIR)/src/*.cc $(GTEST_DIR)/src/*.h $(GTEST_HEADERS)

# For simplicity and to avoid depending on Google Test's
# implementation details, the dependencies specified below are
# conservative and not optimized.  This is fine as Google Test
# compiles fast and for ordinary users its source rarely changes.
gtest-all.o : $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c \
	        $(GTEST_DIR)/src/gtest-all.cc

gtest_main.o : $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c \
	        $(GTEST_DIR)/src/gtest_main.cc

gtest.a : gtest-all.o
	$(AR) $(ARFLAGS) $@ $^

gtest_main.a : gtest-all.o gtest_main.o
	$(AR) $(ARFLAGS) $@ $^
