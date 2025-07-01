### General Notes
*   **Type:**
    *   **C:** Command only, no parameters follow.
    *   **W:** Write command, followed by the specified number of parameter bytes sent *to* the display.
    *   **R:** Read command, instructs the display to send the specified number of parameter bytes back *from* the display.
*   **Parameters:** `[15:8]` refers to the high byte, and `[7:0]` refers to the low byte of a 16-bit value.

***

### 1. System, Status & Diagnostic Commands

| Op Code (Hex) | Command Name | Type | Params | Parameter Description |
| :--- | :--- | :--- | :--- | :--- |
| **00h** | `nop` (No Operation) | C | 0 | Does nothing. Can be used to terminate a memory write/read sequence. |
| **01h** | `soft_reset` | C | 0 | Resets the controller to its default state. Requires a 5ms wait. |
| **04h** | `get_display_ID` | R | 3 (+1 dummy) | Reads the module's primary identification information. |
| | | | Param 2-4| Returns Dummy, Manufacturer ID, Module/Driver Version, Module/Driver ID. |
| **05h** | `get_DSI_err` | R | 1 (+1 dummy) | Reads the number of parity errors on the DSI interface. |
| | | | Param 2 | **P[7:0]:** `P[6:0]` is the error count. `P[7]` is the overflow flag. |
| **09h** | `read_display_status` | R | 4 (+1 dummy) | Reads 32 bits of extensive status information about the display's current state. |
| **0Fh** | `get_diagnostic_result`| R | 1 (+1 dummy) | Reads self-diagnostic results following a Sleep Out command. |
| | | | Param 2 | **Result Byte:** Reports on register loading, functionality, and checksum comparison. |
| **AAh** | `read_first_checksum` | R | 1 (+1 dummy) | Returns the first calculated checksum of user registers and frame memory. |
| **AFh** | `read_continue_checksum`| R | 1 (+1 dummy) | Returns the continuously calculated checksum after the first one. |
| **BFh** | `device_code_read` | R | 5 | Reads a 5-byte device code, likely for factory or internal identification. |
| **DAh** | `read_ID1` | R | 1 (+1 dummy) | Reads the TFT LCD module's manufacturer ID. |
| **DBh** | `read_ID2` | R | 1 (+1 dummy) | Reads the TFT LCD module/driver version. |
| **DCh** | `read_ID3` | R | 1 (+1 dummy) | Reads the TFT LCD module/driver identifier. |
| **D3h** | `read_ID4` | R | 3 (+1 dummy) | Reads the IC device code / model name. |

### 2. Power & Mode Control

| Op Code (Hex) | Command Name | Type | Params | Parameter Description |
| :--- | :--- | :--- | :--- | :--- |
| **10h** | `enter_sleep_mode` | C | 0 | Puts the display into a low-power state; frame memory is retained. |
| **11h** | `exit_sleep_mode` | C | 0 | Wakes the display from sleep mode. |
| **12h** | `enter_partial_mode` | C | 0 | Activates Partial Mode (active area defined by `30h`). |
| **13h** | `enter_normal_mode` | C | 0 | Exits Partial and/or Scroll modes. |
| **38h** | `exit_idle_mode` | C | 0 | Exits Idle Mode, restoring full color depth. |
| **39h** | `enter_idle_mode` | C | 0 | Activates Idle Mode (reduced color depth). |
| **0Ah** | `get_power_mode` | R | 1 | Reads a status byte indicating the current power mode (Idle, Partial, Sleep, etc.). |

### 3. Memory, Display & Interface Configuration

| Op Code (Hex) | Command Name | Type | Params | Parameter Description |
| :--- | :--- | :--- | :--- | :--- |
| **28h** | `set_display_off` | C | 0 | Turns the display panel off. |
| **29h** | `set_display_on` | C | 0 | Turns the display panel on. |
| **2Ah** | `set_column_address` | W | 4 | Defines the horizontal window (`X` axis) for memory access. |
| | | | Param 1-4 | Start Column `SC[15:0]` (2 bytes), End Column `EC[15:0]` (2 bytes). |
| **2Bh** | `set_page_address` | W | 4 | Defines the vertical window (`Y` axis) for memory access. |
| | | | Param 1-4 | Start Page/Row `SP[15:0]` (2 bytes), End Page/Row `EP[15:0]` (2 bytes). |
| **36h** | `set_address_mode` | W | 1 | **(Critical)** Sets memory access direction and screen orientation. |
| | | | Param 1 | **MADCTR Byte:** Controls Row/Col Order, Row/Col Exchange, Refresh Order, RGB/BGR Order, and Flips. |
| **0Bh** | `get_address_mode` | R | 1 | Reads the current MADCTR setting. |
| **3Ah** | `set_pixel_format` | W | 1 | Sets the color depth for the data interface. |
| | | | Param 1 | **Pixel Format:** `0x55` for 16-bit/pixel, `0x66` for 18-bit/pixel. |
| **0Ch** | `get_pixel_format` | R | 1 | Reads the current pixel format setting. |
| **B0h** | `interface_mode_control` | W | 1 | Controls polarity of RGB interface signals (DE, PCLK, HSYNC, VSYNC) and selects 3/4-wire SPI. |
| **B6h** | `display_function_control` | W | 3 | Complex control over display operation. |
| | | | Param 1 | `BYPASS`, `RCM`, `RM`, `DM`: Selects interface (internal clock/RGB), GRAM access interface, and RGB transfer mode (DE/SYNC). |
| | | | Param 2-3 | `GS`, `SS`, `SM`, `ISC`, `NL`: Controls gate/source driver scan direction, non-display area behavior, and LCD drive line settings. |

### 4. Memory Access

| Op Code (Hex) | Command Name | Type | Params | Parameter Description |
| :--- | :--- | :--- | :--- | :--- |
| **2Ch** | `write_memory_start` | W | Var. | Begins transfer of pixel data into the frame memory window defined by `2Ah`/`2Bh`. |
| **3Ch** | `write_memory_continue`| W | Var. | Continues a memory write from where the previous one left off. |
| **2Eh** | `read_memory_start` | R | Var. | Begins reading pixel data from the frame memory. |
| **3Eh** | `read_memory_continue`| R | Var. | Continues a memory read from where the previous one left off. |

### 5. Display Effects, Scrolling & Tearing

| Op Code (Hex) | Command Name | Type | Params | Parameter Description |
| :--- | :--- | :--- | :--- | :--- |
| **20h** | `exit_invert_mode` | C | 0 | Turns off display color inversion. |
| **21h** | `enter_invert_mode` | C | 0 | Inverts the displayed colors. |
| **30h** | `set_partial_area` | W | 4 | Defines the row range for Partial Display Mode. |
| | | | Param 1-4 | Start Row `SR[15:0]` (2 bytes), End Row `ER[15:0]` (2 bytes). |
| **33h** | `set_scroll_area` | W | 6 | Defines the areas for vertical scrolling. |
| | | | Param 1-6 | Top Fixed Area (2 bytes), Vertical Scroll Area (2 bytes), Bottom Fixed Area (2 bytes). |
| **37h** | `set_scroll_start` | W | 2 | Sets the starting line number for the vertical scroll. |
| | | | Param 1-2 | **Vertical Scroll Pointer (VSP[15:0]):** The line to be displayed at the top of the scroll area. |
| **B4h** | `display_inversion_control` | W | 1 | Sets the type of inversion (column, 1-dot, 2-dot). |
| **34h** | `set_tear_off` | C | 0 | Disables the Tearing Effect (TE) output signal pin. |
| **35h** | `set_tear_on` | W | 1 | Enables the TE signal pin. |
| | | | Param 1 | **TE Mode:** `0x00` (V-Blank only), `0x01` (V-Blank & H-Blank). |
| **44h** | `set_tear_scanline` | W | 2 | Sets the scanline at which the TE signal will activate. |
| | | | Param 1-2 | **Scanline (STS[8:0]):** 9-bit line number. |
| **45h** | `get_scanline` | R | 2 (+1 dummy) | Reads the current scanline being updated. |
| **0Dh** | `get_display_mode` | R | 1 | Reads status about inversion and vertical scrolling. |
| **0Eh** | `get_signal_mode` | R | 1 | Reads the status of interface signals like TE, HSYNC, VSYNC. |

### 6. Brightness & Backlight Control

| Op Code (Hex) | Command Name | Type | Params | Parameter Description |
| :--- | :--- | :--- | :--- | :--- |
| **51h** | `set_display_brightness`| W | 1 | Sets the display brightness value for manual control. |
| | | | Param 1 | **Brightness Value (DBV[7:0]):** `0x00` (min) to `0xFF` (max). |
| **52h** | `get_display_brightness`| R | 1 (+1 dummy) | Reads the current brightness value set by `51h`. |
| **53h** | `set_control_display` | W | 1 | A control byte for multiple brightness/backlight features. |
| | | | Param 1 | **Control Byte:** `D5(BCTRL)`: Brightness On/Off, `D3(DD)`: Dimming On/Off, `D2(BL)`: Backlight On/Off. |
| **54h** | `get_control_display` | R | 1 (+1 dummy) | Reads the current control display settings from `53h`. |
| **55h** | `set_cabc_mode` | W | 1 | Sets the mode for Content Adaptive Brightness Control (CABC). |
| | | | Param 1 | **CABC Mode:** `0x00` (Off), `0x01` (UI), `0x02` (Still), `0x03` (Moving). |
| **56h** | `get_cabc_mode` | R | 1 (+1 dummy) | Reads the current CABC mode. |
| **5Eh** | `set_cabc_min_brightness`| W | 1 | Sets the minimum brightness level CABC can use. |
| | | | Param 1 | **Min Brightness (CMB[7:0]):** `0x00` (min) to `0xFF` (max). |
| **5Fh** | `get_cabc_min_brightness`| R | 1 (+1 dummy) | Reads the CABC minimum brightness setting. |

### 7. Advanced Power, Frame Rate, VCOM & Gamma

| Op Code (Hex) | Command Name | Type | Params | Parameter Description |
| :--- | :--- | :--- | :--- | :--- |
| **B1h** | `frame_rate_control (Normal)` | W | 2 | Sets frame rate and clock division for Normal Mode. |
| **B2h** | `frame_rate_control (Idle)` | W | 2 | Sets frame rate and clock division for Idle Mode. |
| **B3h** | `frame_rate_control (Partial)` | W | 2 | Sets frame rate and clock division for Partial Mode. |
| **B5h** | `blanking_porch_control` | W | 4 | Sets the vertical and horizontal blanking porch periods. |
| **B7h** | `entry_mode_set` | W | 1 | Controls Deep Standby mode, low voltage detection, and internal data format. |
| **C0h** | `power_control_1` | W | 2 | Sets VREG1OUT and VREG2OUT voltages for positive gamma. |
| **C1h** | `power_control_2` | W | 2 | Sets Vci ratio and step-up factor for internal voltage generation. |
| **C2h** | `power_control_3 (Normal)` | W | 1 | Sets step-up circuit frequency for Normal Mode. |
| **C4h** | `power_control_5 (Partial)` | W | 1 | Sets step-up circuit frequency for Partial Mode. |
| **C5h** | `vcom_control_1` | W | 4 | Sets the VCOM voltage. |
| **D0h** | `nv_memory_write` | W | 1 | Writes one byte to the Non-Volatile Memory. Requires key from `D1h`. |
| **D1h** | `nv_memory_protection_key`| W | 3 | **Unlocks NV Memory.** Must be set to `0x55`, `0xAA`, `0x66`. |
| **D2h** | `nv_memory_status_read`| R | 2 (+1 dummy) | Reads the NV memory program count and stored VCM value. |
| **E0h** | `gamma_setting` | W | 15 | Sets the positive and negative gamma correction curves. |
| | | | Param 1-15 | A series of 15 bytes defining fine-tuning, gradient, and amplitude for gamma curves. |