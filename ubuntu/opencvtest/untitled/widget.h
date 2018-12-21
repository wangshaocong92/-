#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <opencv4/opencv2/core.hpp>
#include <opencv4/opencv2/opencv.hpp>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private:
    Ui::Widget *ui;
    cv::Mat mat;
    void onPushButtonClicked();
};

#endif // WIDGET_H
