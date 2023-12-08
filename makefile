CC_FLAGS=-c -W -Wall
SOURCE=lib
TARGET=objects

clean:
	rm -rf ${TARGET}/*.o *~ tspdl_solver

arrays.o: ${SOURCE}/arrays.h ${SOURCE}/arrays.c
	gcc -o ${TARGET}/arrays.o ${SOURCE}/arrays.c ${CC_FLAGS}

graphs.o: ${SOURCE}/graphs.h ${SOURCE}/graphs.c
	gcc -o ${TARGET}/graphs.o ${SOURCE}/graphs.c ${CC_FLAGS}

solutions.o: ${SOURCE}/solutions.h ${SOURCE}/solutions.c
	gcc -o ${TARGET}/solutions.o ${SOURCE}/solutions.c ${CC_FLAGS}

lists.o: ${SOURCE}/solutions.h ${SOURCE}/lists.h ${SOURCE}/lists.c
	gcc -o ${TARGET}/lists.o ${SOURCE}/lists.c ${CC_FLAGS}


containers: arrays.o graphs.o solutions.o lists.o


main.o: main.c ${SOURCE}/meta_index_tabu.h
	gcc -o ${TARGET}/main.o main.c ${CC_FLAGS}

all: tspdl_solver

tspdl_solver: main.o lists.o graphs.o
	gcc -o tspdl_solver lists.o graphs.o
