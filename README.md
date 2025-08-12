# Corne ZMK config

## Tool
- [ZMK](https://zmk.dev/)
- [Keymap editor web](https://nickcoutsos.github.io/keymap-editor/)

## Backlight

- [Configurations](https://github.com/zmkfirmware/zmk/pull/1895/files#diff-cbfa08fa13ebf5e1f3e9ffbe7ac696a072575071a36bf6ab139d7a152ab38811R166)

For this set up, the backlight is actually also used as a frontlight. The SK6812 MINI-E RGB LEDs 3535 are mounted on the top of the PCB, facing the keycaps. The WS2812B RGB LEDs 5050 are mounted on the bottom of the PCB, facing the desk. Since ZMK doesn't support per-key RGB backlighting yet, I have to use the same LEDs for both backlight and frontlight.

## Troubleshooting

### OLED remains blank after EP_OFF
Mapping for EP_ON & EP_OFF in case of OLED issue on ZMK
```
&ext_power EP_ON
&ext_power EP_OFF
```

Then flash the firmware, click `EP_OFF` and `EP_ON` on the keyboard, then click `Reset` on the keyboard. The OLED should be back to normal. If not, try to flash the firmware again.
