# -*- m4 -*-
#
# $Id$
#
# Blame: Jordan Hrycaj <jordan@teddy-net.com>

# ---------------------------------------------------------------------------
# Package and version helper
# ---------------------------------------------------------------------------

dnl Syntax: [copyleft]
AC_DEFUN([AC_CONFIG_INIT],[

  dnl initialise helpers
  AM_INIT_AUTOMAKE([-Wall no-define subdir-objects])
  AM_PROG_AR
  AC_CANONICAL_HOST
  AC_CHECK_CONFIG_SHELL

  pp="$PACKAGE"
  pv="$PACKAGE_VERSION"

  : ${SED:=sed}

  dnl n -- copyleft notice (optional)
  m4_ifvaln([$1],[y=`date -u '+%Y'`;
                  n=`echo "$1"|$SED 's/@YEAR@/'"$y"'/g'`
		  AC_DEFINE_UNQUOTED([PACKAGE_OWNER],
				     ["Copyleft (c) $n"],
                                     [vendor/copyleft string])])

  dnl b -- lib basename
  dnl o -- version octet: major minor kid
  dnl h -- version git-hash
  dnl d -- version date
  dnl t -- version time
  b=`expr "$pp" : '@<:@Ll@:>@ib\(@<:@^.@:>@*\)' \| "$pp"`
  o=`echo "$pv" | $SED -e 's/^@<:@^0-9@:>@*//' -e 's/-.*$//'`
  h=`expr "$pv" : '.*-\(@<:@^-@:>@*\)$'`
  d=`date -u +%Y-%m-%d`
  t=`date -u +%H:%M:%S`

  dnl a -- version major
  dnl i -- version minor
  dnl k -- version kid
  dnl p -- version patch level
  a=`expr "$pv" : '@<:@^0-9@:>@*\(@<:@0-9@:>@*\)'`
  i=`expr "$pv" : '@<:@^0-9@:>@*@<:@0-9@:>@*\.\(@<:@0-9@:>@*\)'`
  k=`expr "$pv" : '@<:@^0-9@:>@*@<:@0-9@:>@*\.@<:@0-9@:>@*\.\(@<:@0-9@:>@*\)'`
  p=`expr "$pv" : '@<:@^0-9@:>@*@<:@0-9@:>@*\.@<:@0-9@:>@*\.@<:@0-9@:>@*-\(@<:@0-9@:>@*\)'`

  _num_sanitise () {
     w=${1:-0}
     test 0 -le "$w" -a 256 -gt "$w" || w=255
     echo $w
  }

  a=`_num_sanitise $a`
  i=`_num_sanitise $i`
  k=`_num_sanitise $k`
  p=`_num_sanitise $p`
  n=`expr \( \( $a \* 256 + $i \) \* 256 + $k \) \* 256 + $p`

  PACKAGE_LIBNAME=$b
  PACKAGE_NUM=$n
  PACKAGE_MAJOR=$a
  PACKAGE_MINOR=$i

  AC_SUBST([PACKAGE_LIBNAME])
  AC_SUBST([PACKAGE_NUM])
  AC_SUBST([PACKAGE_MAJOR])
  AC_SUBST([PACKAGE_MINOR])

  AC_DEFINE_UNQUOTED([PACKAGE_MAJOR],
		     [$PACKAGE_MAJOR],
		     [Major package version])

  AC_DEFINE_UNQUOTED([PACKAGE_MINOR],
		     [$PACKAGE_MINOR],
		     [Minor package version])

  AC_DEFINE_UNQUOTED([PACKAGE_HASH],
		     ["$h"],
		     [Git hash identifier])

  AC_DEFINE_UNQUOTED([PACKAGE_LIBNAME],
		     ["$PACKAGE_LIBNAME"],
		     [Package library base name])

  AC_DEFINE_UNQUOTED([PACKAGE_NUM],
		     [$PACKAGE_NUM],
		     [Version octets as number])

  AC_DEFINE_UNQUOTED([PACKAGE_TAG],
		     ["$o"],
		     [Package version test])

  AC_DEFINE_UNQUOTED([PACKAGE_TAGX],
		     ["$o-$p"],
		     [Extended package version string])

  AC_DEFINE_UNQUOTED([PACKAGE_ISODATE],
		     ["$d"],
                     [Configuration date])

  AC_DEFINE_UNQUOTED([PACKAGE_ISOTIME],
		     ["$t"],
                     [Configuration time])
])

# ---------------------------------------------------------------------------
# End
# ---------------------------------------------------------------------------
