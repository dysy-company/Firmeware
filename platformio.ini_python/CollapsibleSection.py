import os
from PyQt5.QtWidgets import QWidget, QVBoxLayout, QSizePolicy
from PyQt5.QtCore import Qt, pyqtSlot

from PyQt5.QtWidgets import QToolButton, QFrame
from PyQt5.QtCore import QPropertyAnimation, QEasingCurve

class CollapsibleSection(QWidget):
    def __init__(self, text="Секция"):
        super().__init__()

        self.setSizePolicy(QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.main_layout = QVBoxLayout(self)
        self.main_layout.setContentsMargins(0, 0, 0, 0)

        # Заголовок — кнопка
        self.toggle_button = QToolButton()
        self.toggle_button.setText(text)
        self.toggle_button.setCheckable(True)
        self.toggle_button.setChecked(True)
        self.toggle_button.setToolButtonStyle(Qt.ToolButtonTextBesideIcon)
        self.toggle_button.setArrowType(Qt.RightArrow)
        self.toggle_button.clicked.connect(self.toggle_section)

        self.toggle_button.setStyleSheet("""
            QToolButton {
                background-color: transparent;
                font-size: 14px;
                padding: 4px;
            }
        """)

        # Контейнер с рамкой вокруг контента
        self.content_area = QFrame()
        self.content_area.setFrameShape(QFrame.StyledPanel)
        self.content_area.setMaximumHeight(0)
        self.content_area.setSizePolicy(QSizePolicy.Expanding, QSizePolicy.Fixed)

        # Стиль рамки секции
        self.content_area.setStyleSheet("""
            QFrame {
                border: 2px solid #cccccc;
                border-radius: 6px;
                background-color: #f9f9f9;
            }
        """)

        # Анимация раскрытия
        self.animation = QPropertyAnimation(self.content_area, b"maximumHeight")
        self.animation.setDuration(1000)
        self.animation.setEasingCurve(QEasingCurve.OutCubic)

        self.main_layout.addWidget(self.toggle_button)
        self.main_layout.addWidget(self.content_area)

        self.collapsed_height = 0
        self.expanded_height = 100

    def set_content(self, widget):
        layout = QVBoxLayout()
        layout.addWidget(widget)
        layout.setContentsMargins(10, 10, 10, 10)
        self.content_area.setLayout(layout)
        self.expanded_height = widget.sizeHint().height() + 20

    @pyqtSlot()
    def toggle_section(self):
        if self.toggle_button.isChecked():
            self.toggle_button.setArrowType(Qt.DownArrow)
            self.animation.setStartValue(self.content_area.maximumHeight())
            self.animation.setEndValue(self.expanded_height)
        else:
            self.toggle_button.setArrowType(Qt.RightArrow)
            self.animation.setStartValue(self.content_area.maximumHeight())
            self.animation.setEndValue(0)
        self.animation.start()