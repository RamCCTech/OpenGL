#include "stdafx.h"
#include "OpenGLWindow.h"
#include <QOpenGLContext>
#include <QOpenGLPaintDevice>
#include <QOpenGLShaderProgram>
#include <QPainter>
#include "SutherlandCohen.h"
#include "SutherlandHodgman.h"
#include "HermiteCurve.h"
#include "BezierCurve.h"
#include "BSplineCurve.h"

OpenGLWindow::OpenGLWindow(const QColor& background, QWidget* parent) : mBackground(background)
{
    setParent(parent);
    setMinimumSize(300, 250);
    const QStringList pathList = { "vertexShader.glsl" ,"fragmentShader.glsl" };
    mShaderWatcher = new QFileSystemWatcher(pathList, this);
    connect(mShaderWatcher, &QFileSystemWatcher::fileChanged, this, &OpenGLWindow::shaderWatcher);

    mTimer = new QTimer(this);
    connect(mTimer, SIGNAL(timeout()), this, SLOT(updateAnimation()));
    mTimer->start(16);
    mTimeValue = 0.0f;
}

OpenGLWindow::~OpenGLWindow()
{
    reset();
}

void OpenGLWindow::reset()
{
    makeCurrent();
    delete mProgram;
    mProgram = nullptr;
    delete mVshader;
    mVshader = nullptr;
    delete mFshader;
    mFshader = nullptr;
    mVbo.destroy();
    doneCurrent();

    QObject::disconnect(mContextWatchConnection);
}
QString OpenGLWindow::readShader(QString path)
{
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return "Invalid file!";

    QTextStream stream(&file);
    QString line = stream.readLine();
    while (!stream.atEnd()) {
        line.append(stream.readLine());
    }
    file.close();
    return line;
}
void OpenGLWindow::shaderWatcher()
{
    QString vertexShaderSource = readShader("vertexShader.glsl");
    QString fragmentShaderSource = readShader("fragmentShader.glsl");

    mProgram->release();
    mProgram->removeAllShaders();
    mProgram = new QOpenGLShaderProgram(this);
    mProgram->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource);
    mProgram->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSource);

    mProgram->link();
}
void OpenGLWindow::initializeGL()
{
    QString vertexShaderSource = readShader("vertexShader.glsl");
    QString fragmentShaderSource = readShader("fragmentShader.glsl");

    initializeOpenGLFunctions();

    mProgram = new QOpenGLShaderProgram(this);
    mProgram->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource);
    mProgram->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSource);

    mProgram->link();

    m_posAttr = mProgram->attributeLocation("posAttr");
    Q_ASSERT(m_posAttr != -1);
    m_colAttr = mProgram->attributeLocation("colAttr");
    Q_ASSERT(m_colAttr != -1);
    m_matrixUniform = mProgram->uniformLocation("matrix");
    Q_ASSERT(m_matrixUniform != -1);
}


void OpenGLWindow::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);
    mProgram->bind();
    setupMatrix();
    mProgram->setUniformValue("time", mTimeValue);

    drawVertices(mVertices, mColors);

    mProgram->release();
}


void OpenGLWindow::drawVertices(const QVector<GLfloat>& vertices, const QVector<GLfloat>& colors)
{
    glVertexAttribPointer(m_posAttr, 2, GL_FLOAT, GL_FALSE, 0, vertices.data());
    glVertexAttribPointer(m_colAttr, 3, GL_FLOAT, GL_FALSE, 0, colors.data());

    glEnableVertexAttribArray(m_posAttr);
    glEnableVertexAttribArray(m_colAttr);

    glDrawArrays(GL_LINES, 0, vertices.size() / 2);

    glDisableVertexAttribArray(m_colAttr);
    glDisableVertexAttribArray(m_posAttr);
}
void OpenGLWindow::updateAnimation() {
    mTimeValue += 0.05f;
    update();
}
void OpenGLWindow::setupMatrix()
{
    QMatrix4x4 matrix;
    matrix.ortho(-10.0f, 10.0f, -10.0f, 10.0f, 0.1f, 100.0f);
    matrix.translate(0, 0, -2);
    matrix.rotate(rotationAngle);

    mProgram->setUniformValue(m_matrixUniform, matrix);
}

void OpenGLWindow::mouseMoveEvent(QMouseEvent* event)
{
    int dx = event->x() - lastPos.x();
    int dy = event->y() - lastPos.y();

    if (event->buttons() & Qt::LeftButton)
    {
        QQuaternion rotX = QQuaternion::fromAxisAndAngle(0.0f, 1.0f, 0.0f, 0.5f * dx);
        QQuaternion rotY = QQuaternion::fromAxisAndAngle(1.0f, 0.0f, 0.0f, 0.5f * dy);

        rotationAngle = rotX * rotY * rotationAngle;
        update();
    }
    lastPos = event->pos();
}

void OpenGLWindow::updateShape(QVector<GLfloat>& vertices, QVector<GLfloat>& colors)
{
    mVertices = vertices;
    mColors = colors;
    emit shapesUpdated();
}

void OpenGLWindow::setColor(const QString& text, const QString& filePath) {
    QFile file(filePath);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream stream(&file);
        stream << "varying lowp vec4 col;\n";
        stream << "void main() {\n";
        stream << "    gl_FragColor = vec4(" + text + ");\n";
        stream << "}\n";
        file.close();
        qDebug() << "String written to file successfully.";
    }
    else {
        qDebug() << "Failed to open the file.";
    }
}