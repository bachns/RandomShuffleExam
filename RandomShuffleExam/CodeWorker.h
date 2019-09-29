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
* File name: RandomShuffleExam/CodeWorker.h
* Date created: September 29, 2019
* Written by Bach Nguyen Sy
*/

#ifndef CODEWORKER_H
#define CODEWORKER_H

#include <QObject>

class CodeWorker final : public QObject
{
	Q_OBJECT
	
public:
	CodeWorker(QString exam, QString code, QString saveDir);
	~CodeWorker();

public slots:
	void process();

signals:
	void finished();

private:
	QString m_exam;
	QString m_code;
	QString m_saveDir;
};

#endif // CODEWORKER_H


