bigint
==========
This directory contains sources for a simple & lightweight *C* library for performing computations
on big integers. Implementation is based on primary school level math.

### Compilation
There is a *cmake* script included with this library so in order to compile the project use the following commands
``cmake CMakeLists.txt; make`` which should work on any **\*nix** operating system. For **Windows** you may have to
check out the great [Cygwin](http://www.cygwin.com/) project.

Compiling examples is the same operation but run from the example application's directory. However, have in
mind that you should have *bigint* library already compiled as the examples are dependant from it.

### Running examples
As far as I know, the fastest way to run the examples is to instruct the system where to look for the *bigint* library
by exporting the path via ``LD_LIBRARY_PATH`` system variable, eg: ``export LD_LIBRARY_PATH="/path/to/library/"``. As
mentioned before, this command should work perfectly on any **\*nix** operating system and for **Windows** check out
[Cygwin](http://www.cygwin.com/) project.
