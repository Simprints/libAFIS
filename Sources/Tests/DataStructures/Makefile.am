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

lib_LTLIBRARIES = libdatastructures.la
lib_LIBRARIES   = libdatastructures.a

# ---------------------------------------------------------------------------
# Config/settings
# ---------------------------------------------------------------------------

local_cflags = -I$(SOURCES_DIR)/Utils -I$(SOURCES_DIR)/Utils/Unity

libdatastructures_la_CFLAGS = $(local_cflags)
libdatastructures_a_CFLAGS  = $(local_cflags)

# ---------------------------------------------------------------------------
# Sources
# ---------------------------------------------------------------------------

local_sources = Test_DataStructures.c TestRunner_DataStructures.c

libdatastructures_la_SOURCES = $(local_sources)
libdatastructures_a_SOURCES  = $(local_sources)

# ---------------------------------------------------------------------------
# End
# ---------------------------------------------------------------------------
