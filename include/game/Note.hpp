/*
 * =====================================================================================
 *
 *       Filename:  Note.hpp
 *
 *    Description:
 *
 *        Created:  29/07/2018 13:06:25
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef NOTE_HPP_
#define NOTE_HPP_

#include "Chart.hpp"
#include "Sprite.hpp"

class Note : public IDrawable, public Transformable {
	public:
		Note(const ChartNote &note);

		const ChartNote &note() const { return *m_note; }

		u16 width() { return m_sprite.frameWidth(); }
		u16 height() { return m_sprite.frameHeight(); }

	private:
		void draw(RenderTarget &target, RenderStates states) const override;

		Sprite m_sprite{"texture-notes", 132, 132};
		Image m_tail{"texture-tail"};

		const ChartNote *m_note;
};

#endif // NOTE_HPP_
