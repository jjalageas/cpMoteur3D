/*!
 * \copyright (c) Nokia Corporation and/or its subsidiary(-ies) (qt-info@nokia.com) and/or contributors
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 *
 * \license{This source file is part of QmlOgre abd subject to the BSD license that is bundled
 * with this source code in the file LICENSE.}
 */

import QtQuick 2.0
import Ogre 1.0
import Example 1.0

Rectangle {
    id: ogre
    width: 1024
    height: 768
    color: "white"

    Camera {
        id: cam1
    }

    Camera {
        id: cam2
    }
    Camera {
        id: cam3
    }

    Camera {
        id: cam4
    }

    Grid
    {
        columns: 2
        spacing: 2


        OgreItem {
            id: ogreitem4
            width: ogre.width/2; height: ogre.height/2
            camera: cam4
            ogreEngine: OgreEngine

            Behavior on opacity { NumberAnimation { } }
            Behavior on width { NumberAnimation { } }
            Behavior on height { NumberAnimation { } }

            states: [
                State {
                    name: "State1"

                    PropertyChanges {
                        target: ogreitem4
                        width: ogre.width
                        height: ogre.height
                    }

                }
            ]

            MouseArea {
                anchors.fill: parent
                acceptedButtons: Qt.LeftButton | Qt.RightButton

                property int prevX: -1
                property int prevY: -1

                onPositionChanged: {
                    if (pressedButtons & Qt.LeftButton) {
                        if (prevX > -1)
                            ogreitem4.camera.yaw -= (mouse.x - prevX) / 2
                        if (prevY > -1)
                            ogreitem4.camera.pitch -= (mouse.y - prevY) / 2
                        prevX = mouse.x
                        prevY = mouse.y
                    }
                    if (pressedButtons & Qt.RightButton) {
                        if (prevY > -1)
                            ogreitem4.camera.zoom = Math.min(6, Math.max(0.1, ogreitem4.camera.zoom - (mouse.y - prevY) / 100));
                        prevY = mouse.y
                    }
                }
                onReleased: { prevX = -1; prevY = -1 }
            }
        }

        OgreItem {
            id: ogreitem3
            width: ogre.width/2; height: ogre.height/2
            camera: cam3
            ogreEngine: OgreEngine

            Behavior on opacity { NumberAnimation { } }
            Behavior on width { NumberAnimation { } }
            Behavior on height { NumberAnimation { } }

            states: [
                State {
                    name: "State1"

                    PropertyChanges {
                        target: ogreitem3
                        width: ogre.width
                        height: ogre.height
                    }

                }
            ]

            MouseArea {
                anchors.fill: parent
                acceptedButtons: Qt.LeftButton | Qt.RightButton

                property int prevX: -1
                property int prevY: -1

                onPositionChanged: {
                    if (pressedButtons & Qt.LeftButton) {
                        if (prevX > -1)
                            ogreitem3.camera.yaw -= (mouse.x - prevX) / 2
                        if (prevY > -1)
                            ogreitem3.camera.pitch -= (mouse.y - prevY) / 2
                        prevX = mouse.x
                        prevY = mouse.y
                    }
                    if (pressedButtons & Qt.RightButton) {
                        if (prevY > -1)
                            ogreitem3.camera.zoom = Math.min(6, Math.max(0.1, ogreitem3.camera.zoom - (mouse.y - prevY) / 100));
                        prevY = mouse.y
                    }
                }
                onReleased: { prevX = -1; prevY = -1 }
            }
        }

        OgreItem {
            id: ogreitem2
            width: ogre.width/2; height: ogre.height/2
            camera: cam2
            ogreEngine: OgreEngine

            Behavior on opacity { NumberAnimation { } }
            Behavior on width { NumberAnimation { } }
            Behavior on height { NumberAnimation { } }

            states: [
                State {
                    name: "State1"

                    PropertyChanges {
                        target: ogreitem2
                        width: ogre.width
                        height: ogre.height
                    }

                }
            ]

            MouseArea {
                anchors.fill: parent
                acceptedButtons: Qt.LeftButton | Qt.RightButton

                property int prevX: -1
                property int prevY: -1

                onPositionChanged: {
                    if (pressedButtons & Qt.LeftButton) {
                        if (prevX > -1)
                            ogreitem2.camera.yaw -= (mouse.x - prevX) / 2
                        if (prevY > -1)
                            ogreitem2.camera.pitch -= (mouse.y - prevY) / 2
                        prevX = mouse.x
                        prevY = mouse.y
                    }
                    if (pressedButtons & Qt.RightButton) {
                        if (prevY > -1)
                            ogreitem2.camera.zoom = Math.min(6, Math.max(0.1, ogreitem2.camera.zoom - (mouse.y - prevY) / 100));
                        prevY = mouse.y
                    }
                }
                onReleased: { prevX = -1; prevY = -1 }
            }
        }

        OgreItem {
            id: ogreitem
            width: ogre.width/2; height: ogre.height/2
            camera: cam1
            ogreEngine: OgreEngine

            Behavior on opacity { NumberAnimation { } }
            Behavior on width { NumberAnimation { } }
            Behavior on height { NumberAnimation { } }

            states: [
                State {
                    name: "State1"

                    PropertyChanges {
                        target: ogreitem
                        width: ogre.width
                        height: ogre.height
                    }
                }
            ]

            MouseArea {
                anchors.fill: parent
                acceptedButtons: Qt.LeftButton | Qt.RightButton

                property int prevX: -1
                property int prevY: -1

                onPositionChanged: {
                    if (pressedButtons & Qt.LeftButton) {
                        if (prevX > -1)
                            ogreitem.camera.yaw -= (mouse.x - prevX) / 2
                        if (prevY > -1)
                            ogreitem.camera.pitch -= (mouse.y - prevY) / 2
                        prevX = mouse.x
                        prevY = mouse.y
                    }
                    if (pressedButtons & Qt.RightButton) {
                        if (prevY > -1)
                            ogreitem.camera.zoom = Math.min(6, Math.max(0.1, ogreitem.camera.zoom - (mouse.y - prevY) / 100));
                        prevY = mouse.y
                    }
                }
                onReleased: { prevX = -1; prevY = -1 }
            }
        }

    }
}
