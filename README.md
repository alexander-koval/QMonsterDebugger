# QMonsterDebugger

`QMonsterDebugger` is a desktop debugging application written in C++ and Qt, designed to intercept, analyze, and visualize network traffic that uses the Action Message Format (AMF) protocol.

The application functions as a proxy server, allowing developers to inspect the data exchanged between a client and a server in real-time.

## Key Features

*   **Proxy Server:** Runs a TCP server on port **5840** to intercept network connections.
*   **AMF Handling:** Deserializes AMF0 and AMF3 messages, making them human-readable.
*   **Data Visualization:** Displays incoming and outgoing messages in a structured tree view (`TraceView`), showing the details of each packet.
*   **Session Management:** Each new connection is handled in a separate session.
*   **Cross-Platform:** Can be built and run on any platform supported by the Qt framework.

## Technology Stack

*   **C++17**
*   **Qt 6** (Core, Gui, Widgets, Network, QML)
*   **Build System:** qmake

## Building from Source

To build the project, you will need Qt 6 and a corresponding compiler (GCC, Clang, or MSVC) installed.

1.  **Clone the repository:**
    ```bash
    git clone <repository-url>
    cd QMonsterDebugger/qmonsterdebugger
    ```

2.  **Run qmake to generate the Makefile:**
    ```bash
    qmake
    ```

3.  **Build the project:**
    *   For Linux and macOS:
        ```bash
        make
        ```
    *   For Windows (with MinGW):
        ```bash
        mingw32-make
        ```
    *   For Windows (with MSVC), use `nmake` from the Visual Studio Developer Command Prompt.

    The executable will be created in a subdirectory that depends on the build configuration (e.g., `build/` or `debug/`/`release/`).

## Usage

1.  Run the compiled application.
2.  The server will automatically start listening on port `5840`.
3.  Configure your client application to send requests to `localhost:5840` (or the IP address of the machine where `QMonsterDebugger` is running).
4.  All intercepted messages will be displayed in the application window.
