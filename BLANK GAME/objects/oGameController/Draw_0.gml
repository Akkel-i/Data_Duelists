global.NFC1 = 49230523
global.NFC2 = 34389293
//Perusluku homma
//if (global.arduinoIndex != -1)
//{
//    var receiveData = "";
//    while (global.NFC1 = "" && global.NFC2 = "")
//    {
//        // Read a line from the serial port
//        var line = arduino_read(global.arduinoIndex, 8);
        
//        // Exit the loop if no more data is available
//        if (is_undefined(line) || string_length(line) == 0)
//            break;
        
//        // Append the non-empty line to the received data
//        receiveData += line;
//    }
//        // Check if there's non-empty data before processing
//    if (string_length(receiveData) > 0)
//    {
//        // Split the received data into separate lines
//        var lines = string_split(receiveData,"\n")

//		if (array_length_1d(lines) >= 2)
//{
//    // Assign the values to separate variables
//    global.NFC1 = lines[0];
//    global.NFC2 = lines[1];

//    // Trim or truncate NFC1 to 8 characters
//    if (string_length(global.NFC1) > 8)
//    {
//        global.NFC1 = string_copy(global.NFC1, 1, 8);
//    }
//    // Pad or handle the case where NFC1 is less than 8 characters
//    else
//    {
//        while (string_length(global.NFC1) < 8)
//        {
//            global.NFC1 += "5"  // Add a random number between 0 and 9
//        }
//    }

//    // Trim or truncate NFC2 to 8 characters
//    if (string_length(global.NFC2) > 8)
//    {
//        global.NFC2 = string_copy(global.NFC2, 1, 8);
//    }
//    // Pad or handle the case where NFC2 is less than 8 characters
//    else
//    {
//        while (string_length(global.NFC2) < 8)
//        {
//            global.NFC2 += "5"  // Add a random number between 0 and 9
//        }
//    }

//    // Display or use the values as needed
//    show_debug_message("NFC1: " + global.NFC1);
//    show_debug_message("NFC2: " + global.NFC2);
//}

//	}
//}
//else
//{
//    show_debug_message("Failed to connect to COM3 at 115200 baud. Error code: " + string(global.arduinoIndex));
//}


if (array_length(global.NFC1array) == 0 && global.NFC1 != "")
{
// Iterate through the string in steps of 2
for (var i = 0; i < 4; i++) {
    // Extract two characters from the string and convert them to numbers
    var num1 = real(string_char_at(global.NFC1, i * 2 + 1));
    var num2 = real(string_char_at(global.NFC1, i * 2 + 2));

    // Calculate the sum of the pair and store it in the array
    global.NFC1array[i] = num1 + num2;
}
for (var i = 0; i < 4; i++) {
    // Extract two characters from the string and convert them to numbers
    var num3 = real(string_char_at(global.NFC2, i * 2 + 1));
    var num4 = real(string_char_at(global.NFC2, i * 2 + 2));

    // Calculate the sum of the pair and store it in the array
    global.NFC2array[i] = num3 + num4;
}


// Display the contents of the array for testing purposes
for (var i = 0; i < 4; i++) {
    show_debug_message("Sum " + string(i+1) + ": " + string(global.NFC1array[i]));
}
for (var i = 0; i < 4; i++) {
    show_debug_message("Sum " + string(i+1) + ": " + string(global.NFC2array[i]));
}
}

createPlayer = function (statsArray)
{
    
        // Create a new player instance or use an existing player object
        var player = instance_create_layer(x, y,"Background", oPlayerObject);

        // Assign stats to the player
        player.hp = statsArray[0];
        player.atk = statsArray[1];
        player.def = statsArray[2];
        player.agi = statsArray[3];

        // Additional initialization or handling if needed
        // ...

        // Return the created player instance
        return player;

}

// Example usage for creating players with NFC data
if (array_length(global.NFC1array) == 4 && array_length(global.NFC2array) == 4 && global.playersMade == false)
{
    var player1 = createPlayer(global.NFC1array);
    var player2 = createPlayer(global.NFC2array);
	
	show_debug_message(player1.hp)
	show_debug_message(player2.def)
	
	global.playersMade = true
	
    // Additional logic or handling if needed
    // ...
}
