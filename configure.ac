AC_INIT([TBB-Community-Game], [1.0], [])


AC_CANONICAL_TARGET

AC_PROG_CC
AC_PROG_CXX
AC_PROG_INSTALL

AC_ARG_WITH([build-type],[--with-build-type=<build type>. Allows you to configure the type of build. Defaults to release. Acceptable values are debug, debug-sanitize, and release],
	[
		build_type=$withval
	],
	[
		build_type=release
	])
AC_SUBST([build_type])

AC_ARG_ENABLE([shared],[--enable-shared. Allows you to enable or disable the building of shared libraries],
	[
		lclib_cxx_build_shared=$enableval
	],
	[
		lclib_cxx_build_shared=yes
	])
AC_SUBST([lclib_cxx_build_shared])

AC_ARG_ENABLE([static],[--enable-static. Allows you to enable or disable the building of static archives],
	[
		lclib_cxx_build_static=$enableval
	],
	[
		lclib_cxx_build_static=yes
	])
AC_SUBST([lclib_cxx_build_shared])


shell=/bin/bash
AC_SUBST([shell])

os=${target_os}
AC_SUBST([os])

AC_CONFIG_FILES([Makefile])

AC_OUTPUT
