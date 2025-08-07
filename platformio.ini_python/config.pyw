import sys
import os
import re
import ctypes
import json
from PyQt5.QtWidgets import QApplication, QWidget, QVBoxLayout, QPushButton, QHBoxLayout, QScrollArea
from PyQt5.QtGui import QIcon
from PyQt5.QtCore import Qt

from PyQt5.QtMultimedia import QMediaPlayer, QMediaContent, QMediaPlaylist
from PyQt5.QtCore import QUrl

from Lib import LabeledCheckBox, LabeledComboBox, SettingsSection

# Путь к папке
script_dir = os.path.dirname(os.path.abspath(__file__))  # Папка скрипта

class PlatformioConfigGenerator(QWidget):
    def __init__(self):
        global checkbox_count

        super().__init__()

        self.setWindowTitle('PlatformIO Configuration Generator')
        self.resize(650, 900)
        self.setMinimumSize(650, 900)
        self.setMaximumWidth(650)

        # Установка иконки окна
        self.setWindowIcon(QIcon(os.path.join(script_dir, 'rickroll.ico')))

        layout = QVBoxLayout(self)

        # Установка стиля
        self.setStyleSheet("""
            QWidget {
                font-size: 16px;
            }
            QWidget {
                background-color: #eeeeee;
                font-family: Segoe UI, sans-serif;
                font-size: 14px;
            }
        """)
        # Кнопка дефолтных настроек
        default_button = QPushButton('Default')
        default_button.clicked.connect(self.default_ini)
        default_button.setFixedWidth(100)
        default_button.setLayoutDirection(Qt.RightToLeft)
        default_button.setStyleSheet("""
            QPushButton {
                background-color: #0078d7;
                color: white;
                padding: 6px 12px;
                border: none;
                border-radius: 10px;
            }
            QPushButton:hover {
                background-color: #005fa3;
            }
            QPushButton:pressed {
                background-color: #004b82;
            }
        """)

        # Кнопка чтения настроек
        read_button = QPushButton('Read')
        read_button.clicked.connect(self.read_ini)
        read_button.clicked.connect(self.read_json)
        read_button.setFixedWidth(100)
        read_button.setLayoutDirection(Qt.LeftToRight)
        read_button.setStyleSheet("""
            QPushButton {
                background-color: #0078d7;
                color: white;
                padding: 6px 12px;
                border: none;
                border-radius: 10px;
            }
            QPushButton:hover {
                background-color: #005fa3;
            }
            QPushButton:pressed {
                background-color: #004b82;
            }
        """)
        
        hbox = QHBoxLayout()
        hbox.addWidget(read_button)
        hbox.addStretch(1)
        hbox.addWidget(default_button)
        layout.addLayout(hbox)

####################################################################################################

        scroll = QScrollArea()
        scroll.setWidgetResizable(True)
        scroll.setFixedSize(628, 610)
        layout.addWidget(scroll)

        content = QWidget()
        content_layout = QVBoxLayout(content)

####################################################################################################

        self.widgets = []

        # Выпадающий список выбора контроллера
        self.board_combo = LabeledComboBox('Board:', ['nucleo_h743zi', 'nucleo_f767zi'])
        self.widgets.append((self.board_combo, r'\bboard = (\w+)'))

        # Выпадающий список выбора платы
        self.controller_board_combo = LabeledComboBox('Controller Board:', ['CONTROLLER_BOARD_TYPE_SERVO_HYDRAULIC_RED', 
                                                                      'CONTROLLER_BOARD_TYPE_SERVO_HYDRAULIC_GREEN', 
                                                                      'CONTROLLER_BOARD_TYPE_SERVO_MECHANIC_GREEN'])
        self.widgets.append((self.controller_board_combo, r'\bCONTROLLER_BOARD_TYPE=(\w+)'))
        
        # Выпадающий список выбора типа сборки
        self.build_type_combo = LabeledComboBox('Build Type:', ['Debug', 'Release'])
        self.widgets.append((self.build_type_combo, r'\bdefault_envs = (\w+)'))

        section1 = SettingsSection("Controller Settings", [
            self.board_combo,
            self.controller_board_combo,
            self.build_type_combo
        ])
        content_layout.addWidget(section1.widget())
        
        # Выпадающий список выбора типа концевика
        self.limit_switch_type_combo = LabeledComboBox('Limit Switch:', ['LIMIT_SWITCH_TYPE_UNDEFINED', 
                                                                         'LIMIT_SWITCH_TYPE_ONE', 
                                                                         'LIMIT_SWITCH_TYPE_TWO'])
        self.widgets.append((self.limit_switch_type_combo, r'\bLIMIT_SWITCH_TYPE=(\w+)'))
        
        # Выпадающий список выбора питания концевика
        self.limit_switch_power_combo = LabeledComboBox('Limit Switch Power:', ['LIMIT_SWITCH_POWER_UNDEFINED', 
                                                                                'LIMIT_SWITCH_POWER_5V', 
                                                                                'LIMIT_SWITCH_POWER_24V'])
        self.widgets.append((self.limit_switch_power_combo, r'\bLIMIT_SWITCH_POWER=(\w+)'))

        # Выпадающий список выбора типа концевика дверей
        self.limit_switch_doors_type_combo = LabeledComboBox('Limit Switch Doors:', ['LIMIT_SWITCH_DOORS_TYPE_UNDEFINED',
                                                                                     'LIMIT_SWITCH_DOORS_TYPE_TWO'])
        self.widgets.append((self.limit_switch_doors_type_combo, r'\bLIMIT_SWITCH_DOORS_TYPE=(\w+)'))
        
        section2 = SettingsSection("Limit Switch Settings", [
            self.limit_switch_type_combo,
            self.limit_switch_power_combo,
            self.limit_switch_doors_type_combo
        ])
        content_layout.addWidget(section2.widget())

        # Выпадающий список выбора типа удалённого управления
        self.remote_control_combo = LabeledComboBox('Remote Control:', ['REMOTE_CONTROL_TYPE_UNDEFINED', 
                                                                        'REMOTE_CONTROL_TYPE_ENCODER', 
                                                                        'REMOTE_CONTROL_TYPE_BUTTONS_WITHOUT_PERMISSION', 
                                                                        'REMOTE_CONTROL_TYPE_BUTTONS_WITH_PERMISSION',
                                                                        'REMOTE_CONTROL_TYPE_FAST_BUTTONS_WITH_START_STOP'])
        self.widgets.append((self.remote_control_combo, r'\bREMOTE_CONTROL_TYPE=(\w+)'))

        # Чекбокс экстренной остановки
        self.emergency_stop_check = LabeledCheckBox('Emergency Stop:', ['EMERGENCY_STOP_UNDEFINED',
                                                                        'EMERGENCY_STOP_TYPE_BUTTON'])
        self.widgets.append((self.emergency_stop_check, r'\bEMERGENCY_STOP_TYPE=(\w+)'))

        section3 = SettingsSection("Remote Control Settings", [
            self.remote_control_combo,
            self.emergency_stop_check
        ])
        content_layout.addWidget(section3.widget())

        # Выпадающий список выбора типа АЦП усилия
        self.adc_strain_type_combo = LabeledComboBox('ADC Strain Type:', ['ADC_STRAIN_TYPE_ADS8320', 
                                                                          'ADC_STRAIN_TYPE_ADS869x'])
        self.widgets.append((self.adc_strain_type_combo, r'\bADC_STRAIN_TYPE=(\w+)'))

        # Выпадающий список выбора имени проекта
        self.project_name_combo = LabeledComboBox('Project Name:', ['PROJECT_NAME_UNDEFINED',
                                                                    'PROJECT_NAME_OLD_SVM_BOARD',
                                                                    'PROJECT_NAME_MPD'])
        self.widgets.append((self.project_name_combo, r'\bPROJECT_NAME=(\w+)'))

        # Чекбокс батарейки
        self.battery_check = LabeledCheckBox('Battery:', ['BATTERY_UNDEFINED', 'BATTERY_AVAILABLE'])
        self.widgets.append((self.battery_check, r'\bBATTERY=(\w+)'))

        section4 = SettingsSection("Project Settings", [
            self.adc_strain_type_combo,
            self.project_name_combo,
            self.battery_check
        ])
        content_layout.addWidget(section4.widget())

####################################################################################################

        # Кнопка генерации
        generate_button = QPushButton('Generate platformio.ini')
        generate_button.clicked.connect(self.generate_ini)
        generate_button.setFixedWidth(200)
        generate_button.setStyleSheet("""
            QPushButton {
                background-color: #0078d7;
                color: white;
                padding: 6px 12px;
                border: none;
                border-radius: 10px;
            }
            QPushButton:hover {
                background-color: #005fa3;
            }
            QPushButton:pressed {
                background-color: #004b82;
            }
        """)
        layout.addWidget(generate_button, alignment=Qt.AlignCenter)

####################################################################################################

        scroll1 = QScrollArea()
        scroll1.setWidgetResizable(True)
        scroll1.setFixedSize(628, 150)

        layout.addWidget(scroll1)

        content1 = QWidget()
        content_layout1 = QVBoxLayout(content1)
####################################################################################################

        self.jsonWidgets = []

        # Выпадающий список выбора источника тактирования
        self.project_clock_source_combo = LabeledComboBox('Clock source:', ['USE_PLL_HSE_XTAL', 
                                                                            'USE_PLL_HSI'])
        self.jsonWidgets.append((self.project_clock_source_combo, "target.clock_source"))

        # Выпадающий список выбора частоты тактирования
        self.project_clock_frequency_combo = LabeledComboBox('Frequency:', ['8000000',
                                                                            '16000000',
                                                                            '24000000', 
                                                                            '32000000',
                                                                            '40000000',
                                                                            '48000000',
                                                                            ])
        self.jsonWidgets.append((self.project_clock_frequency_combo, "target.hse_value"))

        section5 = SettingsSection("Clock Settings", [
            self.project_clock_source_combo,
            self.project_clock_frequency_combo
        ])
        content_layout1.addWidget(section5.widget())

        generate_button_json = QPushButton('Generate mbed_app.json')
        generate_button_json.clicked.connect(self.generate_json)
        generate_button_json.setFixedWidth(200)
        generate_button_json.setStyleSheet("""
            QPushButton {
                background-color: #0078d7;
                color: white;
                padding: 6px 12px;
                border: none;
                border-radius: 10px;
            }
            QPushButton:hover {
                background-color: #005fa3;
            }
            QPushButton:pressed {
                background-color: #004b82;
            }
        """)
        layout.addWidget(generate_button_json, alignment=Qt.AlignCenter)

        content_layout.addStretch()
        scroll.setWidget(content)
        scroll1.setWidget(content1)
        self.setLayout(layout)

        # Настройка музыкального плеера
        self.mediaPlayer = QMediaPlayer()
        self.playlist = QMediaPlaylist()
        self.mediaPlayer.setVolume(30)
        self.mediaPlayer.setPlaylist(self.playlist)

        # Добавление трека в плейлист
        url = QUrl.fromLocalFile(os.path.join(os.path.dirname(__file__), "ct.mp3"))
        self.playlist.addMedia(QMediaContent(url))
        self.playlist.setCurrentIndex(0)

        # Воспроизведение трека
        self.mediaPlayer.play()

        self.read_ini()
        self.read_json()

    def default_ini(self):
        for widget, pattern in self.widgets:
            widget.setDefault()
        for widget, pattern in self.jsonWidgets:
            widget.setDefault()

    def read_ini(self):
        if os.path.exists('platformio.ini'):
            with open('platformio.ini', 'r') as config_file:
                try:
                    config_text = config_file.read()
                    for widget, pattern in self.widgets:
                        try:
                            value = self.safe_search(pattern, config_text)
                            if value is not ("" or None or ''):
                                widget.setText(value)
                            else:
                                pattern = pattern.replace(r"\b", "")
                                pattern = pattern.replace(r"=(\w+)", "")
                                hwnd = self.winId().__int__()
                                ctypes.windll.user32.MessageBoxW(
                                    hwnd,
                                    f"Не удалось считать {pattern}\nПараметр отсутствует",
                                    "Ошибка при чтении файла",
                                    0x10
                                )
                        except Exception as e:
                            pattern = pattern.replace(r"\b", "")
                            pattern = pattern.replace(r"=(\w+)", "")
                            hwnd = self.winId().__int__()
                            ctypes.windll.user32.MessageBoxW(
                                hwnd,
                                f"Не удалось считать {pattern}\nПараметр отсутствует",
                                "Ошибка при чтении файла",
                                0x10
                            )

                except Exception:
                    hwnd = self.winId().__int__()
                    ctypes.windll.user32.MessageBoxW(
                        hwnd,
                        "Не удалось считать файл platformio.ini\nВыставлены параметры по умолчанию",
                        "Ошибка при чтении файла",
                        0x10
                    )
                    self.default_ini()
        else:
            hwnd = self.winId().__int__()
            ctypes.windll.user32.MessageBoxW(
                hwnd,
                "Файл platformio.ini отсутствует\nВыставлены параметры по умолчанию",
                "Ошибка при чтении файла",
                0x10
            )
            
    def safe_search(self, pattern, text):
        """Возвращает найденное значение или пустую строку"""
        match = re.search(pattern, text)
        return match.group(1) if match else ""

    def read_json(self):
        if os.path.exists('mbed_app.json'):
            with open('mbed_app.json', 'r') as json_file:
                try:
                    data = json.load(json_file)
                    overrides = data.get("target_overrides", {})
                    for self.widget, pattern in self.jsonWidgets:
                        value = overrides.get("NUCLEO_H743ZI2", {}).get(pattern)
                        if value is not ("" or None or ''):
                            self.widget.setText(str(value))
                        else:
                            hwnd = self.winId().__int__()
                            ctypes.windll.user32.MessageBoxW(
                                hwnd,
                                f"Не удалось считать {pattern}\nПараметр отсутствует",
                                "Ошибка при чтении файла",
                                0x10
                            )    
                except Exception:
                    hwnd = self.winId().__int__()
                    ctypes.windll.user32.MessageBoxW(
                        hwnd,
                        "Не удалось считать файл mbed_app.json\nВыставлены параметры по умолчанию",
                        "Ошибка при чтении файла",
                        0x10
                    )
        else:
            hwnd = self.winId().__int__()
            ctypes.windll.user32.MessageBoxW(
                hwnd,
                "Файл mbed_app.json отсутствует\nВыставлены параметры по умолчанию",
                "Ошибка при чтении файла",
                0x10
            )

    def generate_ini(self):
        board = self.board_combo.currentText()
        controller_board = self.controller_board_combo.currentText()
        build_type = self.build_type_combo.currentText()
        remote_control = self.remote_control_combo.currentText()
        limit_switch_type = self.limit_switch_type_combo.currentText()
        limit_switch_power = self.limit_switch_power_combo.currentText()
        limit_switch_doors_type = self.limit_switch_doors_type_combo.currentText()
        adc_strain_type = self.adc_strain_type_combo.currentText()
        emergency_stop_type = self.emergency_stop_check.currentText()
        battery = self.battery_check.currentText()
        project_name = self.project_name_combo.currentText()
        match board:
            case "nucleo_h743zi":
                board_index = 2
                freq = 480000000
            case "nucleo_f767zi":
                board_index = 3
                freq = 216000000 
        config_text = f"""; PlatformIO Project Configuration File
;
;   Build options: build flags, source filter
;   Upload options: custom upload port, speed and extra flags
;   Library options: dependencies, extra library storages
;   Advanced options: extra scripting
;
; Please visit documentation for the other options and examples
; https://docs.platformio.org/page/projectconf.html


[platformio]
name = Universal testing machine firmware
description = Firmware for universal testing machines
default_envs = {build_type}
build_cache_dir = .platformio_cache

[env]
platform = ststm32@17.0.0
framework = mbed

[env:Release]
build_type = release
board = {board}
board_build.f_cpu = {freq}
build_flags =  
    -I lib 
    -DPIO_FRAMEWORK_MBED_RTOS_PRESENT 
    -D BOARD_INDEX={board_index}
    -D CONTROLLER_BOARD_TYPE={controller_board}
    -D REMOTE_CONTROL_TYPE={remote_control}
    -D LIMIT_SWITCH_TYPE={limit_switch_type}
    -D LIMIT_SWITCH_POWER={limit_switch_power}
    -D LIMIT_SWITCH_DOORS_TYPE={limit_switch_doors_type}
    -D ADC_STRAIN_TYPE={adc_strain_type}
    -D EMERGENCY_STOP_TYPE={emergency_stop_type}
    -D BATTERY={battery}
    -D PROJECT_NAME={project_name}

[env:Debug]
build_type = debug
board = {board}
board_build.f_cpu = {freq}
test_speed = 9600
monitor_speed = 9600
test_ignore = test_blink
build_flags = 
    -O0 -g -ggdb
    -Wl,-Map,${'{BUILD_DIR}'}/firmware.map
    -D PIO_FRAMEWORK_MBED_RTOS_PRESENT
    -D BOARD_INDEX={board_index}   
    -D CONTROLLER_BOARD_TYPE={controller_board}
    -D REMOTE_CONTROL_TYPE={remote_control}
    -D LIMIT_SWITCH_TYPE={limit_switch_type}
    -D LIMIT_SWITCH_POWER={limit_switch_power}
    -D LIMIT_SWITCH_DOORS_TYPE={limit_switch_doors_type}
    -D ADC_STRAIN_TYPE={adc_strain_type}
    -D EMERGENCY_STOP_TYPE={emergency_stop_type}
    -D BATTERY={battery}
    -D PROJECT_NAME={project_name}"""
        with open('platformio.ini', 'w') as config_file:
            config_file.write(config_text)
        print('platformio.ini file generated successfully')

    def generate_json(self):
        frequency_json = self.project_clock_frequency_combo.currentText()
        source_json = self.project_clock_source_combo.currentText()
    
        json_text = f"""{{
"target_overrides": {{
    "*": {{
        "target.printf_lib": "std",
        "lwip.tcp-mss": 1060
    }},
    "NUCLEO_F767ZI": {{
        "target.lse_available": 0,
        "target.flash_dual_bank": "1",
        "target.clock_source": "USE_PLL_HSE_XTAL"
    }},
    "NUCLEO_H743ZI2": {{
        "target.clock_source": "{source_json}",
        "target.hse_value": {frequency_json}
    }},
    "NUCLEO_H753ZI": {{
        "target.clock_source": "{source_json}",
        "target.hse_value": {frequency_json}
    }}
}}
}}
        """
        with open('mbed_app.json', 'w') as json_file:
            json_file.write(json_text)
        print('mbed_app.json file generated successfully')

if __name__ == '__main__':
    app = QApplication(sys.argv)
    window = PlatformioConfigGenerator()
    window.show()
    sys.exit(app.exec_())
