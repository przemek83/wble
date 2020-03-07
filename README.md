# About project
 Library of useful Qt widgets. Created as a result of division of code of Volbx project and moving parts of it to independent library. Library contains:  
 + double slider
 + numeric filters (integer and double one)
 + string filter
 + date filter  

**Work is in progress.**
 
# Building
Clone and use Cmake directly or via QtCreator. Cmake **should**:
+ configure everything automatically,
+ compile library and create binaries.

**TIP**: remember to set properly `CMAKE_PREFIX_PATH` env variable. It should have Qt installation path to let Cmake `find_package` command work.  

As a result of compilation dynamic lib should be created along with headers dir.

To use it as external project via Cmake you may check how it is done in my other project called Volbx.

# Usage
Easiest way is to check examples subproject where you can find how to create and interact with each widget included in this library.  
Alternatively tests subroject can be checked or my other project called Volbx where widgets from this library are used.

# Widgets

