#include "LayoutTest.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QGridLayout>

CLayoutTest::CLayoutTest(QWidget *parent):QWidget(parent)
{
    initControl();
}

CLayoutTest::~CLayoutTest()
{

}

void CLayoutTest::initControl()
{
    QVBoxLayout* vLayout = new QVBoxLayout();
    QHBoxLayout* hLayout = new QHBoxLayout();

    //前后按钮的外观
    m_objPreBtn.setText("Pre Page");
    m_objPreBtn.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    m_objPreBtn.setMinimumSize(160, 30);

    m_objNextBtn.setText("Next Page");
    m_objNextBtn.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    m_objNextBtn.setMinimumSize(160, 30);

    connect(&m_objPreBtn, SIGNAL(clicked()), this, SLOT(onPreBtnClicked()));
    connect(&m_objNextBtn, SIGNAL(clicked()), this, SLOT(onNextBtnClicked()));

    //添加前后按钮
    hLayout->addWidget(&m_objPreBtn);
    hLayout->addWidget(&m_objNextBtn);

    //添加3个导航页
    m_objsLayout.addWidget(Get1stPate());
    m_objsLayout.addWidget(Get2ndPate());
    m_objsLayout.addWidget(Get3rdPate());

    //设置当前QWidget的布局布局管理器
    vLayout->addLayout(&m_objsLayout);
    vLayout->addLayout(hLayout);

    setLayout(vLayout);


}

QWidget *CLayoutTest::Get1stPate()
{
    QWidget* ret = new QWidget();
    QGridLayout* gLayout = new QGridLayout();

    m_Lable1.setText("This");
    m_Lable2.setText("is");
    m_Lable3.setText("1st");
    m_Lable4.setText("page");

    gLayout->addWidget(&m_Lable1, 0, 0);
    gLayout->addWidget(&m_Lable2, 0, 1);
    gLayout->addWidget(&m_Lable3, 1, 0);
    gLayout->addWidget(&m_Lable4, 1, 1);

    ret->setLayout(gLayout);

    return ret;

}

QWidget *CLayoutTest::Get2ndPate()
{
    QWidget* ret = new QWidget();

    QFormLayout* layout = new QFormLayout();
    m_lineEdit.setText("This is 2nd page");

    layout->addRow("Hint:", &m_lineEdit);
    ret->setLayout(layout);

    return ret;
}

QWidget *CLayoutTest::Get3rdPate()
{
    QWidget* ret = new QWidget();
    QVBoxLayout* layout = new QVBoxLayout();

    m_objBtn1.setText("This is");
    m_objBtn2.setText("3rd page");

    layout->addWidget(&m_objBtn1);
    layout->addWidget(&m_objBtn2);

    ret->setLayout(layout);

    return ret;
}

void CLayoutTest::onPreBtnClicked()
{
    int index = ( (m_objsLayout.currentIndex() - 1) + 3) % 3;
    m_objsLayout.setCurrentIndex(index);
}

void CLayoutTest::onNextBtnClicked()
{
    int index = (m_objsLayout.currentIndex() + 1) % 3;
    m_objsLayout.setCurrentIndex(index);
}
