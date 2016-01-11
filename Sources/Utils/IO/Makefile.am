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

lib_LTLIBRARIES = libio.la
lib_LIBRARIES   = libio.a

# ---------------------------------------------------------------------------
# Config/settings
# ---------------------------------------------------------------------------

local_cflags = -I$(SOURCES_DIR)

libio_la_CFLAGS = $(local_cflags)
libio_a_CFLAGS  = $(local_cflags)

# ---------------------------------------------------------------------------
# Sources
# ---------------------------------------------------------------------------

local_sources  = ArrayIO.c BinaryMapIO.c BlockMapIO.c HistogramIO.c
local_sources += ImageIO.c SimpleDataTypesIO.c

libio_la_SOURCES = $(local_sources)
libio_a_SOURCES  = $(local_sources)

# ---------------------------------------------------------------------------
# End
# ---------------------------------------------------------------------------
