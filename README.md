# Corne ZMK Configuration - WCORNE claudi0

Configuración personalizada del firmware ZMK para el teclado mecánico **Corne (Split Keyboard)** con Bluetooth, RGB underglow/frontlight, pantalla OLED, y múltiples capas de teclas.

## 📋 Contenidos

- [Hardware](#hardware)
- [Características](#características)
- [Configuración de LEDs](#configuración-de-leds)
- [Layout del Teclado](#layout-del-teclado)
- [Comportamientos Especiales](#comportamientos-especiales)
- [Compilación](#compilación)
- [Troubleshooting](#troubleshooting)
- [Referencias](#referencias)

---

## 🔧 Hardware

| Componente | Especificación |
|-----------|----------------|
| **Microcontrolador** | nice_nano_v2 |
| **Conexión** | Wireless via Bluetooth + USB |
| **Pantalla** | OLED (SSD1306) en cada mitad |
| **LEDs RGB** | WS2812B (27 total per half) |
| **Batería** | Optimizada para deep sleep (15 min idle) |
| **Nombre del Dispositivo** | `WCORNE claudi0` |

---

## ⚡ Características

✅ **Wireless Bluetooth** - Conexión sin cables, soporte multi-device  
✅ **RGB Underglow** - 27 LEDs con efecto Spectrum  
✅ **Display OLED** - Información de batería, capa activa, WPM, estado de conexión  
✅ **Múltiples Capas** - 4 capas de funcionalidad (BASE, FX, SYMBOLS, EXTENDED)  
✅ **Combos** - Teclas especiales por combinación simultánea  
✅ **Macros Git** - Acceso rápido a comandos git  
✅ **Comportamientos Personalizados** - Tap dance para lock/sleep  
✅ **Deep Sleep** - Ahorro de batería  
✅ **Compilación Automática** - GitHub Actions CI/CD  

---

## 🎨 Configuración de LEDs

### Estado Actual
- **Enabled**: `CONFIG_ZMK_RGB_UNDERGLOW=y`
- **Driver**: `CONFIG_WS2812_STRIP=y`
- **Efecto Inicial**: Spectrum (2)
- **Chain Length**: 27 LEDs per half
- **Composición**: WS2812B RGB LEDs 5050 (underglow en la base del teclado)

### Comportamiento de LEDs
```
- Encendidos automáticamente al iniciar
- Efecto: Spectrum (animación)
- Control disponible en Layer Extended (FX + SYMBOLS)
```

### Keys para Control de LEDs (Layer EXTENDED)

```
RGB_EFR / RGB_EFF  - Cambiar efecto (reverse/forward)
RGB_BRI / RGB_BRD  - Brillo (increase/decrease)
RGB_SAI / RGB_SAD  - Saturación (increase/decrease)
RGB_ON / RGB_OFF   - Encender/apagar
EP_ON / EP_OFF     - Power externo
```

---

## ⌨️ Layout del Teclado

### Corne 42-key Split Keyboard
- 21 teclas por mitad (incluye thumb keys)
- Split con rol central/periférico

### Layer 0: BASE (QWERTY)

```
╔════════════════════════════════════════════════════════════════════╗
║ ESC     Q       W       E       R       T  ║  Y       U       I       O       P      BSPC  ║
║ LSHIFT  A       S       D       F       G  ║  H       J       K       L       ;       '    ║
║ LCTRL   Z       X       C       V       B  ║  N       M       ,       .       /       DEL  ║
║                         ALT/TAB FX  SPACE  ║  ENTER  SYM    ENTER                         ║
╚════════════════════════════════════════════════════════════════════╝
```

### Layer 1: FX (Function Keys & Numbers)

```
╔════════════════════════════════════════════════════════════════════╗
║ F1      F2      F3      F4      F5      F6  ║  F7     F8      F9     F10     F11     F12   ║
║ —       1       2       3       4       5   ║  6       7       8       9       0       —    ║
║ —       `       ~       |       =       +   ║  [       ]       {       }       \       —    ║
║                         —       —       —   ║  —       —       —                          ║
╚════════════════════════════════════════════════════════════════════╝
```

### Layer 2: SYMBOLS (Símbolos & Navegación)

```
╔════════════════════════════════════════════════════════════════════╗
║ ESC     !       @       #       $       %   ║  LCTRL  &       *       (       )       —    ║
║ ESC     —       ↑       PgDn    PgUp    <   ║  -       =       [       ]       \       `    ║
║ —       ←       ↓       →       PgUp    >   ║  _       +       {       }       |       ~    ║
║                         —       —       —   ║  —       —       —                          ║
╚════════════════════════════════════════════════════════════════════╝
```

### Layer 3: EXTENDED (RGB, Bluetooth, Media)

```
╔════════════════════════════════════════════════════════════════════╗
║ —       RGB↶    RGB↷    F3      F4      F5  ║  F6     F7      F8     F9      F10     F12   ║
║ ⏯       ⏮       ⏭       🔇      🔉       🔊   ║  ☀-     ☀+      EP_ON  EP_OFF  RGB_OFF RGB_↑ ║
║ —       BT0     BT1     BT2     BT3     BT4 ║  BT_CLR RGB_BRT- RGB_BRT+ RESET RGB_ON RGB_↓ ║
║                         —       —       —   ║  —       —       —                          ║
╚════════════════════════════════════════════════════════════════════╝
```

---

## 🎯 Comportamientos Especiales

### Combos (Teclas Simultáneas)

```
┌─────────────────────────────────────────────────┐
│ COMBO                 │ Teclas Simultáneas  │ Acción                  │
├─────────────────────────────────────────────────┤
│ Clear BLE Profile    │ (ESC + DEL + T)     │ BT_CLR (limpiar BT)     │
│ Space                │ (M + ,)             │ SPACE                   │
│ Enter                │ (K + J)             │ ENTER                   │
│ Capslock             │ (T + Y)             │ CAPS LOCK               │
└─────────────────────────────────────────────────┘
```

### Tap Dance: Lock/Sleep

```
┌─────────────────────────────────────────────────────────┐
│ Acción                  │ Resultado                   │
├─────────────────────────────────────────────────────────┤
│ Tap 1x (td_lock)       │ ⌘+⌃+Q (Lock en macOS)      │
│ Tap 2x (td_lock)       │ ⌘+⌥+Eject (Sleep en macOS)│
│ Tiempo máximo: 200ms   │                             │
└─────────────────────────────────────────────────────────┘
```

### Macros Git

```
┌──────────────────────────────────────────────────┐
│ MACRO            │ Salida                        │
├──────────────────────────────────────────────────┤
│ git_status       │ git status                    │
│ git_commit_all   │ git commit -a -m ""           │
│                  │ (cursor dentro de comillas)   │
└──────────────────────────────────────────────────┘
```

---

## 🔨 Compilación

### Automatizada (GitHub Actions)

El repositorio tiene configurado **GitHub Actions** que compila automáticamente al hacer `push`:

```bash
git add .
git commit -m "Cambios en keymap"
git push
```

### Local (Requiere West + Zephyr SDK)

```bash
cd config
west build -d build/left -s zmk/app -b nice_nano_v2 -- -DSHIELD=corne_left
west build -d build/right -s zmk/app -b nice_nano_v2 -- -DSHIELD=corne_right
```

---

## 🔧 Troubleshooting

### OLED remains blank after EP_OFF

Mapping for EP_ON & EP_OFF in case of OLED issue on ZMK:

```
Press: EP_OFF → RESET → EP_ON
```

If the OLED still doesn't work, try flashing the firmware again.

### LEDs not working

- Verify `CONFIG_ZMK_RGB_UNDERGLOW=y` is enabled
- Check `CONFIG_WS2812_STRIP=y` is set
- Verify chain-length matches your hardware (currently set to 27)

### Bluetooth Connection Issues

- Press `Clear_BLE_Profile` combo (ESC + DEL + T) to clear profiles
- Reconnect with `BT0`, `BT1`, etc. from Extended layer

---

## 📚 Referencias

- [ZMK Documentation](https://zmk.dev/)
- [Keymap Editor Web](https://nickcoutsos.github.io/keymap-editor/)
- [ZMK RGB Underglow](https://zmk.dev/docs/hardware-integration/lighting/underglow)
- [GitHub Actions CI](https://github.com/claudi0-udev/zmk-config-corne-zmk_studio/actions)
