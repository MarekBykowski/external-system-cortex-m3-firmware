Readme
======

Prerequisites (Tools)
---------------------

To properly build External system firmware for a target product, the following tools are
required:

- Git
- [GNU Arm Embedded Toolchain ("6-2017-q2-update" or later)](https://developer.arm.com/open-source/gnu-toolchain/gnu-rm)
- GNU Make
- Python 3 (3.5.0 or later)

Prerequisites (CMSIS Libraries)
-------------------------------

External system firmware requires the use of components from the Cortex Microcontroller
System Interface Standard (CMSIS) Software Pack, specifically the CMSIS Core
and CMSIS Real-Time Operating System (RTOS) components. The CMSIS Software pack
is included as a Git submodule.

To retrieve the CMSIS Software pack, just initialize and update the submodule
of the repository.

    $> git submodule update --init

The required CMSIS components are now present and the correct version has been
selected.

Building Products
-----------------
To build a product the basic command format for invoking 'make' is:

    $> make [TARGET] <PRODUCT=<name>> [OPTIONS]

It is not necessary to provide a target since the default target for the product
will build all the firmware contained within the product.

The 'help' target provides further information on the arguments that can be
given:

    $> make help

For more guidance on the build system, refer to the full set of documentation
that includes the 'Build System' chapter.



