# -*- makefile-automake -*-
#
# Build library
#
# $Id$
#
# Blame: Jordan Hrycaj <jordan@teddy-net.com>

SUBDIRS = runners

# ---------------------------------------------------------------------------
# Target
# ---------------------------------------------------------------------------

lib_LTLIBRARIES = libmodel.la
lib_LIBRARIES   = libmodel.a

# ---------------------------------------------------------------------------
# Config/settings
# ---------------------------------------------------------------------------

local_cflags  = -I$(SOURCES_DIR) -I$(SOURCES_DIR)/Utils/Unity


libmodel_la_CFLAGS = $(local_cflags)
libmodel_a_CFLAGS  = $(local_cflags)

# ---------------------------------------------------------------------------
# Sources
# ---------------------------------------------------------------------------

local_sources  = Test_DotRemover.c

libmodel_la_SOURCES = $(local_sources)
libmodel_a_SOURCES  = $(local_sources)

# ---------------------------------------------------------------------------
# End
# ---------------------------------------------------------------------------
