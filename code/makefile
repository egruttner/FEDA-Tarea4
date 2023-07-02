CC = g++
CFLAGS = -std=c++14 -O2

SRCS = main.cpp 
OBJS = $(SRCS:.cpp=.o)

LDLIBS="distance.cpp"

TEST_CASES_NUMBER := $(shell seq 1 20) #rango de archivos de input y output

RANGE = 1 2 3 4#distintas tareas a probar

# 1 CLASICA - Gutenberg VS Gutenberg
# 2 ADAPTIVA - Gutenberg VS Gutenberg
# 3 CLASICA - Gutenberg VS Alterado Gutenberg
# 4 ADAPTIVA - Gutenberg VS Alterado Gutenberg

INPUT_PREFIX := datasets/input$(num_dataset)/input

OUTPUT_PREFIX := output/output

all: program

	for j in $(RANGE); do \
		echo "Executing program with $$j --head $$num_dataset"; \
		./program $$j --head $$num_dataset; \
		for i in $(TEST_CASES_NUMBER); do \
			echo "./program --test $$j $$num_dataset $$i > $(OUTPUT_PREFIX)$$j$$i.txt"; \
			./program $$j --test $$num_dataset $$i > $(OUTPUT_PREFIX)$$j$$i.txt; \
		done; \
	done

program: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LDLIBS) -o program

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) program output*

