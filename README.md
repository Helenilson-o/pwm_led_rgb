# PWM RGB LED Controller for ESP32

## 📌 Visão Geral
Este projeto implementa um controlador de LED RGB usando PWM no ESP32, permitindo ajuste de cores e efeitos de transição suaves.

## 🛠️ Requisitos
- ESP32 DevKit
- Plataforma de desenvolvimento: [PlatformIO](https://platformio.org/)
- Biblioteca ESP-IDF
- LED RGB com pinos separados para `Red`, `Green` e `Blue`

## 🔧 Configuração do Hardware
Conecte o LED RGB aos pinos GPIO do ESP32 conforme a tabela:

| Cor  | GPIO  |
|------|-------|
| 🔴 Vermelho | `XX` |
| 🟢 Verde    | `XX` |
| 🔵 Azul     | `XX` |

Substitua `XX` pelos pinos específicos usados no seu projeto.
