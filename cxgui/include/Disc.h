#include <Color.h>
#include <gtkmm/drawingarea.h>

namespace cxgui
{

class Disc : public Gtk::DrawingArea
{

public:

    Disc();
    Disc(double p_red, double p_green, double p_blue, double p_alpha);
    virtual ~Disc();

protected:

    // Signal handlers:
    bool on_draw(const Cairo::RefPtr<Cairo::Context>& p_context) override;

private:

    double m_red       {0.0};
    double m_green     {0.0};
    double m_blue      {0.0};
    double m_alpha     {0.0};
    bool   m_hasBorder {true};

};

} // namespace cxgui
