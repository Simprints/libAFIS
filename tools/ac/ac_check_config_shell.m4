# -*- m4 -*-
#
# $Id$
#
# Blame: Jordan Hrycaj <jordan@teddy-net.com>

# ---------------------------------------------------------------------------
# Check environment for certain Bourne shell quirks
# ---------------------------------------------------------------------------

AC_DEFUN([AC_CHECK_CONFIG_SHELL],[
  have_bash=no
  case $CONFIG_SHELL in */bash) have_bash=yes ; esac

  need_config_shell=no
  case $build_os in
  *UnixWare*) test $have_bash = no &&
	      need_config_shell="<path-to-bash>"
  esac
  case $host_os in
  *UnixWare*) test $have_bash = no &&
              need_config_shell="<path-to-bash>"
  esac

  if test $need_config_shell != no
  then
    for d in /sbin /bin /usr/bin /usr/local/bin
    do
	test -x $d/bash || continue
	need_config_shell=$d/bash
	break
    done

    m="Please set the environment variable CONFIG_SHELL"
    n="export CONFIG_SHELL; CONFIG_SHELL=$need_config_shell"
    AC_MSG_ERROR([$m, e.g. as "$n"])
  fi
])

# ---------------------------------------------------------------------------
# End
# ---------------------------------------------------------------------------
