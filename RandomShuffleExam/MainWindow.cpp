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
* File name: RandomShuffleExam/MainWindow.cpp
* Date created: September 27, 2019
* Written by Bach Nguyen Sy
*/

#include "MainWindow.h"
#include "Vietnamese.h"
#include <QFileDialog>
#include <QHeaderView>
#include <QMessageBox>
#include <QProgressBar>
#include <QFile>
#include <QTextStream>
#include <QFileInfo>
#include <QThread>
#include <random>
#include "CodeWorker.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, m_currentIndex(0)
	, m_codeWorderFinished(false)
{
	setupUi(this);
	m_timer = new QTimer(this);
	
	initTableWidget();
	createConnections();
}

void MainWindow::createConnections()
{
	connect(browseBtn, &QPushButton::clicked, [=] { loadExam(); });
	connect(shuffleBtn, &QPushButton::clicked, [=] { shuffle(); });
	connect(applyBtn, &QPushButton::clicked, [=] { apply(); });
	connect(cancelBtn, &QPushButton::clicked, [=] { m_timer->stop(); close(); });
	connect(selectDirBtn, &QPushButton::clicked, [=] { selectDir(); });
	connect(m_timer, &QTimer::timeout, this, &MainWindow::process);
}

void MainWindow::process()
{
	if (m_currentIndex < tableWidget->rowCount())
	{
		if (m_codeWorderFinished)
		{
			const auto exam = tableWidget->item(m_currentIndex, 0)->text();
			const auto code = tableWidget->item(m_currentIndex, 1)->text();
			auto progressBar = dynamic_cast<QProgressBar*>(tableWidget->cellWidget(m_currentIndex, 2));
			progressBar->setMinimum(0);
			progressBar->setMaximum(0);

			auto thread = new QThread;
			auto worker = new CodeWorker(exam, code, m_saveDir);
			worker->moveToThread(thread);
			connect(thread, &QThread::started, [=] { m_codeWorderFinished = false; });
			connect(thread, SIGNAL(started()), worker, SLOT(process()));
			connect(worker, &CodeWorker::finished, [=] {
				tableWidget->removeCellWidget(m_currentIndex, 2);
				const auto item = new QTableWidgetItem("Xong");
				item->setTextAlignment(Qt::AlignCenter);
				tableWidget->setItem(m_currentIndex, 2, item);
				m_codeWorderFinished = true;
				m_currentIndex++;
			});
			connect(worker, &CodeWorker::error, [=](const QString& message)
			{
				tableWidget->removeCellWidget(m_currentIndex, 2);
				const auto item = new QTableWidgetItem(message);
				item->setTextAlignment(Qt::AlignCenter);
				tableWidget->setItem(m_currentIndex, 2, item);
				m_codeWorderFinished = true;
				m_currentIndex++;
			});
			connect(worker, SIGNAL(finished()), thread, SLOT(quit()));
			connect(worker, SIGNAL(finished()), worker, SLOT(deleteLater()));
			connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
			thread->start();
		}
	}
	else
	{
		m_timer->stop();
		QFile textFile(m_saveDir + "\\sophach.txt");
		if (textFile.open(QIODevice::WriteOnly | QIODevice::Text))
		{
			QTextStream textStream(&textFile);
			for (auto i = 0; i < tableWidget->rowCount(); i++)
			{
				const auto exam = tableWidget->item(i, 0)->text();
				const auto code = tableWidget->item(i, 1)->text();
				textStream << code << " : " << QFileInfo(exam).baseName() << "\n";
			}
			textFile.close();
		}
		QMessageBox::information(this, windowTitle(),
			Vietnamese::str(L"Hoàn thành!\nKiểm tra sophach.txt để xem chi tiết"));
	}
}

void MainWindow::initTableWidget() const
{
	tableWidget->setColumnCount(3);
	tableWidget->setHorizontalHeaderLabels(
		{Vietnamese::str(L"Bài làm"), Vietnamese::str(L"Số phách"),
			Vietnamese::str(L"Tiến trình")});
	tableWidget->horizontalHeader()->setStretchLastSection(false);
	tableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
	tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
	tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void MainWindow::selectDir()
{
	const auto location = QFileDialog::getExistingDirectory(this,
		Vietnamese::str(L"Chọn nơi lưu kết quả"));
	if (!location.isEmpty())
	{
		dirLedr->setText(location);
	}
}

void MainWindow::loadExam()
{
	const auto exams = QFileDialog::getOpenFileNames(this,
		Vietnamese::str(L"Chọn bài làm"), QString(),
		Vietnamese::str(L"Tệp tin nén (*.zip *.7z *.rar)"));
	if (!exams.isEmpty())
	{
		tableWidget->setRowCount(0);
		for (auto i = 0; i < exams.size(); i++)
		{
			tableWidget->insertRow(i);
			const auto item = new QTableWidgetItem(exams.at(i));
			tableWidget->setItem(i, 0, item);
		}
		tableWidget->resizeRowsToContents();
		tableWidget->clearSelection();
		shuffle();
	}
}

void MainWindow::shuffle() const
{
	std::vector<int> codes(tableWidget->rowCount());
	for (auto i = 0; i < tableWidget->rowCount(); i++)
	{
		codes.at(i) = i + 1;
	}
	std::random_device rd;
	std::mt19937 g(rd());
	std::shuffle(codes.begin(), codes.end(), g);
	for (auto i = size_t(0); i < codes.size(); i++)
	{
		const auto code = QString("%1").arg(codes.at(i), 2, 10, QLatin1Char('0'));
		const auto item = new QTableWidgetItem(code);
		item->setTextAlignment(Qt::AlignCenter);
		tableWidget->setItem(i, 1, item);
	}
}

void MainWindow::apply()
{
	m_saveDir = dirLedr->text().trimmed();
	if (m_saveDir.isEmpty())
	{
		QMessageBox::warning(this, windowTitle(),
			Vietnamese::str(L"Chưa chọn vị trí lưu kết quả"));
		return;
	}
	
	for (auto i = 0; i < tableWidget->rowCount(); i++)
	{
		tableWidget->takeItem(i, 2);
		const auto progressBar = new QProgressBar;
		progressBar->setTextVisible(false);
		tableWidget->setCellWidget(i, 2, progressBar);
	}

	if (tableWidget->rowCount())
	{
		m_currentIndex = 0;
		m_codeWorderFinished = true;
		m_timer->start(1000);
	}
}