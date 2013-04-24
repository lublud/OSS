#/**
#*
#* @File : makefile
#*
#*
#* @Synopsis : Makefile pour l'OS
#*
#**/

INCLUDE = ../include

COMPILER = gcc -I$(INCLUDE) -Wall -w -g -ansi -pedantic -std=c99 -Werror $*.c

all: OSS

OSS: 
	gcc -o OSS.run -I$(INCLUDE) -pthread -w -g -ansi -pedantic -std=c99 -Werror main.c

# Edition de liens
#
#$(nom).run : $(nom).o
#	gcc -s -o $(nom).run $(nom).o
#
#$(nom).o : $(nom).c
#	$(COMPILER)

#
# Nettoyage du repertoire courant : executables et fichiers .o
#
clean :
	clear; rm -rf *.o *.run ../lib -v *~ ../include/*~
#
