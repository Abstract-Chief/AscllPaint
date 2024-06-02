# AscllPaint
  A console program for drawing ASCII animations using the ncurses library.

![image](https://github.com/Abstract-Chief/AscllPaint/assets/92479577/9f9599c6-c814-46ef-aed1-4aea29f12f70)

# Info
  AsciiPaint allows you to draw and edit animations and individual layers, run them in debug mode for preview, and much more.

# Install & Build
  --install ncurses
  sudo apt-get install libncurses-dev
  --install AsciiPaint
  git clone https://github.com/Abstract-Chief/AscllPaint
  --build
  make build --> "To create the editor itself"
  make parserC --> "To create the C parser"
  make parserCPP --> "To create the C++ parser"

#Controls
  ### Navigation:
- **Shift + Left Arrow**: Go to the left page
- **Shift + Right Arrow**: Go to the right page

### Actions:
- **Ctrl + N**: Add image
- **Ctrl + V**: Add copy
- **Ctrl + B**: Pick color
- **Ctrl + D**: Delete image
- **Ctrl + F**: Clear page
- **Backspace**: Clear point

### Debugging:
- **F10**: Debug mode
- **Ctrl + Up Arrow**: Increase debug speed
- **Ctrl + Down Arrow**: Decrease debug speed

### Saving:
- **Ctrl + T**: Save animation
- **Ctrl + Y**: Save layer

