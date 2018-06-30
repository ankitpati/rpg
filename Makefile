# Makefile for Random Password Generator

CC         = cc
CFLAGS     = -c -O3
SOURCES    = src/rpg.c
OBJECTS    = $(SOURCES:.c=.o)
EXECUTABLE = rpg

.PHONY: all
all: $(SOURCES) $(EXECUTABLE) done

$(EXECUTABLE): $(OBJECTS)
	@echo Linking...
	$(CC) $(OBJECTS) -o $@
	strip $(EXECUTABLE)
	chmod 755 $(EXECUTABLE)

.c.o:
	@echo Compiling...
	$(CC) $(CFLAGS) $< -o $@

.PHONY: clean
clean:
	@echo Cleaning...
	find . -name "*.o"   -type f -delete
	find . -name "*.gch" -type f -delete

.PHONY: done
done:
	@echo -n

.PHONY: install
install:
	@echo Installing...
ifeq ($(shell id -u), 0)
	mkdir -p /usr/bin/
	cp $(EXECUTABLE) /usr/bin/
else
	mkdir -p ~/bin/
	cp $(EXECUTABLE) ~/bin/
endif

# end of Makefile
