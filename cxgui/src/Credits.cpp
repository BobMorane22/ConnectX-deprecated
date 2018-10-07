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
 * Implementation for a simple 'credits' dialog.
 *
 **************************************************************************************************/

#include <algorithm>
#include <fstream>
#include <regex>
#include <vector>

#include <gdkmm/screen.h>
#include <pangomm/fontdescription.h>

#include <cxutil/include/Assertion.h>
#include <cxutil/include/Color.h>
#include <cxutil/include/ContractException.h>
#include <cxutil/include/narrow_cast.h>
#include <cxutil/include/util.h>
#include <cxgui/include/util.h>

#include "../include/Credits.h"


namespace
{

/***************************************************************************************************
 * @brief Transfer the contributor list information to the credits text buffer.
 *
 * This helper function transfers the contents of any contributor list to a text buffer. This
 * function mostly exist to remove code duplication.
 *
 * @param p_iterator An iterator representing a position in the text buffer.
 * @param p_title    The title of the new section to create in the text buffer. All the transeferd
 *                   information will go in between sections.
 * @param p_credits  The credits text buffer.
 * @param p_list     The contributor's list.
 * @param p_tags     The needed tags for proper formatting.
 *
 * @pre The title must be a non empty string.
 * @pre There has to be exactly three tags (one for the title, one for the contributor's name
 *      and one for its email address, in that order).
 * @pre Every tag should be valid.
 *
 **************************************************************************************************/
void transferFromList(Gtk::TextIter& p_iterator,
                      const std::string& p_title,
                      Glib::RefPtr<Gtk::TextBuffer> p_credits,
                      const cxgui::dlg::Credits::ContributorList& p_list,
                      const std::vector<Glib::RefPtr<Gtk::TextBuffer::Tag>>& p_tags)
{
    PRECONDITION(!p_title.empty());
    PRECONDITION(p_tags.size() == 3);

    for(const auto& tag : p_tags)
    {
        PRECONDITION(tag);
    }

    const Glib::RefPtr<Gtk::TextBuffer::Tag> listTitleTag{p_tags[0]};
    const Glib::RefPtr<Gtk::TextBuffer::Tag> nameTag     {p_tags[1]};
    const Glib::RefPtr<Gtk::TextBuffer::Tag> emailTag    {p_tags[2]};

    p_iterator = p_credits->insert_with_tag(p_iterator, p_title + "\n", listTitleTag);

    for(const auto& contributor : p_list)
    {
        // Developper name:
        p_iterator = p_credits->insert_with_tag(p_iterator, contributor.first, nameTag);

        // Formatted developper email address
        p_iterator = p_credits->insert(p_iterator, " <");
        p_iterator = p_credits->insert_with_tag(p_iterator, contributor.second, emailTag);
        p_iterator = p_credits->insert(p_iterator, ">\n");
    }
}

} // unamed namespace


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

    INVARIANTS();
}

cxgui::dlg::Credits::Credits(const std::string& p_creditsFilePath)
 : m_creditsFilePath{p_creditsFilePath}
 , m_fromFile{true}
{
    PRECONDITION(!p_creditsFilePath.empty());
}


cxgui::dlg::Credits::~Credits() = default;


void cxgui::dlg::Credits::configureWindow()
{
    set_title("Credits");
    set_position(Gtk::WIN_POS_CENTER);

    // We get the screen information to calculate good dimensions
    // for the dialog. Sadly, by default, almost no information is
    // displayed because of the scrolling area:
    Glib::RefPtr<Gdk::Screen> screen{Gdk::Screen::get_default()};
    CX_ASSERT(screen);

    const int nbOfMonitors{screen->get_n_monitors()          };
    const int width       {screen->get_width() / nbOfMonitors};
    const int height      {screen->get_height()              };

    set_size_request(width/3, height/2);
}


void cxgui::dlg::Credits::registerWidgets()
{
    m_mainLayout.add(m_scrollArea);
    m_scrollArea.add(m_textArea);
}


void cxgui::dlg::Credits::configureWidgets()
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

    m_scrollArea.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);

    // Read only:
    m_textArea.set_editable(false);
    m_textArea.set_cursor_visible(false);

    show_all();
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

    INVARIANTS();
}


/***************************************************************************************************
 * @brief Transfers the information of the lists to the text area and adds proper formating.
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

    transferFromList(iter, "Development",   m_credits, m_devList, {listTitleTag, nameTag, emailTag});
    transferFromList(iter, "Documentation", m_credits, m_docList, {listTitleTag, nameTag, emailTag});
    transferFromList(iter, "Artwork",       m_credits, m_artList, {listTitleTag, nameTag, emailTag});
}


void cxgui::dlg::Credits::checkInvariant() const
{
    const std::vector<cxgui::dlg::Credits::ContributorList> lists{m_devList, m_docList, m_artList};
    std::size_t nbContributors{0};

    for(const auto& list : lists)
    {
        for(const auto& contributor : list)
        {
            INVARIANT(!contributor.first.empty()                       );
            INVARIANT(contributor.second.find('@') != std::string::npos);
            nbContributors += list.size();
        }
    }

    INVARIANT(nbContributors > 0);

    if(m_fromFile)
    {
        INVARIANT(!m_creditsFilePath.empty());
    }
}
