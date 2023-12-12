CC_FLAGS=-c -W -Wall -std=gnu11
SOURCE=lib
TARGET=obj

all: ${TARGET}/main.o ${TARGET}/containers.o ${TARGET}/solvers.o
	gcc -o tspdl ${TARGET}/main.o ${TARGET}/containers.o ${TARGET}/solvers.o

clean:
	rm -rf ${TARGET}/*.o *~ tspdl

${TARGET}/arrays.o: ${SOURCE}/arrays.c ${SOURCE}/arrays.h
	gcc -o ${TARGET}/arrays.o ${SOURCE}/arrays.c ${CC_FLAGS}

${TARGET}/graphs.o: ${SOURCE}/graphs.c ${SOURCE}/graphs.h
	gcc -o ${TARGET}/graphs.o ${SOURCE}/graphs.c ${CC_FLAGS}

${TARGET}/solutions.o: ${SOURCE}/solutions.c ${SOURCE}/solutions.h
	gcc -o ${TARGET}/solutions.o ${SOURCE}/solutions.c ${CC_FLAGS}

${TARGET}/lists.o: ${SOURCE}/lists.c ${SOURCE}/lists.h ${SOURCE}/solutions.h
	gcc -o ${TARGET}/lists.o ${SOURCE}/lists.c ${CC_FLAGS}

${TARGET}/local_search.o: ${SOURCE}/local_search.c ${SOURCE}/local_search.h ${SOURCE}/solutions.h
	gcc -o ${TARGET}/local_search.o ${SOURCE}/local_search.c ${CC_FLAGS}

${TARGET}/containers.o: ${TARGET}/arrays.o ${TARGET}/graphs.o ${TARGET}/solutions.o ${TARGET}/lists.o
	ld -relocatable -o ${TARGET}/containers.o ${TARGET}/arrays.o ${TARGET}/graphs.o ${TARGET}/solutions.o ${TARGET}/lists.o

${TARGET}/solvers.o: ${TARGET}/local_search.o
	ld -relocatable -o ${TARGET}/solvers.o ${TARGET}/local_search.o

${TARGET}/main.o: main.c ${SOURCE}/local_search.h
	gcc -o ${TARGET}/main.o main.c ${CC_FLAGS}

