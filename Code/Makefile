# project name (generate executable with this name)
TARGET   = main

CC       = gcc
# compiling flags here
CFLAGS   = -Wall -I. `sdl-config --libs` -lSDL_image -lSDL_ttf


LINKER   = gcc -o
# linking flags here
LFLAGS   = -I. -lm `sdl-config --libs` -lSDL_image -lSDL_ttf


# change these to set the proper directories where each files shoould be
SRCDIR   = src
OBJDIR   = build
BINDIR   = bin

SOURCES  := $(wildcard $(SRCDIR)/*.c)
INCLUDES := $(wildcard $(SRCDIR)/*.h)
OBJECTS  := $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
rm       = rm -f


$(BINDIR)/$(TARGET): $(OBJECTS)
	@test -d $(BINDIR) || mkdir -p $(BINDIR)
	@$(LINKER) $@ $(OBJECTS) $(LFLAGS)
	@echo "Linking complete!"

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.c
	@test -d $(OBJDIR) || mkdir -p $(OBJDIR)
	@$(CC) -c $< -o $@ $(CFLAGS)
	@echo "Compiled "$<" successfully!"

.PHONEY: test
test: $(OBJECTS)
	gcc -c tests/main_test.c -o build/main_test.o
	$(LINKER) bin/main_test build/element.o build/IA.o build/item.o build/jeux.o build/main_test.o build/plateau.o build/score.o build/sdl_functions.o build/snake.o build/test.o $(LFLAGS)

.PHONEY: clean
clean:
	@$(rm) $(OBJECTS)
	@echo "Cleanup complete!"

.PHONEY: remove
remove: clean
	@$(rm) $(BINDIR)/$(TARGET)
	@echo "Executable removed!"