import QtQuick 2.3
import QtQuick.Window 2.2
import QtQuick.Controls 1.2
import QtQuick.Dialogs 1.2
import QtQuick.Controls 2.5
import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.0


Window {
    id: window
    signal submitTextField(string dir)//for dir now
    signal searchTextField(string text)
    signal openFileInQml(string filename,string fileUrl)//to send file name to c++
    function setTextField(text){
        output.append(text)
    }
    function listFileNames(nameOfFile){
        modelmsg.append({filename: nameOfFile})
    }
    function viewFileInTextArea(text){
        wordsView.text=text
    }

    visible: true
    width: 1000
    height: 700
    title: "Search now"
        FileDialog{
            id: filedialog
            selectFolder: true
            onAccepted: {
                directory.text=this.fileUrl;
                submitTextField(directory.text)
            }
        }

    Rectangle {
        id: rectangle
        width: parent.width * 2/3
        height: parent.height/3
        color: "#1f9cbe"
        anchors.top: parent.top
        anchors.left: parent.left

        Button {
            id: chooseDir
            x: 438
            y: 21
            width: 85
            height: 33
            text: qsTr("Browse")
             onClicked: {
                 filedialog.open()
             }
        }

        TextField {
            id: directory
            x: 96
            y: 21
            width: 319
            height: 33
            placeholderText: qsTr("the choosen Directory")
        }

        TextField {
            id: textField1
            x: 96
            y: 75
            width: 319
            height: 33
            text: ""
            placeholderText: qsTr("Please Enter a Word to Search")
        }

        Button {
            id: search
            x: 438
            y: 75
            width: 85
            height: 33
            text: qsTr("Search")
            onClicked: {
                modelmsg.clear()
                searchTextField(textField1.text)
            }
        }
    }

    Rectangle {
        id: rectangle3
        anchors.top: parent.top
        anchors.left: rectangle.right
        width: parent.width/3
        height: parent.height/3
        color: "#000"
        ScrollView{
            id: scroll
            width: rectangle3.width
            height: rectangle3.height
            x:0
            y:0
            TextArea {
                id: output
                color: "#20b517"
                text: "Console Log\n"
                wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                cursorVisible: true
                horizontalAlignment: Text.AlignLeft
            }
        }
    }

    Rectangle {
        id: wordsInFile
        anchors.top: rectangle.bottom
        anchors.left: parent.left
        width: parent.width * 2 /3
        height: parent.height*2/3
        color: "#2C4050"
        ScrollView{
            anchors.centerIn: parent.Center
            width: parent.width
            height: parent.height
                TextArea {
                    id: wordsView
                    width: 650
                    height: 116
                    wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                    visible: true
                    color: "#fff"
                }
        }
    }

    Rectangle {
        id: rectangle2
        width: parent.width/3
        height: parent.height*2/3
        color: "#ffffff"
        anchors.top: rectangle3.bottom
        anchors.left: wordsInFile.right
        ScrollView{
            id: scrol
            x:0
            y:0
            width: parent.width
            height:parent.height
                    ListView {
                        id: listView
                        x: 0
                        y: 0
                        width: parent.width
                        height:parent.height
                        contentWidth: 0
                        bottomMargin: 15
                        topMargin: 20
                        clip: true
                        boundsMovement: Flickable.StopAtBounds
                        pixelAligned: true
                        boundsBehavior: Flickable.DragOverBounds
                        model: ListModel {
                            id: modelmsg
                        }
                        delegate: Item {
                            id: itemRow
                            x: 5
                            width: parent.width - 30
                            height: 40
                            Row {
                                id: row1
                                anchors.centerIn: parent.Center
                                Text {
                                    text: filename
                                    anchors.verticalCenter: parent.verticalCenter
                                    font.bold: true
                                }
                                Button{
                                text: "open"
                                width: 80
                                height: 30
                                onClicked: openFileInQml(filename,directory.text)
                                }
                                spacing: 90
                            }
                        }
                    }
                }
            }
        }




