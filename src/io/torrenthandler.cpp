/* - DownZemAll! - Copyright (C) 2019-present Sebastien Vavassori
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

#include "torrenthandler.h"

#include <Core/IDownloadItem>
#include <Core/TorrentMessage>

#include <QtCore/QDebug>
#include <QtCore/QFile>


bool TorrentHandler::canRead() const
{
    return true;
}

bool TorrentHandler::canWrite() const
{
    return false;
}

bool TorrentHandler::read(DownloadEngine *engine)
{
    if (!engine) {
        qWarning("TorrentHandler::read() cannot read into null pointer");
        return false;
    }
    QIODevice *d = device();
    if (!d->isReadable()) {
        return false;
    }
    /*
     * Rem: The .torrent file is not read at this point.
     * The address is simply passed to the DownloadTorrentItem.
     * The DownloadTorrentItem is in charge of (down)loading the .torrent file
     * (eventually from magnet link), that contains metadata,
     * and finally download the data of the file itself.
     */
    QUrl url;
    auto f = dynamic_cast<QFile*>(d);
    if (f) {
        auto filename = f->fileName();
        url = QUrl(filename);
    }
    IDownloadItem *item = engine->createTorrentItem(url);
    if (!item) {
        qWarning("DownloadEngine::createItem() not overridden. It still returns null pointer!");
        return false;
    }

    QList<IDownloadItem*> items;
    items.append(item);
    engine->append(items, false);
    return true;
}

bool TorrentHandler::write(const DownloadEngine &/*engine*/)
{
    return false;
}
