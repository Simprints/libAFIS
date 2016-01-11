# -*- makefile-automake -*-
#
# Build library
#
# $Id$
#
# Blame: Jordan Hrycaj <jordan@teddy-net.com>

SUBDIRS= IO Misc Unity

# ---------------------------------------------------------------------------
# Target
# ---------------------------------------------------------------------------

lib_LTLIBRARIES = libutils.la
lib_LIBRARIES   = libutils.a

# ---------------------------------------------------------------------------
# Config/settings
# ---------------------------------------------------------------------------

local_cflags = -I../..

libutils_la_CFLAGS = $(local_cflags)
libutils_a_CFLAGS  = $(local_cflags)

libutils_la_LIBADD = IO/libio.la Misc/libmisc.la Unity/libunity.la
libutils_a_LIBADD  = IO/libio.a  Misc/libmisc.a  Unity/libunity.a

# ---------------------------------------------------------------------------
# Sources
# ---------------------------------------------------------------------------

local_sources =

libutils_la_SOURCES = $(local_sources)
libutils_a_SOURCES  = $(local_sources)

# ---------------------------------------------------------------------------
# End
# ---------------------------------------------------------------------------
