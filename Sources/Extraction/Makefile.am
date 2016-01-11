# -*- makefile-automake -*-
#
# Build library
#
# $Id$
#
# Blame: Jordan Hrycaj <jordan@teddy-net.com>

SUBDIRS = Filters MinutiaeDetection Model

# ---------------------------------------------------------------------------
# Target
# ---------------------------------------------------------------------------

lib_LTLIBRARIES = libextraction.la

# ---------------------------------------------------------------------------
# Config/settings
# ---------------------------------------------------------------------------

libextraction_la_CFLAGS  = -I$(SOURCES_DIR)

libextraction_la_LIBADD  = Filters/libfilters.la
libextraction_la_LIBADD += MinutiaeDetection/libminutiaedetection.la
libextraction_la_LIBADD += Model/libmodel.la

# ---------------------------------------------------------------------------
# Sources
# ---------------------------------------------------------------------------

libextraction_la_SOURCES  = Extract.c

# ---------------------------------------------------------------------------
# End
# ---------------------------------------------------------------------------
