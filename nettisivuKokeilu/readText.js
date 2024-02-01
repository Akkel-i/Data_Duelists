// Make a fetch request to retrieve the HTML content of another page
fetch('http://hh3dlab.fi/dataduelist/iotwrite.txt')
    .then(response => response.text())
    .then(html => {
        // Create a temporary container element
        const tempContainer = document.createElement('div');
        // Set the retrieved HTML as the innerHTML of the container
        tempContainer.innerHTML = html;

        // Access the <body> element content
        const bodyContent = tempContainer.querySelector('body').innerHTML;

        // Now, you can use the bodyContent as needed
        console.log(bodyContent);
    })
    .catch(error => console.error('Error fetching the page:', error));



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