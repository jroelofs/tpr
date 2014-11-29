tpr
=====

USB programmer for the Teensy3.1

Copyright 2014, Jonathan Roelofs <jonathan@codesourcery.com>

This is a third-party program loader for the Teensy 3.1, which is an ARM
Cortex-M4 based USB development board. Teensy's can be purchased from:
https://www.pjrc.com/store/teensy31.html

Build
=====

    $ mkdir build
    $ cd build
    $ cmake ../
    $ make

Usage
=====

    $ tpr -mcpu=mkd20x256 <foo.hex>
