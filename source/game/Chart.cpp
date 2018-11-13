/*
 * =====================================================================================
 *
 *       Filename:  Chart.cpp
 *
 *    Description:
 *
 *        Created:  29/07/2018 13:25:24
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#include "Chart.hpp"

Chart::Chart(const std::string &path) {
	parse(path);
}

const ChartNote *Chart::getNextNote(u64 time) const {
	for (auto &it : m_notes)
		if (time < it.time)
			return &it;
	return nullptr;
}

void Chart::parse(const std::string &path) {
	m_parser.parse(path, m_notes);
}

