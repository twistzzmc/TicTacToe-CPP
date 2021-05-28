FLAGS = -Wall -pedantic -Wextra -Werror -Weffc++ -std=c++14

# commands for running program
all: compile run

compile:
	g++ $(FLAGS) *.cpp -o tictactoe

run:
	./tictactoe -p medium 

clean:
	rm -rf tictactoe


# Commands for running tests

test: compile test-compile test-run

test-compile:
	$(MAKE) -C tests

test-run:
	./tests/runTests

test-clean:
	rm -rf /tests/runTests
