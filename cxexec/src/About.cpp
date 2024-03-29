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
 * Implementation for the Connect X 'about' dialog.
 *
 **************************************************************************************************/

#include <cxutil/include/Assertion.h>
#include <cxutil/include/Date.h>
#include <cxutil/include/util.h>

#include "../include/About.h"
#include "../include/util.h"


namespace
{

const cxgui::ApplicationInformation APPLICATION_INFORMATION
{
    cxutil::path::currentExecutablePath() + "/icons/cxicon64.png",
    "Connect X",
    "1.0",
    "A scalable connect 4 game."
};

const cxgui::CopyrightInformation COPYRIGHT_INFORMATION
{
    "Eric Poirier",
    cxutil::Date{2016, 1, 1},
    cxutil::Date()
};

} // unamed namespace


cx::ui::About::About() : cxgui::dlg::About(APPLICATION_INFORMATION, COPYRIGHT_INFORMATION)
{
}


cx::ui::About::~About() = default;


void cx::ui::About::setWindowIcon()
{
    cx::ui::setConnectXWindowIcon(this, cx::ui::IconSize::PIXELS_16);
}


void cx::ui::About::registerLayouts()
{
    // Nothing to do: only the main layout is used.
}


void cx::ui::About::configureSignalHandlers()
{
    // Important to call base class handers:
    cxgui::dlg::About::configureSignalHandlers();

    m_credits.signal_clicked().connect([this](){onCreditBtnClicked();}  );
    m_license.signal_clicked().connect([this](){onLicenseBtnClicked();} );
}


void cx::ui::About::onCreditBtnClicked()
{
    m_creditsWindow.reset(new cx::ui::Credits());
    CX_ASSERT(m_creditsWindow);

    m_creditsWindow->show_all();
}


void cx::ui::About::onLicenseBtnClicked()
{
    m_licenseWindow.reset(new cx::ui::License());
    CX_ASSERT(m_licenseWindow);

    m_licenseWindow->show_all();
}
