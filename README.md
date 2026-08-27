# Corne 2.1 ZMK Config (ZMK Studio & OLED Display)

Repositorio de configuración de ZMK Firmware optimizado para teclado divididio **Corne 2.1 Cherry MX** con controladores inalámbricos **nice!nano v2**, pantallas **OLED 0.91"** y soporte nativo para **ZMK Studio**.

---

## 🛠️ Especificaciones de Hardware

- **Teclado**: Corne 2.1 Cherry MX (42 teclas)
- **Controladores**: nice!nano v2 Wireless (`nice_nano@2.0.0//zmk`)
- **Pantallas**: OLED 0.91" 128×32 SSD1306
- **Iluminación**: Tira de LEDs WS2812B (Underglow) + LEDs SK6812 MINI-E (Por tecla)

---

## ✨ Características Principales

### 🎛️ 1. Soporte para ZMK Studio (Edición en Tiempo Real)
- Habilitado mediante `CONFIG_ZMK_STUDIO=y` y el snippet `studio-rpc-usb-uart`.
- Permite modificar mapas de teclas y capas dinámicamente desde el navegador en [zmk.studio](https://zmk.studio/) sin necesidad de volver a compilar ni flashear.
- Desbloqueable en tiempo real presionando la tecla **`&studio_unlock`** en la capa `ADJUST` (posición `ESC`).

### 📺 2. Pantallas OLED Optimizadas
- **Lado Izquierdo (Central / Master)**:
  - Nivel de Batería con porcentaje (`100%`).
  - Estado de Salida Activa (`USB` o perfiles Bluetooth **`BLE 1`** a **`BLE 5`**).
  - Nombre explícito de la Capa Activa (**`QWERTY`**, **`LOWER`**, **`RAISE`**, **`ADJUST`**).
- **Lado Derecho (Periférico / Slave)**:
  - Pantalla nativa de periférico con el logo oficial de ZMK/Corne, batería derecha y estado de conexión BLE con el lado izquierdo.

### 🌈 3. Iluminación RGB Sincronizada
- Control global sincronizado por Bluetooth entre ambas mitades.
- Configuración inicial saturada al 100% y brillo al 80% con efecto Espectro (Arcoíris).
- Desacoplado de `EXT_POWER` (`CONFIG_ZMK_RGB_UNDERGLOW_EXT_POWER=n`) para apagar o cambiar luces sin apagar las pantallas OLED.

---

## 🎹 Mapa de Capas

| Capa | Nombre | Descripción | Acceso |
| :---: | :--- | :--- | :--- |
| **0** | **`QWERTY`** | Disposición alfanumérica base | Predeterminada |
| **1** | **`LOWER`** | Números, Teclas de Función (F1–F12) y Flechas de Navegación | Mantener `MO(1)` |
| **2** | **`RAISE`** | Símbolos, Corchetes, Llaves y Caracteres Especiales | Mantener `MO(2)` |
| **3** | **`ADJUST`** | Desbloqueo ZMK Studio, Controles RGB y Teclas Multimedia | Mantener **`LOWER` + `RAISE`** simultáneamente |

### 🎛️ Controles RGB en la Capa `ADJUST`:

| Tecla | Acción | Descripción |
| :---: | :--- | :--- |
| **Q** | `&rgb_ug RGB_TOG` | Encender / Apagar iluminación RGB (sin apagar pantallas) |
| **W** | `&rgb_ug RGB_EFF` | Siguiente efecto de iluminación (Sólido ➔ Respiración ➔ Espectro ➔ Remolino) |
| **E** | `&rgb_ug RGB_EFR` | Anterior efecto de iluminación |
| **R** | `&rgb_ug RGB_SPI` | Aumentar velocidad del efecto |
| **T** | `&rgb_ug RGB_SPD` | Disminuir velocidad del efecto |
| **S / X** | `&rgb_ug RGB_HUI / HUD` | Aumentar / Disminuir Tono de Color (Hue) |
| **D / C** | `&rgb_ug RGB_SAI / SAD` | Aumentar / Disminuir Saturación de Color |
| **F / V** | `&rgb_ug RGB_BRI / BRD` | Aumentar / Disminuir Brillo |

---

## 🚀 Compilación e Instalación

### Compilación Automática (GitHub Actions)
Cada `push` a la rama principal desencadena la compilación en GitHub Actions generando el archivo `firmware.zip`.

### Flasheo de los Controladores
1. Descarga `firmware.zip` desde la pestaña **Actions** de GitHub.
2. Extrae los archivos: `corne_left-nice_nano_v2-zmk.uf2`, `corne_right-nice_nano_v2-zmk.uf2` y `settings_reset-nice_nano_v2-zmk.uf2`.
3. Conecta la **mitad izquierda** por USB, presiona dos veces el botón de Reset en el nice!nano para entrar en modo Bootloader y copia el archivo `corne_left`.
4. Repite el proceso para la **mitad derecha** copiando el archivo `corne_right`.
5. Si deseas resetear los perfiles de memoria flash o emparejamiento BLE, flashea primero `settings_reset` en ambos lados.