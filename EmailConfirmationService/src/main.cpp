/* E-mail confirmation sample for BlackBerry 10 - Client side
 * Copyright (C) <2015> Dielson Carvalho <dielson.carvalho@compelab.org>
 * Copyright (C) <2015> Durval Pereira <durval@compelab.org>
 * Copyright (C) <2015> Leandro Melo de Sales <leandro@compelab.org>
 *
 * This code is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This code is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU. Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this code; if not, write to the


 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#include <bb/Application>

#include "applicationheadless.hpp"

using namespace bb;

int main(int argc, char **argv)
{
    Application app(argc, argv);

    // Create the Application UI object, this is where the main.qml file
    // is loaded and the application scene is set.
    ApplicationHeadless appHeadless;

    // Enter the application main event loop.
    return Application::exec();
}
