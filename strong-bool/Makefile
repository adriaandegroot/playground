TARGETS=	example-0 \
		example-1 \
		example-2 \
		example-4 \
		example-6
		# example-3
		# example-5

all: $(TARGETS)

clean:
	rm -f $(TARGETS)

example-0: example-1.cc
	$(CXX) -o $@ $?

example-1: example-1.cc
	$(CXX) -o $@ -Wall -Wextra -Wpedantic -std=c++20 $?

example-2: example-2.cc
	$(CXX) -o $@ -Wall -Wextra -Wpedantic -std=c++20 $?

example-3: example-3.cc
	# Does not compile
	$(CXX) -o $@ -Wall -Wextra -Wpedantic -std=c++20 $?

example-4: example-4.cc
	$(CXX) -o $@ -Wall -Wextra -Wpedantic -std=c++20 $?

example-5: example-5.cc
	$(CXX) -o $@ -Wall -Wextra -Wpedantic -std=c++20 $?

example-6: example-6.cc
	$(CXX) -o $@ -Wall -Wextra -Wpedantic -std=c++20 $?
