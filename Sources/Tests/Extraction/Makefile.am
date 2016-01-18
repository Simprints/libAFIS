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

lib_LTLIBRARIES = libextraction.la

# ---------------------------------------------------------------------------
# Config/settings
# ---------------------------------------------------------------------------

libextraction_la_CFLAGS = -I$(SOURCES_DIR) -I$(SOURCES_DIR)/Utils/Unity

# ---------------------------------------------------------------------------
# Sources
# ---------------------------------------------------------------------------

libextraction_la_SOURCES  = Filters/runners/TestRunner_HillOrientation.c
libextraction_la_SOURCES += Filters/runners/TestRunner_OrientedSmoother.c
libextraction_la_SOURCES += Filters/runners/TestRunner_LinesByOrientation.c
libextraction_la_SOURCES += Filters/runners/TestRunner_Thinner.c
libextraction_la_SOURCES += Filters/runners/TestRunner_LocalHistogram.c
libextraction_la_SOURCES += Filters/runners/TestRunner_VotingFilter.c

libextraction_la_SOURCES += Filters/Test_HillOrientation.c
libextraction_la_SOURCES += Filters/Test_LocalHistogram.c
libextraction_la_SOURCES += Filters/Test_Thinner.c
libextraction_la_SOURCES += Filters/Test_LinesByOrientation.c
libextraction_la_SOURCES += Filters/Test_OrientedSmoother.c
libextraction_la_SOURCES += Filters/Test_VotingFilter.c

libextraction_la_SOURCES += Model/runners/TestRunner_DotRemover.c

libextraction_la_SOURCES += Model/Test_DotRemover.c

# ---------------------------------------------------------------------------
# End
# ---------------------------------------------------------------------------
