from sphinx.ext.autodoc import PropertyDocumenter, AttributeDocumenter, ClassLevelDocumenter, SUPPRESS
from sphinx.util import inspect
from typing import Any, Callable, Dict, Iterator, List, Sequence, Set, Tuple, Union


class TypedPropertyDocumenter(PropertyDocumenter):  # type: ignore
    """
    Specialized Documenter subclass for properties.
    """
    objtype = 'typedproperty'
    directivetype = 'method'
    member_order = 60

    # before AttributeDocumenter
    priority = PropertyDocumenter.priority + 10

    def document_members(self, all_members: bool = False) -> None:
        pass

    def format_signature(self, **kwargs) -> str:
        from inspect import signature, getdoc
        sig = super().format_signature(**kwargs)
        if not sig:
            import re
            sig = re.sub('(.*) ->', '() ->', getdoc(self.object.fget))
        return sig

    def add_directive_header(self, sig: str) -> None:
        super().add_directive_header(sig)


class EnumAttributeDocumenter(AttributeDocumenter):  # type: ignore
    """
    Specialized Documenter subclass for attributes.
    """
    objtype = 'attribute'
    priority = AttributeDocumenter.priority + 5

    def add_directive_header(self, sig: str) -> None:
        ClassLevelDocumenter.add_directive_header(self, sig)
        sourcename = self.get_sourcename()
        if not self.options.annotation:
            if not self._datadescriptor:
                try:
                    objrepr = str(int(self.object))
                except ValueError:
                    pass
                else:
                    self.add_line('   :annotation: = ' + objrepr, sourcename)
        elif self.options.annotation is SUPPRESS:
            pass
        else:
            self.add_line('   :annotation: %s' % self.options.annotation, sourcename)

    # def add_content(self, more_content: Any, no_docstring: bool = False) -> None:
    #     ClassLevelDocumenter.add_content(self, more_content, no_docstring)
