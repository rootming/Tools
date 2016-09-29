
#include "calc.h"

Calc::Calc(QWidget *parent) : QWidget(parent)
{

    //layout = new QGridLayout(this);
    //textLayout = new QGridLayout(this);
    calcLayout = new QGridLayout(this);
    number = new QSpinBox[5]();
    decNumber = new QLineEdit[4]();
    binaryNumber = new QLineEdit[4]();
    binaryMask = new QLineEdit[4]();
    network = new QLineEdit[4]();
    broadcast = new QLineEdit[4]();
    text = new QLabel[6]();

    for(int i = 0; i < 4; i++){
        number[i].setMinimum(0);
        number[i].setMaximum(255);
        calcLayout->addWidget(&number[i], 0, i + 1, 1, 1);
        calcLayout->addWidget(&decNumber[i], 1, i + 1, 1, 1);
        calcLayout->addWidget(&binaryNumber[i], 2, i + 1, 1, 1);
        calcLayout->addWidget(&binaryMask[i], 3, i + 1, 1, 1);
        calcLayout->addWidget(&network[i], 4, i + 1, 1, 1);
        calcLayout->addWidget(&broadcast[i], 5, i + 1, 1, 1);

    }
    number[3].setMinimum(0);
    number[4].setMinimum(0);
    number[4].setMaximum(32);
    calcLayout->addWidget(&number[4], 0, 5, 1, 1);  //mask
    text[0].setText("IP :");
    text[1].setText("Mask :");
    text[2].setText("Binary IP :");
    text[3].setText("Binary Mask :");
    text[4].setText("Network :");
    text[5].setText("Broadcast :");
    for(int i = 0; i < 6; i++){
        calcLayout->addWidget(&text[i], i, 0, 1, 1);
        //text[i].setAlignment(Qt::AlignRight);
    }


    //layout->addLayout(textLayout, 0, 0, 2, 4);
    //layout->addLayout(calcLayout, 0, 2, 5, 5);
    setLayout(calcLayout);

    for(int i = 0; i < 4; i++){
        connect(&number[i], SIGNAL(editingFinished()), this, SLOT(updateMaskNumber()));
        connect(&decNumber[i], SIGNAL(editingFinished()), this, SLOT(updateMaskNumber()));
    }
    connect(&number[4], SIGNAL(editingFinished()), this, SLOT(updateBinaryNumber()));

}


Calc::~Calc()
{

}

const static QString char2binary(int num)
{
    char tmp[9];
    for(int i = 0; i < 8; i++)
        tmp[i] = (num >> (7 - i) & 0x1) == 0 ? '0' : '1';
    tmp[8] = '\0';
    return QString(tmp);
}

void Calc::updateBinaryNumber()
{
    addrMask = 0;    //clear mask
    addr = 0;        //clear IP address
    broadAddr = 0;   //clear Broadcast address
    int count = 0;
//    int pos = 31;
    int tmp;
    const int mask = number[4].text().toInt();
    //create 32-bit mask
//    if(mask != 0)
//    while(count < mask){
//        num |= 1 << pos--;
//        count++;
//    }
    if(mask != 0)
        for(int pos = 31; count < mask; count++) addrMask |= 1 << pos--;

    for(int i = 0; i < 4; i++){
        tmp = addrMask >> 8 * (3 - i) & 0xFF;
        //get 8-bit mask
        decNumber[i].setText(QString::number(tmp));
        //show 8-bit mask by dec format
        binaryNumber[i].setText(char2binary(number[i].text().toInt()));
        //show IP by binary format
        binaryMask[i].setText(char2binary(tmp));
        //show 8-bit mask by binary format
        network[i].setText(QString::number(tmp & number[i].text().toInt()));
        //show network address
        addr |= number[i].text().toInt() << (3 - i) * 8;
        //store IP address
    }

    broadAddr = addr;
    for(int i = 0; i <= 31 - mask; i++){
        broadAddr |= 1 << i;
    }
    for(int i = 0; i < 4; i++){
        broadcast[i].setText(QString::number((broadAddr >> (3 - i) * 8 & 0xFF)));
    }
    qDebug("Update");
}


void Calc::updateMaskNumber()
{
    int num = 0;
    int count = 0;
    for(int i = 0; i < 4; i++)
        num |= decNumber[i].text().toInt() << ((3 - i) * 8);
    for(int i = 31; i >= 0; i--){
        if((num >> i & 0x1) == 1)
            count++;
    }
    number[4].setValue(count);
    updateBinaryNumber();

}
