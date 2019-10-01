#ifndef OBLJBCGEN_H
#define OBLJBCGEN_H

/*
* Copyright 2019 Rochus Keller <mailto:me@rochus-keller.ch>
*
* This file is part of the Oberon parser/compiler library.
*
* The following is the license that applies to this copy of the
* library. For a license to use the library under conditions
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

#include <Oberon/ObCodeModel.h>

namespace Lua
{
    class JitComposer;
}
namespace Ob
{
    class CodeModel;
    class Errors;

    class LjbcGen : public QObject
    {
    public:
        explicit LjbcGen(CodeModel*);
        bool emitModules(const QString& outdir );
        QByteArray emitModule( CodeModel::Module* );
    protected:
        void emitDecls(const CodeModel::Unit* ds, Lua::JitComposer& out );
        void emitProc(const CodeModel::Unit* ds, Lua::JitComposer& out );
        void emitStatementSeq(const CodeModel::Unit* ds, const QList<SynTree*>& seq, Lua::JitComposer& out );
    private:
        CodeModel* d_mdl;
        Errors* d_errs;
        CodeModel::Module* d_curMod;
    };
}

#endif // OBLJBCGEN_H
