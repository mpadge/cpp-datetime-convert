[![Build Status](https://travis-ci.org/mpadge/cpp-datetime-convert.svg)](https://travis-ci.org/mpadge/cpp-datetime-convert) 

# cpp-datetime-convert

Lightweight, generic conversion of date-time strings to standard format with no
library dependencies. The functional bits are `datetime.h` and `datetime.cpp`,
which are intended to be taken and bundled into any other code. Just `#include
"datetime.h"` to give access to the main functions:

1. `convert_datetime (std::string t)`
2. `timediff (std::string t1, std::string t2)`
3. `prettytime (long int t)`

The functionality is demonstrated with `make`, which gives the following output
```
Demonstration of format conversions:
2000-01-01 01:01:00 -> 2000-01-01 01:01:00
2000-01-01 01:01 -> 2000-01-01 01:01:00
2000-01-01 1:1:0 -> 2000-01-01 01:01:00
2000-01-01 1:1 -> 2000-01-01 01:01:00
2000-1-1 01:01:00 -> 2000-01-01 01:01:00
2000-1-1 01:01 -> 2000-01-01 01:01:00
2000-1-1 1:1:0 -> 2000-01-01 01:01:00
2000-1-1 1:1 -> 2000-01-01 01:01:00
01/01/2000 01:01:00 -> 2000-01-01 01:01:00
01/01/2000 01:01 -> 2000-01-01 01:01:00
01/01/2000 1:1:0 -> 2000-01-01 01:01:00
01/01/2000 1:1 -> 2000-01-01 01:01:00
1/1/2000 01:01:00 -> 2000-01-01 01:01:00
1/1/2000 01:01 -> 2000-01-01 01:01:00
1/1/2000 1:1:0 -> 2000-01-01 01:01:00
1/1/2000 1:1 -> 2000-01-01 01:01:00
00-01-01 01:01:00 -> 2000-01-01 01:01:00
67-01-01 01:01 -> 1967-01-01 01:01:00

Demonstration of time differences:
time difference (1967-12-23 01:34:57 - 2014-07-18 18:37:11) = 17009 days, 17:02:14
time difference (1967-12-23 01:34:57 - 1967-12-23 14:23:02) = 12:48:05
time difference (1967-12-23 01:34:57 - 1967-12-23 04:23:02) = 2:48:05
time difference (1967-12-23 01:34:57 - 1967-12-23 01:35:07) = 10
```
Note that the last 2 conversions automatically recognise and appropriately
convert the two-digit years. This is done based on the current year, so any
years up to the current will be have `"20"` pre-pended; otherwise they'll be
assued to be 20th century years and have "19" pre-pended. This should suffice
for another 81 years from time of writing.

## The repo

It's `makefile` controlled, so just
```
$ make
```
There's also a `tmux-start.bash` file, so for
[`tmux`](https://github.com/tmux/tmux/wiki) fans, the code can be opened for
editing with
```
$ bash tmux-start.bash
```
