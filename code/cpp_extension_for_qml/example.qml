import QtQuick 2.10
import TimeModule 1.0

Rectangle {
  Time {
    id:time
  }

  Text {
    text: qsTr("hour is " + time.hour + qsTr(" minute is " + time.minute))
  }
}
