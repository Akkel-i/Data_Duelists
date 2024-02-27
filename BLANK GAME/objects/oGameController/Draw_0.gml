var readString = arduino_read_line()
show_debug_message(readString)
draw_self()
draw_text(100,100, string_digits(readString))

