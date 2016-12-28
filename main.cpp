#include <iostream>
#include <iomanip>
#include <vector>
#include <numeric>
#include <ctime>
#include <algorithm>
#include <range.hpp>
#include <chunked.hpp>
#include <zip.hpp>
#include <accumulate.hpp>

const int weekStartsAt = 1;
const int firstDayOfYear = 4; // In which index position is the first day of the year. For 2016 that is friday jan 1st.

const std::vector<std::string> dayNamesAccordingToWeekStart(const int weekStartDay)
{
  // Define dayNames in std::tm tm_wday format. Now we know which day is which index.
  const std::vector<std::string> dayNames = {"s", "m", "t", "w", "t", "f", "s"};
  std::vector<std::string> reorderedDayNames(7);

  for (int index: iter::range(0, 7))
  {
    reorderedDayNames[index] = dayNames[((index + weekStartDay) % 7)];
  }

  return reorderedDayNames;
}

constexpr bool isLeapYear(const int year)
{
  return ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0));
}

constexpr int daysInMonth(const int month, const bool isLeapYear)
{
  return 31 - ((month == 2) ? (3 - isLeapYear) : ((month - 1) % 7 % 2));
}

constexpr char *dayColumn(char day, char *data)
{
  data[0] = ' ';
  data[1] = (day > 9) ? '0' + ((day - (day % 10)) / 10) : ' ';
  data[2] = '0' + (day % 10);
  data[3] = '\0';

  return data;
}

// Define dayNames in std::tm tm_wday format. Now we know which day is which index.
const std::vector<std::string> dayNamesShort = dayNamesAccordingToWeekStart(weekStartsAt);

int main(int, char **)
{
  std::time_t time = std::time(nullptr);
  std::tm *tm = std::localtime(&time);

  int daysThusFar = 0;
  char dayColumnBuffer[4];

  for (auto &&month : iter::range(1, 13)) // 1, 13 is only for the isLeapYear function that assumes the second (2) month is februari.
  {
    int daysInCurrentMonth = daysInMonth(month, isLeapYear(tm->tm_year));
    int dayIndex = ((daysThusFar % 7) + firstDayOfYear);
    int startPosition = (dayIndex > 7) ? dayIndex % 7 : dayIndex;
    daysThusFar += daysInCurrentMonth;

    for (int dayNameIndex: iter::range(0, 7))
    {
      std::cout << "  " << dayNamesShort[dayNameIndex] << ' ';
    }

    std::cout << std::endl;

    for (auto&& daysInWeek: iter::chunked(iter::range(1 - startPosition, daysInCurrentMonth + 1), 7))
    {
      for (char day: daysInWeek)
      {
        if (day < 1)
        {
          std::cout << "    ";
        }
        else
        {
          std::cout << dayColumn(day, dayColumnBuffer) << ' ';
        }
      }
      std::cout << '\n';
    }
    std::cout << '\n';
  }

  return 0;
}
