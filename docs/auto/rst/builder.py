# -*- coding: utf-8 -*-
"""
    sphinxcontrib.builders.rst
    ~~~~~~~~~~~~~~~~~~~~~~~~~~
    ReST Sphinx builder.
    :copyright: Copyright 2012-2013 by Freek Dijkstra.
    :license: BSD, see LICENSE.txt for details.
"""

from __future__ import (print_function, unicode_literals, absolute_import)

import codecs
from os import path

from docutils.io import StringOutput

from sphinx.builders import Builder
from sphinx.util.osutil import ensuredir, os_path, SEP

def get_text(e):
    return ''.join(str(c) for c in e.children)

def gen_signature(s, indent):
    def g(e, additional):
        if e.tagname == 'desc_signature':
            pass
        elif e.tagname == 'desc_annotation':
            a = get_text(e).strip()
            if a == 'property':
                additional.append(':%s:'%a)
            #else:
                #print('A ', a )
            return ''
        elif e.tagname == 'desc_name':
            return get_text(e)
        elif e.tagname == 'desc_addname':
            return get_text(e)
        elif e.tagname == 'desc_parameterlist':
            # TODO: finish
            
            return '(%s)'%(', '.join(get_text(c) for c in e.children if c.tagname == 'desc_parameter'))
        elif e.tagname == 'desc_returns':
            return ' -> '+get_text(e)
        else:
            print( 'Unknown signature tag ', e.tagname )
        sign = ''
        for c in e.children:
            sign += g(c, additional)
        return sign
    
    additional = []
    for c in s.children:
        if c.tagname == 'desc_signature':
            sign = g(c, additional)
    sign += '\n'
    for a in additional:
        sign += indent + str(a) + '\n'
    return sign


def gen(e, writer, indent='', hide_paragraph=True):
    if e.tagname == 'document':
        pass
    elif e.tagname == 'index':
        return
    elif e.tagname == 'paragraph':
        if not hide_paragraph:
            writer.write('\n%s\n\n'%(indent+get_text(e)))
        return
    elif e.tagname == 'desc':
        writer.write('\n'+indent+'.. %s:%s:: '%(e.attributes['domain'], e.attributes['desctype']))
        indent = 3 * ' ' + indent
        writer.write(gen_signature(e, indent))
    elif e.tagname == 'desc_signature':
        return
    elif e.tagname == 'desc_content':
        hide_paragraph = False
    elif e.tagname == 'enumerated_list':
        print( e.parent )
        indent = indent + '* '
    elif e.tagname == 'list_item':
        hode_paragraph = False
    else:
        print( 'Unknown tag', e.tagname )
        return
    # Recurse
    for c in e.children:
        gen(c, writer, indent=indent, hide_paragraph=hide_paragraph)

class RstBuilder(Builder):
    name = 'rst'
    format = 'rst'
    file_suffix = '.rst'

    def init(self):
        """Load necessary templates and perform initialization."""
        if self.config.rst_file_suffix is not None:
            self.file_suffix = self.config.rst_file_suffix

    def prepare_writing(self, docnames):
        pass

    def write_doc(self, docname, doctree):
        print(docname, type(doctree))
        
        outfilename = path.join(self.outdir, docname+self.file_suffix)
        # print "write(%s,%s) -> %s" % (type(doctree), type(destination), outfilename)
        ensuredir(path.dirname(outfilename))
        try:
            f = codecs.open(outfilename, 'w', 'utf-8')
            try:
                gen(doctree, f)
            finally:
                f.close()
        except (IOError, OSError) as err:
            self.warn("error writing file %s: %s" % (outfilename, err))

    def finish(self):
        pass
