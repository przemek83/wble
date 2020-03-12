# About project
 Library of useful Qt widgets. Created as a result of division of code of Volbx project and moving parts of it to independent library. Library contains:  
 + double slider
 + numeric filters (integer and double one)
 + string filter
 + date filter  
 + infinity progress bar
 + counter progress bar
  
# Building
Clone and use Cmake directly or via QtCreator. Cmake **should**:
+ configure everything automatically,
+ compile library and create binaries.

**TIP**: remember to set properly `CMAKE_PREFIX_PATH` env variable. It should have Qt installation path to let Cmake `find_package` command work.  

As a result of compilation dynamic lib should be created along with headers dir.

To use it as external project via Cmake you may check how it is done in my other project called Volbx.

# Usage
Easiest way is to check examples subproject where you can find how to create and interact with each widget included in this library.  
Alternatively tests subproject can be checked. Usage also can be found in my other project called Volbx where widgets from this library are used.

# Widgets
## Double slider
![Alt text](DoubleSlider.png?raw=true "Double slider")  
Each handle can be moved independently. Check also Integer and Double filters which are wrapping double slider into handy adjustable widgets.  
## Filters
Each filter widget inherits from `QGroupBox`. It means all filters can be checkable or not. Use standard `setCheckable()` to alter behavior.
### Integer filter
![Alt text](IntegerFilter.png?raw=true "Integer filter not checkable")  
Wrapped double slider into adjustable widget. Dedicated for integer values.
### Double filter
![Alt text](DoubleFilter.png?raw=true "Double filter not checkable")  
Wrapped double slider into adjustable widget. Dedicated for double values.
### Date filter
![Alt text](DateFilter.png?raw=true "Date filter not checkable")  
Widget allowing to pick custom date range. Additional "Ignore data with empty dates" check box can be used to filter out data entries with empty dates.
### String filter
![Alt text](StringFilter.png?raw=true "String filter not checkable")  
Widget allowing to pick multiple string values as filtered set. Additional checkbox "Select/Unselect all" for quick unchecking / checking all string values in filter.
## Progress bars
Widgets capable of showing progress of longer tasks. Can be used as a blend in widget or modal one. 
### Infinity progress bar
![Alt text](InfinityProgressBar.png?raw=true "String filter not checkable")  
Can be used for tasks with unknown end time. Progress bar displays moving arcs until it is stopped or destroyed.
### Counter progress bar
![Alt text](CounterProgressBar.png?raw=true "String filter not checkable")  
Can be used for tasks with known end time. Progress bar displays arc which is moving from 0 towards 100 percent. In the middle current percent is displayed.
