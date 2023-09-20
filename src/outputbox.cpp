#include "outputbox.h"
#include <iostream>

outputBox::outputBox() :
    scrollArea(nullptr), container(nullptr), vBox(nullptr)
{
}

outputBox::outputBox(QScrollArea *scrollArea, QWidget *container, QVBoxLayout *vBox) :
    scrollArea(scrollArea), container(container), vBox(vBox)
{
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    scrollArea->setWidgetResizable(true);
}

void outputBox::addToVBox(QWidget *widget){
    vBox->addWidget(widget);
}
