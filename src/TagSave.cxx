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

#include "TagSave.hxx"
#include "tag/Tag.hxx"
#include "io/BufferedOutputStream.hxx"

#include <fmt/format.h>

#define SONG_TIME "Time: "

void
tag_save(BufferedOutputStream &os, const Tag &tag)
{
	if (!tag.duration.IsNegative())
		os.Fmt(FMT_STRING(SONG_TIME "{}\n"), tag.duration.ToDoubleS());

	if (tag.has_playlist)
		os.Write("Playlist: yes\n");

	for (const auto &i : tag)
		os.Fmt(FMT_STRING("{}: {}\n"),
		       tag_item_names[i.type], i.value);
}
