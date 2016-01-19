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

libextraction_la_CFLAGS  = -I$(SOURCES_DIR)

# ---------------------------------------------------------------------------
# Sources
# ---------------------------------------------------------------------------

libextraction_la_SOURCES  = Filters/AbsoluteContrast.c Filters/Equalizer.c
libextraction_la_SOURCES += Filters/InnerMask.c Filters/OrientedSmoother.c
libextraction_la_SOURCES += Filters/Thinner.c Filters/ClippedContrast.c
libextraction_la_SOURCES += Filters/HillOrientation.c
libextraction_la_SOURCES += Filters/LinesByOrientation.c
libextraction_la_SOURCES += Filters/RelativeContrast.c
libextraction_la_SOURCES += Filters/ThresholdBinarizer.c
libextraction_la_SOURCES += Filters/CrossRemover.c Filters/ImageInverter.c
libextraction_la_SOURCES += Filters/LocalHistogram.c
libextraction_la_SOURCES += Filters/SegmentationMask.c Filters/VotingFilter.c

libextraction_la_SOURCES += MinutiaeDetection/MinutiaeDetection.c

libextraction_la_SOURCES += Model/DotRemover.c Model/Minutia.c
libextraction_la_SOURCES += Model/Ridge.c Model/SkeletonBuilder.c

libextraction_la_SOURCES += Extract.c

# ---------------------------------------------------------------------------
# End
# ---------------------------------------------------------------------------
