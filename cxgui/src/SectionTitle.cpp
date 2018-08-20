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
 * @file    SectionTitle.cpp
 * @author  Eric Poirier
 * @date    May 2018
 * @version 1.0
 *
 * Implementation for a Section title widget.
 *
 **************************************************************************************************/

#include "../include/util.h"
#include "../include/SectionTitle.h"

cxgui::SectionTitle::SectionTitle(const std::string& p_title,
                                  const Gtk::Align p_alignement,
                                  const bool p_canExpandHorizontally,
                                  const bool p_canExpandVertically)
{
    attach(m_label         , 0, 0, 1, 1);
    attach(m_horizontalLine, 0, 1, 1, 1);

    // Label properties:
    const std::string boldTitle{addBoldMarkupTags(p_title)};
    m_label.set_text(boldTitle);
    m_label.set_use_markup(true);

    m_label.set_alignment(p_alignement);
    m_label.set_hexpand(p_canExpandHorizontally);
    m_label.set_vexpand(p_canExpandVertically);

    // Horizontal line properties:
    m_horizontalLine.set_hexpand(true);
    m_horizontalLine.set_vexpand(false);
}


cxgui::SectionTitle::~SectionTitle() = default;
