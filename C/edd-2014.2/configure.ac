# Define nombre del proyecto y versión
AC_INIT([edd], [2014.2])
# Directorio para guardar archivos auxiliares
AC_CONFIG_AUX_DIR([build])
# Hace una copia de los archivos de libtool en el directorio m4
AC_CONFIG_MACRO_DIR([m4])
# Inicializa automake
AM_INIT_AUTOMAKE
# Compila sin hacer ruido
AM_SILENT_RULES([yes])
# Comprueba que tengamos el compilador de C
AC_PROG_CC
# Permite cambiar las banderas de compilación para cada objetivo
AM_PROG_CC_C_O
# Comprueba que tengamos libtool
AC_PROG_LIBTOOL
# Inicializa libtool (con él creamos la biblioteca libpractica)
LT_INIT
# Check es necesario para las pruebas unitarias.
AC_ARG_WITH([check],
    AS_HELP_STRING([--without-check],
                   [No usar check incluso si está disponible]))
# Si el usuario quiere check, vemos si está disponible.
AS_IF([test "x$with_check" != "xno"],
      [PKG_CHECK_MODULES([CHECK], [check],
                         [have_check=yes], [have_check=no])],
      [have_check=no])
# Si check está disponible...
AS_IF([test "x$have_check" = "xyes"],
      # Lo usamos si el usuario no pidió --withouth-check.
      [],
      # Error: el usuario lo pidió, pero no está.
      [AS_IF([test "x$with_check" = "xyes"],
             [AC_MSG_ERROR([check no está disponible]) ]) ])
# Doxygen para la documentación
AC_CHECK_PROGS([DOXYGEN], [doxygen])
AS_IF([test -z "$DOXYGEN"],
      [have_doxygen=no],
      [have_doxygen=yes])
AS_IF([test "x$have_doxygen" = "xno"],
      [AC_MSG_WARN([Doxygen no encontrado - no se generará la documentación]) ])
AM_CONDITIONAL([HAVE_DOXYGEN], 
               [test -n "$DOXYGEN"])
AM_COND_IF([HAVE_DOXYGEN], [AC_CONFIG_FILES([doc/doxyfile]) ])
# Le pedimos que genere los Makefiles
AC_CONFIG_FILES([ Makefile ])
# Y lo generamos
AC_OUTPUT
