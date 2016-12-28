# Console Calendar
This is a small application meant as C++14 and C++17 playground. It therefore requires C++17 support (you **need** Clang 4.0).

Right now you have to specify which day (as in monday, tuesday, wednesday, ...) the first day of the year is. In 2016, januari 1st was on Friday. The "firstDayOfYear" int must then be the index value of friday in std::tm wm_day index value. So friday would be 4. At this moment it's only used to get to the right day index for a given day. A day index is the human readable (monday, tues... you get the point) dayname for a given day.

You also need to specify the "weekStartsAt" which is also an int and must be an index value in std::tm wm_day. So if your week starts at monday (some have it on sunday, some on saturday) then the value for that index is 1. This value is used to calculate how weeks are represented and in which column a day should be represented.

## Credits
This application uses C++17's Structured Bindings and some of the [cppitertools](https://github.com/ryanhaining/cppitertools) that make some loops really nice!

## License
BSD 3 clause. Aka, do what you want, i don't care :)

## Todo
* The dayIndex value can probably be done differently so that "firstDayOfYear" isn't required anymore. Look into that.
* "dayNamesAccordingToWeekStart" now copies internally to make a list that is re-ordered according to whatever you had set as "weekStartsAt" value. This can be done differently. At the very least a second list with just ints can be done. That list would server as a "proxy".
* With a bit more effort, support different calendar systems. Right now it's very much focused on the gregorian calendar.
