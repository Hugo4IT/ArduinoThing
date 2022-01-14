#include <ESP8266WiFi.h>
#include <WebSocketsServer.h>

const String PAGE = R"===(
<html>
    <head>
        <title>RODILF.UwU.pogchamp</title>
        <style>
            :root {
                font-family:-apple-system, BlinkMacSystemFont, 'Segoe UI', Roboto, Oxygen, Ubuntu, Cantarell, 'Open Sans', 'Helvetica Neue', sans-serif;
                font-size: 16pt;
                color: white;

                --blue-1: #3742fa;
                --blue-2: #5352ed;
                --blue-3: #1e90ff;
                --blue-4: #70a1ff;
            }

            /* Reset styles */
            body,html{margin:0;padding:0;min-height:100vh}
            *,*::before,*::after{box-sizing:border-box}
            button{font-size:1rem;font-family:inherit;color:inherit}
            a{text-decoration:none}
            a:visited{color:white}

            .container {
                display: flex;
                flex-direction: column;
                justify-content: center;
                align-items: center;

                height: 100%;
            }

            .camera-feed {
                display: flex;
                flex-direction: column;

                background-color: var(--blue-3);
                border-radius: 32px;
                padding: 16px;
            }

            /* Add seperation */
            .camera-feed>*:not(:first-child) {
                margin-top: 16px;
            }

            .cutout-corners {
                border-radius: 16px;
                overflow: hidden;
            }

            .socket-status {
                background-color: var(--blue-1);
                padding: 8px 16px;
                border-radius: 16px;

                display: flex;
                flex-direction: column;
            }

            .ss-row {
                display: flex;
                flex-direction: row;
                justify-content: space-between;
            }
        </style>
    </head>
    <body style="background:var(--blue-1)">
        <div class="container">
            <div class="camera-feed">
                <div class="cutout-corners">
                    <canvas id="cameraFeed" width="640" height="480"></canvas>
                </div>
                <div class="socket-status">
                    <h3 style="margin:0 0 8px 0;text-align:center">Client -> Server</h3>
                    <div class="ss-row">
                        <span>Axis</span>
                        <canvas width="24" height="24" id="axisIndicator" style="border-radius:50%"></canvas>
                    </div>
                </div>
                <div class="status-box">
                    <span>Status: </span>
                    <span class="status-message">Test log message</span>
                </div>
            </div>
        </div>

        <script type="text/javascript">
            // jQuery replacements
            var $ = s=>document.querySelector(s);
            var $$ = s=>document.querySelectorAll(s);
            var isSocketConnected = false;
            var axis = [0, 0];
            var axisCtx;

            function status(message) {
                if ($(".status-message").textContent == message) return;
                else {
                    $(".status-message").textContent = message;
                    window.requestAnimationFrame(() => status(message)); // Wait a frame
                }
            }

            function updateAxis(socket) {
                var length = Math.sqrt(
                    Math.abs(axis[0]) ** 2 + 
                    Math.abs(axis[1]) ** 2);

                axisCtx.fillStyle = "#1e90ff";
                axisCtx.fillRect(0, 0, 24, 24);
                axisCtx.strokeStyle = "white";
                axisCtx.lineWidth = 2;
                axisCtx.beginPath();
                axisCtx.moveTo(12, 12);
                axisCtx.lineTo(12 + (axis[0]*12) / length, 12 - (axis[1]*12) / length);
                axisCtx.stroke();

                if (isSocketConnected)
                    // A+1+1 for [1, 1]
                    // A-1+1 for [-1, 1]
                    // Etc
                    socket.send("A" + 
                        (axis[0] < 0 ? "-" : "+") +
                        Math.abs(axis[0]).toString() + 
                        (axis[1] < 0 ? "-" : "+") +
                        Math.abs(axis[1]).toString());
            }

            window.onload = () => {
                status("Loading canvas");
                let canvas = $("#cameraFeed");
                let ctx = canvas.getContext("2d");
                let image = new Image();
                image.src = "http://placekitten.com/640/480";
                image.onload = () => {
                    ctx.drawImage(image, 0, 0);
                    ctx.fillStyle = "white";
                    ctx.font = "48px -apple-system, BlinkMacSystemFont, 'Segoe UI', Roboto, Oxygen, Ubuntu, Cantarell, 'Open Sans', 'Helvetica Neue', sans-serif";
                    ctx.fillText("Camera feed", 0, canvas.height);
                };

                let axisCanvas = $("#axisIndicator");
                axisCtx = axisCanvas.getContext("2d");
                axisCtx.fillStyle = "#1e90ff";
                axisCtx.fillRect(0, 0, 24, 24);

                status("Connecting websocket...");
                let url = "ws://" + window.location.hostname + ":81";
                let socket = new WebSocket(url);
                socket.onopen = () => {
                    isSocketConnected = true;
                    status("Connected!");
                }
                socket.onclose = () => {
                    if (isSocketConnected) status("Socket connection closed.");
                    else status("Couldn't connect.");
                    isSocketConnected = false;
                }
                socket.onmessage = event => {
                    console.log("Received data from socket: ", event.data);
                };

                window.onkeydown = event => {
                    if (event.repeat) return;
                    switch (event.key) {
                        case "ArrowUp":
                            axis[1] += 1;
                            updateAxis(socket);
                            break;
                        case "ArrowLeft":
                            axis[0] -= 1;
                            updateAxis(socket);
                            break;
                        case "ArrowRight":
                            axis[0] += 1;
                            updateAxis(socket);
                            break;
                        case "ArrowDown":
                            axis[1] -= 1;
                            updateAxis(socket);
                            break;
                        default: break;
                    }
                };

                window.onkeyup = event => {
                    if (event.repeat) return;
                    switch (event.key) {
                        case "ArrowUp":
                            axis[1] -= 1;
                            updateAxis(socket);
                            break;
                        case "ArrowLeft":
                            axis[0] += 1;
                            updateAxis(socket);
                            break;
                        case "ArrowRight":
                            axis[0] -= 1;
                            updateAxis(socket);
                            break;
                        case "ArrowDown":
                            axis[1] += 1;
                            updateAxis(socket);
                            break;
                        default: break;
                    }
                };
            };
        </script>
    </body>
</html>
)===";
const String HEADERS = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";

WiFiServer server(80);
WebSocketsServer webSocket(81);

const char SSID[] = "ESP_SERV";
const char PASS[] = "pain";

void webSocketEvent(char num, WStype_t type, unsigned char *payload, size_t length) {
    if (type == WStype_TEXT) {
        if (payload[0] == 'A') { // Axis, format: "A[+/-]X[+/-]Y", e.g.: A-1+1 for X:-1 and Y:1
            int x = (int)((char)payload[2] - '0');
            int y = (int)((char)payload[4] - '0');
            if (payload[1] == '-') x *= -1;
            if (payload[3] == '-') y *= -1;
            Serial.printf("Recieved: [%d, %d]\n", x, y);
        }
    }
}

void setup() {
    Serial.begin(115200);
    Serial.print("Creating AP... ");
    if (WiFi.softAP(SSID, PASS)) {
        Serial.println("Done!");
    } else {
        Serial.println("Failed.");
        Serial.println("The Arduino will now start looping to prevent further code execution.");
        Serial.println("To retry, press the RESET button on the Arduino.");
        while(1);
    }

    Serial.print("Starting WebServer... ");
    server.begin();
    Serial.println("Done!");

    Serial.print("Starting WebSocketsServer... ");
    webSocket.begin();
    webSocket.onEvent(webSocketEvent);
    Serial.println("Done!");

    Serial.printf("You can now connect to the WiFi network %s with password %s.\n", SSID, PASS);
    Serial.print("Then open"); Serial.print(WiFi.localIP()); Serial.println("in a browser and try it out.");
}

void loop() {
    webSocket.loop();

    WiFiClient client = server.available();
    if (!client) return;

    client.flush();
    client.print(HEADERS);
    client.print(PAGE);
    Serial.println("Page was requested, and sent.");

    delay(5);
}
