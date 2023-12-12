CC_FLAGS=-c -W -Wall
SOURCE=lib
TARGET=obj

clean:
	rm -rf ${TARGET}/*.o *~ tspdl_solver

arrays.o: ${TARGET}/arrays.o
${TARGET}/arrays.o: ${SOURCE}/arrays.c ${SOURCE}/arrays.h
	gcc -o ${TARGET}/arrays.o ${SOURCE}/arrays.c ${CC_FLAGS}

graphs.o: ${TARGET}/graphs.o
${TARGET}/graphs.o: ${SOURCE}/graphs.c ${SOURCE}/graphs.h
	gcc -o ${TARGET}/graphs.o ${SOURCE}/graphs.c ${CC_FLAGS}

solutions.o: ${TARGET}/solutions.o
${TARGET}/solutions.o: ${SOURCE}/solutions.c ${SOURCE}/solutions.h
	gcc -o ${TARGET}/solutions.o ${SOURCE}/solutions.c ${CC_FLAGS}

lists.o: ${TARGET}/lists.o
${TARGET}/lists.o: ${SOURCE}/lists.c ${SOURCE}/lists.h ${SOURCE}/solutions.h
	gcc -o ${TARGET}/lists.o ${SOURCE}/lists.c ${CC_FLAGS}

local_search.o: ${TARGET}/local_search.o
${TARGET}/local_search.o: ${SOURCE}/local_search.c ${SOURCE}/local_search.h ${SOURCE}/solutions.h
	gcc -o ${TARGET}/local_search.o ${SOURCE}/local_search.c ${CC_FLAGS}

containers.o: ${TARGET}/containers.o
${TARGET}/containers.o: ${TARGET}/arrays.o ${TARGET}/graphs.o ${TARGET}/solutions.o ${TARGET}/lists.o
	ld -relocatable -o ${TARGET}/containers.o ${TARGET}/arrays.o ${TARGET}/graphs.o ${TARGET}/solutions.o ${TARGET}/lists.o


main.o: main.c ${SOURCE}/meta_index_tabu.h
	gcc -o ${TARGET}/main.o main.c ${CC_FLAGS}

all: tspdl_solver

tspdl_solver: main.o lists.o graphs.o
	gcc -o tspdl_solver lists.o graphs.o
