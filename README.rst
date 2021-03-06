Release: 20130609

Embtextf ("Embedded System Text Formatting") is a collection of functions
supporting \*printf(3c) and numeric formatting functionality on embedded
devices with highly constrained memory.  It derives from functions
originally provided in msp430-libc from the `MSPGCC`_ project.

Embtextf features:

* The base embtextf_vuprintf() function supports \*printf(3c)
  compatible output through a caller-provided callback function that
  handles each formatted character as it is produced.  This approach
  eliminates the need for large internal buffers to hold the
  constructed data;

* The format-string capabilities cover most non-floating-point format
  specifiers and modifiers, with some compile-time control to mediate
  between features and required code space;

* Additional functions for generating base-2 through base-36 representations
  of standard C integer types;

* Option to build ISO C-compatible wrappers that replace libc functionality
  with embtextf implementations, saving up to 20KB of relative to other libc
  implementations;

* The entire family of \*printf(3c) functions takes between 1KB and 3KB of
  code depending on target processor and feature selection.

The conversions operate on native C types, abstracting away from word size
and byte order. The module has been tested on both 16- and 32-bit
microcontrollers.

Each provided function is prefixed with ``embtextf_`` to isolate it from
both the toolchain and application namespaces.  This allows embtextf to
co-exist with toolchains like `mspgcc`_, which provide the same
functionality in a compatible way, and others like Code Composer Studio or
toolchains using `newlib`_ which provide similarly named functions with
different semantics, interfaces, or memory expectations.  The application
program can use the preprocessor to redirect unqualified names to the
embtextf implementations.

Please see the `documentation`_, `issue tracker`_, and
`homepage`_ on github.  Get a copy using git::

 git clone git://github.com/pabigot/embtextf.git

or by downloading the master branch via: https://github.com/pabigot/embtextf/tarball/master

Copyright 2011-2013, Peter A. Bigot.  embtextf_vuprintf() contains material
copyright 2006-2011, Chris Liechti.  Licensed under `BSD-3-Clause`_.

.. _documentation: http://pabigot.github.com/embtextf/
.. _issue tracker: http://github.com/pabigot/embtextf/issues
.. _homepage: http://github.com/pabigot/embtextf
.. _BSD-3-Clause: http://www.opensource.org/licenses/BSD-3-Clause
.. _MSPGCC: http://sourceforge.net/projects/mspgcc/
.. _newlib: http://sourceware.org/newlib/
