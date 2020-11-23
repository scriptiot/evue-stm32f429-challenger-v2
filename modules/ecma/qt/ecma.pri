INCLUDEPATH += $$PWD
INCLUDEPATH += $$PWD/../inc

HEADERS += \
    $$PWD/../inc/ecma.h \
    $$PWD/../inc/re.h

SOURCES += \
    $$PWD/../src/ecma.c \
    $$PWD/../src/ecma_array.c \
    $$PWD/../src/ecma_date.c \
    $$PWD/../src/ecma_math.c \
    $$PWD/../src/ecma_number.c \
    $$PWD/../src/ecma_object.c \
    $$PWD/../src/ecma_regexp.c \
    $$PWD/../src/ecma_string.c \
    $$PWD/../src/ecma_timeout.c \
    $$PWD/../src/re.c
