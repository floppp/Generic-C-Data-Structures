TEMPLATE = app
QMAKE_CFLAGS += -std=gnu99
CONFIG -= app_bundle
CONFIG -= qt
SUBDIR = \
	headers\
	src\
SOURCES += main.c

HEADERS += \
	headers/lecture_5.h \
	headers/utils.h \
	headers/stack.h \
	headers/queue.h \
	headers/list.h \
	headers/linked_list.h \
	headers/students_group.h \
    headers/test_stack.h \
    headers/test_queue.h \
    headers/test_list.h \
    headers/test_linked_list.h \
    headers/vector.h \
    headers/test_vector.h \
    headers/hashset.h \
    headers/test_hashset.h

SOURCES += \
	src/lecture_5.c \
	main.c \
	src/utils.c \
	src/stack.c \
	src/queue.c \
	src/list.c \
	src/linked_list.c \
	src/students_group.c \
    src/test_stack.c \
    src/test_queue.c \
    src/test_list.c \
    src/test_linked_list.c \
    src/vector.c \
    src/test_vector.c \
    src/hashset.c \
    src/test_hashset.c

DISTFILES += \
    headers/test_queue

