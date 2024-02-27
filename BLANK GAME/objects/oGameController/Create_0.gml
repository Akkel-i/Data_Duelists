var arduinoIndex = arduino_create("COM3", 115200);

if (arduinoIndex != -1)
{
    show_debug_message("Connected to COM3 at 115200 baud");

    // Perform additional checks or operations if needed
    
    // Close the connection
    
}
else
{
    show_debug_message("Failed to connect to COM3 at 115200 baud. Error code: " + string(arduinoIndex));
}