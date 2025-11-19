import QtQuick 2.12
import QtQuick.Window 2.12
import ipCheck 1.0

Window {
    id: window
    width: 640
    height: 640
    visible: true
    title: qsTr("TactilaDial-Tester")

    property int counterZero: 0
    property int pressCounterZero: 0
    property int counterOne: 0
    property int pressCounterOne: 0
    property int counterTwo: 0
    property int pressCounterTwo: 0
    property int counterThree: 0
    property int pressCounterThree: 0
    property int counterFour: 0
    property int pressCounterFour: 0
    property int counterFive: 0
    property int pressCounterFive: 0
    property int counterSix: 0
    property int pressCounterSix: 0
    property int counterSeven: 0
    property int pressCounterSeven: 0
    property int counterEight: 0
    property int pressCounterEight: 0
    property int counterNine: 0
    property int pressCounterNine: 0
    property int counterTen: 0
    property int pressCounterTen: 0
    property int counterEleven: 0
    property int pressCounterEleven: 0
    property int counterTwelve: 0
    property int pressCounterTwelve: 0
    property int counterThirteen: 0
    property int pressCounterThirteen: 0
    property int counterFourteen: 0
    property int pressCounterFourteen: 0
    property int counterFifteen: 0
    property int pressCounterFifteen: 0

    IpChecker{
        id:iphere
    }
    Text {
        id: ipshow
        color: "#ffffff"
        text: iphere.ipAddress
        font.pointSize: 15
        style: Text.Outline

        Timer{
            id:recheckIP
            running: true
            repeat: true
            interval: 1000
            onTriggered: {

                ipshow.text=iphere.ipAddress
                //Recheck the IP every 10s
                ipshow.visible=iphere.ipAddress !== "0"
                //Show the IP if its not 0
            }
        }

    }

    Connections{
        target:dialZero
        function onPositionIncremented(incCount) {
            for(var i=0;i<incCount;i++)
            {
                counterZero++
            }
        }
        function onPositionDecremented(decCount) {
            for(var i=0;i<decCount;i++)
            {
                counterZero--
            }
        }
        function onButtonPressed() {
            pressCounterZero++
            counterZeroButton.text = "pressed"

        }
        function onButtonReleased() {
            counterZeroButton.text = "released"
        }

    }
    Connections{
        target:dialOne
        function onPositionIncremented(incCount) {
            for(var i=0;i<incCount;i++)
            {
                counterOne++
            }
        }
        function onPositionDecremented(decCount) {
            for(var i=0;i<decCount;i++)
            {
                counterOne--
            }
        }
        function onButtonPressed() {
            pressCounterOne++
            counterOneButton.text = "pressed"
        }
        function onButtonReleased() {
            counterOneButton.text = "released"
        }
    }
    Connections{
        target:dialTwo
        function onPositionIncremented(incCount) {
            for(var i=0;i<incCount;i++)
            {
                counterTwo++
            }
        }
        function onPositionDecremented(decCount) {
            for(var i=0;i<decCount;i++)
            {
                counterTwo--
            }
        }
        function onButtonPressed() {
            pressCounterTwo++
            counterTwoButton.text = "pressed"
        }
        function onButtonReleased() {
            counterTwoButton.text = "released"
        }
    }
    Connections{
        target:dialThree
        function onPositionIncremented(incCount) {
            for(var i=0;i<incCount;i++)
            {
                counterThree++
            }
        }
        function onPositionDecremented(decCount) {
            for(var i=0;i<decCount;i++)
            {
                counterThree--
            }
        }
        function onButtonPressed() {
            pressCounterThree++
            counterThreeButton.text = "pressed"
        }
        function onButtonReleased() {
            counterThreeButton.text = "released"
        }
    }
    Connections{
        target:dialFour
        function onPositionIncremented(incCount) {
            for(var i=0;i<incCount;i++)
            {
                counterFour++
            }
        }
        function onPositionDecremented(decCount) {
            for(var i=0;i<decCount;i++)
            {
                counterFour--
            }
        }
        function onButtonPressed() {
            pressCounterFour++
            counterFourButton.text = "pressed"
        }
        function onButtonReleased() {
            counterFourButton.text = "released"
        }
    }
    Connections{
        target:dialFive
        function onPositionIncremented(incCount) {
            for(var i=0;i<incCount;i++)
            {
                counterFive++
            }
        }
        function onPositionDecremented(decCount) {
            for(var i=0;i<decCount;i++)
            {
                counterFive--
            }
        }
        function onButtonPressed() {
            pressCounterFive++
            counterFiveButton.text = "pressed"
        }
        function onButtonReleased() {
            counterFiveButton.text = "released"
        }
    }
    Connections{
        target:dialSix
        function onPositionIncremented(incCount) {
            for(var i=0;i<incCount;i++)
            {
                counterSix++
            }
        }
        function onPositionDecremented(decCount) {
            for(var i=0;i<decCount;i++)
            {
                counterSix--
            }
        }
        function onButtonPressed() {
            pressCounterSix++
            counterSixButton.text = "pressed"
        }
        function onButtonReleased() {
            counterSixButton.text = "released"
        }
    }
    Connections{
        target:dialSeven
        function onPositionIncremented(incCount) {
            for(var i=0;i<incCount;i++)
            {
                counterSeven++
            }
        }
        function onPositionDecremented(decCount) {
            for(var i=0;i<decCount;i++)
            {
                counterSeven--
            }
        }
        function onButtonPressed() {
            pressCounterSeven++
            counterSevenButton.text = "pressed"
        }
        function onButtonReleased() {
            counterSevenButton.text = "released"
        }
    }
    Connections{
        target:dialEight
        function onPositionIncremented(incCount) {
            for(var i=0;i<incCount;i++)
            {
                counterEight++
            }
        }
        function onPositionDecremented(decCount) {
            for(var i=0;i<decCount;i++)
            {
                counterEight--
            }
        }
        function onButtonPressed() {
            pressCounterEight++
            counterEightButton.text = "pressed"
        }
        function onButtonReleased() {
            counterEightButton.text = "released"
        }
    }
    Connections{
        target:dialNine
        function onPositionIncremented(incCount) {
            for(var i=0;i<incCount;i++)
            {
                counterNine++
            }
        }
        function onPositionDecremented(decCount) {
            for(var i=0;i<decCount;i++)
            {
                counterNine--
            }
        }
        function onButtonPressed() {
            pressCounterNine++
            counterNineButton.text = "pressed"
        }
        function onButtonReleased() {
            counterNineButton.text = "released"
        }
    }
    Connections{
        target:dialTen
        function onPositionIncremented(incCount) {
            for(var i=0;i<incCount;i++)
            {
                counterTen++
            }
        }
        function onPositionDecremented(decCount) {
            for(var i=0;i<decCount;i++)
            {
                counterTen--
            }
        }
        function onButtonPressed() {
            pressCounterTen++
            counterTenButton.text = "pressed"
        }
        function onButtonReleased() {
            counterTenButton.text = "released"
        }
    }
    Connections{
        target:dialEleven
        function onPositionIncremented(incCount) {
            for(var i=0;i<incCount;i++)
            {
                counterEleven++
            }
        }
        function onPositionDecremented(decCount) {
            for(var i=0;i<decCount;i++)
            {
                counterEleven--
            }
        }
        function onButtonPressed() {
            pressCounterEleven++
            counterElevenButton.text = "pressed"
        }
        function onButtonReleased() {
            counterElevenButton.text = "released"
        }
    }
    Connections{
        target:dialTwelve
        function onPositionIncremented(incCount) {
            for(var i=0;i<incCount;i++)
            {
                counterTwelve++
            }
        }
        function onPositionDecremented(decCount) {
            for(var i=0;i<decCount;i++)
            {
                counterTwelve--
            }
        }
        function onButtonPressed() {
            pressCounterTwelve++
            counterTwelveButton.text = "pressed"
        }
        function onButtonReleased() {
            counterTwelveButton.text = "released"
        }
    }
    Connections{
        target:dialThirteen
        function onPositionIncremented(incCount) {
            for(var i=0;i<incCount;i++)
            {
                counterThirteen++
            }
        }
        function onPositionDecremented(decCount) {
            for(var i=0;i<decCount;i++)
            {
                counterThirteen--
            }
        }
        function onButtonPressed() {
            pressCounterThirteen++
            counterThirteenButton.text = "pressed"
        }
        function onButtonReleased() {
            counterThirteenButton.text = "released"
        }
    }
    Connections{
        target:dialFourteen
        function onPositionIncremented(incCount) {
            for(var i=0;i<incCount;i++)
            {
                counterFourteen++
            }
        }
        function onPositionDecremented(decCount) {
            for(var i=0;i<decCount;i++)
            {
                counterFourteen--
            }
        }
        function onButtonPressed() {
            pressCounterFourteen++
            counterFourteenButton.text = "pressed"
        }
        function onButtonReleased() {
            counterFourteenButton.text = "released"
        }
    }
    Connections{
        target:dialFifteen
        function onPositionIncremented(incCount) {
            for(var i=0;i<incCount;i++)
            {
                counterFifteen++
            }
        }
        function onPositionDecremented(decCount) {
            for(var i=0;i<decCount;i++)
            {
                counterFifteen--
            }
        }
        function onButtonPressed() {
            pressCounterSeven++
            counterFifteenButton.text = "pressed"
        }
        function onButtonReleased() {
            counterFifteenButton.text = "released"
        }
    }

    Column {
        id: column
        x: 206
        y: 59
        width: 200
        height: 567
        anchors.verticalCenter: parent.verticalCenter
        spacing: 10
        anchors.horizontalCenter: parent.horizontalCenter

        Text {
            id: counterZeroText
            width: 600
            color: "black"
            text: "Dial Zero("+ dialZero.positionCount +")" +": " + counterZero + "#"+ dialZero.position+ "  Presses: " + pressCounterZero
            horizontalAlignment: Text.AlignLeft
            anchors.horizontalCenter: parent.horizontalCenter
            font.pointSize: 15
            Text{
                id:counterZeroButton
                x: 253
                y: 0
                width: 47
                height: 23
                font.pointSize: 15
                color: "black"
                text: "button"
                anchors.fill: parent
                horizontalAlignment: Text.AlignRight
            }

        }

        Text {
            id: counterOneText
            width: 600
            color: "black"
            text: "Dial One("+ dialOne.positionCount +")" +": " + counterOne + "#"+ dialOne.position+ "  Presses: " + pressCounterOne
            anchors.horizontalCenter: parent.horizontalCenter
            font.pointSize: 15
            Text{
                id:counterOneButton
                x: 253
                y: 0
                width: 47
                height: 23
                font.pointSize: 15
                color: "black"
                text: "button"
                anchors.fill: parent
                horizontalAlignment: Text.AlignRight
            }
        }

        Text {
            id: counterTwoText
            width: 600
            color: "black"
            text: "Dial Two("+ dialTwo.positionCount +")" +": " + counterTwo+ "#"+ dialTwo.position + "  Presses: " + pressCounterTwo
            anchors.horizontalCenter: parent.horizontalCenter
            font.pointSize: 15
            Text{
                id:counterTwoButton
                x: 253
                y: 0
                width: 47
                height: 23
                font.pointSize: 15
                color: "black"
                text: "button"
                anchors.fill: parent
                horizontalAlignment: Text.AlignRight
            }

        }

        Text {
            id: counterThreeText
            width: 600
            color: dialThree.positionCount != -1 ? "black" : "gray"
            text: "Dial Three("+ dialThree.positionCount +")" +": " + counterThree+ "#"+ dialThree.position + "  Presses: " + pressCounterThree
            anchors.horizontalCenter: parent.horizontalCenter
            font.pointSize: 15
            Text{
                id:counterThreeButton
                x: 253
                y: 0
                width: 47
                height: 23
                font.pointSize: 15
                color: dialThree.positionCount != -1 ? "black" : "gray"
                text:"button"
                anchors.fill: parent
                horizontalAlignment: Text.AlignRight
            }

        }
        Text {
            id: counterFourText
            width: 600
            color: dialFour.positionCount != -1 ? "black" : "gray"
            text: "Dial Four("+ dialFour.positionCount +")" +": " + counterFour+ "#"+ dialFour.position + "  Presses: " + pressCounterFour
            anchors.horizontalCenter: parent.horizontalCenter
            font.pointSize: 15
            Text{
                id:counterFourButton
                x: 253
                y: 0
                width: 47
                height: 23
                font.pointSize: 15
                color: dialFour.positionCount != -1 ? "black" : "gray"
                text: "button"
                anchors.fill: parent
                horizontalAlignment: Text.AlignRight
            }

        }
        Text {
            id: counterFiveText
            width: 600
            color: dialFive.positionCount !== -1 ? "black" : "gray"
            text: "Dial Five("+ dialFive.positionCount +")" +": " + counterFive+ "#"+ dialFive.position + "  Presses: " + pressCounterFive
            anchors.horizontalCenter: parent.horizontalCenter
            font.pointSize: 15
            Text{
                id:counterFiveButton
                x: 253
                y: 0
                width: 47
                height: 23
                font.pointSize: 15
                color: dialFive.positionCount !== -1 ? "black" : "gray"
                text: "button"
                anchors.fill: parent
                horizontalAlignment: Text.AlignRight
            }

        }
        Text {
            id: counterSixText
            width: 600
            color: dialSix.positionCount !== -1 ? "black" : "gray"
            text: "Dial Six("+ dialSix.positionCount +")" +": " + counterSix+ "#"+ dialSix.position + "  Presses: " + pressCounterSix
            anchors.horizontalCenter: parent.horizontalCenter
            font.pointSize: 15
            Text{
                id:counterSixButton
                x: 253
                y: 0
                width: 47
                height: 23
                font.pointSize: 15
                color: dialSix.positionCount !== -1 ? "black" : "gray"
                text: "button"
                anchors.fill: parent
                horizontalAlignment: Text.AlignRight
            }

        }
        Text {
            id: counterSevenText
            width: 600
            color: dialSeven.positionCount !== -1 ? "black" : "gray"
            text: "Dial Seven("+ dialSeven.positionCount +")" +": " + counterSeven+ "#"+ dialSeven.position + "  Presses: " + pressCounterSeven
            anchors.horizontalCenter: parent.horizontalCenter
            font.pointSize: 15
            Text{
                id:counterSevenButton
                x: 253
                y: 0
                width: 47
                height: 23
                font.pointSize: 15
                color: dialSeven.positionCount !== -1 ? "black" : "gray"
                text: "button"
                anchors.fill: parent
                horizontalAlignment: Text.AlignRight
            }

        }
        Text {
            id: counterEightText
            width: 600
            color: dialEight.positionCount !== -1 ? "black" : "gray"
            text: "Dial Eight("+ dialEight.positionCount +")" +": " + counterEight+ "#"+ dialEight.position + "  Presses: " + pressCounterEight
            anchors.horizontalCenter: parent.horizontalCenter
            font.pointSize: 15
            Text{
                id:counterEightButton
                x: 253
                y: 0
                width: 47
                height: 23
                font.pointSize: 15
                color: dialEight.positionCount !== -1 ? "black" : "gray"
                text: "button"
                anchors.fill: parent
                horizontalAlignment: Text.AlignRight
            }

        }
        Text {
            id: counterNineText
            width: 600
            color: dialNine.positionCount !== -1 ? "black" : "gray"
            text: "Dial Nine("+ dialNine.positionCount +")" +": " + counterNine+ "#"+ dialNine.position + "  Presses: " + pressCounterNine
            anchors.horizontalCenter: parent.horizontalCenter
            font.pointSize: 15
            Text{
                id:counterNineButton
                x: 253
                y: 0
                width: 47
                height: 23
                font.pointSize: 15
                color: dialNine.positionCount !== -1 ? "black" : "gray"
                text: "button"
                anchors.fill: parent
                horizontalAlignment: Text.AlignRight
            }

        }
        Text {
            id: counterTenText
            width: 600
            color: dialTen.positionCount !== -1 ? "black" : "gray"
            text: "Dial Ten("+ dialTen.positionCount +")" +": " + counterTen+ "#"+ dialTen.position + "  Presses: " + pressCounterTen
            anchors.horizontalCenter: parent.horizontalCenter
            font.pointSize: 15
            Text{
                id:counterTenButton
                x: 253
                y: 0
                width: 47
                height: 23
                font.pointSize: 15
                color: dialTen.positionCount !== -1 ? "black" : "gray"
                text: "button"
                anchors.fill: parent
                horizontalAlignment: Text.AlignRight
            }

        }
        Text {
            id: counterElevenText
            width: 600
            color: dialEleven.positionCount !== -1 ? "black" : "gray"
            text: "Dial Eleven("+ dialEleven.positionCount +")" +": " + counterEleven+ "#"+ dialEleven.position + "  Presses: " + pressCounterEleven
            anchors.horizontalCenter: parent.horizontalCenter
            font.pointSize: 15
            Text{
                id:counterElevenButton
                x: 253
                y: 0
                width: 47
                height: 23
                font.pointSize: 15
                color: dialEleven.positionCount !== -1 ? "black" : "gray"
                text: "button"
                anchors.fill: parent
                horizontalAlignment: Text.AlignRight
            }

        }
        Text {
            id: counterTwelveText
            width: 600
            color: dialTwelve.positionCount !== -1 ? "black" : "gray"
            text: "Dial Twelve("+ dialTwelve.positionCount +")" +": " + counterTwelve+ "#"+ dialTwelve.position + "  Presses: " + pressCounterTwelve
            anchors.horizontalCenter: parent.horizontalCenter
            font.pointSize: 15
            Text{
                id:counterTwelveButton
                x: 253
                y: 0
                width: 47
                height: 23
                font.pointSize: 15
                color: dialTwelve.positionCount !== -1 ? "black" : "gray"
                text: "button"
                anchors.fill: parent
                horizontalAlignment: Text.AlignRight
            }

        }
        Text {
            id: counterThirteenText
            width: 600
            color: dialThirteen.positionCount !== -1 ? "black" : "gray"
            text: "Dial Thirteen("+ dialThirteen.positionCount +")" +": " + counterThirteen+ "#"+ dialThirteen.position + "  Presses: " + pressCounterThirteen
            anchors.horizontalCenter: parent.horizontalCenter
            font.pointSize: 15
            Text{
                id:counterThirteenButton
                x: 253
                y: 0
                width: 47
                height: 23
                font.pointSize: 15
                color: dialThirteen.positionCount !== -1 ? "black" : "gray"
                text: "button"
                anchors.fill: parent
                horizontalAlignment: Text.AlignRight
            }

        }
        Text {
            id: counterFourteenText
            width: 600
            color: dialFourteen.positionCount !== -1 ? "black" : "gray"
            text: "Dial Fourteen("+ dialFourteen.positionCount +")" +": " + counterFourteen+ "#"+ dialFourteen.position + "  Presses: " + pressCounterFourteen
            anchors.horizontalCenter: parent.horizontalCenter
            font.pointSize: 15
            Text{
                id:counterFourteenButton
                x: 253
                y: 0
                width: 47
                height: 23
                font.pointSize: 15
                color: dialFourteen.positionCount !== -1 ? "black" : "gray"
                text: "button"
                anchors.fill: parent
                horizontalAlignment: Text.AlignRight
            }

        }
        Text {
            id: counterFifteenText
            width: 600
            color: dialFifteen.positionCount !== -1 ? "black" : "gray"
            text: "Dial Fifteen("+ dialFifteen.positionCount +")" +": " + counterFifteen+ "#"+ dialFifteen.position + "  Presses: " + pressCounterFifteen
            anchors.horizontalCenter: parent.horizontalCenter
            font.pointSize: 15
            Text{
                id:counterFifteenButton
                x: 253
                y: 0
                width: 47
                height: 23
                font.pointSize: 15
                color: dialFifteen.positionCount !== -1 ? "black" : "gray"
                text: "button"
                anchors.fill: parent
                horizontalAlignment: Text.AlignRight
            }

        }
    }


}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.75}
}
##^##*/
