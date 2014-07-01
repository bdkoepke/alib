SUBDIRS = src

alibdocdir = $(prefix)/doc/alib
alibdoc_DATA = \
	README\
	COPYING\
	AUTHORS\
	ChangeLog\
	INSTALL\
	NEWS

EXTRA_DIST = $(alib_DATA)

ACLOCAL_AMFLAGS = -I m4

# Remove doc directory on uninstall
uninstall-local:
	-rm -r $(alibdocdir)
