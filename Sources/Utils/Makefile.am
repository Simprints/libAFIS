# -*- makefile-automake -*-
#
# Build library
#
# $Id$
#
# Blame: Jordan Hrycaj <jordan@teddy-net.com>

# ---------------------------------------------------------------------------
# Target
# ---------------------------------------------------------------------------

lib_LTLIBRARIES = libutils.la

# ---------------------------------------------------------------------------
# Config/settings
# ---------------------------------------------------------------------------

libutils_la_CFLAGS = -I$(SOURCES_DIR)

# ---------------------------------------------------------------------------
# Sources
# ---------------------------------------------------------------------------

libutils_la_SOURCES  = IO/ArrayIO.c IO/BinaryMapIO.c IO/BlockMapIO.c
libutils_la_SOURCES += IO/HistogramIO.c IO/ImageIO.c IO/SimpleDataTypesIO.c

libutils_la_SOURCES += Misc/binarise.c

libutils_la_SOURCES += Unity/unity.c Unity/unity_fixture.c

# ---------------------------------------------------------------------------
# End
# ---------------------------------------------------------------------------
