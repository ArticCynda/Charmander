import sys
import csv
import math
import datetime
from PyQt5.QtWidgets import (QWidget, QApplication,
                             QHBoxLayout, QVBoxLayout, QComboBox, QPushButton, QTextEdit, QLineEdit, QLCDNumber)
from PyQt5.QtCore import QObject, Qt, pyqtSignal, QIODevice, QTimer, QRect
from PyQt5.QtSerialPort import QSerialPort, QSerialPortInfo
from PyQt5.QtGui import QPainter, QFont, QColor, QPen, QTextCursor


class Example(QWidget):

    def __init__(self):
        super().__init__()
        self.cell = 0;
        self.csv = open("Cell_ " + str(self.cell) + "_test.csv", 'w+')
        self.csv.write("time,voltage,\r\n")

        self.timer = QTimer()
        self.timer.timeout.connect(self.readSerialChar)

        for i in QSerialPortInfo.availablePorts():
            print(i.portName())
        portname = input()
        self.SerialPort = QSerialPort()
        self.connectSerial(portname)


    def connectSerial(self, portname):
        self.SerialPort.setPortName(portname)
        self.SerialPort.setBaudRate(QSerialPort.Baud115200, QSerialPort.AllDirections)
        self.SerialPort.setParity(QSerialPort.NoParity)
        self.SerialPort.setDataBits(QSerialPort.Data8)
        self.SerialPort.setStopBits(QSerialPort.OneStop)
        self.SerialPort.open(QIODevice.ReadWrite)
        self.timer.start(50)
        self.timer.timeout.connect(self.readSerialChar)


    def disconnectSerial(self):
        if self.SerialPort.isOpen():
            self.SerialPort.close()
            self.timer.stop()


    def readSerialChar(self):
        if self.SerialPort.isOpen():
            data = self.SerialPort.read(self.SerialPort.bytesAvailable()).decode("ascii")
            print(data)
    def sendSerial(self):
        if self.SerialPort.isOpen():
            data = str.encode(self.serialSender.text())
            self.SerialPort.writeData(data)
            self.serialSender.setText('')


if __name__ == '__main__':
    app = QApplication(sys.argv)
    ex = Example()
    sys.exit(app.exec_())