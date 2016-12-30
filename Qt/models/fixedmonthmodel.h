#ifndef FIXEDMONTHMODEL_H
#define FIXEDMONTHMODEL_H

#include <QAbstractTableModel>
#include <QVector>

class FixedMonthModel : public QAbstractTableModel
{
  Q_OBJECT

public:

  enum Roles
  {
    // This role maps to a bool. It's true for all index values within the model that represent the month that is being shown.
    // It's false for the pre- and post offset numbers.
    isWholeMonth = Qt::UserRole + 1
  };

  FixedMonthModel(QObject *parent = 0);

  int rowCount(const QModelIndex &parent) const;
  int columnCount(const QModelIndex &parent) const;
  QVariant data(const QModelIndex &index, int role) const;
  QVariant headerData(int section, Qt::Orientation orientation, int role) const;

  void updateModel(int month, int year);

public slots:
  void nextMonth();
  void previousMonth();
  void nextYear();
  void previousYear();
  void toMonth(int month);
  void toYear(int year);
  void toDate(int month, int year);


private:
  int daysPreviousMonth(int month, int year);
  constexpr static bool isLeapYear(const int year);
  constexpr static int daysInMonth(const int month, const bool isLeapYear);
  int m_preOffset;
  int m_postOffset;
  int m_month;
  int m_year;
  char m_firstDayOfWeek;
  QVector<char> m_calendarMonth;
};

#endif // FIXEDMONTHMODEL_H
