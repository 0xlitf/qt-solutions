// Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
// SPDX-License-Identifier: BSD-3-Clause

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMap>
#include "qtcanvas.h"

class QtProperty;

class CanvasView : public QtCanvasView
{
    Q_OBJECT
public:
    CanvasView(QWidget *parent = 0)
        : QtCanvasView(parent), moving(0) { }
    CanvasView(QtCanvas *canvas, QWidget *parent = 0)
        : QtCanvasView(canvas, parent), moving(0) { }
signals:
    void itemClicked(QtCanvasItem *item);
    void itemMoved(QtCanvasItem *item);
protected:
    void contentsMousePressEvent(QMouseEvent *event);
    void contentsMouseDoubleClickEvent(QMouseEvent *event);
    void contentsMouseMoveEvent(QMouseEvent* event);
private:
    void handleMouseClickEvent(QMouseEvent *event);
    QPoint moving_start;
    QtCanvasItem *moving;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);

private slots:
    void newRectangle();
    void newEllipse();
    void newLine();
    void newText();
    void deleteObject();
    void clearAll();
    void fillView();

    void itemClicked(QtCanvasItem *item);
    void itemMoved(QtCanvasItem *item);
    void valueChanged(QtProperty *property, double value);
    void valueChanged(QtProperty *property, const QString &value);
    void valueChanged(QtProperty *property, const QColor &value);
    void valueChanged(QtProperty *property, const QFont &value);
    void valueChanged(QtProperty *property, const QPoint &value);
    void valueChanged(QtProperty *property, const QSize &value);

private:
    QtCanvasItem *addRectangle();
    QtCanvasItem *addEllipse();
    QtCanvasItem *addLine();
    QtCanvasItem *addText();
    void addProperty(QtProperty *property, const QString &id);
    void updateExpandState();

    QAction *deleteAction;

    class QtDoublePropertyManager *doubleManager;
    class QtStringPropertyManager *stringManager;
    class QtColorPropertyManager *colorManager;
    class QtFontPropertyManager *fontManager;
    class QtPointPropertyManager *pointManager;
    class QtSizePropertyManager *sizeManager;

    class QtTreePropertyBrowser *propertyEditor;
    CanvasView *canvasView;
    QtCanvas *canvas;
    QtCanvasItem *currentItem;
    QMap<QtProperty *, QString> propertyToId;
    QMap<QString, QtProperty *> idToProperty;
    QMap<QString, bool> idToExpanded;
};

#endif
