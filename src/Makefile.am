## Makefile.am -- Process this file with automake to produce Makefile.in
bin_PROGRAMS = yasa scorecorpora

yasa_CXXFLAGS = -I$(top_srcdir)/lib/libyasa

yasa_LDADD = $(top_builddir)/lib/libyasa/libyasa.a
#-L$(top_builddir)/lib/libyasa/ -ljapa

yasa_SOURCES = main.cc

#######
scorecorpora_CXXFLAGS = -I$(top_srcdir)/lib/libyasa

scorecorpora_LDADD = $(top_builddir)/lib/libyasa/libyasa.a

scorecorpora_SOURCES = scorecorpora.cc

