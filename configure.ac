AC_INIT([The Powder Toy], 89.0-273.0, [https://github.com/simtr/The-Powder-Toy/issues], powder, [http://powdertoy.co.uk/])

AC_ARG_ENABLE(lua,   [  --disable-lua           turn off lua scripting support], withlua=$enableval)
AC_ARG_ENABLE(lua,   [  --disable-sdl           do not use SDL for rendering], withlua=$enableval)
AC_ARG_ENABLE(lua,   [  --enable-debug          turn on a few debug features], withdebug=$enableval)
AC_ARG_ENABLE(64bit, [  --disable-64bit         force 32-bit executable], with64bit=$enableval)
AC_ARG_ENABLE(sse,   [  --disable-sse           force non-SSE executable], withsse=$enableval)
AC_ARG_ENABLE(sse2,  [  --disable-sse2          force non-SSE2 executable], withsse2=$enableval)
AC_ARG_ENABLE(sse3,  [  --disable-sse3          force non-SSE3 executable], withsse3=$enableval)

AC_PROG_CC
AC_PROG_CC_STDC
AC_PROG_CXX
AC_LANG(C++)

CXXFLAGS="$CXXFLAGS -std=c++98"
CPPFLAGS="$CPPFLAGS -DUSE_STDINT -D_GNU_SOURCE -D_REENTRANT -D_POSIX_C_SOURCE=2000112L -Isrc -Idata"

AC_DEFUN(AC_TEST_ADD_CXXFLAG,[
	s_cppflags="$CXXFLAGS"
	CXXFLAGS="$CXXFLAGS $1"
	AC_MSG_CHECKING($2)
	AC_COMPILE_IFELSE([AC_LANG_PROGRAM([])],
		[AC_MSG_RESULT([yes])],
		[
			AC_MSG_RESULT([no])
			CXXFLAGS="$s_cppflags"
		]
	)
])

AC_DEFUN(AC_TEST_ASSERT_CXXFLAG,[
	CXXFLAGS="$CXXFLAGS $1"
	AC_MSG_CHECKING($2)
	AC_COMPILE_IFELSE([AC_LANG_PROGRAM([])],
		[AC_MSG_RESULT([yes])],
		[
			AC_MSG_RESULT([no])
			AC_MSG_ERROR([$3])
		]
	)
])

if test "$with64bit" == no; then
	AC_TEST_ASSERT_CXXFLAG(-m32, [whether we are able to compile for a 32-bit target], [unable to compile for selected architecture])
else
	if test "$with64bit" == yes; then
		AC_TEST_ASSERT_CXXFLAG(-m64, [whether we are able to compile for a 64-bit target], [unable to compile for selected architecture])
		CPPFLAGS="$CPPFLAGS -D_64BIT"
	else
		s_cppflags="$CXXFLAGS"
		CXXFLAGS="$CXXFLAGS -m64"
		AC_MSG_CHECKING([whether we are able to compile for a 64-bit target])
		AC_COMPILE_IFELSE([AC_LANG_PROGRAM([])],
			[
				AC_MSG_RESULT([yes])
				CPPFLAGS="$CPPFLAGS -D_64BIT"
			],
			[
				AC_MSG_RESULT([no])
				CXXFLAGS="$CXXFLAGS -m32"
				AC_MSG_CHECKING([whether we are able to compile for a 32-bit target])
			
				AC_COMPILE_IFELSE([AC_LANG_PROGRAM([])],
					[AC_MSG_RESULT([yes])],
					[
						AC_MSG_RESULT([no])
						CXXFLAGS="$s_cppflags"
					]
				)
			]
		)
	fi
fi

if test "$withsse" != no; then
	AC_TEST_ADD_CXXFLAG(-msse,[whether we are able to compile for an sse target])
	if test "$withsse2" != no; then
		AC_TEST_ADD_CXXFLAG(-msse2,[whether we are able to compile for an sse2 target])
		if test "$withsse3" != no; then
			AC_TEST_ADD_CXXFLAG(-msse3,[whether we are able to compile for an sse3 target])
		fi
	fi
fi

AC_TEST_ASSERT_CXXFLAG(-fkeep-inline-functions, [whether -fkeep-inline-functions is supported], [-fkeep-inline-functions is not supported])

AC_HAVE_LIBRARY(z, , [AC_MSG_ERROR([No libz found])])
AC_HAVE_LIBRARY(bz2, , [AC_MSG_ERROR([No libbz2 found])])
AC_HAVE_LIBRARY(pthread, , [AC_MSG_ERROR([No libpthread found])])
AC_HAVE_LIBRARY(m, , [AC_MSG_ERROR([No libm found])])
LDFLAGS="$LDFLAGS -lz -lbz2 -lpthread -lm"

if test "$withlua" != no; then
	AC_CHECK_LIB(lua5.1, main,
		[LDFLAGS="$LDFLAGS -llua5.1"],
		[
			AC_HAVE_LIBRARY(lua51,
				[LDFLAGS="$LDFLAGS -llua51"],
				[
					AC_HAVE_LIBRARY(lua,
						[LDFLAGS="$LDFLAGS -llua"],
						[AC_MSG_ERROR([No liblua found])]
					)
				]
			)
		]
	)
	AC_CHECK_HEADER(lua.h, ,
		[
			CPPFLAGS="$CPPFLAGS -I/usr/include/lua5.1"
			AS_UNSET(ac_cv_header_lua_h)
			AC_CHECK_HEADER(lua.h, , [AC_MSG_ERROR([No lua.h found])])
		]
	)
	CPPFLAGS="$CPPFLAGS -DLUACONSOLE"
	AC_SUBST(luasocket,true)
fi

if test "$withdebug" == yes; then
	CPPFLAGS="$CPPFLAGS -DDEBUG"
	CFLAGS="$CFLAGS -g"
	CXXFLAGS="$CXXFLAGS -g"
fi

if test "$withsdl" != no; then
	AC_HAVE_LIBRARY(SDLmain, , [AC_MSG_ERROR([No libSDLmain found])])
	AC_HAVE_LIBRARY(SDL, , [AC_MSG_ERROR([No libSDL found])])
	CPPFLAGS="$CPPFLAGS -DUSE_SDL"
	LDFLAGS="$LDFLAGS -lSDLmain -lSDL"
fi

if test "$withfft" != no; then
	AC_HAVE_LIBRARY(fftw3f, , [AC_MSG_ERROR([No libfftw3f found])])
	CPPFLAGS="$CPPFLAGS -DGRAVFFT"
	LDFLAGS="$LDFLAGS -lfftw3f"
fi

if test "$EXEEXT" == .exe; then
	echo lel
else	
	LDFLAGS="$LDFLAGS -lX11"
	CPPFLAGS="$CPPFLAGS -DLIN"
fi

CPPFLAGS="$CPPFLAGS -DSTABLE"
AC_OUTPUT(Makefile)
