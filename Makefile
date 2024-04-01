# Makefile and comments based on tutorial at
# https://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/

# Compiler $(CC)
CC=gcc

# Directory for header files $(IDIR)
IDIR=include
# Directory for object files $(ODIR)
ODIR=obj
# Directory for libraries	 $(LDIR)
LDIR=lib

# -lm: link math.h
LIBS=#-lm
# Flags to the compilation command $(CFLAGS)
CFLAGS=-I$(IDIR) -lpthread

# header files $(DEPS)
_DEPS = # func.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))
# Object files $(OBJ)
_OBJ = main.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))
# patsubst : Pattern substitution for each wildcard '%' pattern replace it
# with the pattern prepended by the folder

# gcc: 
# -o specify output file
# -c compile and assemble but do not link, generates the .o object file

# Target .o files depend on its .c file and all .h files
# $@ indicates the file named as the target on left side of the :
# $< : First item in dependencies list (the .c file in this case)
$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

# Builds each .o from changed .c files but ignores changes in .h files
# $^ : Right side of the : symbol (the list of .o files in this case)
main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

# Do not do anything with a file named clean
.PHONY: clean

# Does not work on windows
clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~
