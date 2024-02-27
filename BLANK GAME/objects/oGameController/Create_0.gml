global.arduinoIndex = arduino_create("COM3", 115200);

if (global.arduinoIndex != -1)
{
    show_debug_message("Connected to COM3 at 115200 baud");

    // Perform additional checks or operations if needed
    
    // Close the connection
	//if(arduino_connected())
	//{
	//	var recievedData = arduino_read_line_new(arduinoIndex)
	//	show_debug_message("Received: " + recievedData)
	//}
}
else
{
    show_debug_message("Failed to connect to COM3 at 115200 baud. Error code: " + string(arduinoIndex));
}

