SHELL= bash
CC= cc
CHMOD= chmod
CLANG= clang
CLANG_FORMAT= clang-format
CPP= cpp
GCC= gcc
MV= mv
RM= rm
RMDIR= rmdir
TRUE= true
CSILENCE= -Wno-poison-system-directories -Wno-unsafe-buffer-usage -Wno-overriding-deployment-version -Wno-missing-field-initializers -Wno-multistatement-macros -Wno-unused-variable -Wno-array-bounds -Wno-stringop-overread
CUNKNOWN= -Wno-unknown-warning-option
CWARN= -Wall -Wextra -pedantic ${CSILENCE} ${CUNKNOWN}
CSTD= -std=gnu17
ARCH=
CDEFINE=
CINCLUDE=
COTHER=
OPT= -O3
CFLAGS= ${CSTD} ${CWARN} ${ARCH} ${CDEFINE} ${CINCLUDE} ${COTHER} ${OPT}
LDFLAGS=
CC= cc
ifeq "$(findstring $(CLANG),${CC})" "$(CLANG)"
CSILENCE+=
CWARN+= -Weverything
endif
ifeq "$(findstring $(GCC),${CC})" "$(GCC)"
CSILENCE+=
CWARN+=
endif
PROG= elfsh
OBJ= ${PROG}.o
TARGET= ${PROG}
DATA=

all: data ${TARGET}
	@${TRUE}

.PHONY: all alt data everything clean clobber

${PROG}: ${PROG}.c
	${CC} ${CFLAGS} ${PROG}.c -o $@ ${LDFLAGS}

clean:
	${RM} -f ${OBJ} ${ALT_OBJ} *.elf

clobber: clean
	@
	@
	${RM} -f ${TARGET} ${ALT_TARGET}
	${RM} -rf *.dSYM

-include 1337.mk ../1337.mk ../../1337.mk
