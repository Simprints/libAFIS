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

local_sources  = TestRunner_HillOrientation.c TestRunner_LocalHistogram.c
local_sources += TestRunner_Thinner.c TestRunner_LinesByOrientation.c
local_sources += TestRunner_OrientedSmoother.c TestRunner_VotingFilter.c

librunners_la_SOURCES = $(local_sources)
librunners_a_SOURCES  = $(local_sources)

# ---------------------------------------------------------------------------
# End
# ---------------------------------------------------------------------------
