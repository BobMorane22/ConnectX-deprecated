#include <algorithm>
#include <cmath>

#include "Disc.h"

using namespace cxgui;


Disc::Disc() : m_red{0.0}, m_green{0.0}, m_blue{0.0}, m_alpha{1.0}
{
}


Disc::~Disc() = default;


Disc::Disc(double p_red, double p_green, double p_blue, double p_alpha):
           m_red{p_red}, m_green{p_green}, m_blue{p_blue}, m_alpha{p_alpha}
{
}


bool Disc::on_draw(const Cairo::RefPtr<Cairo::Context>& p_context)
{
    // Get space allocated by parent widget to the Disc:
    const Gtk::Allocation allocation{get_allocation()};

    const int width{allocation.get_width()};
    const int height{allocation.get_height()};
    const int smallestDimension{std::min(width, height)};

    // Get allocated space center position coordinates:
    const int xCenter{width / 2};
    const int yCenter{height / 2};

    // Change border thikness according to parent dimensions:
    p_context->set_line_width(smallestDimension * 0.02);

    // Define and draw the background:
    p_context->save();

    p_context->set_source_rgba(0.0, 0.0, 1.0, 1.0);

    p_context->move_to(0, 0);
    p_context->line_to(width, 0);
    p_context->line_to(width, height);
    p_context->line_to(0, height);
    p_context->line_to(0, 0);

    p_context->fill();

    p_context->restore();

    // Define and draw the circle:
    p_context->save();

    p_context->arc(xCenter,
                   yCenter,
                   smallestDimension / 2.5,
                   0.0,
                   2.0 * M_PI);

    p_context->set_source_rgba(m_red, m_green, m_blue, m_alpha);
    p_context->fill_preserve();

    p_context->restore();

    // Stroke the boarder in black, if needed:
    if(m_hasBorder)
    {
        p_context->stroke();
    }

    return true;
}
