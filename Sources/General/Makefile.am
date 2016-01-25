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

srcs  = Angle.c BinaryMap.c Calc.c pgm.c PointF.c
srcs += Range.c Size.c Array.c BlockMap.c List.c
srcs += Point.c PolarPoint.c RectangleC.c SizeF.c

# ---------------------------------------------------------------------------
# End
# ---------------------------------------------------------------------------
