/*
 * =====================================================================================
 *
 *       Filename:  ChartParser.hpp
 *
 *    Description:
 *
 *        Created:  17/10/2018 15:54:06
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef CHARTPARSER_HPP_
#define CHARTPARSER_HPP_

#include <map>
#include <string>
#include <vector>

#include <gk/core/IntTypes.hpp>

struct ChartNote;

class ChartParser {
	public:
		void parse(const std::string &filepath, std::vector<ChartNote> &notes);

	private:
		bool parseSection(std::ifstream &chart, std::vector<ChartNote> &notes);
		bool parseSongInfo(std::ifstream &chart);
		bool parseSyncTrack(std::ifstream &chart);
		bool parseNotes(std::ifstream &chart, std::vector<ChartNote> &notes);

		float getCurrentBpm(u64 position);

		void skipWhitespaces(std::ifstream &chart);

		u64 m_time = 0;

		// FIXME: Move this
		u32 m_songResolution = 0;
		u32 m_songOffset = 0;
		std::map<u64, u32> m_songBpm;
};

#endif // CHARTPARSER_HPP_
