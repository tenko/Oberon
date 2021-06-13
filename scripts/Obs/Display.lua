--[[
* Copyright 2021 Rochus Keller <mailto:me@rochus-keller.ch>
*
* This file is part of the Oberon+ parser/compiler library.
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
]]--

local module = {}

local obxlj = require("obxlj")
local ffi = require 'ffi'
local C = ffi.C

ffi.cdef[[
	typedef uint8_t ByteArray[];
	void ObxFfi_initByteArrayFromHex( ByteArray ba, int count, const char* hex );
	void ObsDisplay_ReplConst(int color, int x, int y, int w, int h, int mode );
	void ObxDisplay_CopyPattern(int color, ByteArray patadr, int count, int x, int y, int mode );
	void ObxDisplay_CopyBlock(int sx, int sy, int w, int h, int dx, int dy, int mode);
	void ObxDisplay_Dot(int color, int x, int y, int mode);
]]

local Width = 1024
local Height = 768

local patternLen = 32

local arrow = obxlj.createByteArray(patternLen)
C.ObxFfi_initByteArrayFromHex(arrow,patternLen,"0F0F 0060 0070 0038 001C 000E 0007 8003 C101 E300 7700 3F00 1F00 3F00 7F00 FF00")

local star = obxlj.createByteArray(patternLen)
C.ObxFfi_initByteArrayFromHex(arrow,patternLen,"0F0F 8000 8220 8410 8808 9004 A002 C001 7F7F C001 A002 9004 8808 8410 8220 8000")

local hook = obxlj.createByteArray(patternLen)
C.ObxFfi_initByteArrayFromHex(arrow,patternLen,"0C0C 070F 8707 C703 E701 F700 7F00 3F00 1F00 0F00 0700 0300 01")

local updown = obxlj.createByteArray(patternLen)
C.ObxFfi_initByteArrayFromHex(arrow,patternLen,"080E 183C 7EFF 1818 1818 1818 FF7E3C18")

local block = obxlj.createByteArray(patternLen)
C.ObxFfi_initByteArrayFromHex(arrow,patternLen,"0808 FFFF C3C3 C3C3 FFFF")

function module.ReplConst(color, x, y, w, h, mode)
	C.ObsDisplay_ReplConst(color, x, y, w, h, mode)
end

function module.CopyPattern(color, patadr, x, y, mode )
	C.ObxDisplay_CopyPattern(color, patadr, ffi.sizeof(patadr), x, y, mode )
end

function module.CopyBlock(sx, sy, w, h, dx, dy, mode)
	C.ObxDisplay_CopyBlock(sx, sy, w, h, dx, dy, mode)
end

function module.Dot(col, x, y, mode)
	C.ObxDisplay_Dot(col, x, y, mode)
end

-- NOTE: these numbers are allocated by ObxLjbcGen and need to be updated if Display.Def changes!
module[0] = Width
module[1] = Height
module[2] = arrow
module[3] = star
module[4] = hook
module[5] = updown
module[6] = block
module[7] = module.ReplConst
module[8] = module.CopyPattern
module[9] = module.CopyBlock
module[10] = module.Dot
module[11] = {} -- record FrameMsg
module[12] = {} -- record FrameDesc

return module
