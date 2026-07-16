# 🟢 Zephyr RTOS MCP LED Controller

[![Zephyr RTOS](https://img.shields.io/badge/RTOS-Zephyr-blue)](https://zephyrproject.org/)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

An advanced, edge-AI-compatible firmware built on **Zephyr RTOS**. This project bridges local hardware with modern AI agents by hosting a native **Model Context Protocol (MCP)** server alongside a traditional web dashboard. 

With this setup, you can control a physical RGB LED through a standard browser UI *or* let an LLM agent dynamically adjust the hardware using standardized tool-calling over a local network.

---

## 🛠️ Key Features

*   **⚡ Real-Time Control (Zephyr RTOS):** Multithreaded execution ensuring low-latency hardware control and network handling.
*   **🤖 Model Context Protocol (MCP) Server:** Exposes a JSON-RPC over HTTP/SSE interface, allowing AI agents (like Claude Desktop) to discover and call the `set_rgb_color` tool natively.
*   **📡 Wi-Fi & Zero-Conf (mDNS):** Automatically connects to your local network and broadcasts itself as `mcp-led.local`—no hunting for dynamic IP addresses.
*   **🌐 Embedded Web Server:** Hosts a lightweight, responsive HTML/JS color-picker dashboard to control the LED from any web browser.
*   **💡 Hardware Abstraction:** Leverages Zephyr's Devicetree to seamlessly map to RGB LEDs across supported development boards (STM32, ESP32, Nordic, etc.).

---

## 📐 System Architecture

```
┌────────────────────────┐
│    AI Agent / Client   │
└───────────┬────────────┘
            │ (MCP Tool Call / SSE)
            ▼
┌─────────────────┐   ┌────────────────────────┐
│  User Browser   ├──►│ Web Server (Port 80)   │
└─────────────────┘   ├────────────────────────┤
                      │  MCP Server (Port 8080)│
                      └───────────┬────────────┘
                                  │
                                  ▼
                          ┌────────────────┐
                          │ Zephyr RTOS    │
                          │ - MCP Service  │
                          │ - Web Server   │
                          │ - Wi-Fi        │
                          │ - LED Driver   │
                          └────────────────┘
                                  │
                                  ▼
                        [ GPIO/PWM Driver Control ]
                                 │
                                 ▼
                           🔴 🟢 🔵 RGB LED
```

---

## 🚀 Quick Start

### Prerequisites
* [Zephyr SDK](https://docs.zephyrproject.org/latest/develop/getting_started/index.html) installed and configured.
* The `west` meta-tool initialized.

### Building & Flashing

---

## 🚀 Quick Start

### Prerequisites
* [Zephyr SDK](https://docs.zephyrproject.org/latest/develop/getting_started/index.html) installed and configured.
* The `west` meta-tool initialized.

### Building & Flashing
1. Clone this repository inside your west workspace:
   ```bash
   git clone [https://github.com/andrescvargasr/wifi_led_mcp.git](https://github.com/andrescvargasr/wifi_led_mcp.git)
   cd wifi_led_mcp
   ```

2. Build the application for your target board (e.g., xiao_esp32c5/esp32c5/hpcore or esp32c5_devkitc/esp32c5/hpcore):

```bash
west build -b xiao_esp32c5/esp32c5/hpcore
```

3. Flash the firmware:

```bash
west flash
```

### Sample console interaction

```bash
shell> wifi scan
Scan requested
shell>
Num  | SSID                             (len) | Chan | RSSI | Sec
1    | kapoueh!                         8     | 1    | -93  | WPA/WPA2
2    | mooooooh                         8     | 6    | -89  | WPA/WPA2
3    | Ap-foo blob..                    13    | 11   | -73  | WPA/WPA2
4    | gksu                             4     | 1    | -26  | WPA/WPA2
----------
Scan request done

shell> wifi connect "gksu" 4 SecretStuff
Connection requested
shell>
Connected
shell>
```

4. Connect an AI Agent

Point your MCP-compatible client (e.g., Claude Desktop, Cursor) to:

[http://mcp-led.local:8080/mcp](http://mcp-led.local:8080/mcp)

Once connected, ask your agent: "Set the physical LED to a warm purple" and watch the hardware respond!

📄 License

This project is licensed under the MIT License - see the [LICENSE](./LICENSE.md) file for details.
