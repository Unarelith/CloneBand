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
#include <fstream>

#include "Chart.hpp"
#include "Exception.hpp"

Chart::Chart(const std::string &path) {
	parse(path);
}

const ChartNote *Chart::getNextNote(u64 time) {
	for (auto &it : m_notes)
		if (time < it.time)
			return &it;
	return nullptr;
}

void Chart::parse(const std::string &path) {
	std::ifstream chart(path);
	if (!chart.is_open())
		throw EXCEPTION("Error failed to open:", path);

	while (parseSection(chart));

	chart.close();
}

bool Chart::parseSection(std::ifstream &chart) {
	if (chart.get() != '[')
		return false;

	std::string sectionName;
	std::getline(chart, sectionName, ']');

	DEBUG("Section name:", sectionName);

	skipWhitespaces(chart);

	if (sectionName != "MediumSingle") {
		std::string sectionLine;
		while (std::getline(chart, sectionLine, '\n') && sectionLine[0] != '}')
			skipWhitespaces(chart);
	}
	else {
		if (char c = chart.get() ; c != '{')
			throw EXCEPTION("Syntax error at char '", (int)c, "'", chart.tellg());

		skipWhitespaces(chart);

		try {
			while (parseNotes(chart))
				skipWhitespaces(chart);
		}
		catch(...) {
			throw EXCEPTION("Syntax error at char '", (int)chart.peek(), "'", chart.tellg());
		}
	}

	return true;
}

bool Chart::parseNotes(std::ifstream &chart) {
	if (chart.peek() == '}') {
		chart.get();
		return false;
	}

	std::string key;
	std::getline(chart, key, '=');
	u64 notePosition = std::stoull(key);

	skipWhitespaces(chart);
	char eventType = chart.get();
	if (eventType != 'N') {
		while (chart.get() != '\n');
		return true;
	}

	skipWhitespaces(chart);
	int noteType = chart.get() - '0';
	skipWhitespaces(chart);

	std::string length;
	std::getline(chart, length, '\n');
	int noteLength = std::stoi(length);

	// FIXME: Read this data from the .chart file
	float currentBpm = 127500 / 1000.0f;
	u32 resolution = 192;
	u32 offset = 2200;
	if (!m_notes.empty()) {
		m_time += 1000 * ((notePosition - m_notes.back().position) * 60 / (currentBpm * resolution));
	}
	int noteTime = m_time + offset;

	if (notePosition < 1000)
		DEBUG("New note:", notePosition, noteTime, eventType, noteType, noteLength);

	m_notes.emplace_back(m_notes.size(), notePosition, noteTime, noteType, noteLength);

	return true;
}

void Chart::skipWhitespaces(std::ifstream &chart) {
	while (chart.peek() == ' ' || chart.peek() == '\n' || chart.peek() == '\t' || chart.peek() == '\r')
		chart.get();
}

