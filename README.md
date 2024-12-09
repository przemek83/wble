[![Build & test](https://github.com/przemek83/wble/actions/workflows/buld-and-test.yml/badge.svg)](https://github.com/przemek83/wble/actions/workflows/buld-and-test.yml)
[![CodeQL](https://github.com/przemek83/wble/actions/workflows/codeql.yml/badge.svg)](https://github.com/przemek83/wble/actions/workflows/codeql.yml)
[![codecov](https://codecov.io/gh/przemek83/wble/graph/badge.svg?token=G42WUKQD8V)](https://codecov.io/gh/przemek83/wble)

[![Quality Gate Status](https://sonarcloud.io/api/project_badges/measure?project=przemek83_wble&metric=alert_status)](https://sonarcloud.io/summary/new_code?id=przemek83_wble)
[![Bugs](https://sonarcloud.io/api/project_badges/measure?project=przemek83_wble&metric=bugs)](https://sonarcloud.io/summary/new_code?id=przemek83_wble)
[![Code Smells](https://sonarcloud.io/api/project_badges/measure?project=przemek83_wble&metric=code_smells)](https://sonarcloud.io/summary/new_code?id=przemek83_wble)
[![Coverage](https://sonarcloud.io/api/project_badges/measure?project=przemek83_wble&metric=coverage)](https://sonarcloud.io/summary/new_code?id=przemek83_wble)
[![Duplicated Lines (%)](https://sonarcloud.io/api/project_badges/measure?project=przemek83_wble&metric=duplicated_lines_density)](https://sonarcloud.io/summary/new_code?id=przemek83_wble)

## Table of content
- [About project](#about-project)
- [Building](#building)
- [Usage](#usage)
- [Widgets](#widgets)

# About project
 Library of useful Qt widgets. Created as a result of division of code of Volbx project and moving parts of it to independent library. Library contains:  
 + double slider
 + numeric filters (integer and double one)
 + string filter
 + date filter  
 + infinity progress bar
 + counter progress bar
  
# Building
Clone and use CMake directly or via Qt Creator. CMake **should**:
+ configure everything automatically,
+ compile library and create binaries.

**TIP**: remember to set properly `CMAKE_PREFIX_PATH` env variable. It should have Qt installation path to let CMake `find_package` command work.  

As a result of compilation, dynamic lib should be created along with headers dir.

To use it as external project via CMake you may check how it is done in my other project called Volbx.

## Used tools and libs
| Tool |  Windows | Lubuntu |
| --- | --- | --- |
| OS version | 10 22H2 | 22.04 |
| GCC | 11.2.0 | 11.3.0 |
| CMake | 3.25.0 | 3.25.0 |
| Git | 2.38.1 | 2.34.1 |
| Qt | 6.5.2 | 6.5.2 |
| Qt Creator | 10.0.2 | 10.0.2 |

# Usage
The easiest way is to check examples subproject, where you can find how to create and interact with each widget included in this library.  
Alternatively, tests subproject can be checked. Usage also can be found in my other project called Volbx where widgets from this library are used.

# Widgets
## Double slider
![Alt text](DoubleSlider.png?raw=true "Double slider")  
Each handle can be moved independently. Check also Integer and Double filters, which are wrapping double slider into handy adjustable widgets.  
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
Widget allowing to pick custom date range. An additional "Ignore data with empty dates" check box can be used to filter out data entries with empty dates.
### String filter
![Alt text](StringFilter.png?raw=true "String filter not checkable")  
Widget allowing to pick multiple string values as filtered set. Additional checkbox "Select/Unselect all" for quick unchecking / checking all string values in filter.
## Progress bars
Widgets capable of showing progress of longer tasks. Can be used as a blend in widget or modal one. 
### Infinity progress bar
![Alt text](InfinityProgressBar.png?raw=true "String filter not checkable")  
Can be used for tasks with unknown end time. The progress bar displays moving arcs until it is stopped or destroyed.
### Counter progress bar
![Alt text](CounterProgressBar.png?raw=true "String filter not checkable")  
Can be used for tasks with known end time. The progress bar displays arc, which is moving from 0 towards 100 percent. In the middle, current percent is displayed.
