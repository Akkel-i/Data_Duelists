// Luodaan XMLHttpRequest-objekti, joka auttaa lataamaan tiedostoja
var xmlhttp = new XMLHttpRequest();

// Määritellään, mitä tapahtuu, kun tiedosto on ladattu
xmlhttp.onreadystatechange = function() {
    // Tarkistetaan, onko pyyntö valmis ja onnistunut (readyState 4 ja status 200)
    if (this.readyState == 4 && this.status == 200) {
        // Tiedoston sisältö on xmlhttp.responseText
        var textContent = this.responseText;

        // Näytetään teksti HTML-sivulla
        document.getElementById("txt-container").innerHTML = textContent;
    }
};

// Määritellään HTTP-metodi ja tiedoston nimi
xmlhttp.open("GET", "luettavaa.txt", true);

// Lähetetään pyyntö
xmlhttp.send();
