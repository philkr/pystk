from sphinx.ext.autodoc import PropertyDocumenter, AttributeDocumenter, ClassLevelDocumenter, SUPPRESS


class TypedPropertyDocumenter(PropertyDocumenter):  # type: ignore
    """
    Specialized Documenter subclass for properties.
    """
    objtype = 'typedproperty'
    directivetype = 'method'
    member_order = 60

    # before AttributeDocumenter
    priority = PropertyDocumenter.priority + 10

    def format_signature(self, **kwargs) -> str:
        from inspect import signature, getdoc
        sig = super().format_signature(**kwargs)
        if not sig:
            import re
            sig = re.sub('(.*) ->', '() ->', getdoc(self.object.fget))
        return sig

    def add_directive_header(self, sig: str) -> None:
        super().add_directive_header(sig)
        sourcename = self.get_sourcename()
        self.add_line('   :property:', sourcename)


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
