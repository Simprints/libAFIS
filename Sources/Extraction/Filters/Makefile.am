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

all-local:: SOURCES

SOURCES: Makefile
	@rm -f $@
	@echo ">>> Generating $@"
	@echo "# Generated from $(subdir)/Makefile.am" >> $@
	@d=`basename $(subdir)`;\
	 for s in $(srcs); do \
		echo "srcs += $$d/$$s"; done           >> $@
	@echo "# End"                                  >> $@

# ---------------------------------------------------------------------------
# Sources
# ---------------------------------------------------------------------------

srcs  = AbsoluteContrast.c Equalizer.c InnerMask.c OrientedSmoother.c
srcs += Thinner.c ClippedContrast.c HillOrientation.c LinesByOrientation.c
srcs += RelativeContrast.c ThresholdBinarizer.c CrossRemover.c
srcs += ImageInverter.c LocalHistogram.c SegmentationMask.c VotingFilter.c

# ---------------------------------------------------------------------------
# End
# ---------------------------------------------------------------------------
