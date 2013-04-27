#/**
#*
#* @File : makefile
#*
#*
#* @Synopsis : Makefile pour l'OS
#*
#**/

INCLUDE = ../include

all: OSS

OSS: 
	gcc -o OSS.run -I$(INCLUDE) -pthread -w -g -ansi -pedantic -std=c99 -Werror main.c

#
# Nettoyage du repertoire courant : executables et fichiers .o
#
clean :
	clear; rm -rf *.o *.run ../lib -v *~ ../include/*~
#
