#include <Arduino.h>
#ifdef ESP32
  #include <WiFi.h>
  #include <AsyncTCP.h>
#else
  #include <ESP8266WiFi.h>
  #include <ESPAsyncTCP.h>:
#endif
#include <ESPAsyncWebServer.h>
#include"matfun.h"

AsyncWebServer server(80);

const char* ssid = "Mustafa";
const char* password = "password";

const char* input_parameter00 = "input00";
const char* input_parameter01 = "input01";
const char* input_parameter02 = "input02";
const char* input_parameter10 = "input10";
const char* input_parameter11 = "input11";
const char* input_parameter12 = "input12";
const char* input_parameter20 = "input20";
const char* input_parameter21 = "input21";
const char* input_parameter22 = "input22";
const char* input_parameter30 = "input30";
const char* input_parameter31 = "input31";
const char* input_parameter32 = "input32";
const char* matrix1[3]={input_parameter00,input_parameter01,input_parameter02};     // matrix for vertex A
const char* matrix2[3]={input_parameter10,input_parameter11,input_parameter12};     // matrix for vertex B
const char* matrix3[3]={input_parameter20,input_parameter21,input_parameter22};    // mattix for vertex D
const char* matrix4[3]={input_parameter30,input_parameter31,input_parameter32};    // mattix for vertex e1

const char index_html[] PROGMEM = R"rawliteral(
 <!DOCTYPE HTML><html><head>
    <title>TRIANGLE PROPERTIES</title>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <style>
      html {font-family: Times New Roman; display: inline-block; text-align: center;}
      h2 {font-size: 2.0rem; color: blue;}
    </style> 
    </head><body>
    <h2>VECTOR PROPERTIES</h2> 
    <p>Enter the values of points A, B ,C and e1
    <form action="/get">
      Enter the values of Point A: <input type="number" name="input00"> <input type="number" name="input01"> <input type="number" name="input02"><br><br>
      Enter the values of Point B: <input type="number" name="input10"> <input type="number" name="input11"> <input type="number" name="input12"><br><br>
      Enter the values of Point C: <input type="number" name="input20"> <input type="number" name="input21"> <input type="number" name="input22"><br><br>
      Enter the values of Point e1: <input type="number" name="input30"> <input type="number" name="input31"> <input type="number" name="input32"><br><br>
      <input type="submit" value="Submit">
    </form><br>
  </body></html>)rawliteral";

void notFound(AsyncWebServerRequest *request) {
  request->send(404, "text/plain", "Not found");
}

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  if (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("Connecting...");
    return;
  }
  Serial.println();
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html);
  });

server.on("/get", HTTP_GET, [] (AsyncWebServerRequest *request) {




double **A,**B,**D,**e1;//declaring matrices names
double **n1,**n2,**n3,**n4,**d1,**d2,**d3,**num,**den;
int m = 3, n = 4;

A = load_ser(request,matrix1,3);
B = load_ser(request,matrix2,3);
D = load_ser(request,matrix3,3);
e1 = load_ser(request,matrix4,3);

n1 = Matmul(transposeMat(B,m,1),B,1,m,1);
n2 = Matmul(transposeMat(B,m,1),D,1,m,1);
n3 = Matmul(transposeMat(D,m,1),D,1,m,1);
n4 = Matmul(transposeMat(A,m,1),Matadd(B,D,3,1),1,m,1);
d1 = Matmul(transposeMat(A,m,1),e1,1,m,1);
d2 = Matmul(transposeMat(B,m,1),e1,1,m,1);
d3 = Matmul(transposeMat(e1,m,1),D,1,m,1);
num = Matadd(Matsub(Matadd(n1,n3,1,1),Matmul(n4,n4,1,1,1),1,1),Matscale(n2,1,1,2),1,1);
den = Matscale(Matsub(Matsub(Matmul(d1,n4,1,1,1),d2,1,1),d3,1,1),1,1,2);
double lambda = Matdiv(num,den);
//printf("lambda = %lf \n",lambda);
 String lambdaString = String(lambda, 6); // Adjust the precision as needed

  // Concatenate lambdaString with HTML content
  String response = "<br><p> Lambda = " + lambdaString + "</p>";
//	response += "<br><p> Lamda = +String(lamda)+</p>"
	response += "<br><a href=\"/\">Return to Home Page</a>";
    // Send the HTML response with dynamic content
    request->send(200, "text/html", response);
});
  server.onNotFound(notFound);
  server.begin();
}
void loop() { 
}
