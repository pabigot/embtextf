Release: 20130322

Embtextf ("Embedded System Text Formatting") is a collection of functions
supporting \*printf(3c) and numeric formatting functionality on embedded
devices with highly constrained memory.  It derives from functions
originally provided in msp430-libc from the `MSPGCC`_ project.

Embtextf features:

* Output is generated using a callback function to produce the generated
  text, eliminating large memory buffers on the heap or stack;

* Most standard printf(3c) format string expressions are supported;

* Additional functions for generating base-2 through base-36 representations
  of standard C integer types;

* Highly space-efficient implementation (between 1KB and 2.5KB for the
  entire family of \*printf() functions, depending on feature selection)

Each provided function is prefixed with ``embtextf_`` to isolate it from both
the toolchain and application namespaces.  This allows embtextf to co-exist
with toolchains like `mspgcc`_, which provide the same functionality in a
compatible way, and others like Code Composer Studio which provide similarly
named functions but with different semantics or interfaces.  The application
program can use the preprocessor to redirect unqualified names to the
embtextf implementations.

  **WARNING** This should be considered a beta release of embtextf.  The
  functionality is complete and reliable.  However, public function names,
  the set of available wrappers, and the build approach may change in a
  future release.

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
