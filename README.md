# Carmageddon 1 disassembly [![Build Status](https://travis-ci.org/jeff-1amstudios/c1-disassembly.svg?branch=master)](https://travis-ci.org/jeff-1amstudios/c1-disassembly) [![Gitter chat](https://badges.gitter.im/gitterHQ/gitter.png)](https://gitter.im/carma-disassembly/)

In 1997, [Carmageddon 1](https://en.wikipedia.org/wiki/Carmageddon), a fun destruction/racing open-world game was first released.

In 2014, Watcom debugging symbols for an earlier internal build were discovered on the [Splat Pack](http://carmageddon.wikia.com/wiki/Carmageddon_Splat_Pack) expansion CD release. The symbols unfortunately did not match any known released executable, meaning they were interesting but not immediately usable to reverse engineer the game.

This is what it looked like from the Watcom debugger - the names of all the methods were present but the code location they were pointing to was junk:
[![watcom-debugger](http://1amstudios.com/img/watcom-debugger.jpg)]

More details are in [_Carmageddon 1 symbols dumped_](http://1amstudios.com/2014/12/02/carma1-symbols-dumped/)

In 2018, a couple of members of the Carmageddon community did the painstaking work of manually matching up the functions and data structures in the executable to the debugging symbols. 

And now we begin the next step - reversing the assembly code back into _as original as possible_ C code.
