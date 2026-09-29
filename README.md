# IPv4-Subnetting-Tool
# 🌐 IPv4 Subnet Calculator 

An interactive, web-based IPv4 Subnetting Tool built with C++ and compiled to WebAssembly (Wasm) for high-performance bitwise networking calculations directly inside the web browser.

Live Demo: [https://sarthaksh89-bot.github.io/IPv4-Subnetting-Tool/](https://sarthaksh89-bot.github.io/IPv4-Subnetting-Tool/)

---

## 📌 Features

* **Classful IPv4 Analysis:** Automatically detects Network Classes (A, B, C), Loopback, and Reserved ranges (Class D/E).
* **Dual Calculation Modes:**
  * **By Required Hosts per Network:** Calculates borrowed host bits and generates maximum subnets.
  * **By Required Subnets:** Calculates necessary borrowed bits and outputs host capacity.
* **Complete Subnet Table:** Generates network addresses, usable host ranges, and broadcast addresses for each generated subnet.
* **Binary & Decimal Masks:** Displays full 32-bit binary representation alongside standard dotted-decimal subnet masks.
* **Browser-Native Speed:** Powered by WebAssembly (`app.wasm`) and JavaScript for instant, zero-latency execution without external backend servers.

---

## 📁 Repository Structure

```text
├── IPv4SubnettingTool.cpp   # Core C++ subnetting logic and algorithms
├── app.js                   # Emscripten glue code interfacing WebAssembly with JS
├── app.wasm                 # Compiled C++ WebAssembly binary module
└── index.html               # Responsive frontend dashboard and user interface
