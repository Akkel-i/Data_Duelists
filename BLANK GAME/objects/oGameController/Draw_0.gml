//var readString = arduino_read_line()
////show_debug_message(readString)
////draw_self()
////draw_text(100,100, string_digits(readString))

//var playerStats = arduino_read_line_new(1)
//show_debug_message(playerStats)

	//if(arduino_connected())
	//{
	//	var recievedData = arduino_read_line_new(arduinoIndex)
	//	show_debug_message("Received: " + recievedData)
	//}
	
//var arduinoIndex = arduino_create("COM3", 115200);
	
//		if(arduino_connected(arduinoIndex))
//	{
//		show_debug_message("jee")
//	}
	
//	else
//	{ 
//		show_debug_message("pöö")
		
//	}



if (global.arduinoIndex != -1)
{
    //show_debug_message("Connected to COM3 at 115200 baud");
	arduino_read(global.arduinoIndex, 10)
    // Perform additional checks or operations if needed
    
    // Close the connection
	//if(arduino_connected())
	//{
	//	var recievedData = arduino_read_line_new(arduinoIndex)
	//	show_debug_message("Received: " + recievedData)
	//}
    //		if(arduino_connected(global.arduinoIndex))
	//{
	//	show_debug_message("jee")
		
	//}
	
	//else
	//{ 
	//	show_debug_message("pöö")
		
	//}
}
else
{
    show_debug_message("Failed to connect to COM3 at 115200 baud. Error code: " + string(arduinoIndex));
}

