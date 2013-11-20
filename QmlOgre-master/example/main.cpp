/*!
 * \copyright (c) Nokia Corporation and/or its subsidiary(-ies) (qt-info@nokia.com) and/or contributors
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 *
 * \license{This source file is part of QmlOgre abd subject to the BSD license that is bundled
 * with this source code in the file LICENSE.}
 */

#include "exampleapp.h"
#include "coral.hpp"

#include <QtGui/QGuiApplication>

int main(int argc, char **argv)
{
    /*QGuiApplication app(argc, argv);

    ExampleApp eApp;

    eApp.resize(900, 700);
    eApp.show();
    eApp.raise();

    return app.exec();*/

    Coral *app;
    int ret;

    app = Coral::instance(argc, argv);
    ret = app->run();
    Coral::drop();

    return ret;
}
