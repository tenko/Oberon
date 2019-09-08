/*
* Copyright 2019 Rochus Keller <mailto:me@rochus-keller.ch>
*
* This file is part of the Oberon to C++ (OBNCPP) transpiler.
*
* The following is the license that applies to this copy of the
* application. For a license to use the application under conditions
* other than those described here, please email to me@rochus-keller.ch.
*
* GNU General Public License Usage
* This file may be used under the terms of the GNU General Public
* License (GPL) versions 2.0 or 3.0 as published by the Free Software
* Foundation and appearing in the file LICENSE.GPL included in
* the packaging of this file. Please review the following information
* to ensure GNU General Public Licensing requirements will be met:
* http://www.fsf.org/licensing/licenses/info/GPLv2.html and
* http://www.gnu.org/copyleft/gpl.html.
*/

#include <QCoreApplication>
#include <QFile>
#include <QtDebug>
#include <QFileInfo>
#include <QDir>
#include <QThread>
//#include "LuaJitBytecode.h"
#include "ObCodeModel.h"
#include "ObErrors.h"
#include "ObLjbcGen.h"

static QStringList collectFiles( const QDir& dir )
{
    QStringList res;
    QStringList files = dir.entryList( QDir::Dirs | QDir::NoDotAndDotDot, QDir::Name );

    foreach( const QString& f, files )
        res += collectFiles( QDir( dir.absoluteFilePath(f) ) );

    files = dir.entryList( QStringList() << QString("*.Mod")
                                           << QString("*.mod"),
                                           QDir::Files, QDir::Name );
    foreach( const QString& f, files )
    {
        res.append( dir.absoluteFilePath(f) );
    }
    return res;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    a.setOrganizationName("Rochus Keller");
    a.setOrganizationDomain("https://github.com/rochus-keller/Oberon");
    a.setApplicationName("OBNLJC");
    a.setApplicationVersion("2019-08-21");

    QTextStream out(stdout);
    out << "OBNLJC version: " << a.applicationVersion() <<
                 " author: me@rochus-keller.ch  license: GPL" << endl;

    QStringList dirOrFilePaths;
    QString outPath;
    bool syntImports = true;
    const QStringList args = QCoreApplication::arguments();
    for( int i = 1; i < args.size(); i++ ) // arg 0 enthaelt Anwendungspfad
    {
        if(  args[i] == "-h" || args.size() == 1 )
        {
            out << "usage: OBNLJC [options] sources" << endl;
            out << "  reads Oberon sources (files or directories) and translates them to corresponding C++ code." << endl;
            out << "options:" << endl;
            out << "  -dsmi     don't synthesize missing imports" << endl;
            out << "  -dst      dump syntax trees to files" << endl;
            out << "  -o=path   path where to save generated files (default like first source)" << endl;
            out << "  -ns=name  namespace for the generated files (default empty)" << endl;
            out << "  -mod=name directory of the generated files (default empty)" << endl;
            out << "  -h        display this information" << endl;
            return 0;
        }else if( args[i] == "-dsmi" )
            syntImports = false;
        else if( args[i].startsWith("-o=") )
            outPath = args[i].mid(3);
        else if( !args[ i ].startsWith( '-' ) )
        {
            dirOrFilePaths += args[ i ];
        }else
        {
            qCritical() << "error: invalid command line option " << args[i] << endl;
            return -1;
        }
    }
    if( dirOrFilePaths.isEmpty() )
    {
        qWarning() << "no file or directory to process; quitting (use -h option for help)" << endl;
        return -1;
    }

    QStringList files;
    foreach( const QString& path, dirOrFilePaths )
    {
        QFileInfo info(path);
        if( outPath.isEmpty() )
            outPath = info.isDir() ? info.absoluteFilePath() : info.absolutePath();
        if( info.isDir() )
            files += collectFiles( info.absoluteFilePath() );
        else
            files << path;
    }

    qDebug() << "processing" << files.size() << "files...";

    Ob::CodeModel m;
    m.getErrs()->setRecord(false);
    m.setSynthesize(syntImports);
    m.parseFiles(files);

    qDebug() << "generating files...";
    Ob::LjbcGen g(&m);
    g.emitModules(outPath);

    if( m.getErrs()->getErrCount() == 0 && m.getErrs()->getWrnCount() == 0 )
        qDebug() << "successfully completed";
    else
        qDebug() << "completed with" << m.getErrs()->getErrCount() << "errors and" <<
                    m.getErrs()->getWrnCount() << "warnings";
    return 0;
}
