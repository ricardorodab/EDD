ACLOCAL_AMFLAGS = -I m4
AUTOMAKE_OPTIONS = subdir-objects

AM_CFLAGS = -std=c99 -D_GNU_SOURCE -Wall $(CFLAGS) -I$(top_srcdir)/lib
AM_LDFLAGS = -lrt -lm $(LDFLAGS)

noinst_LTLIBRARIES = lib/libedd.la

END_LIST =

lib_libedd_la_SOURCES =		\
	lib/arbolbinario.c	\
	lib/arbolbinario.h	\
	lib/arreglos.c		\
	lib/arreglos.h		\
	lib/cola.c		\
	lib/cola.h		\
	lib/diccionario.c	\
	lib/diccionario.h	\
	lib/grafica.c		\
	lib/grafica.h		\
	lib/lista.c		\
	lib/lista.h		\
	lib/monticulominimo.c	\
	lib/monticulominimo.h	\
	lib/pila.c		\
	lib/pila.h		\
	lib/util.c		\
	lib/util.h		\
	$(END_LIST)

bin_PROGRAMS = src/main

src_main_LDADD = $(top_builddir)/lib/libedd.la $(AM_LDFLAGS)
src_main_CFLAGS = $(AM_CFLAGS)
src_main_SOURCES = src/main.c

TESTS = 				\
	test/test-arbolbinario		\
	test/test-arreglos		\
	test/test-cola			\
	test/test-diccionario		\
	test/test-grafica		\
	test/test-lista			\
	test/test-monticulominimo	\
	test/test-pila			\
	test/test-util			\
	$(END_LIST)

check_PROGRAMS = $(TESTS)

TEST_CFLAGS = $(AM_CFLAGS) @CHECK_CFLAGS@
TEST_LDADD = $(top_builddir)/lib/libedd.la @CHECK_LIBS@ $(AM_LDFLAGS)

test_test_arbolbinario_SOURCES = test/test-arbolbinario.c
test_test_arbolbinario_CFLAGS = $(TEST_CFLAGS)
test_test_arbolbinario_LDADD = $(TEST_LDADD)

test_test_arreglos_SOURCES = test/test-arreglos.c
test_test_arreglos_CFLAGS = $(TEST_CFLAGS)
test_test_arreglos_LDADD = $(TEST_LDADD)

test_test_cola_SOURCES = test/test-cola.c
test_test_cola_CFLAGS = $(TEST_CFLAGS)
test_test_cola_LDADD = $(TEST_LDADD)

test_test_diccionario_SOURCES = test/test-diccionario.c
test_test_diccionario_CFLAGS = $(TEST_CFLAGS)
test_test_diccionario_LDADD = $(TEST_LDADD)

test_test_grafica_SOURCES = test/test-grafica.c
test_test_grafica_CFLAGS = $(TEST_CFLAGS)
test_test_grafica_LDADD = $(TEST_LDADD)

test_test_lista_SOURCES = test/test-lista.c
test_test_lista_CFLAGS = $(TEST_CFLAGS)
test_test_lista_LDADD = $(TEST_LDADD)

test_test_monticulominimo_SOURCES = test/test-monticulominimo.c
test_test_monticulominimo_CFLAGS = $(TEST_CFLAGS)
test_test_monticulominimo_LDADD = $(TEST_LDADD)

test_test_pila_SOURCES = test/test-pila.c
test_test_pila_CFLAGS = $(TEST_CFLAGS)
test_test_pila_LDADD = $(TEST_LDADD)

test_test_util_SOURCES = test/test-util.c
test_test_util_CFLAGS = $(TEST_CFLAGS)
test_test_util_LDADD = $(TEST_LDADD)

EXTRA_DIST = doc/edd.dox doc/logo-cc.png

if HAVE_DOXYGEN
docs:
	cd $(top_srcdir)/doc && doxygen

docs-pdf: docs
	cd $(top_srcdir)/doc/latex && make
else
docs:
	echo "No se encontró doxygen: la documentación no puede generarse.";

docs-pdf: docs
endif

clean-local: clean-docs

clean-docs:
	rm -rf $(top_srcdir)/doc/html $(top_srcdir)/doc/latex

dist-hook:
	cd $(top_srcdir) && git log --no-color --stat --name-only --date=short --abbrev-commit > ${srcdir}/ChangeLog
