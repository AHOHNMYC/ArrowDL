/* - DownZemAll! - Copyright (C) 2019 Sebastien Vavassori
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this program; If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef CORE_ABSTRACT_DOWNLOAD_ITEM_H
#define CORE_ABSTRACT_DOWNLOAD_ITEM_H

#include <Core/IDownloadItem>

#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QUrl>
#include <QtCore/QTime>
#include <QtCore/QTimer>

class AbstractDownloadItem : public QObject, public IDownloadItem
{
    Q_OBJECT

public:
    explicit AbstractDownloadItem(QObject *parent = Q_NULLPTR);
    virtual ~AbstractDownloadItem() noexcept {} /* Important: This class is abstract. */

    virtual State state() const Q_DECL_OVERRIDE;
    void setState(const State state);

    virtual qint64 bytesReceived() const Q_DECL_OVERRIDE;
    void setBytesReceived(qint64 bytesReceived);

    virtual qint64 bytesTotal() const Q_DECL_OVERRIDE;
    void setBytesTotal(qint64 bytesTotal);

    virtual double speed() const Q_DECL_OVERRIDE;
    virtual int progress() const Q_DECL_OVERRIDE;

    int httpErrorNumber() const;
    void setHttpErrorNumber(int error);

    virtual int maxConnectionSegments() const Q_DECL_OVERRIDE;
    void setMaxConnectionSegments(int connectionSegments);

    virtual int maxConnections() const Q_DECL_OVERRIDE;
    void setMaxConnections(int connections);

    virtual bool isResumable() const Q_DECL_OVERRIDE;
    virtual bool isPausable() const Q_DECL_OVERRIDE;
    virtual bool isCancelable() const Q_DECL_OVERRIDE;
    virtual bool isDownloading() const Q_DECL_OVERRIDE;

    QTime remainingTime();

    virtual void setReadyToResume() Q_DECL_OVERRIDE;

    virtual void pause() Q_DECL_OVERRIDE;
    virtual void stop() Q_DECL_OVERRIDE;

    void beginResume();
    bool checkResume(bool connected);
    void tearDownResume();
    void preFinish(bool commited);

    void finish();

signals:
    void changed();
    void finished();

public slots:
    void updateInfo(qint64 bytesReceived, qint64 bytesTotal);

private slots:
    void updateInfo();

private:
    // todo: rendre privé, voire DownloadItemPrivate pour avoir une interface propre
    State m_state;

    qreal m_speed;
    qint64 m_bytesReceived;
    qint64 m_bytesTotal;

    int m_httpErrorNumber;

    int m_maxConnectionSegments;
    int m_maxConnections;

    QTime m_downloadTime;
    QTime m_remainingTime;
    QTimer m_updateInfoTimer;
    QTimer m_updateCountDownTimer;

};

#endif // CORE_ABSTRACT_DOWNLOAD_ITEM_H
