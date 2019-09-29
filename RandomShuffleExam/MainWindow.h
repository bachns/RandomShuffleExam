/********************************************************************************
*   Copyright (C) 2019 by Bach Nguyen Sy                                       *
*   Unauthorized copying of this file via any medium is strictly prohibited    *
*                                                                              *
*   <bachns.dev@gmail.com>                                                     *
*   https://bachns.wordpress.com                                               *
*   https://www.facebook.com/bachns.dev                                        *
*                                                                              *
********************************************************************************/

/**
* File name: RandomShuffleExam/MainWindow.h
* Date created: September 27, 2019
* Written by Bach Nguyen Sy
*/
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_MainWindow.h"
#include <QTimer>

class MainWindow final : public QMainWindow, Ui::MainWindowClass
{
	Q_OBJECT

public:
	explicit  MainWindow(QWidget *parent = Q_NULLPTR);

private slots:
	void process();
	
private:
	void createConnections();
	void initTableWidget() const;
	void selectDir();
	void loadExam();
	void shuffle() const;
	void apply();
	QTimer* m_timer;
	int m_currentIndex;
	bool m_codeWorderFinished;
	QString m_saveDir;
};


#endif // MAINWINDOW_H

