# -*- makefile-automake -*-
#
# $Id$
#
# Blame: Jordan Hrycaj <jordan@teddy-net.com>

# SUBDIRS = General Matcher Utils Tests

SUBDIRS = Extraction General Matcher Utils

# ---------------------------------------------------------------------------
# Target
# ---------------------------------------------------------------------------

lib_LTLIBRARIES = libafis.la libutils.la

# ---------------------------------------------------------------------------
# Config/settings
# ---------------------------------------------------------------------------

libafis_la_CFLAGS  = -I$(SOURCES_DIR)
libutils_la_CFLAGS  = -I$(SOURCES_DIR)

# ---------------------------------------------------------------------------
# Sources for libafis
# ---------------------------------------------------------------------------

srcs =

include    General/SOURCES
include Extraction/SOURCES
include    Matcher/SOURCES

libafis_la_SOURCES = $(srcs)

# ---------------------------------------------------------------------------
# Sources for libutils
# ---------------------------------------------------------------------------

usrc =

include Utils/SOURCES

libutils_la_SOURCES = $(usrc)

# ---------------------------------------------------------------------------
# End
# ---------------------------------------------------------------------------
