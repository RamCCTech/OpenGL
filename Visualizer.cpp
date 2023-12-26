#include "stdafx.h"
#include "Visualizer.h"
#include "OpenGLWindow.h"
#include "Geometry.h"
#include "HermiteCurve.h"
#include "BSplineCurve.h"
#include "BezierCurve.h"
#include "SutherlandCohen.h"
#include "SutherlandHodgman.h"

Visualizer::Visualizer(QWindow* parent) : QMainWindow(nullptr), mClippingPolygon({})
{
    setupUi();
    connectSignalsSlots();
}

Visualizer::~Visualizer()
{}

void Visualizer::setupUi()
{
    resize(861, 650);
    mCentralWidget = new QWidget(this);
    mGridLayoutWidget = new QWidget(mCentralWidget);
    mGridLayoutWidget->setGeometry(QRect(0, 0, 861, 650));
    mGridLayout = new QGridLayout(mGridLayoutWidget);
    mGridLayout->setSpacing(6);
    mGridLayout->setContentsMargins(11, 11, 11, 11);


    QLabel* label = new QLabel("Clipper", mGridLayoutWidget);
    label->setAlignment(Qt::AlignLeading | Qt::AlignHCenter | Qt::AlignVCenter);
    mGridLayout->addWidget(label, 0, 0, 1, 1);

    QSizePolicy sizePolicy2(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    sizePolicy2.setHorizontalStretch(0);
    sizePolicy2.setVerticalStretch(0);

    mOpenGLWidget = new OpenGLWindow(QColor(0, 0, 0), mCentralWidget);
    sizePolicy2.setHeightForWidth(mOpenGLWidget->sizePolicy().hasHeightForWidth());
    mOpenGLWidget->setSizePolicy(sizePolicy2);
    mGridLayout->addWidget(mOpenGLWidget, 1, 0, 1, 1);

    mHorizontalLayout10 = new QHBoxLayout();
    mHorizontalLayout10->setSpacing(6);
    mVerticalLayout5 = new QVBoxLayout();
    mVerticalLayout5->setSpacing(6);
    mHorizontalLayout5 = new QHBoxLayout();
    mHorizontalLayout5->setSpacing(6);
    QLabel* label_4 = new QLabel("Point3D Input ->", mGridLayoutWidget);

    mHorizontalLayout5->addWidget(label_4);

    QLabel* label_7 = new QLabel("X", mGridLayoutWidget);
    QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Preferred);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(label_7->sizePolicy().hasHeightForWidth());
    label_7->setSizePolicy(sizePolicy);
    label_7->setAlignment(Qt::AlignRight | Qt::AlignTrailing | Qt::AlignVCenter);

    mHorizontalLayout5->addWidget(label_7);

    mDoubleSpinBox5 = new QDoubleSpinBox(mGridLayoutWidget);
    mDoubleSpinBox5->setMinimum(-100.000000000000000);
    mDoubleSpinBox5->setMaximum(100.000000000000000);
    mHorizontalLayout5->addWidget(mDoubleSpinBox5);

    QLabel* label_8 = new QLabel("Y", mGridLayoutWidget);
    sizePolicy.setHeightForWidth(label_8->sizePolicy().hasHeightForWidth());
    label_8->setSizePolicy(sizePolicy);
    label_8->setAlignment(Qt::AlignRight | Qt::AlignTrailing | Qt::AlignVCenter);

    mHorizontalLayout5->addWidget(label_8);

    mDoubleSpinBox6 = new QDoubleSpinBox(mGridLayoutWidget);
    mDoubleSpinBox6->setMinimum(-100.000000000000000);
    mDoubleSpinBox6->setMaximum(100.000000000000000);
    mHorizontalLayout5->addWidget(mDoubleSpinBox6);

    mPushButton2 = new QPushButton("ADD", mGridLayoutWidget);
    mHorizontalLayout5->addWidget(mPushButton2);

    mPushButton11 = new QPushButton("Change Color", mGridLayoutWidget);
    mHorizontalLayout5->addWidget(mPushButton11);

    mVerticalLayout5->addLayout(mHorizontalLayout5);

    mListWidget3 = new QListWidget(mGridLayoutWidget);
    QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Minimum);
    sizePolicy1.setHorizontalStretch(0);
    sizePolicy1.setVerticalStretch(0);
    sizePolicy1.setHeightForWidth(mListWidget3->sizePolicy().hasHeightForWidth());
    mListWidget3->setSizePolicy(sizePolicy1);
    mVerticalLayout5->addWidget(mListWidget3);
    mHorizontalLayout10->addLayout(mVerticalLayout5);
    mGridLayout->addLayout(mHorizontalLayout10, 2, 0, 1, 1);

    mHorizontalLayout7 = new QHBoxLayout();
    mHorizontalLayout7->setSpacing(6);
    mPushButton4 = new QPushButton("ADD Region", mGridLayoutWidget);
    mHorizontalLayout7->addWidget(mPushButton4);
    mPushButton3 = new QPushButton("ADD Polygon", mGridLayoutWidget);
    mHorizontalLayout7->addWidget(mPushButton3);
    mPushButton5 = new QPushButton("ADD Line", mGridLayoutWidget);
    mHorizontalLayout7->addWidget(mPushButton5);

    mHorizontalLayout8 = new QHBoxLayout();
    mPushButton6 = new QPushButton("Clip Lines", mGridLayoutWidget);
    mHorizontalLayout8->addWidget(mPushButton6);
    mPushButton7 = new QPushButton("Clip Polygons", mGridLayoutWidget);
    mHorizontalLayout8->addWidget(mPushButton7);

    mPushButton8 = new QPushButton("Bezier Curve", mGridLayoutWidget);
    mPushButton9 = new QPushButton("Hermite Curve", mGridLayoutWidget);
    mPushButton10 = new QPushButton("BSpline Curve", mGridLayoutWidget);


    // Create a QTabWidget
    tabWidget = new QTabWidget(mGridLayoutWidget);

    // Create tabs for the different layouts
    tabLayout1 = new QWidget(tabWidget);
    tabLayout2 = new QWidget(tabWidget);
    tabLayout3 = new QWidget(tabWidget);
    tabLayout4 = new QWidget(tabWidget);

    tabLayout1Vertical = new QVBoxLayout(tabLayout1);
    tabLayout1Vertical->addLayout(mHorizontalLayout7);
    tabLayout1Vertical->addLayout(mHorizontalLayout8);
    tabLayout1->setLayout(tabLayout1Vertical);

    tabLayout2Vertical = new QVBoxLayout(tabLayout2);
    tabLayout2Vertical->addWidget(mPushButton8);
    tabLayout2->setLayout(tabLayout2Vertical);

    tabLayout3Vertical = new QVBoxLayout(tabLayout3);
    tabLayout3Vertical->addWidget(mPushButton9);
    tabLayout2->setLayout(tabLayout3Vertical);

    tabLayout4Vertical = new QVBoxLayout(tabLayout4);
    tabLayout4Vertical->addWidget(mPushButton10);
    tabLayout2->setLayout(tabLayout4Vertical);

    // Add tabs to the tab widget
    tabWidget->addTab(tabLayout1, "Clip");
    tabWidget->addTab(tabLayout2, "Bezier Curve");
    tabWidget->addTab(tabLayout3, "Hermite Curve");
    tabWidget->addTab(tabLayout4, "BSpline Curve");

    // Add the tab widget to the main layout
    mGridLayout->addWidget(tabWidget, 6, 0, 1, 1);

    setCentralWidget(mCentralWidget);
}


void Visualizer::connectSignalsSlots()
{
    // Connect signals to slots
    connect(mOpenGLWidget, SIGNAL(shapesUpdated()), mOpenGLWidget, SLOT(update()));
    connect(mPushButton2, &QPushButton::clicked, this, &Visualizer::addPoints);
    connect(mPushButton4, &QPushButton::clicked, this, &Visualizer::addRegion);
    connect(mPushButton3, &QPushButton::clicked, this, &Visualizer::addPolygon);
    connect(mPushButton5, &QPushButton::clicked, this, &Visualizer::addLine);
    connect(mPushButton6, &QPushButton::clicked, this, &Visualizer::clipLines);
    connect(mPushButton7, &QPushButton::clicked, this, &Visualizer::clipPolygons);
    connect(mPushButton8, &QPushButton::clicked, this, &Visualizer::addBezier);
    connect(mPushButton9, &QPushButton::clicked, this, &Visualizer::addHermite);
    connect(mPushButton10, &QPushButton::clicked, this, &Visualizer::addBSpline);
    connect(mPushButton11, &QPushButton::clicked, this, &Visualizer::changeColor);
}

void Visualizer::changeColor()
{
    QColorDialog colorDialog(this);
    QColor selectedColor = colorDialog.getColor();
    if (selectedColor.isValid())
    {
        int red = selectedColor.red();
        int green = selectedColor.green();
        int blue = selectedColor.blue();
        int alpha = selectedColor.alpha();
        QString color = QString("%1, %2, %3, %4").arg(red).arg(green).arg(blue).arg(alpha);
        mOpenGLWidget->setColor(color, "fragmentShader.glsl");
    }
}

void Visualizer::addPoints()
{
    // Add a point to the list
    double xValue = mDoubleSpinBox5->value();
    double yValue = mDoubleSpinBox6->value();

    QString itemText = QString("X: %1, Y: %2").arg(xValue).arg(yValue);
    Point3D p(xValue, yValue);
    mPoints.push_back(p);

    QListWidgetItem* newItem = new QListWidgetItem(itemText);
    mListWidget3->addItem(newItem);
}

void Visualizer::addRegion()
{
    if (mPoints.size() < 3) {
        QMessageBox::warning(this, "Error", "At least three points are needed to create a Region.");
        return;
    }

    Shape* s = createShapeFromPoints();
    addClippingPolygon(s);

    // Clear the list and points
    clearListAndPoints();
}

void Visualizer::addLine()
{
    if (mPoints.size() < 2) {
        QMessageBox::warning(this, "Error", "At least two points are needed to create a line.");
        return;
    }

    std::vector<Line> lines = createLinesFromPoints();
    addLines(lines);

    // Clear the list and points
    clearListAndPoints();
}

void Visualizer::addPolygon()
{
    if (mPoints.size() < 3) {
        QMessageBox::warning(this, "Error", "At least three points are needed to create a polygon.");
        return;
    }

    Shape* polygon = createShapeFromPoints();
    addPolygons(polygon);

    // Clear the list and points
    clearListAndPoints();
}

void Visualizer::addHermite()
{
    if (mPoints.size() != 4) {
        QMessageBox::warning(this, "Error", "Four points are needed to create a Hermite curve.");
        return;
    }
    HermiteCurve bs(mPoints);
    std::vector<Point3D> hermitePoints = bs.calculateHermite();
    addCurveLines(hermitePoints);

    // Clear the list and points
    clearListAndPoints();
}

void Visualizer::addBezier()
{
    if (mPoints.size() != 4) {
        QMessageBox::warning(this, "Error", "Four points are needed to create a Bezier curve.");
        return;
    }
    BezierCurve bs(mPoints);
    std::vector<Point3D> bezierPoints = bs.calculateBezier();
    addCurveLines(bezierPoints);

    // Clear the list and points
    clearListAndPoints();
}

void Visualizer::addBSpline()
{
    if (mPoints.size() != 4) {
        QMessageBox::warning(this, "Error", "Four points are needed to create a BSpline curve.");
        return;
    }
    BSplineCurve bs(3);
    std::vector<Point3D> bsplinePoints = bs.evaluate(mPoints, 100);

    addCurveLines(bsplinePoints);

    // Clear the list and points
    clearListAndPoints();
}

Shape* Visualizer::createShapeFromPoints()
{
    // Create a shape from the points
    std::vector<Line> lines;
    int size = mPoints.size();
    for (int i = 0; i < size; i++) {
        lines.push_back(Line(mPoints.at(i), mPoints.at((i + 1) % size)));
    }

    return new Shape(lines);
}

std::vector<Line> Visualizer::createLinesFromPoints()
{
    // Create lines from the points
    std::vector<Line> lines;
    int size = mPoints.size();
    for (int i = 0; i < size - 1; i += 2) {
        lines.push_back(Line(mPoints.at(i), mPoints.at(i + 1)));
    }

    return lines;
}

void Visualizer::clearListAndPoints()
{
    mListWidget3->clear();
    mPoints.clear();
}

void Visualizer::addPolygonsVertices(float red, float green, float blue)
{
    for (int i = 0; i < mPolygons.size(); i++) {
        addShapeVertices(mPolygons.at(i), red, green, blue);
    }
}

void Visualizer::addShapeVertices(Shape shape, float red, float green, float blue)
{
    std::vector<Line> lines = shape.getShape();
    for (int j = 0; j < lines.size(); j++) {
        vertices << lines.at(j).p1().x() << lines.at(j).p1().y();
        vertices << lines.at(j).p2().x() << lines.at(j).p2().y();
        colors << red << green << blue;
        colors << red << green << blue;
    }
}

void Visualizer::addCurveLines(const std::vector<Point3D>& points)
{
    for (int i = 0; i < points.size() - 1; i++) {
        mLines.push_back(Line(points[i], points[i + 1]));
    }
    addShapeVertices(mLines, 0.0f, 1.0f, 1.0f);
    mOpenGLWidget->updateShape(vertices, colors);

}

void Visualizer::clipPolygons()
{
    for (int i = 0; i < mPolygons.size(); i++) {
        SutherlandHodgman sh(mClippingPolygon, mPolygons.at(i));
        mPolygons.at(i) = sh.getClippedPolygon();
    }
    vertices.clear();
    colors.clear();
    addShapeVertices(mLines, 0.0f, 0.0f, 1.0f);
    addPolygonsVertices(1.0f, 1.0f, 1.0f);
    addShapeVertices(mClippingPolygon, 1.0f, 1.0f, 0.0f);
    mOpenGLWidget->updateShape(vertices, colors);

}

void Visualizer::clipLines()
{
    for (int i = 0; i < mLines.size(); i++) {
        SutherlandCohen sc(mClippingPolygon, mLines[i]);
        mLines[i] = sc.getClippedLine();
    }

    vertices.clear();
    colors.clear();
    addShapeVertices(mLines, 0.0f, 0.0f, 1.0f);
    addPolygonsVertices(1.0f, 1.0f, 1.0f);
    addShapeVertices(mClippingPolygon, 1.0f, 1.0f, 0.0f);
    mOpenGLWidget->updateShape(vertices, colors);

}

void Visualizer::addClippingPolygon(Shape* s)
{
    mClippingPolygon = *s;
    addShapeVertices(mClippingPolygon, 1.0f, 1.0f, 0.0f);
    mOpenGLWidget->updateShape(vertices, colors);

}

void Visualizer::addPolygons(Shape* s)
{
    mPolygons.push_back(*s);
    addPolygonsVertices(1.0f, 1.0f, 1.0f);
    mOpenGLWidget->updateShape(vertices, colors);

}

void Visualizer::addLines(std::vector<Line> lines)
{
    for (Line l : lines)
        mLines.push_back(l);
    addShapeVertices(mLines, 0.0f, 1.0f, 1.0f);
    mOpenGLWidget->updateShape(vertices, colors);
}