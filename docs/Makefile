# Minimal makefile for Sphinx documentation
#

# You can set these variables from the command line.
SPHINXOPTS    = -a
SPHINXBUILD   = sphinx-build
SPHINXPROJ    = pystk
SOURCEDIR     = .
BUILDDIR      = _build

# Put it first so that "make" without argument is like "make help".
help:
	@$(SPHINXBUILD) -M help "$(SOURCEDIR)" "$(BUILDDIR)" $(SPHINXOPTS) $(O)

.PHONY: help Makefile

# Catch-all target: route all unknown targets to Sphinx using the new
# "make mode" option.  $(O) is meant as a shortcut for $(SPHINXOPTS).
%: Makefile
	@$(SPHINXBUILD) -M $@ "$(SOURCEDIR)" "$(BUILDDIR)" $(SPHINXOPTS) $(O)

rst: Makefile
	@$(SPHINXBUILD) -M rst "$(SOURCEDIR)/auto" "$(BUILDDIR)" $(SPHINXOPTS) $(O)
	cp -f "$(BUILDDIR)"/rst/*.grst auto/

