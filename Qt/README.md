# Qt version of the calendar experiments
The model calculates the days within a month on the fly in a very efficient manner.

## Fixed month model (FixedMonthModel.cpp/h)
The model itself is a grid model of 7 columns and 6 rows. Thus 42 cells in total.
It calculates which days should be shown in a given grid based on the year and month.
Pre and post offsets are also added which results in a model filled with 42 cells.

This model never resets! When you go to another month all the values within the model 
are updated, not reset. This would allow for view to do transitional animations from 
one month to another.
