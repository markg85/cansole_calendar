#include <QApplication>
#include <QTableView>
#include <QTimer>
#include <QDebug>

#include "fixedmonthmodel.h"

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);

  FixedMonthModel *model = new FixedMonthModel(&a);
//  model->updateModel(1, 2016);
//  model->updateModel(2, 2016);
//  model->updateModel(3, 2016);
//  model->updateModel(4, 2016);
//  model->updateModel(5, 2016);
//  model->updateModel(6, 2016);
//  model->updateModel(7, 2016);
//  model->updateModel(8, 2016);
//  model->updateModel(9, 2016);
//  model->updateModel(10, 2016);
//  model->updateModel(11, 2016);
  model->updateModel(12, 2016);
  QTableView *view = new QTableView();
  view->setModel(model);
  view->resize(800, 600);
  view->show();


  QTimer::singleShot(5000, [&model](){
    model->updateModel(2, 2016);
    qDebug() << "View should now display Februari 2016.";
  });

  return a.exec();
}
