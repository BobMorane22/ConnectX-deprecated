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
 * @file    test_RAIICairoPath.cpp
 * @author  Eric Poirier
 * @date    March 2018
 * @version 1.0
 *
 * Unit tests for a the RAIICairoPath class.
 *
 **************************************************************************************************/

#include<gtest/gtest.h>

#include <cairomm/context.h>
#include <cairomm/surface.h>

#include <cxutil/include/ContractException.h>

#include "../../include/RAIICairoPath.h"


TEST(RAIICairoPath, test1)
{
    Cairo::Path* t_invalidHandle{nullptr};

    ASSERT_THROW(cxgui::RAIICairoPath t_RAII{t_invalidHandle}, PreconditionException);
}


TEST(RAIICairoPath, test2)
{
    Cairo::RefPtr<Cairo::Surface> mockSurface{Cairo::ImageSurface::create(Cairo::Format::FORMAT_A8, 200, 200)};
    ASSERT_TRUE(mockSurface);

    Cairo::RefPtr<Cairo::Context> context{Cairo::Context::create(mockSurface)};
    ASSERT_TRUE(context);

    // Add some data to the paths:
    context->line_to(100, 100);
    context->line_to(100, -100);

    // Two exactly alike paths:
    Cairo::Path* t_path1{context->copy_path()};
    ASSERT_FALSE(t_path1 == nullptr);

    Cairo::Path* t_path2{context->copy_path()};
    ASSERT_FALSE(t_path2 == nullptr);

    cxgui::RAIICairoPath t_RAIIPath2{t_path2};

    // We check if reading works:
    ASSERT_TRUE(t_path1->cobj()->status   == t_RAIIPath2->status);
    ASSERT_TRUE(t_path1->cobj()->num_data == t_RAIIPath2->num_data);

    delete(t_path1);
}


TEST(RAIICairoPath, test3)
{
    Cairo::RefPtr<Cairo::Surface> mockSurface{Cairo::ImageSurface::create(Cairo::Format::FORMAT_A8, 200, 200)};
    ASSERT_TRUE(mockSurface);

    Cairo::RefPtr<Cairo::Context> context{Cairo::Context::create(mockSurface)};
    ASSERT_TRUE(context);

    // Add some data to the path:
    context->line_to(100, 100);
    context->line_to(100, -100);

    Cairo::Path* t_path{context->copy_path()};
    ASSERT_FALSE(t_path == nullptr);

    cxgui::RAIICairoPath t_RAIIPath{t_path};

    ASSERT_TRUE(t_RAIIPath);
}




