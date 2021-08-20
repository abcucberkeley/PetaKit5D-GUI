#ifndef OUTPUTBOX_H
#define OUTPUTBOX_H
#include <QLabel>
#include <QPushButton>
#include <QScrollArea>
#include <QVBoxLayout>

class outputBox
{
public:
    outputBox();
    outputBox(QScrollArea *scrollArea, QWidget *container, QVBoxLayout *vBox);
    void addToVBox(QWidget *widget);
    QScrollArea *scrollArea;
    QWidget *container;
    QVBoxLayout *vBox;

};

#endif // OUTPUTBOX_H
