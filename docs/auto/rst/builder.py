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
from sphinx.builders import Builder
from sphinx.util.osutil import ensuredir, os_path, SEP


def get_text(e):
    import docutils
    return ''.join(str(c) if isinstance(c, docutils.nodes.Text) else get_text(c) for c in e.children)


def gen_signature(s, indent):
    def all_children(e):
        r = [e]
        for c in e.children:
            r.extend(all_children(c))
        return r

    for c in s.children:
        if c.tagname == 'desc_signature':
            all_c = all_children(c)
            break
    additional = []
    desc_name = ''
    desc_addname = ''
    desc_parameterlist = []
    desc_returns = None
    for e in all_c:
        if e.tagname == 'desc_annotation':
            a = get_text(e).strip()
            if a == 'property':
                additional.append(':%s:'%a)
            elif a == 'static':
                additional.append(':staticmethod:')
            elif a == 'class':
                pass
            else:
                additional.append(':annotation: '+a)
                # print(c)
        elif e.tagname == 'desc_name':
            desc_name = get_text(e)
        elif e.tagname == 'desc_addname':
            desc_addname = get_text(e)
        elif e.tagname == 'desc_parameterlist':
            desc_parameterlist = [get_text(c) for c in e.children if c.tagname == 'desc_parameter']
        elif e.tagname == 'desc_returns':
            desc_returns = get_text(e)
    if desc_returns is not None and desc_name != '__init__':
        sign = '%s%s (%s) -> %s\n'%(desc_addname, desc_name, ', '.join(desc_parameterlist), desc_returns)
    elif desc_parameterlist:
        sign = '%s%s (%s)\n'%(desc_addname, desc_name, ', '.join(desc_parameterlist))
    else:
        sign = '%s%s\n'%(desc_addname, desc_name)
    for a in additional:
        sign += indent + str(a) + '\n'
    return sign


def gen(e, writer, indent='', hide_paragraph=True):
    if e.tagname == 'document':
        pass
    elif e.tagname == 'index':
        return hide_paragraph
    elif e.tagname == 'paragraph':
        if not hide_paragraph:
            text = get_text(e)
            if 'Members:' in text:
                hide_paragraph = True
            else:
                writer.write('\n%s\n\n'%(indent+get_text(e)))
        return hide_paragraph
    elif e.tagname == 'desc':
        # if e.attributes['desctype'] == 'attribute':
        #     print(e.attributes['domain'], e.attributes['desctype'])
        #     print(e)
        writer.write('\n'+indent+'.. %s:%s:: '%(e.attributes['domain'], e.attributes['desctype']))
        indent = 3 * ' ' + indent
        writer.write(gen_signature(e, indent))
    elif e.tagname == 'desc_signature':
        return hide_paragraph
    elif e.tagname == 'desc_content':
        hide_paragraph = len(e.children) and 'Members:' in get_text(e.children[0])
    elif e.tagname == 'enumerated_list':
        indent = indent + '* '
    elif e.tagname == 'list_item':
        hide_paragraph = False
    elif e.tagname == 'block_quote':
        pass
    else:
        print('Unknown tag', e.tagname)
        return hide_paragraph
    # Recurse
    for c in e.children:
        hide_paragraph = gen(c, writer, indent=indent, hide_paragraph=hide_paragraph)


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

    def get_target_uri(self, docname: str, typ: str = None):
        return docname

    def write_doc(self, docname, doctree):
        outfilename = path.join(self.outdir, docname+self.file_suffix)
        # print "write(%s,%s) -> %s" % (type(doctree), type(destination), outfilename)
        # print('-'*20, docname, '-'*20)
        # print(doctree)
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
