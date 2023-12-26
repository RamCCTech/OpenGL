#pragma once

#include <QtWidgets/QMainWindow>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QDoubleSpinBox>
#include <QListWidget>
#include <vector>
#include <QOpenGLFunctions>
#include <QOpenGLWidget>

#include "Shape.h"

class OpenGLWindow;

class Visualizer : public QMainWindow, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    Visualizer(QWindow* parent = nullptr);
    ~Visualizer();
    void addLines(std::vector<Line> lines);
    void addPolygons(Shape* s);
    void addClippingPolygon(Shape* s);
    void addCurveLines(const std::vector<Point3D>& points);

private:
    void setupUi();
    void connectSignalsSlots();
    Shape* createShapeFromPoints();
    std::vector<Line> createLinesFromPoints();
    void clearListAndPoints();
    void addShapeVertices(Shape shape, float red, float green, float blue);
    void addPolygonsVertices(float red, float green, float blue);

private slots:
    void addPoints();
    void addRegion();
    void addLine();
    void addHermite();
    void addBezier();
    void addBSpline();
    void addPolygon();
    void clipPolygons();
    void clipLines();
    void changeColor();

private:
    QWidget* mCentralWidget;
    QWidget* mGridLayoutWidget;
    QGridLayout* mGridLayout;
    QHBoxLayout* mHorizontalLayout7;
    QHBoxLayout* mHorizontalLayout8;
    QVBoxLayout* mVerticalLayout5;
    QHBoxLayout* mHorizontalLayout5;
    QHBoxLayout* mHorizontalLayout10;

    // Buttons
    QPushButton* mPushButton4;
    QPushButton* mPushButton3;
    QPushButton* mPushButton5;
    QPushButton* mPushButton6;
    QPushButton* mPushButton7;
    QPushButton* mPushButton8;
    QPushButton* mPushButton9;
    QPushButton* mPushButton10;
    QPushButton* mPushButton11;

    // DoubleSpinBoxes
    QDoubleSpinBox* mDoubleSpinBox5;
    QDoubleSpinBox* mDoubleSpinBox6;

    // Other widgets
    QPushButton* mPushButton2;
    QListWidget* mListWidget3;
    OpenGLWindow* mOpenGLWidget;

    QTabWidget* tabWidget;

    QWidget* tabLayout1;
    QWidget* tabLayout2;
    QWidget* tabLayout3;
    QWidget* tabLayout4;

    QVBoxLayout* tabLayout1Vertical;
    QVBoxLayout* tabLayout2Vertical;
    QVBoxLayout* tabLayout3Vertical;
    QVBoxLayout* tabLayout4Vertical;

    // Data
    std::vector<Point3D> mPoints;
    Shape mClippingPolygon;
    std::vector<Shape> mPolygons;
    std::vector<Line> mLines;
    QVector<GLfloat> vertices;
    QVector<GLfloat> colors;
};