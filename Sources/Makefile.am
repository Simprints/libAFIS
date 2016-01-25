# -*- makefile-automake -*-
#
# $Id$
#
# Blame: Jordan Hrycaj <jordan@teddy-net.com>

# SUBDIRS = General Matcher Utils Tests

SUBDIRS = Extraction General Matcher Utils Tests

# ---------------------------------------------------------------------------
# Target
# ---------------------------------------------------------------------------

lib_LTLIBRARIES = libafis.la libutils.la libtest.la

# bin_PROGRAMS = all_tests extract

# ---------------------------------------------------------------------------
# Config/settings
# ---------------------------------------------------------------------------

libafis_la_CFLAGS  = -I$(SOURCES_DIR)
libutils_la_CFLAGS = -I$(SOURCES_DIR)
libtest_la_CFLAGS  = -I$(SOURCES_DIR) -I$(SOURCES_DIR)/Utils/Unity

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
# Sources for libtest
# ---------------------------------------------------------------------------

tsrc =

include Tests/SOURCES

libtest_la_SOURCES = $(tsrc)

# ---------------------------------------------------------------------------
# Linking test programmes
# ---------------------------------------------------------------------------

local_cflags = -I$(SOURCES_DIR) -I$(SOURCES_DIR)/Utils/Unity
local_libadd = libtest.la libafis.la libtest.la

#all_tests_SOURCES = Tests/all_tests.c
#all_tests_CFLAGS = $(local_cflags)
#all_tests_LDADD  = $(local_libadd)

#extract_SOURCES   = Tests/extract.c
#extract_CFLAGS   = $(local_cflags)
#extract_LDADD    = $(local_libadd)

# ---------------------------------------------------------------------------
# End
# ---------------------------------------------------------------------------
