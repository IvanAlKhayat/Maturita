#include <Ethernet.h>
#include <SPI.h>
#include <Servo.h>
//int led = 4;
Servo microservo; 
int pos = 0; 
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };   //physical mac address
byte ip[] = { 192, 168, 1, 178 };                      // ip in lan (that's what you need to use in your browser. ("192.168.1.178")
byte gateway[] = { 192, 168, 1, 1 };                   // internet access via router
byte subnet[] = { 255, 255, 255, 0 };                  //subnet mask
EthernetServer server(80);                             //server port     
String readString;

void setup() {
 // Open serial communications and wait for port to open:
  Serial.begin(9600);
  pinMode(5,OUTPUT);
   while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  pinMode(4, OUTPUT);
  pinMode(6,OUTPUT);
  //microservo.attach(7);
  // start the Ethernet connection and the server:
  Ethernet.begin(mac, ip, gateway, subnet);
  server.begin();
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());
}

void loop() {
  // put your main code here, to run repeatedly:

  EthernetClient client = server.available();
  if (client) {
    while (client.connected()) {   
      if (client.available()) {
        char c = client.read();
     
        //read char by char HTTP request
        if (readString.length() < 100) {
          //store characters to string
          readString += c;
          //Serial.print(c);
         }

         //if HTTP request has ended
         if (c == '\n') {          
           Serial.println(readString); //print to serial monitor for debuging
    /* client.println();
           client.println("HTTP/1.1 200 OK"); //send new page
           client.println("<HTML>");
           client.println("<HEAD> ciao </HEAD>");
           client.println("<BODY>");
           client.println("<p>BENVENUTI </p>");
           client.println("</BODY>");
           client.println("</HTML>");
          
          //192.168.1.41:7070/new_trafic_light.html*/

                     client.println();     
           client.println("<HTML>");
           client.println("<HEAD>");
       //    client.println("<meta name='apple-mobile-web-app-capable' content='yes' />");
         //  client.println("<meta name='apple-mobile-web-app-status-bar-style' content='black-translucent' />");
         //  client.println("<link rel='stylesheet' type='text/css' href='http://randomnerdtutorials.com/ethernetcss.css' />");
           client.println("<TITLE>SEMAFORO</TITLE>");
           client.println("</HEAD>");
           client.println("<BODY>");
           client.println("<H1>Lighting Ledlight</H1>");
          // client.println("<hr />");
          // client.println("<br />");  
          // client.println("<H2>Arduino with Ethernet Shield</H2>");
          // client.println("<br />");  
           client.println("<a href=\"http://192.168.1.41:7070/new_trafic_light.html\"\">Turn On LED green</a>");
          // client.println("<a href=\"/?button1off\"\">Turn Off LED green</a><br />");   
          // client.println("<br />");     
          // client.println("<br />"); 
          // client.println("<a href=\"/?button2on\"\">Rotate Left</a>");
          // client.println("<a href=\"/?button2off\"\">Rotate Right</a><br />");
           
           //client.println("<a href=\"/?buttonLEDorangeOn\"\">Turn on Led Oraange</a><br />");   

          //client.println("<a href=\"/?buttonLEDgreenOn\"\">Turn on Led green</a><br />");
 
           //client.println("<p>Created by Rui Santos and modified by Ivan Al Khayat. Visit http://randomnerdtutorials.com for more projects!</p>");  
           //client.println("<br />"); 
           client.println("</BODY>");
           client.println("</HTML>");
     
                     delay(1);
           //stopping client
       client.stop();    
readString="";
         }
if(readString.indexOf("funk") > 0){
  //orange case
  digitalWrite(5,HIGH);
  digitalWrite(4,LOW);
  digitalWrite(6,LOW);
  client.println("<HTML>");
  client.println( "<meta http-equiv=refresh content=\"0; url=http://192.168.1.41:7070/semaforoarancio.html\">");
    client.println("</HTML>");

}
if(readString.indexOf("fink") > 0){
  //green case
  digitalWrite(4,HIGH);
    digitalWrite(5,LOW);
  digitalWrite(6,LOW);
  client.println("<HTML>");
  client.println( "<meta http-equiv=refresh content=\"0; url=http://192.168.1.41:7070/semaforoverde.html\">");
    client.println("</HTML>");
}
        if(readString.indexOf("fonk") > 0){
          //red case
            digitalWrite(4,LOW);
    digitalWrite(5,LOW);
  digitalWrite(6,HIGH);
    client.println("<HTML>");
  client.println( "<meta http-equiv=refresh content=\"0; url=http://192.168.1.41:7070/semafororosso.html\">");
    client.println("</HTML>");
          }
  

  
}
    }
  }
}
