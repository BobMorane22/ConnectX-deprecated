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
 * @file    Credits.cpp
 * @author  Eric Poirier
 * @date    September 2018
 * @version 1.0
 *
 * Implementation for a simple credits dialog.
 *
 **************************************************************************************************/

#include <algorithm>
#include <fstream>
#include <regex>

#include <pangomm/fontdescription.h>

#include <cxutil/include/Assertion.h>
#include <cxutil/include/Color.h>
#include <cxutil/include/ContractException.h>
#include <cxutil/include/narrow_cast.h>
#include <cxutil/include/util.h>
#include <cxgui/include/util.h>

#include "../include/Credits.h"


cxgui::dlg::Credits::Credits(const std::map<CreditedTeam, ContributorList>& p_contributorLists)
 : m_fromFile{false}
{
    PRECONDITION(!p_contributorLists.empty());
    PRECONDITION(p_contributorLists.size() < cxutil::narrow_cast<unsigned int>(CreditedTeam::LAST) + 1);

    // Lists setup:
    for(const auto& list : p_contributorLists)
    {
        switch(list.first)
        {
            case CreditedTeam::DEVELOPMENT:
            {
                m_devList = list.second;

                break;
            }
            case CreditedTeam::DOCUMENTATION:
            {
                m_docList = list.second;

                break;
            }
            case CreditedTeam::ARTWORK:
            {
                m_artList = list.second;

                break;
            }
            default:
            {
                CX_ASSERT_MSG(false, "Impossible, not a defined team.");
                break;
            }
        }
    }

    // Window setup:
    set_title("Credits");

    std::string iconPath{cxutil::path::currentExecutablePath()};
    iconPath.append("/icons/cxicon16.png");

    set_icon_from_file(iconPath);
    set_position(Gtk::WIN_POS_CENTER);

    // Layouts registration:
    registerLayouts();

    // Widgets registration in layouts:
    registerWidgets();

    // Layout and Widgets look:
    configureLayoutsAndWidgets();

    // Display all widgets:
    show_all();
}

cxgui::dlg::Credits::Credits(const std::string& p_creditsFilePath)
 : m_creditsFilePath{p_creditsFilePath}
 , m_fromFile{true}
{
    PRECONDITION(!p_creditsFilePath.empty());

    // Window setup:
    set_title("Credits");

    std::string iconPath{cxutil::path::currentExecutablePath()};
    iconPath.append("/icons/cxicon16.png");

    set_icon_from_file(iconPath);
    set_position(Gtk::WIN_POS_CENTER);

    // Layouts registration:
    registerLayouts();

    // Widgets registration in layouts:
    registerWidgets();

    // Layout and Widgets look:
    configureLayoutsAndWidgets();

    // Display all widgets:
    show_all();
}


cxgui::dlg::Credits::~Credits() = default;


void cxgui::dlg::Credits::registerLayouts()
{
    // Add the main layout to the window:
    add(m_mainLayout);
}


void cxgui::dlg::Credits::registerWidgets()
{
    m_mainLayout.add(m_scrollArea);
    m_scrollArea.add(m_textArea);
}


void cxgui::dlg::Credits::configureLayoutsAndWidgets()
{
    if(m_fromFile)
    {
        populateListFromFile();
    }

    // Format the text area to display the credits:
    formatTextArea();

    // Link the credits text buffer to its respective text view:
    m_textArea.set_buffer(m_credits);

    // Expand to whole window:
    m_scrollArea.set_hexpand(true);
    m_scrollArea.set_vexpand(true);

    // Read only:
    m_textArea.set_editable(false);
}


/***************************************************************************************************
 * @brief Reads the contributor file and populates the list with its information.
 *
 * This method has not yet been implemented. The file reader is not ready.
 *
 **************************************************************************************************/
void cxgui::dlg::Credits::populateListFromFile()
{
    // Open file:
    std::ifstream in{m_creditsFilePath, std::ifstream::in};
    CX_ASSERT(in.is_open());

    // Read all content into a string stream, which we will parse later. We
    // do this because this file will always stay of reasonable size,
    // so it does not cost too much, but saves a lot of work!
    std::stringstream sstr;
    sstr << in.rdbuf();

    // We close the stream, the information is now in the string stream.
    in.close();

    const std::string fileContents{sstr.str()};

    // The string should contain at least one entry:
    CX_ASSERT(!fileContents.empty());

    // We 'vectorize' the string, such that each vector element is
    // a line from the file:
    std::vector<std::string> fileContentsByLine{cxutil::string::vectorize(fileContents, "\n")};

    // We remove: 1) blank lines;
    //            2) comment lines (starting with '#'):
    const std::regex blankLineRegex{"(\\s|\\t)*"};

    const auto isNotNeeded{
        [&blankLineRegex](const std::string p_line)
        {
            if(p_line.empty())
            {
                return true;
            }
            else if(p_line[0] == '#')
            {
                return true;
            }
            else if(std::regex_match(p_line, blankLineRegex))
            {
                return true;
            }
            else
            {
                return false;
            }
        }
    };

    const auto endAllContributors = std::remove_if(fileContentsByLine.begin(),
                                                   fileContentsByLine.end(),
                                                   isNotNeeded);

    fileContentsByLine.resize(std::distance(fileContentsByLine.begin(), endAllContributors));

    // The vector should contain at least one entry, otherwise we had no contributors!
    CX_ASSERT_MSG(!fileContents.empty(), "There is no contributor listed in the contributor "
                                         "file. Please add some.");

    // Finally we add all entries that are left into the right contributor
    // list:
    for(auto& line : fileContentsByLine)
    {
        std::vector<std::string> contributor{cxutil::string::vectorize(line, ", ")};
        CX_ASSERT(contributor.size() == 3);

        // For readability:
        const std::string team {contributor[0]};
        const std::string name {contributor[1]};
        const std::string email{contributor[2]};

        CX_ASSERT_MSG(email.find("@") != std::string::npos, "There is no '@' character in "
                                                            "one of the email address in the "
                                                            "contributor file.");

        if(team == "DEVELOPMENT")
        {
            m_devList.emplace(name, email);
        }
        else if(team == "DOCUMENTATION")
        {
            m_docList.emplace(name, email);
        }
        else if(team == "ARTWORK")
        {
            m_artList.emplace(name, email);
        }
        else
        {
            CX_ASSERT_MSG(false, "There is a syntax error in the contributor file.");
        }
    }
}


/***************************************************************************************************
 * @brief Transfers the information of the lists to the text area and adds proper formating.
 *
 * Note: I think using the tag table, this could be done only once and reused everytime.
 * investigate this upon second pass...
 *
 **************************************************************************************************/
void cxgui::dlg::Credits::formatTextArea()
{
    // Generate adequate formatting tags:
    Glib::RefPtr<Gtk::TextBuffer::Tag> listTitleTag{Gtk::TextBuffer::Tag::create()};
    listTitleTag->property_weight() = Pango::Weight::WEIGHT_BOLD;
    listTitleTag->property_scale()  = Pango::SCALE_X_LARGE;
    listTitleTag->property_pixels_above_lines() = 25;
    listTitleTag->property_pixels_below_lines() = 15;
    listTitleTag->property_left_margin_set() = true;
    listTitleTag->property_left_margin() = 5;

    Glib::RefPtr<Gtk::TextBuffer::Tag> nameTag{Gtk::TextBuffer::Tag::create()};
    nameTag->property_left_margin_set() = true;
    nameTag->property_left_margin() = 15;

    Glib::RefPtr<Gtk::TextBuffer::Tag> emailTag{Gtk::TextBuffer::Tag::create()};
    emailTag->property_foreground_rgba() = cxgui::convertToGdkRGBA(cxutil::Color::blue());

    // Add those tags to the tag table for further use:
    Glib::RefPtr<Gtk::TextBuffer::TagTable> refTagTable{Gtk::TextBuffer::TagTable::create()};
    refTagTable->add(listTitleTag);
    refTagTable->add(nameTag);
    refTagTable->add(emailTag);

    // Create a Textbuffer with the TagTable:
    m_credits = Gtk::TextBuffer::create(refTagTable);
    m_textArea.set_buffer(m_credits);

    auto iter{m_credits->get_iter_at_offset(0)};

    // Handle developpement list:
    iter = m_credits->insert_with_tag(iter, "Development\n", listTitleTag);

    for(const auto& developper : m_devList)
    {
        // Developper name:
        iter = m_credits->insert_with_tag(iter, developper.first, nameTag);

        // Formatted developper email address
        iter = m_credits->insert(iter, " <");
        iter = m_credits->insert_with_tag(iter, developper.second, emailTag);
        iter = m_credits->insert(iter, ">\n");
    }

    // Handle documentation list:
    iter = m_credits->insert_with_tag(iter, "Documentation\n", listTitleTag);

    for(const auto& documentationWriter : m_docList)
    {
        // Developper name:
        iter = m_credits->insert_with_tag(iter, documentationWriter.first, nameTag);

        // Formatted developper email address
        iter = m_credits->insert(iter, " <");
        iter = m_credits->insert_with_tag(iter, documentationWriter.second, emailTag);
        iter = m_credits->insert(iter, ">\n");
    }

    // Handle artwork list:
    iter = m_credits->insert_with_tag(iter, "Artwork\n", listTitleTag);

    for(const auto& artworkArtist : m_artList)
    {
        // Developper name:
        iter = m_credits->insert_with_tag(iter, artworkArtist.first, nameTag);

        // Formatted developper email address
        iter = m_credits->insert(iter, " <");
        iter = m_credits->insert_with_tag(iter, artworkArtist.second, emailTag);
        iter = m_credits->insert(iter, ">\n");
    }
}
