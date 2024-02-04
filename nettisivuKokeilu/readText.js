// Make a fetch request to retrieve the HTML content of another page
//('http://hh3dlab.fi/dataduelist/iotwrite.txt')
    // Replace this URL with the actual URL of your .txt file
    const url = "http://hh3dlab.fi/dataduelist/iotwrite.txt";

    // Fetch the content of the file
    fetch(url)
        .then(response => {
            if (!response.ok) {
                throw new Error(`HTTP error! Status: ${response.status}`);
            }
            return response.text();
        })
        .then(fileContent => {
            // Display the content on the webpage
            document.getElementById("fileContent").innerText = fileContent;
        })
        .catch(error => {
            console.error('Error fetching the file:', error);
        });

/*     JSONP (JSON with Padding):
JSONP is a technique for overcoming the same-origin policy limitations. It involves injecting a <script> tag into the page, and the server responds with a JSON object wrapped in a function call. This technique is limited to supporting only GET requests.

Example:

javascript
Copy code
function handleData(data) {
  console.log(data);
}

const script = document.createElement('script');
script.src = 'https://example.com/data?callback=handleData';
document.head.appendChild(script);
The server should respond with something like:

javascript
Copy code
handleData({ "key": "value" });
Note that JSONP has security considerations, and you should only use it with trusted sources.

Always be aware of the legal and ethical considerations when accessing data from external sources and ensure that you comply with the terms of service and privacy policies of the target website. */