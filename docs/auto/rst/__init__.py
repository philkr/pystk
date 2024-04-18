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
from sphinx.application import Sphinx
from .builder import RstBuilder
from .property import TypedPropertyDocumenter, EnumAttributeDocumenter



def setup(app: Sphinx):
    app.require_sphinx('1.0')
    app.add_builder(RstBuilder)
    app.add_config_value('rst_file_suffix', ".rst", False)
    app.add_autodocumenter(TypedPropertyDocumenter)
    app.add_autodocumenter(EnumAttributeDocumenter)
