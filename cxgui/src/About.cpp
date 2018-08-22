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
 * @file    About.cpp
 * @author  Eric Poirier
 * @date    August 2018
 * @version 1.0
 *
 * Implementation for a simple 'about' dialog.
 *
 **************************************************************************************************/

#include <sstream>

#include <gtkmm/stock.h>

#include <cxgui/include/util.h>
#include <cxutil/include/util.h>

#include "../include/About.h"


namespace
{

/***********************************************************************************************//**
 * @brief Formats a copyright notice.
 *
 * Two formats are available, depending on the copyright years range. If the copyright is only
 * valid in 20XX, for example, the format <tt>Copyright © 20XX Owner</tt> will be used. If the
 * copiright is valid from 20XX to 20YY (with XX < YY), the the format will be:
 * <tt>Copyright © 20XX-20YY Owner</tt>.
 *
 * @param p_copyrightInfo A structure containing the necessary copyright information.
 *
 * @pre The copyright start year is at most equal to the copyright end year.
 *
 * @return The formatted copyright notice.
 *
 * @see cxgui::CopyrightInformation
 *
 **************************************************************************************************/
std::string buildCopyrightNotice(const cxgui::CopyrightInformation& p_copyrightInfo)
{
    const int  startYear    {p_copyrightInfo.m_copyrightStart.year()};
    const int  endYear      {p_copyrightInfo.m_copyrightEnd.year()};

    // The precondition is put here because it reads better with the local variable names and
    // if the condition is respected, no other call to the method returning the year from a
    // date is needed:
    PRECONDITION(startYear <= endYear);

    const bool oneYearFormat{startYear == endYear};

    std::ostringstream os;

    os << "Copyright © ";

    if(oneYearFormat)
    {
        os << startYear;
    }
    else
    {
        os << startYear << "-" << endYear;
    }

    os << " " << p_copyrightInfo.m_copyrightOwner;

    return os.str();
}


/***********************************************************************************************//**
 * @brief Formats the application name to add the version number.
 *
 * Formats the application name to add the version number in a consistent way. The format is as
 * follow for an application named 'Application name' with version number 'XX.YY':
 * <tt>Application Name XX.YY</tt>.
 *
 * @param p_applicationInfo A structure containing basic application information.
 *
 * @pre The @c ApplicationInformation structure holds a non-empty application name.
 * @pre The @c ApplicationInformation structure holds a non-empty application version number.
 *
 * @return The application name formatted with the version number.
 *
 * @see cxgui::ApplicationInformation
 *
 **************************************************************************************************/
std::string buildVersionedApplicationName(const cxgui::ApplicationInformation& p_applicationInfo)
{
    PRECONDITION(!p_applicationInfo.m_name.empty());
    PRECONDITION(!p_applicationInfo.m_version.empty());

    return p_applicationInfo.m_name + " " + p_applicationInfo.m_version;
}

} // unnamed namespace


cxgui::dlg::About::About(const ApplicationInformation& p_appInfo,
                         const CopyrightInformation& p_cpInfo)
 : m_artwork{Gtk::Image()}
 , m_softwareDescription{p_appInfo.m_description}
 , m_credits{"Credits"}
 , m_license{"License"}
 , m_close{Gtk::Stock::CLOSE}
{

    PRECONDITION(!p_appInfo.m_description.empty());
    PRECONDITION(!p_appInfo.m_name.empty());
    PRECONDITION(!p_appInfo.m_version.empty());

    // Window setup:
    set_title("About Connect X");

    std::string iconPath{cxutil::path::currentExecutablePath()};
    iconPath.append("/icons/cxicon16.png");

    set_icon_from_file(iconPath);
    set_position(Gtk::WIN_POS_CENTER);

    // Layouts registration:
    registerLayouts();

    // Widgets registration in layouts:
    registerWidgets();

    // Layout and Widgets look:
    const bool artworkDefined{!p_appInfo.m_pathToArtwork.empty()};

    if(artworkDefined)
    {
        m_artwork.set(p_appInfo.m_pathToArtwork);
        m_artwork.show();
    }
    else
    {
        m_artwork.hide();
    }

    // General information labels:
    const std::string applicationName{buildVersionedApplicationName(p_appInfo)};

    m_softwareName.set_label(cxgui::addBoldMarkupTags(cxgui::addBigMarkupTags(applicationName)));
    m_softwareName.set_use_markup(true);

    m_copyrightInformation.set_label(buildCopyrightNotice(p_cpInfo));

    // Here we show the widgets one by one, except for the artwork widget.
    // We deal with this on in the constructor:
    m_mainLayout          .show();
    m_softwareName        .show();
    m_softwareDescription .show();
    m_copyrightInformation.show();
    m_credits             .show();
    m_license             .show();
    m_close               .show();

    INVARIANTS();
}


cxgui::dlg::About::~About() = default;


void cxgui::dlg::About::registerLayouts()
{
    // Add the main layout to the window:
    add(m_mainLayout);
}


void cxgui::dlg::About::registerWidgets()
{
    // Add all widgets to the main layout:
    m_mainLayout.attach(m_artwork              ,0 ,0 ,3, 1);
    m_mainLayout.attach(m_softwareName         ,0 ,1 ,3, 1);
    m_mainLayout.attach(m_softwareDescription  ,0 ,2 ,3, 1);
    m_mainLayout.attach(m_copyrightInformation ,0 ,3 ,3, 1);
    m_mainLayout.attach(m_credits              ,0 ,4 ,1, 1);
    m_mainLayout.attach(m_license              ,1 ,4 ,1, 1);
    m_mainLayout.attach(m_close                ,2 ,4 ,1, 1);
}


void cxgui::dlg::About::checkInvariant() const
{
    INVARIANT(!m_softwareName.get_label().empty());
    INVARIANT(!m_softwareDescription.get_label().empty());
    INVARIANT(!m_copyrightInformation.get_label().empty());
}
