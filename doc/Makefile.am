# http://www.gnu.org/software/autoconf-archive/ax_prog_doxygen.html
include doxygen.am

DOC_SRC = mainpage.dox install.dox
EXTRA_DIST = $(DOC_SRC)

# All the files have extensions, so this pattern excludes the search subdir
html_DATA = @DX_DOCDIR@/html/*.*

# Add the search subdir separately with all its contents
htmlsearchdir = $(htmldir)/search
htmlsearch_DATA = @DX_DOCDIR@/html/search/*

$(html_DATA) $(htmlsearch_DATA): doxygen-doc

CLEANFILES = $(DX_CLEANFILES)
