/*
 * Copyright 2003-2022 The Music Player Daemon Project
 * http://www.musicpd.org
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#include "DirectoryReader.hxx"
#include "lib/fmt/PathFormatter.hxx"
#include "lib/fmt/SystemError.hxx"

#ifdef _WIN32

#include <handleapi.h> // for INVALID_HANDLE_VALUE

DirectoryReader::DirectoryReader(Path dir)
	:handle(FindFirstFile(MakeWildcardPath(dir.c_str()), &data))
{
	if (handle == INVALID_HANDLE_VALUE)
		throw FmtLastError("Failed to open {}", dir);
}

#else

DirectoryReader::DirectoryReader(Path dir)
	:dirp(opendir(dir.c_str()))
{
	if (dirp == nullptr)
		throw FmtErrno("Failed to open {}", dir);
}

#endif
