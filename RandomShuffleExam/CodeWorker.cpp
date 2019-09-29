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
* File name: RandomShuffleExam/CodeWorker.cpp
* Date created: September 29, 2019
* Written by Bach Nguyen Sy
*/

#include "CodeWorker.h"
#include "Vietnamese.h"
#include <QDir>
#include <QProcess>
#include <QVector>
#include <utility>

CodeWorker::CodeWorker(QString exam, QString code, QString saveDir)
	: m_exam(std::move(exam)), m_code(std::move(code)), m_saveDir(std::move(saveDir))
{
	qRegisterMetaType<QVector<int>>();
}

CodeWorker::~CodeWorker() = default;

void CodeWorker::process()
{
	const auto input = QString("\"%1\"").arg(m_exam);
	const auto output = QString("\"%1\"").arg(m_saveDir);
	auto cmd = "bin\\7z.exe x " + input + " -o" + output;
	QProcess process(this);
	process.start(cmd);
	if(!process.waitForFinished(300000))
	{
		emit error(Vietnamese::str(L"E: Quá thời gian"));
		return;
	}

	const auto baseName = QFileInfo(m_exam).baseName();
	QDir dir(m_saveDir);
	dir.rename(baseName, m_code);

	const auto zipName = QString(R"("%1\%2.zip")").arg(m_saveDir).arg(m_code);
	const auto fileName = QString(R"("%1\%2\*")").arg(m_saveDir).arg(m_code);
	cmd = "bin\\7z.exe a -tzip " + zipName + " " + fileName;
	process.start(cmd);
	if (!process.waitForFinished(300000))
	{
		emit error(Vietnamese::str(L"E: Quá thời gian"));
		return;
	}

	dir.cd(m_code);
	dir.removeRecursively();
	emit finished();
}
