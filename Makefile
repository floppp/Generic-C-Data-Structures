CC = clang
CCFLAGS = -Wall
LDFLAGS = -lm # Requirement to <math.h> compiling
HEADIR = headers
SRCDIR = src
OBJDIR = obj
TESDIR = $(SRCDIR)/tests
# LIBDIR	= lib
DEPEND = students_group.c utils.c stack.c queue.c vector.c
DEPEND_TESTS = test_stack.c test_queue.c test_vector.c
SOURCES = $(addprefix $(SRCDIR)/, $(DEPEND))
OBJECTS = $(addprefix $(OBJDIR)/, $(DEPEND:.c=.o))
EXECUTABLE =
TEST_SOURCES = main_test.c $(addprefix $(TESDIR)/, $(DEPEND_TESTS))
TEST_OBJECTS = main_test.o $(addprefix $(OBJDIR)/, $(DEPEND_TESTS:.c=.o))
TEST_EXECUTABLE = main_test

all: $(OBJECTS) $(TEST_OBJECTS)
	$(CC) $(OBJECTS) $(TEST_OBJECTS) $(CCFLAGS) -o $(TEST_EXECUTABLE) $(LDFLAGS)

debug: $(OBJECTS) $(TEST_OBJECTS)
	$(CC) $(OBJECTS) $(TEST_OBJECTS) -g $(CCFLAGS) -o $(TEST_EXECUTABLE) $(LDFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) -c $(CCFLAGS) $< -o $@

$(OBJDIR)/%.o: $(TESDIR)/%.c
	$(CC) -c $(CCFLAGS) $< -o $@

.PHONY: clean

clean:
	rm main *.o $(OBJDIR)/*.o
