#ifndef CALC_H
#define CALC_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QSpinBox>
#include <QGridLayout>
#include <QLabel>


class Calc : public QWidget
{
    Q_OBJECT
public:
    explicit Calc(QWidget *parent = 0);
    ~Calc();

signals:

public slots:
    void updateBinaryNumber();
    void updateMaskNumber();

private:
    QSpinBox *number;
    QLineEdit *decNumber;
    QLineEdit *binaryNumber;
    QLineEdit *binaryMask;
    QLineEdit *network;
    QLineEdit *broadcast;
    QLabel *text;
    QGridLayout *textLayout;
    QGridLayout *calcLayout;
    QGridLayout *layout;
    int addr;
    int addrMask;
    int broadAddr;

};

#endif // CALC_H
