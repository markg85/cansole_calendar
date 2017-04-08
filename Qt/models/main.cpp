#include <QApplication>
#include <QTableView>
#include <QTimer>
#include <QDebug>

#include "fixedmonthmodel.h"

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);

  QTableView *view = new QTableView();

  FixedMonthModel *model = new FixedMonthModel(view);
  model->updateModel(12, 2016);

  view->setModel(model);
  view->resize(800, 600);
  view->show();

  QTimer::singleShot(5000, [&model](){
    model->updateModel(2, 2016);
    qDebug() << "View should now display Februari 2016.";
  });

  return a.exec();
}
