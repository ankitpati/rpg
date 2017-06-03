# Makefile for Random Password Generator

CC         = cc
CFLAGS     = -c -O3
SOURCES    = src/rpg.c
OBJECTS    = $(SOURCES:.c=.o)
EXECUTABLE = rpg

all: $(SOURCES) $(EXECUTABLE) done

$(EXECUTABLE): $(OBJECTS)
	@echo Linking...
	$(CC) $(OBJECTS) -o $@
	strip $(EXECUTABLE)

.c.o:
	@echo Compiling...
	$(CC) $(CFLAGS) $< -o $@

clean:
	@echo Cleaning...
	find . -name "*.o"   -type f -delete
	find . -name "*.gch" -type f -delete

done:
	@echo -n

# end of Makefile
