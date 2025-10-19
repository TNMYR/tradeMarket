from PyQt5.QtWidgets import QApplication, QOpenGLWidget, QMainWindow
from PyQt5.QtCore import QTimer
import sys
import os

# Добавляем текущую директорию в путь для импорта
import sys

sys.path.append(os.path.dirname(os.path.abspath(__file__)))

try:
    import tradeMarketModule

    HAS_TRADE_MODULE = True
    print("TradeMarketModule imported successfully")
except ImportError as e:
    print(f"Не удалось импортировать tradeMarketModule: {e}")
    HAS_TRADE_MODULE = False


class OpenGLWidget(QOpenGLWidget):
    def __init__(self):
        super().__init__()

    def initializeGL(self):
        if HAS_TRADE_MODULE:
            try:
                tradeMarketModule.initialize()
                print("OpenGL initialized through tradeMarketModule")
            except Exception as e:
                print(f"Error initializing OpenGL: {e}")

    def paintGL(self):
        if HAS_TRADE_MODULE:
            try:
                tradeMarketModule.render()
            except Exception as e:
                print(f"Error rendering: {e}")

    def closeEvent(self, event):
        if HAS_TRADE_MODULE:
            try:
                tradeMarketModule.cleanup()
            except Exception as e:
                print(f"Error during cleanup: {e}")
        event.accept()


class Wind(QMainWindow):
    def __init__(self):
        super().__init__()
        self.widget = OpenGLWidget()
        self.setGeometry(100, 100, 1200, 600)
        self.setCentralWidget(self.widget)
        self.setWindowTitle("Trade Market OpenGL")

        self.timer = QTimer()
        self.timer.timeout.connect(self.widget.update)
        self.timer.start(16)  # ~60 FPS


if __name__ == "__main__":
    app = QApplication(sys.argv)
    w = Wind()
    w.show()

    try:
        sys.exit(app.exec())
    except KeyboardInterrupt:
        print("Application interrupted")