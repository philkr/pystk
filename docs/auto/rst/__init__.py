# -*- coding: utf-8 -*-
"""
    sphinxcontrib.restbuilder
    =========================
    Sphinx extension to output reST files.
    .. moduleauthor:: Freek Dijkstra <software@macfreek.nl>
    :copyright: Copyright 2012-2013 by Freek Dijkstra.
    :license: BSD, see LICENSE.txt for details.
"""

from __future__ import (print_function, unicode_literals, absolute_import)

from sphinx.builders import Builder
from sphinx.writers.text import STDINDENT
from .builder import RstBuilder



def setup(app):
    app.require_sphinx('1.0')
    app.add_builder(RstBuilder)
    app.add_config_value('rst_file_suffix', ".rst", False)
