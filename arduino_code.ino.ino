
#include <ESP32Servo.h>
#include <WiFi.h>

Servo servo1;
Servo servo2;

const char* ssid = <wifi-network name>; // Your Wi-Fi network name
const char* password = <password>; // Your Wi-Fi password
int pos = 0;

WiFiServer server(8080); // Set up the web server on port 8080
String header;           // Stores the HTTP request
String doorstate = "off"; // Represents the current state of the door

void setup() {
  servo1.attach(13);   // Attach servo to GPIO pin 13
  servo2.attach(12);   // Attach servo to GPIO pin 12
  Serial.begin(115200); // Begin serial communication for debugging

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print("."); // Print dots while trying to connect
  }

  Serial.println(""); // Empty line for spacing
  Serial.println("WiFi connected."); // Print connection status
  server.begin(); // Begin the server
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP()); // Display the local IP address
}

void loop() {
  WiFiClient client = server.available(); // Check for incoming clients

  if (client) {
    String currentLine = "";
    Serial.println("New Client connected.");

    while (client.connected()) {
      if (client.available()) {
        char c = client.read(); // Read incoming data from the client
        header += c; // Store the incoming data

        if (c == '\n') {
          if (currentLine.length() == 0) {
            // Send HTTP headers
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();

            // Door open or close logic
            if (header.indexOf("GET /door/on") >= 0) {
              doorstate = "on";
              while (pos < 100) {
                servo1.write(pos);
                servo2.write(180 - pos);
                pos++;
                delay(10);
              }
            } else if (header.indexOf("GET /door/off") >= 0) {
              doorstate = "off";
              while (pos > 0) {
                servo1.write(pos);
                servo2.write(180 - pos);
                pos--;
                delay(10);
              }
            }

            // HTML response
            client.println("<!DOCTYPE html><html>");
            client.println("<head>");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            client.println("<style>html { font-family: Times New Roman; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #195B6A; border: none; border-radius: 50%; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #77878A;}</style></head>");
            client.println("<body><h1>IoT Based Garage Door</h1>");

            if (doorstate == "off") {
              client.println("<p><a href=\"/door/on\"><button class=\"button\">Open</button></a></p>");
            } else {
              client.println("<p><a href=\"/door/off\"><button class=\"button button2\">Close</button></a></p>");
            }

            client.println("</body></html>");
            client.println();
            break;
          } else {
            currentLine = ""; // Clear the current line
          }
        } else if (c != '\r') {
          currentLine += c; // Add non-newline characters to the current line
        }
      }
    }

    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
  }
}
