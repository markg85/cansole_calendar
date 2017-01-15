#ifndef FIXEDMONTHMODEL_H
#define FIXEDMONTHMODEL_H

#include <QAbstractTableModel>

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

  explicit FixedMonthModel(QObject *parent = 0);

  virtual int rowCount(const QModelIndex &parent) const override;
  virtual int columnCount(const QModelIndex &parent) const override;
  virtual QVariant data(const QModelIndex &index, int role) const override;
  virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

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

  // Calculate which day needs to be shown in a given cell.
  inline int dayInCell(int cell) const;

  // We need to know from where to count down in the few cells from the previous month.
  int m_daysInPreviousMonth;

  // The number of days to display before the current month.
  int m_preOffset;

  // The number of days to display after the current month.
  int m_postOffset;

  // Which month is visible.
  int m_month;

  // Which year for the current month.
  int m_year;

  // The first day of the week is... Monday is common in the western world.
  char m_firstDayOfWeek;
};

#endif // FIXEDMONTHMODEL_H
