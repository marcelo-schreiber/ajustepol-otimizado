PROJ_NAME=ajustePol
 
# .c files
C_SOURCE=$(filter-out gera_entrada.c, $(wildcard *.c))
 
# .h files
H_SOURCE=$(wildcard *.h)
 
# Object files
OBJ=$(C_SOURCE:.c=.o)
 
# Compiler
CC=gcc
 
# Flags for compiler
CC_FLAGS=-c         \
				 -O3				\
				 -mavx			\
				 -march=native	\
         -Wall      \

LIKWID_FLAGS=-DLIKWID_PERFMON \
 						 -I{LIKWID_INCLUDE} \
 						 -L{LIKWID_LIB} \


# TODO: mudar para o caminho do likwid e adicionar likwid python
DISTFILES = *.c *.h README* Makefile likwid.py pontos.in teste.in expected.out
DISTDIR = `basename mars22-fqv21`
#
# Compilation and linking
#
all: $(PROJ_NAME)
 
$(PROJ_NAME): $(OBJ)
		$(CC) $(LIKWID_FLAGS) $^ -o $@ -lm -llikwid
 

%.o: %.c %.h
		$(CC) -o $@ $< $(CC_FLAGS) $(LIKWID_C) -lm -llikwid
 
main.o: main.c $(H_SOURCE)
		$(CC) $< $(CC_FLAGS) $(LIKWID_FLAGS) -o $@ -lm -llikwid
 
softclean:
		@rm -f *~ *.bak

clean:  softclean
		@rm -f $(PROG) *.o core a.out $(PROJ_NAME) output.out output2.out
		@rm -rf $(DISTDIR) $(DISTDIR).tar

dist:
		@echo "Gerando arquivo de distribuição ($(DISTDIR).tar) ..."
		@ln -s . $(DISTDIR)
		@tar -cvf $(DISTDIR).tar $(addprefix ./$(DISTDIR)/, $(DISTFILES))
		@rm -rf $(DISTDIR)

distcheck:
		@echo "Verificando se o código compila ..."
		@make dist
		@tar -xvf $(DISTDIR).tar

		@cd $(DISTDIR) && make
		@cd $(DISTDIR) && make check

		@rm -rf ./$(DISTDIR)
		@echo "dist check correto!"

check:
		@echo "Verificando se o tem a saida correta..."
		./$(PROJ_NAME) < teste.in > output.out
		@head -n 2 output.out > output2.out
		@diff -w output2.out expected.out
		@rm output.out output2.out
		@echo "check correto!"

		
.PHONY: all