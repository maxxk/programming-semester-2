#!/bin/sh
CFLAGS_WARN="-std=c99 -pedantic -Wall -Werror -Wextra -pedantic-errors
        -Wpointer-arith -Waggregate-return
        -Wstrict-prototypes -Wmissing-declarations
        -Winline -Wredundant-decls
        -Wcast-align -Wfloat-equal -Wbad-function-cast"

gcc $CFLAGS_WARN "$@"
