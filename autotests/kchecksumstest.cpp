/*
    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include <KFileItem>
#include <KPropertiesDialog>

#include <QCryptographicHash>
#include <QFile>
#include <QLineEdit>
#include <QPushButton>
#include <QStandardPaths>
#include <QTemporaryDir>
#include <QTest>

class KChecksumsTest : public QObject
{
    Q_OBJECT

private Q_SLOTS:
    void initTestCase()
    {
        QStandardPaths::setTestModeEnabled(true);
    }

    void calculatesChecksums_data()
    {
        QTest::addColumn<QString>("kind");
        QTest::newRow("empty-file") << QStringLiteral("empty");
        QTest::newRow("regular-file") << QStringLiteral("regular");
        QTest::newRow("zero-size-readable-file") << QStringLiteral("proc");
    }

    void calculatesChecksums()
    {
        QFETCH(QString, kind);
        QTemporaryDir directory;
        QVERIFY(directory.isValid());

        QString path;
        QByteArray contents;
        if (kind == QLatin1String("proc")) {
#ifdef Q_OS_LINUX
            path = QStringLiteral("/proc/version");
            QFile file(path);
            if (!file.open(QIODevice::ReadOnly) || file.size() != 0) {
                QSKIP("A readable, zero-size procfs fixture is unavailable");
            }
            contents = file.readAll();
            QVERIFY(!contents.isEmpty());
#else
            QSKIP("The zero-size readable file fixture requires procfs on Linux");
#endif
        } else {
            path = directory.filePath(QStringLiteral("checksum.txt"));
            if (kind == QLatin1String("regular")) {
                contents = QByteArray(4097, 'x'); // Exercise multiple reads and progress updates.
            }
            QFile file(path);
            QVERIFY(file.open(QIODevice::WriteOnly));
            QCOMPARE(file.write(contents), qint64(contents.size()));
        }

        const KFileItem item(QUrl::fromLocalFile(path));
        KPropertiesDialog dialog(item);
        const struct {
            const char *prefix;
            QCryptographicHash::Algorithm algorithm;
        } algorithms[] = {
            {"md5", QCryptographicHash::Md5},
            {"sha1", QCryptographicHash::Sha1},
            {"sha256", QCryptographicHash::Sha256},
            {"sha512", QCryptographicHash::Sha512},
        };
        for (const auto &algorithm : algorithms) {
            const QString prefix = QString::fromLatin1(algorithm.prefix);
            auto *button = dialog.findChild<QPushButton *>(prefix + QStringLiteral("Button"));
            auto *result = dialog.findChild<QLineEdit *>(prefix + QStringLiteral("LineEdit"));
            QVERIFY(button);
            QVERIFY(result);
            const QString expected = QString::fromLatin1(QCryptographicHash::hash(contents, algorithm.algorithm).toHex());
            button->click();
            QTRY_COMPARE_WITH_TIMEOUT(result->text(), expected, 10000);
        }
    }
};

QTEST_MAIN(KChecksumsTest)

#include "kchecksumstest.moc"
