/*
 * Copyright 2020-2022 The Music Player Daemon Project
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

#undef NOUSER // COM needs the "MSG" typedef

#include "ComWorker.hxx"
#include "Com.hxx"
#include "thread/Name.hxx"

void
COMWorker::Work() noexcept
{
	SetThreadName("COM Worker");
	COM com;

	std::unique_lock lock{mutex};
	while (running_flag) {
		while (!queue.empty()) {
			auto function = std::move(queue.front());
			queue.pop();

			lock.unlock();
			function();
			lock.lock();
		}

		cond.wait(lock);
	}
}
