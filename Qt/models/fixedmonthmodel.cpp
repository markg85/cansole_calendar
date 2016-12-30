#include "fixedmonthmodel.h"

#include <ctime>
#include <cmath>
#include <QDate>
#include <QDebug>

// ----------------------------------------
// TODO!
// - The headerData is very fragile at this moment. Daynames will break if a week doesn't start on monday.
// - Implement weeknumbers according to ISO-8601.
// - - This implicitly also makes this calendar a "must start with monday if weeknumbers are shown".
// - Expose this model to QML and see how it works there.

FixedMonthModel::FixedMonthModel(QObject *parent)
  : QAbstractTableModel(parent)
  , m_preOffset(0)
  , m_postOffset(0)
  , m_month(0)
  , m_year(0)
  , m_firstDayOfWeek(1) // The first day of the week. This is the index in std::tm tm_wday format.
  , m_calendarMonth(QVector<char>(42))
{

}

int FixedMonthModel::rowCount(const QModelIndex &parent) const
{
  Q_UNUSED(parent)
  return 6;
}

int FixedMonthModel::columnCount(const QModelIndex &parent) const
{
  Q_UNUSED(parent)
  return 7;
}

QVariant FixedMonthModel::data(const QModelIndex &index, int role) const
{
  if (role == Qt::DisplayRole && index.isValid())
  {
    return m_calendarMonth[(index.row() * 7) + index.column()];
  }
  else if (role == Roles::isWholeMonth)
  {
    int day = (index.row() * 7) + index.column();
    return (day > m_preOffset && (day < (42 - m_postOffset)));
  }

  return QVariant();
}

QVariant FixedMonthModel::headerData(int section, Qt::Orientation orientation, int role) const
{
  if (role == Qt::DisplayRole)
  {
    if (orientation == Qt::Orientation::Horizontal)
    {
      // TODO: This right now fails when your week starts with a day other then monday.
      int val = 1 + section;
      return QDate::shortDayName(val);
    }
    else if (orientation == Qt::Orientation::Vertical)
    {
      // TODO: Implement sane week numbering.. The world uses too much different systems for that!
      // https://en.wikipedia.org/wiki/Week#Week_numbering
      // Go for ISO-8601? (Aka, the week with the first thursday or january first after december 31 becomes week 1)
    }
  }

  return QVariant();
}

void FixedMonthModel::updateModel(int month, int year)
{
  if (m_month == month && m_year == year)
  {
    return;
  }

  m_month = month;
  m_year = year;

  std::time_t time = std::time(nullptr);
  std::tm tm = *std::localtime(&time);
  tm.tm_year = year - 1900; // It starts from 1900. So 0 there is year 1900.
  tm.tm_mon = month - 1; // -1 because the month is this function is 1-12, tm_month is 0-11
  tm.tm_mday = 1; // 1 is ok. This one is 1-31, not 0-30... A bit of inconsistency with months?
  std::mktime(&tm);

  int preOffset = std::abs(tm.tm_wday - m_firstDayOfWeek);
  m_preOffset = (preOffset == 0) ? 7 : preOffset;
  m_postOffset = 42 - daysInMonth(month, isLeapYear(year)) - m_preOffset;
  int previousMonth = daysPreviousMonth(month, year);

  for (int i = 0; i < m_preOffset; i++)
  {
    m_calendarMonth[i] = previousMonth - (m_preOffset - (i + 1));
  }

  for (int i = 1, idx = m_preOffset; i <= 42 - (m_preOffset + m_postOffset); i++, idx++)
  {
    m_calendarMonth[idx] = i;
  }

  for (int i = 1, idx = 42 - m_postOffset; i <= m_postOffset; i++, idx++)
  {
    m_calendarMonth[idx] = i;
  }

  emit dataChanged(index(0, 0), index(6, 7)); // The whole model is changed.
}

void FixedMonthModel::nextMonth()
{
  toDate(m_month + 1, m_year);
}

void FixedMonthModel::previousMonth()
{
  toDate(m_month - 1, m_year);
}

void FixedMonthModel::nextYear()
{
  toDate(m_month, m_year + 1);
}

void FixedMonthModel::previousYear()
{
  toDate(m_month, m_year - 1);
}

void FixedMonthModel::toMonth(int month)
{
  toDate(month, m_year);
}

void FixedMonthModel::toYear(int year)
{
  toDate(m_month, year);
}

void FixedMonthModel::toDate(int month, int year)
{
  int tempMonth = month;
  int tempYear = year;

  if (tempMonth < 1)
  {
    tempYear -= 1;
    tempMonth = 12;
  }
  else if (tempMonth > 12)
  {
    tempYear += 1;
    tempMonth = 1;
  }

  updateModel(tempMonth, tempYear);
}

int FixedMonthModel::daysPreviousMonth(int month, int year)
{
  month -= 1;

  if (month < 1)
  {
    year -= 1;
    month = 12;
  }
  else if (month > 12)
  {
    year += 1;
    month = 1;
  }

  return daysInMonth(month, isLeapYear(year));
}

constexpr bool FixedMonthModel::isLeapYear(const int year)
{
  return ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0));
}

constexpr int FixedMonthModel::daysInMonth(const int month, const bool isLeapYear)
{
  return 31 - ((month == 2) ? (3 - isLeapYear) : ((month - 1) % 7 % 2));
}
