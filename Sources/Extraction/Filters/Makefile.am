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

lib_LTLIBRARIES = libfilters.la

# ---------------------------------------------------------------------------
# Config/settings
# ---------------------------------------------------------------------------

libfilters_la_CFLAGS = -I$(SOURCES_DIR)

# ---------------------------------------------------------------------------
# Sources
# ---------------------------------------------------------------------------

libfilters_la_SOURCES  = AbsoluteContrast.c Equalizer.c InnerMask.c
libfilters_la_SOURCES += OrientedSmoother.c Thinner.c ClippedContrast.c
libfilters_la_SOURCES += HillOrientation.c LinesByOrientation.c
libfilters_la_SOURCES += RelativeContrast.c ThresholdBinarizer.c
libfilters_la_SOURCES += CrossRemover.c ImageInverter.c LocalHistogram.c
libfilters_la_SOURCES += SegmentationMask.c VotingFilter.c

# ---------------------------------------------------------------------------
# End
# ---------------------------------------------------------------------------
