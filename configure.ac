AC_INIT([The Powder Toy], 89.0-273.0, [https://github.com/simtr/The-Powder-Toy/issues], powder, [http://powdertoy.co.uk/])

AC_ARG_ENABLE(lua, [  --enable-lua            support lua scripting], [echo $enableval])

AC_PROG_CC
AC_PROG_CXX

AC_HAVE_LIBRARY(lua)
if test "$ac_cv_lib_lua_main" == yes; then
	llua="-llua"
else
	AC_CHECK_LIB(lua5.1, main)
	if test "$ac_cv_lib_lua5_1_main" == yes; then
		llua="-llua5.1"
	else
		AC_HAVE_LIBRARY(lua51)
		if test "$ac_cv_lib_lua51_main" == yes; then
			llua="-llua51"
		else
			AC_MSG_ERROR([No lua found])
		fi
	fi
fi

AC_SUBST(llua, $llua)
AC_SUBST(lsdl, "-lSDLmain -lSDL -lX11 -lrt")
AC_SUBST(lfftw3f, "-lfftw3f")
AC_SUBST(includes, -I/usr/include/SDL/)
AC_SUBST(use_stdint, -DUSE_STDINT)
AC_SUBST(gravfft, -DGRAVFFT)
AC_SUBST(luaconsole, -DLUACONSOLE)
AC_SUBST(use_sdl, -DUSE_SDL)
AC_SUBST(reltype, -DSTABLE)
AC_SUBST(debug, -DDEBUG)
AC_SUBST(features, "-m64 -msse2 -D_64BIT -DX86 -DX86_SSE2")
AC_SUBST(os, -DLIN)
AC_OUTPUT(Makefile)
