/***************************************************************************************************
 *
 * Copyright (C) 2018 Connect X team
 *
 * This file is part of Connect X.
 *
 * Connect X is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Connect X is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Connect X.  If not, see <http://www.gnu.org/licenses/>.
 *
 **************************************************************************************************/

/***********************************************************************************************//**
 * @file    SectionTitle.h
 * @author  Eric Poirier
 * @date    May 2018
 * @version 1.0
 *
 * Interface for a Section title widget.
 *
 **************************************************************************************************/

#ifndef SECTIONTITLE_H_B95063B1_0EAF_463E_B475_86C0AC7ED5F1
#define SECTIONTITLE_H_B95063B1_0EAF_463E_B475_86C0AC7ED5F1

#include <gtkmm/grid.h>
#include <gtkmm/label.h>
#include <gtkmm/separator.h>


namespace cxgui
{

/***********************************************************************************************//**
 * @class SectionTitle
 *
 * @brief Dialog section title.
 *
 * This class is used to create section titles within a dialog with a uniform layout. A section
 * title is nothing more than a title, in bold, that sits on top of an horizontal line separator.
 *
 **************************************************************************************************/
class SectionTitle final : public Gtk::Grid
{

public:

    /******************************************************************************************//**
     * @brief Constructor with parameters
     *
     *
     * @param p_title                  [in] The section title.
     * @param p_alignement             [in] The section title alignement. By default, the title
     *                                      is aligned to the left.
     * @param p_canExpandHorizontally  [in] @c true if the  section title can expand horizontally
     *                                      as the containing window expands, @c false otherwise.
     * @param p_canExpandVertically    [in] @c true if the  section title can expand vertically
     *                                      as the containing window expands, @c false otherwise.
     *
     *********************************************************************************************/
    SectionTitle(const std::string& p_title,
                 const Gtk::Align p_alignement = Gtk::Align::ALIGN_START,
                 const bool p_canExpandHorizontally = false,
                 const bool p_canExpandVertically = false
                 );


    /******************************************************************************************//**
     * @brief Default destructor.
     *
     *********************************************************************************************/
    ~SectionTitle();

private:

    Gtk::Label      m_label;                                                     ///< The label.
    Gtk::Separator  m_horizontalLine{Gtk::Orientation::ORIENTATION_HORIZONTAL};  ///< The horizontal line under the label.
};

} // namespace cxgui


#endif // SECTIONTITLE_H_B95063B1_0EAF_463E_B475_86C0AC7ED5F1
