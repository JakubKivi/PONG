# PingPong LED display

## v2.0

Currently working on it...

### 🕹️ Controls

Button **D** cycles through the main screens (loop: Time -> Settings -> Animation).

- **🕒 Screen: TIME**

  - `A` – Toggle **Auto Brightness**
  - `B` – Toggle **Backlight**
  - `C` – Toggle **Background Animation**
  - `D` – Next screen (_Settings_)

- **⚙️ Screen: SETTINGS**

  - `A` – Submenu: **Color**
  - `B` – Submenu: **Brightness**
  - `C` – Submenu: **Time**
  - `D` – Next screen (_Animation_)

- **✨ Screen: ANIMATION**
  - `A` – Next animation (+1)
  - `B` – Previous animation (-1)
  - `*` – Confirm number input (0-100)
  - `#` – Clear input

## About v1.1

The display is made with ping pong balls (actually halves of them), backlighted with ws2812 diodes. Usually, it shows an actual time, which is loaded from DS1307 timer. The module has a small battery, so even if power is off, it knows what time it is. The display can show simple animations also (watch videos). I even tried to program a simple game (google dinosour game), but it is still in progress. Everything is controlled by an atmega328. Controller box has 3 buttons changing modes (the actual time, animations, a timer, dino-game), colors or brightness. In the end, I want it to be connected with "Jack".

More info [here](https://jakubkivi.github.io/#modalOpen).

![image](img/1.jpg)
