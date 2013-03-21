Release: 20130321

Embtextf ("Embedded System Text Formatting") is a collection of functions
supporting *printf(3c) and numeric formatting functionality on embedded
devices with highly constrained memory

Embtextf features:

* Output generation without large internal buffers by using a callback
  function to process the generated text;

* Most standard printf(3c) format string expressions are supported;

* Additional functions for generating base-2 through base-36 representations
  of standard C integer types;

Each provided function is prefixed with @c embtextf_ to isolate it from both
the toolchain and application namespaces.  This allows embtextf to co-exist
with toolchains like `mspgcc`_, which provide the same functionality in a
compatible way, and others like Code Composer Studio which provide similarly
named functions but with different semantics or interfaces.  The application
program can use the preprocessor to redirect unqualified names to the
embtextf implementations.

Please see the `documentation`_, `issue tracker`_, and
`homepage`_ on github.  Get a copy using git::

 git clone git://github.com/pabigot/embtextf.git

or by downloading the master branch via: https://github.com/pabigot/embtextf/tarball/master

Copyright 2011-2013, Peter A. Bigot.  embtextf_vuprintf() contains material
copyright 2011, Chris Liechti.  Licensed under `BSD-3-Clause`_.

.. _documentation: http://pabigot.github.com/embtextf/
.. _issue tracker: http://github.com/pabigot/embtextf/issues
.. _homepage: http://github.com/pabigot/embtextf
.. _BSD-3-Clause: http://www.opensource.org/licenses/BSD-3-Clause
.. _MSPGCC: http://sourceforge.net/projects/mspgcc/
