CC = clang
CCFLAGS = -Wall
CDFLAGS = -g -Wall
LDFLAGS = -lm # Requirement to <math.h> compiling
HEADIR  = headers
SRCDIR  = src
OBJDIR  = obj
TESDIR  = tests
LIBDIR  = lib
DEPEND  = utils.c stack.c queue.c vector.c lookup3.c
DEPEND += utils_map_functions.c linked_list.c hashmap.c
DEPEND_TESTS  = test_stack.c test_queue.c test_vector.c
DEPEND_TESTS += test_linked_list.c test_hashmap.c libaleatorios.c
DEPEND_TESTS += test_utils.c
SOURCES = $(addprefix $(SRCDIR)/, $(DEPEND))
OBJECTS = $(addprefix $(OBJDIR)/, $(DEPEND:.c=.o))
EXECUTABLE      =
TEST_SOURCES    = main_test.c $(addprefix $(TESDIR)/, $(DEPEND_TESTS))
TEST_OBJECTS    = main_test.o $(addprefix $(OBJDIR)/, $(DEPEND_TESTS:.c=.o))
TEST_EXECUTABLE = main_test

all: $(OBJECTS) $(TEST_OBJECTS)
	$(CC) $(OBJECTS) $(TEST_OBJECTS) $(CCFLAGS) -o $(TEST_EXECUTABLE) $(LDFLAGS)

debug: $(OBJECTS) $(TEST_OBJECTS)
	$(CC) $(OBJECTS) $(TEST_OBJECTS) $(CDFLAGS) -o $(TEST_EXECUTABLE) $(LDFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) -c $(CDFLAGS) $< -o $@

$(OBJDIR)/%.o: $(TESDIR)/%.c
	$(CC) -c $(CDFLAGS) $< -o $@

.PHONY: clean

clean:
	rm main_test *.o $(OBJDIR)/*.o
