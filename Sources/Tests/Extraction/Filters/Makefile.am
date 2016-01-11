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

lib_LTLIBRARIES = libfilters.la
lib_LIBRARIES   = libfilters.a

# ---------------------------------------------------------------------------
# Config/settings
# ---------------------------------------------------------------------------

local_cflags  = -I$(SOURCES_DIR) -I$(SOURCES_DIR)/Utils/Unity

libfilters_la_CFLAGS = $(local_cflags)
libfilters_a_CFLAGS  = $(local_cflags)

# ---------------------------------------------------------------------------
# Sources
# ---------------------------------------------------------------------------

local_sources  = Test_HillOrientation.c Test_LocalHistogram.c
local_sources += Test_Thinner.c Test_LinesByOrientation.c
local_sources += Test_OrientedSmoother.c Test_VotingFilter.c

libfilters_la_SOURCES = $(local_sources)
libfilters_a_SOURCES  = $(local_sources)

# ---------------------------------------------------------------------------
# End
# ---------------------------------------------------------------------------
