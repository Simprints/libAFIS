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

lib_LTLIBRARIES = librunners.la
lib_LIBRARIES   = librunners.a

# ---------------------------------------------------------------------------
# Config/settings
# ---------------------------------------------------------------------------

local_cflags = -I$(SOURCES_DIR)/Utils -I$(SOURCES_DIR)/Utils/Unity

librunners_la_CFLAGS = $(local_cflags)
librunners_a_CFLAGS  = $(local_cflags)

# ---------------------------------------------------------------------------
# Sources
# ---------------------------------------------------------------------------

local_sources  = TestRunner_DotRemover.c

librunners_la_SOURCES = $(local_sources)
librunners_a_SOURCES  = $(local_sources)

# ---------------------------------------------------------------------------
# End
# ---------------------------------------------------------------------------
