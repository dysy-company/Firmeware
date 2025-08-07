import os
from PyQt5.QtWidgets import QWidget, QComboBox, QLabel, QHBoxLayout, QCheckBox, QVBoxLayout
from PyQt5.QtCore import Qt

from CollapsibleSection import CollapsibleSection

# Путь к папке
script_dir = os.path.dirname(os.path.abspath(__file__))  # Папка скрипта

class LabeledComboBox(QWidget):
    def __init__(self, label_text, items=None, parent=None):
        super().__init__(parent)

        layout = QHBoxLayout(self)
        layout.setContentsMargins(0, 0, 0, 0)  # без внешних отступов

        self.label = QLabel(label_text)
        self.combo = MyComboBox()

        if items:
            self.combo.addItems(items)

        self.label.setStyleSheet("""
            QLabel {
                background: transparent;
                border: 1px dotted black;
                border-radius: 4px;
                padding: 1px 6px;
                min-height: 15px;
                color: #333;
                font-weight: bold;
            }
        """)
        self.combo.setStyleSheet("""
            QComboBox {
                background-color: white;
                border: 1px solid #ccc;
                padding: 1px 6px;
                border-radius: 4px;
                min-height: 15px;
            }
        """)
        layout.addWidget(self.label)
        layout.addWidget(self.combo)

    def currentText(self):
        return self.combo.currentText()

    def setDefault(self):
        self.combo.setCurrentIndex(0)
    
    def setText(self, text):
        self.combo.setCurrentText(text)

class LabeledCheckBox(QWidget):
    def __init__(self, label_text, items=None, parent=None):
        super().__init__(parent)
        
        self.items = items

        checked_path = os.path.join(script_dir, 'checked.png').replace("\\", "/")  # Путь к изображению
        unchecked_path = os.path.join(script_dir, 'unchecked.png').replace("\\", "/") # Путь к изображению

        layout = QHBoxLayout(self)
        layout.setContentsMargins(0, 0, 0, 0)  # без внешних отступов

        self.label = QLabel(label_text)
        self.check = QCheckBox("")

        self.label.setStyleSheet("""
            QLabel {
                background: transparent;
                border: 1px dotted black;
                border-radius: 4px;
                padding: 1px 6px;
                min-height: 15px;
                color: #333;
                font-weight: bold;
            }
        """)
        self.check.setStyleSheet(f"""
            QCheckBox::indicator {{
                width: 20px;
                height: 20px;
            }}
            QCheckBox {{
                color: transparent; 
                padding: 1px 6px;
                min-height: 15px;
            }}                    
            QCheckBox::indicator:checked {{
                image: url("{checked_path}");
            }}
            QCheckBox::indicator:unchecked {{
                image: url("{unchecked_path}");
            }}
        """)
        self.check.stateChanged.connect(self.toggled)
        self.check.setTristate(False)  # Только два состояния

        if self.items:
            self.setState(self.items[0])

        layout.addWidget(self.label)
        layout.addWidget(self.check)

    def toggled(self):
        if self.check.isChecked():
            self.check.setText(self.items[1])
        else:
            self.check.setText(self.items[0])

    def setState(self, text):
        self.check.setText(text)
        if "UNDEFINED" in text:
            self.check.setChecked(False)
        else:
            self.check.setChecked(True)

    def setDefault(self):
        self.check.setText(self.items[0])
        self.check.setChecked(False)

    def currentText(self):
        return self.check.text()
    
    def setText(self, text):
        self.setState(text)
    
class MyComboBox(QComboBox):
    def __init__(self):
        super().__init__()
        # Отключаем фокусировку на комбобоксе
        self.setFocusPolicy(Qt.NoFocus)
    def wheelEvent(self, event):
        event.ignore()  # Игнорировать событие прокрутки

    def focusInEvent(self, event):
        # Не устанавливать фокус на ComboBox
        event.ignore()

class SettingsSection(QWidget):
    def __init__(self, title, widgets, parent=None):
        super().__init__(parent)

        # Создаем collapsible секцию
        self.section = CollapsibleSection(title)

        # Контейнер и layout для виджетов
        container = QWidget()
        layout = QVBoxLayout(container)

        # Добавляем переданные виджеты
        for widget in widgets:
            layout.addWidget(widget)

        self.section.set_content(container)
        self.section.toggle_section()  # По желанию, можно убрать

        # Обёртка над всем
        main_layout = QVBoxLayout(self)
        main_layout.addWidget(self.section)

    def widget(self):
        return self.section  # чтобы можно было добавить в другой layout