BIN=encrypt


.PHONY : run build clean clean_all

build : $(BIN)
run : result.txt clean

result.txt : build
	./encrypt -i plain.txt -o result.txt

$(BIN) : main.o encrypt.o io.o

clean :
	rm -f *.o $(BIN)

clean_all : clean
	rm -f result.txt
